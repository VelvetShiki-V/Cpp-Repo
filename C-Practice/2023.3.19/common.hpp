#ifndef __COMMON_HPP
#define __COMMON_HPP
#pragma once
#include <iostream>
#include <string>
#include <cassert>
#include "log.hpp"
#define MAX_BUCKETS 208
#define MAX_BYTES 128 * 1024

void*& next_node(void* node) {
	return *(void**)node;
}

// 自由链表类，管理每个哈希桶内的内存结点块
class FreeList {
public:
	// 1. 内存经使用完毕后还给thread_cache，头插链接到对应桶内的自由链表头部
	void push(void* obj){
		assert(obj);
		next_node(obj) = m_freelist;
		m_freelist = obj;
		logMessage(DEBUG, "当前自由链表头结点地址为: %p", m_freelist);
	}

	// 2. 桶内有对应申请所需内存结点块，将该内存结点块弹出给用户
	void* pop() {
		m_freelist = next_node(m_freelist);
		assert(m_freelist);
		logMessage(DEBUG, "当前自由链表头结点地址为: %p", m_freelist);
		return m_freelist;
	}

	// 3. 判断某个桶内的结点内存块是否为空，是则无法申请，需要移至central_cache申请
	bool empty() {
		return m_freelist == nullptr;
	}
private:
	void* m_freelist = nullptr;			// 初始化列表每个桶最初为空指针
};

class Alignment {
public:
	// 1. 根据传入的申请开辟空间的实际大小，计算出对齐后应分配的大小
	static size_t round(const size_t& size, const size_t& alignNum) {
		assert(size <= MAX_BYTES);
		if (size % alignNum == 0) return size;		// 如果传入的大小能整除，则该分配大小在对应区间上
		else {
			return (size / alignNum + 1) * alignNum;		// 否则需要对齐，并将对齐后需要分配的内存段大小返回
		}
	}
	static size_t space_round_up(const size_t& size) {
		if (size <= 128) {
			return round(size, 8);
		}
		else if (size <= 128 * 8) {
			return round(size, 16);
		}
		else if (size <= 1024) {
			return round(size, 128);
		}
		else if (size <= 1024 * 8) {
			return round(size, 1024);
		}
		else if (size <= 1024 * 64) {
			return round(size, 1024 * 8);
		}
		else assert(false);
		return -1;
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
};

#endif