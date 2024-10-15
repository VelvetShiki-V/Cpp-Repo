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
#define MAX_BYTES 256 * 1024		// ���������256kb�ڴ棬ֱ���������
#define MAX_PAGES 129				// ����������128 * 8kb����1024kb�ڴ�
#define PAGE_SHIFT 13

#ifdef _WIN32
	#include <windows.h>
#elif
	// linux
#endif


// PAGE_ID����
#ifdef _WIN64
typedef unsigned long long PAGE_ID;
#elif _WIN32
typedef size_t PAGE_ID;
#endif	// _WIN64

// malloc�ײ�ռ����
#ifdef _WIN32
#include<windows.h>
#endif
inline static void* system_alloc(size_t pageNums)
{
#ifdef _WIN32
	// ���������kpage��8kb�ֽڿռ�
	void* ptr = VirtualAlloc(0, pageNums << 13, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
#else
	// linux��brk mmap��
#endif

	if (ptr == nullptr)
		throw std::bad_alloc();

	return ptr;
}

// free�ײ����
inline static void SystemFree(void* ptr) {
#ifdef _WIN32
	VirtualFree(ptr, 0, MEM_RELEASE);
#else
	// sbrk unmmp
#endif
}

// �ڴ��ǰ4/8�ֽ�ָ���һ�ڴ�ռ�
static void*& next_node(void* node) {
	return *(void**)node;
}

// ���������࣬����ÿ����ϣͰ�ڵ��ڴ����
class FreeList {
public:
	// �ڴ澭ʹ����Ϻ󻹸�thread_cache��ͷ�����ӵ���ӦͰ�ڵ���������ͷ��
	void push(void* obj){
		assert(obj);
		next_node(obj) = m_freelist;
		m_freelist = obj;
		size++;
	}

	// Ͱ���ж�Ӧ���������ڴ���飬�����ڴ���鵯�����û�
	void* pop() {
		assert(m_freelist);
		void* pGet = m_freelist;
		m_freelist = next_node(m_freelist);
		size--;
		return pGet;
	}

	// �ж�ĳ��Ͱ�ڵĽ���ڴ���Ƿ�Ϊ�գ������޷����룬��Ҫ����central_cache����
	bool empty() {
		return m_freelist == nullptr;
	}

	// �������
	size_t& max_nodes() {
		return max_size;
	}

	// �������ҽ�
	void push_batch(void*& begin, void*& end, const size_t& sz) {
		assert(begin && end);
		next_node(end) = m_freelist;
		m_freelist = begin;
		size += sz;
	}

	// �����黹���
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
	void* m_freelist = nullptr;			// ��ʼ���б�ÿ��Ͱ���Ϊ��ָ��
	size_t max_size = 1;				// ��ʼ������������ڴ��������Ϊ1������ʼ��
	size_t size = 0;					// ��¼һ�����������ϵĽ�����
};

// �������
class Alignment {
public:
	// 1. ���ݴ�������뿪�ٿռ��ʵ�ʴ�С������������Ӧ����Ĵ�С
	static size_t round(const size_t& size, const size_t& alignNum) {
		if (size % alignNum == 0) return size;				// �������Ĵ�С����������÷����С�ڶ�Ӧ������
		else {
			return (size / alignNum + 1) * alignNum;		// ������Ҫ���룬�����������Ҫ������ڴ�δ�С����
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
			return round(size, 1 << PAGE_SHIFT);		// ���ڴ���봦��
		}
	}

	// 2. ��������������ڴ�鴦���ĸ��ڴ�Ͱ��
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

	// 3. ����cache�ڴ����������
	static size_t caches_limit(const size_t& size) {
		size_t limit = MAX_BYTES / size;
		if (limit < 2) limit = 2;
		else if (limit > 512) limit = 512;
		return limit;
	}

	// 4. ��������span����page cache�ж�Ӧ��ҳ��Ͱ�±�
	static size_t page_locate(const size_t& size) {
		size_t memory_batch = caches_limit(size);		// 1. ���������ڴ���Ҫ������ڴ����������
		size_t page_nums = memory_batch * size;			// 2. ͳ�������ڴ����ɵĴ��ڴ��span���ܴ�С
		page_nums >>= PAGE_SHIFT;		// 3. �ܴ�С/8kb�õ�ҳ������page cacheӳ���Ͱ�±�
		if (page_nums == 0) page_nums = 1;
		return page_nums;
	}
};

// span�ṹ�壨ҳʽ�洢��
struct Span {
	PAGE_ID page_id = 0;			// ҳ�ţ���ʶһ��span�������䵽�Ĵ���ڴ�ռ���ʼ��ַ
	size_t page_nums = 0;			// ҳ������ʶһ��span�������䵽�Ĵ���ڴ�ռ��ܴ�С
	size_t use_count = 0;			// span��thread cacheʹ�ü���������++���黹--��ȫ���黹����Ϊ0�����Ϲ黹page cache
	void* freelist = nullptr;		// �����Ŷ��Сcache�ĵ���������
	Span* next = nullptr;			// ˫������ָ��
	Span* prev = nullptr;
	size_t node_counts = 0;			// һ��span�йҽӵĽ�����
	bool isServing = false;			// ��span�Ƿ����ڱ���central cache��ʹ���У���δʹ�ã�page cache�У�
};

// span˫������
class SpanList {
public:
	std::mutex sl_mtx;				// Ͱ������ĳ��Ͱ�������ã�ÿ��Ͱ֮�以������
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
	// ��ָ��span�ڴ������м����
	void insert(Span* pos, Span* node) {
		assert(pos && node);
		node->prev = pos->prev;
		node->next = pos;
		pos->prev->next = node;
		pos->prev = node;
	}
	// ����ĳ��ָ��span����
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