#ifndef __CONCURRENT_ALLOC_HPP
#define __CONCURRENT_ALLOC_HPP
#pragma once
#include "thread_cache.hpp"
#include "central_cache.hpp"
#include "page_cache.hpp"
#include "common.hpp"
// 并发申请thread_cache内存块
static void* concurrent_alloc(const size_t& size) {
	// 如果申请的内存大小超过了MAX_BYTES，直接向page cache申请，无需找thread cache
	if (size > MAX_BYTES) {
		// 将所需申请空间对齐后向page cache直接获取span，并返回span中存储的内存块首地址
		size_t alignSize = Alignment::space_round_up(size);
		size_t pageNums = Alignment::page_locate(alignSize);
		logMessage(DEBUG, "期望申请大块内存: %d字节，实际分配对齐字节: %d字节，定位到page cache页桶[%d]", size, alignSize, pageNums);
		PageCache::get_page_cache()->page_mtx.lock();
		Span* span = PageCache::get_page_cache()->get_a_span(pageNums);
		PageCache::get_page_cache()->page_mtx.unlock();
		void* getBunch = (void*)(span->page_id << PAGE_SHIFT);
		logMessage(NORMAL, "申请的大块内存: %d字节已申请", alignSize);
		return getBunch;
	}
	// 非大对象空间申请，普通的内存池申请流程
	// 1. 如果线程对象首次申请thread_cache，分配自由链表哈希桶
	if (nullptr == pTLSThreadCache) {
		static FixedMemoryPool<ThreadCache> fmp;
		pTLSThreadCache = fmp.acquire();
		logMessage(NORMAL, "tid: %d--初次获取thread_cache成功，thread_cache对象地址: %p", std::this_thread::get_id(), pTLSThreadCache);
	}
	// 2. 不管该线程是否首次申请了桶，按需分配对应内存给它即可
	logMessage(NORMAL, "tid: %d--拥有现存thread_cache，地址为: %p, 现需要%d字节", std::this_thread::get_id(), pTLSThreadCache, size);
	return pTLSThreadCache->allocate(size);
}

// 并发释放thread_cache内存块，将申请到的内存块还回给对应自由链表上挂接起来
static void concurrent_dealloc(void* ptr, const size_t& size) {
	assert(ptr);
	// 大内存块释放
	if (size > MAX_BYTES) {
		// 哈希映射释放span，加锁执行
		PageCache* p = PageCache::get_page_cache();
		Span* span = p->span_belong_memory(ptr);
		p->page_mtx.lock();
		p->span_to_page_cache(span);
		p->page_mtx.unlock();
		logMessage(NORMAL, "申请的大块内存: %d字节已释放", Alignment::space_round_up(size));
	}
	// 将获取到的内存块归还给桶上对应内存区间的自由链表上，头插归还
	else pTLSThreadCache->deallocate(ptr, size);
}

#endif