#ifndef __COMMON_HPP
#define __COMMON_HPP
#pragma once
#include <iostream>
#include <string>
#include <cassert>
#include <mutex>
#include <algorithm>
#include <unordered_map>
#include "lockGuard.hpp"
#include "log.hpp"
#define MAX_BUCKETS 208
#define MAX_BYTES 256 * 1024		// 若申请大于256kb内存，直接向堆申请
#define MAX_PAGES 129				// 最多可以申请128 * 8kb，即1024kb内存
#define PAGE_SHIFT 13

#ifdef _WIN32
	#include <windows.h>
#elif
	// linux
#endif


// PAGE_ID定义
#ifdef _WIN64
typedef unsigned long long PAGE_ID;
#elif _WIN32
typedef size_t PAGE_ID;
#endif	// _WIN64

// malloc底层空间调用
#ifdef _WIN32
#include<windows.h>
#endif
inline static void* system_alloc(size_t pageNums)
{
#ifdef _WIN32
	// 向堆上申请kpage块8kb字节空间
	void* ptr = VirtualAlloc(0, pageNums << 13, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
#else
	// linux下brk mmap等
#endif

	if (ptr == nullptr)
		throw std::bad_alloc();

	return ptr;
}

// free底层调用
inline static void SystemFree(void* ptr) {
#ifdef _WIN32
	VirtualFree(ptr, 0, MEM_RELEASE);
#else
	// sbrk unmmp
#endif
}

// 内存的前4/8字节指向后一内存空间
static void*& next_node(void* node) {
	return *(void**)node;
}

// 自由链表类，管理每个哈希桶内的内存结点块
class FreeList {
public:
	// 内存经使用完毕后还给thread_cache，头插链接到对应桶内的自由链表头部
	void push(void* obj){
		assert(obj);
		next_node(obj) = m_freelist;
		m_freelist = obj;
		size++;
	}

	// 桶内有对应申请所需内存结点块，将该内存结点块弹出给用户
	void* pop() {
		assert(m_freelist);
		void* pGet = m_freelist;
		m_freelist = next_node(m_freelist);
		size--;
		return pGet;
	}

	// 判断某个桶内的结点内存块是否为空，是则无法申请，需要移至central_cache申请
	bool empty() {
		return m_freelist == nullptr;
	}

	// 最大结点数
	size_t& max_nodes() {
		return max_size;
	}

	// 批量结点挂接
	void push_batch(void*& begin, void*& end, const size_t& sz) {
		assert(begin && end);
		next_node(end) = m_freelist;
		m_freelist = begin;
		size += sz;
	}

	// 批量归还结点
	void pop_batch(void*& begin, void*& end, const size_t& sz) {
		assert(sz >= size);
		begin = end = m_freelist;
		for (size_t i = 0; i < sz - 1; ++i) {
			end = next_node(end);
		}
		m_freelist = next_node(end);
		next_node(end) = nullptr;
		size -= sz;
	}

	void* get_head() {
		return m_freelist;
	}

	size_t freelist_size() {
		return size;
	}

private:
	void* m_freelist = nullptr;			// 初始化列表每个桶最初为空指针
	size_t max_size = 1;				// 初始自由链表最大内存块结点数量为1（慢开始）
	size_t size = 0;					// 记录一段自由链表上的结点个数
};

// 对齐规则
class Alignment {
public:
	// 1. 根据传入的申请开辟空间的实际大小，计算出对齐后应分配的大小
	static size_t round(const size_t& size, const size_t& alignNum) {
		if (size % alignNum == 0) return size;				// 如果传入的大小能整除，则该分配大小在对应区间上
		else {
			return (size / alignNum + 1) * alignNum;		// 否则需要对齐，并将对齐后需要分配的内存段大小返回
		}
	}
	static size_t space_round_up(const size_t& size) {
		if (size <= 128) {
			return round(size, 8);
		}
		else if (size <= 1024) {
			return round(size, 16);
		}
		else if (size <= 1024 * 8) {
			return round(size, 128);
		}
		else if (size <= 1024 * 64) {
			return round(size, 1024);
		}
		else if (size <= 1024 * 256) {
			return round(size, 1024 * 8);
		}
		else {
			return round(size, 1 << PAGE_SHIFT);		// 大内存对齐处理
		}
	}

	// 2. 计算所需申请的内存块处于哪个内存桶中
	static size_t locate(const size_t& size, const size_t& assignNum) {
		if (size % assignNum == 0) return size / assignNum - 1;
		else {
			return size / assignNum;
		}
	}
	static size_t bucket_locate(const size_t& size) {
		assert(size <= MAX_BYTES);
		// static int buckets[] = { 16, 56, 56, 56 };
		if (size <= 128) {
			return locate(size, 8);
		}
		else if (size <= 128 * 8) {
			return locate(size, 16);
		}
		else if (size <= 1024) {
			return locate(size, 128);
		}
		else if (size <= 1024 * 8) {
			return locate(size, 1024);
		}
		else if (size <= 1024 * 64) {
			return locate(size, 1024 * 8);
		}
		else assert(false);
		return -1;
	}

	// 3. 计算cache内存块申请上限
	static size_t caches_limit(const size_t& size) {
		size_t limit = MAX_BYTES / size;
		if (limit < 2) limit = 2;
		else if (limit > 512) limit = 512;
		return limit;
	}

	// 4. 计算申请span所在page cache中对应的页号桶下标
	static size_t page_locate(const size_t& size) {
		size_t memory_batch = caches_limit(size);		// 1. 计算所需内存需要分配的内存块数量上限
		size_t page_nums = memory_batch * size;			// 2. 统计所有内存块组成的大内存块span的总大小
		page_nums >>= PAGE_SHIFT;		// 3. 总大小/8kb得到页数，即page cache映射的桶下标
		if (page_nums == 0) page_nums = 1;
		return page_nums;
	}
};

// span结构体（页式存储）
struct Span {
	PAGE_ID page_id = 0;			// 页号，标识一个span中所分配到的大块内存空间起始地址
	size_t page_nums = 0;			// 页数，标识一个span中所分配到的大块内存空间总大小
	size_t use_count = 0;			// span中thread cache使用计数：借走++，归还--，全部归还计数为0，向上归还page cache
	void* freelist = nullptr;		// 连接着多个小cache的单自由链表
	Span* next = nullptr;			// 双向链表指针
	Span* prev = nullptr;
	size_t node_counts = 0;			// 一个span中挂接的结点个数
	bool isServing = false;			// 该span是否正在被（central cache）使用中，或未使用（page cache中）
};

// span双向链表
class SpanList {
public:
	std::mutex sl_mtx;				// 桶锁，由某个桶单独调用，每个桶之间互不干扰
public:
	SpanList() {
		sl_head = new Span;
		sl_head->next = sl_head;
		sl_head->prev = sl_head;
	}
	Span* begin() {
		return sl_head->next;
	}
	Span* end() {
		return sl_head;
	}
	bool isEmpty() {
		return sl_head->next == sl_head;
	}
	// 对指定span内存块进行中间插入
	void insert(Span* pos, Span* node) {
		assert(pos && node);
		node->prev = pos->prev;
		node->next = pos;
		pos->prev->next = node;
		pos->prev = node;
	}
	// 擦除某块指定span结点块
	void erase(Span* pos) {
		assert(pos && (pos != sl_head));
		if (isEmpty()) assert(false);
		pos->prev->next = pos->next;
		pos->next->prev = pos->prev;
	}
	void push_front(Span* span) {
		assert(span);
		insert(begin(), span);
	}
	Span* pop_front() {
		Span* front = begin();
		erase(front);
		return front;
	}
private:
	Span* sl_head;
};

#endif