#ifndef __THREAD_CACHE_HPP
#define __THREAD_CACHE_HPP
#pragma once
#include <iostream>
#include <string>
#include <thread>
#include "common.hpp"
#include "log.hpp"

class ThreadCache {
public:
	void* allocate(const size_t& size){
		// 1. 计算实际申请的空间大小和内存所在哈希坐标
		size_t memory_get = Alignment::space_round_up(size);
		size_t memory_locate = Alignment::bucket_locate(size);
		logMessage(DEBUG, "理论需要%d字节，实际分配%d字节，内存定位到%d号桶", size, memory_get, memory_locate);
		// 2. 如果thread_cache桶内无自由链表内存块，到中心内存申请
		if (fl[memory_locate].empty()) fetch_from_centralCache(size);
		else {
			// 3. 否则直接取得内存块
			return fl[memory_locate].pop();
		}
		// 4. 未解决
		return nullptr;
	}
	void deallocate(void* ptr, const size_t& size){
		assert(ptr);
		assert(size <= MAX_BYTES);
		size_t memory_pos = Alignment::bucket_locate(size);
		logMessage(DEBUG, "%d字节归还至%d号桶上", size, memory_pos);
		fl[memory_pos].push(ptr);
	}
	void fetch_from_centralCache(const size_t& size) {}
private:
	FreeList fl[MAX_BUCKETS];		// 自由链表桶，共208个，分段对齐
};

// TLS指针多线程无锁获取临界资源
static _declspec(thread)ThreadCache* pTLSThreadCache = nullptr;

#endif