#ifndef __THREAD_CACHE_HPP
#define __THREAD_CACHE_HPP
#pragma once
#include <iostream>
#include <string>
#include <thread>
#include "common.hpp"
#include "memoy_pool.hpp"
#include "central_cache.hpp"
#include "log.hpp"

class ThreadCache {
public:
	// 线程从各自的thread cache中获取内存
	void* allocate(const size_t& size){
		// 1. 计算实际申请的空间大小和内存所在哈希坐标
		size_t memory_get = Alignment::space_round_up(size);
		size_t memory_locate = Alignment::bucket_locate(size);
		logMessage(DEBUG, "tid: %d理论需要%d字节，实际分配%d字节，所需%d字节的cache共%d个，内存定位到%d号桶", std::this_thread::get_id(), size, memory_get, memory_get, 1, memory_locate);
		// 2. 如果thread_cache桶内无自由链表内存块，到central cache申请
		if (fl[memory_locate].empty()) {
			// 到central cache对应内存桶上获取对齐后的慢启动批次个cache结点
			logMessage(DEBUG, "tid: %d检查thread cache[%d]桶内结点为空，开始向central cache索要cache", std::this_thread::get_id(), memory_locate);
			void* newMemory = fetch_from_central_cache(memory_get, memory_locate);
			logMessage(NORMAL, "tid: %d所需%d字节内存块向central cache获取内存成功，返回结点首地址: %p", std::this_thread::get_id(), memory_get, std::this_thread::get_id(), memory_locate, newMemory);
			return newMemory;
		}
		else {
			// 3. 否则直接取得内存块
			void* pGet = fl[memory_locate].pop();
			logMessage(NORMAL, "tid: %d的[%d]桶thread cache剩余cache个数: %d个, 获取1个大小为[%d]字节cache成功", std::this_thread::get_id(), memory_locate, fl[memory_locate].freelist_size(), memory_get);
			return pGet;
		}
		// 4. 否则申请失败
		return nullptr;
	}

	// 申请内存不够，到中心缓存申请更多(调用接口为fetch_blocks)
	void* fetch_from_central_cache(const size_t& size, const size_t& location) {
		// 1. 计算cache内存块申请上限和对应桶
		size_t fetch_limit = Alignment::caches_limit(size);
		// 2. 实际申请——慢开始（一次批量获取的结点上限个数，从1开始，逐次递增，每个线程每个桶互不干扰）
		size_t fetch_num = min(fl[location].max_nodes(), fetch_limit);
		if (fl[location].max_nodes() == fetch_num) {
			++fl[location].max_nodes();					// 最少每次获取到的结点个数+1，最多不超过limit个
		}
		// 3. 申请成功，一个返回或多个挂接
		logMessage(DEBUG, "tid: %d向central cache慢启动申请开始，期望申请thread cache结点数: %d个，申请上限数: %d个", std::this_thread::get_id(), fetch_num, fetch_limit);
		CentralCache* p_central = CentralCache::get_cenctral_cache();		// 单例模式获得central cache对象地址
		void* start = nullptr, * end = nullptr;		// 定义范围指针，准备接收来自central cache的批量个结点范围
		size_t actual_fetch = p_central->fetch_blocks(start, end, fetch_num, size);		// 传入获取的结点范围，需要申请的结点个数和需申请内存大小（定位central桶）
		// 4. 若实际申请到的结点个数大于1，返回一个索求cache给线程，位于首结点上，其余挂接到thread cache对应内存单元自由链表上
		if (actual_fetch == 1) {
			assert(start == end);
		}
		else fl[location].push_batch(next_node(start), end, actual_fetch - 1);		// 无锁挂接剩余cache结点到对应内存大小的自由链表上
		return start;
	}

	// 线程还给thread cache内存
	void deallocate(void* ptr, const size_t& size) {
		assert(ptr);
		assert(size <= MAX_BYTES);
		size_t memory_pos = Alignment::bucket_locate(size);
		fl[memory_pos].push(ptr);		// 将使用完毕的该cache内存块头插挂接到对应内存大小的自由链表中
		logMessage(DEBUG, "tid: %d申请%d字节，实际申请%d字节cache已归还至%d号桶上，归还后该桶剩余cache个数: %d个", std::this_thread::get_id(), size, Alignment::space_round_up(size), memory_pos, fl[memory_pos].freelist_size());
		// 当链表结点挂接过长时，需要还给central cache（过长判断：结点挂接数量超过批量申请的数量）
		if (fl[memory_pos].freelist_size() >= fl[memory_pos].max_nodes()) {
			logMessage(DEBUG, "[%d]桶当前挂接结点数: %d个，已达到一次批量申请结点个数上限: %d个，tid: %d开始将批量数个结点归还至central cache", memory_pos, fl[memory_pos].freelist_size(),fl[memory_pos].max_nodes(), std::this_thread::get_id());
			freelist_payback(fl[memory_pos], fl[memory_pos].max_nodes(), memory_pos);		// 将一次批量申请的结点块从thread cache桶中取走
		}
	}

	// 自由链表挂接过长，将一次性申请的批量cache还给对应内存的central cache桶中的span上
	void freelist_payback(FreeList& fl, const size_t& nodeNums, const size_t& pos) {
		// 从长链表中截取批量个数的结点取出，还给span
		void* begin, * end;
		fl.pop_batch(begin, end, nodeNums);
		logMessage(DEBUG, "tid: %d地址从%p--%p的一次性批量申请内存块共: %d个cache从thread cache[%d]桶中取出，准备归还central cache的span中",
			std::this_thread::get_id(), begin, end, nodeNums, pos);
		CentralCache::get_cenctral_cache()->cache_to_span(begin, nodeNums, pos);		// 调用批量归还cache给central cache的span接口进行内存归还
	}
private:
	FreeList fl[MAX_BUCKETS];		// 每个线程都拥有独属自己的自由链表桶，每个桶共208个内存关系映射
};

// TLS指针多线程无锁获取临界资源
static _declspec(thread)ThreadCache* pTLSThreadCache = nullptr;

#endif