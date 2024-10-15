#ifndef __THREAD_CACHE_HPP
#define __THREAD_CACHE_HPP
#pragma once
#include <iostream>
#include <string>
#include <thread>
#include "common.hpp"
#include "central_cache.hpp"
#include "log.hpp"

class ThreadCache {
public:
	// 线程从各自的thread cache中获取内存
	void* allocate(const size_t& size){
		// 1. 计算实际申请的空间大小和内存所在哈希坐标
		size_t memory_get = Alignment::space_round_up(size);
		size_t memory_locate = Alignment::bucket_locate(size);
		logMessage(DEBUG, "理论需要%d字节，实际分配%d字节，所需%d字节的cache共%d个，内存定位到%d号桶", size, memory_get, memory_get, 1, memory_locate);
		// 2. 如果thread_cache桶内无自由链表内存块，到central cache申请
		if (fl[memory_locate].empty()) { 
			// 到指定桶上获取所需内存
			logMessage(DEBUG, "%d号桶为空，开始向central cache索要cache", fl[memory_locate]);
			void* newMemory = fetch_from_central_cache(memory_get, memory_locate); 
			logMessage(NORMAL, "所需%d字节内存块向central cache获取内存成功，返回结点首地址: %p",memory_get, std::this_thread::get_id(), memory_locate, newMemory);
			logMessage(NORMAL, "----------------------------\n");
			return newMemory;
		}
		else {
			// 3. 否则直接取得内存块
			
			logMessage(NORMAL, "[%d]桶thread cache不为空, 获取1个cache成功，该桶内剩余cache: %d个", memory_locate, FreeList::nodes_count(fl[memory_locate].get_head()) - 1);
			logMessage(NORMAL, "----------------------------\n");
			return fl[memory_locate].pop();
		}
		// 4. 否则申请失败
		return nullptr;
	}

	// 线程还给thread cache内存
	void deallocate(void* ptr, const size_t& size){
		assert(ptr);
		assert(size <= MAX_BYTES);
		size_t memory_pos = Alignment::bucket_locate(size);
		logMessage(DEBUG, "%d字节归还至%d号桶上", size, memory_pos);
		fl[memory_pos].push(ptr);
	}

	// 申请内存不够，到中心缓存申请更多(调用接口为fetch_blocks)
	void* fetch_from_central_cache(const size_t& size, const size_t& location) {
		// 1. 计算cache内存块申请上限和对应桶
		size_t fetch_limit = Alignment::caches_limit(size);
		// 2. 实际申请——慢开始
		static size_t max = fl[location].max_nodes();
		size_t fetch_num = min(max, fetch_limit);
		if(max == fetch_num) ++max;		// 最少每次获取到的结点个数+1，最多不超过limit个
		// 3. 申请成功，一个返回或多个挂接
		CentralCache* p_central = CentralCache::get_cenctral_cache();
		void* start = nullptr, * end = nullptr;
		size_t actual_fetch = p_central->fetch_blocks(start, end, fetch_num, size);		// 传入获取的结点范围，需要申请的结点个数和需申请内存大小（定位central桶）
		logMessage(DEBUG, "实际获得cache: %d个，start: %p, end: %p", actual_fetch, start, end);
		// 4. 若实际申请到的结点个数大于1，返回首结点，其余挂接到对应内存单元自由链表上
		if(actual_fetch > 1) fl[location].push_batch(next_node(start), end);
		return start;
	}
private:
	FreeList fl[MAX_BUCKETS];		// 自由链表桶，共208个，分段对齐
};

// TLS指针多线程无锁获取临界资源
static _declspec(thread)ThreadCache* pTLSThreadCache = nullptr;

#endif