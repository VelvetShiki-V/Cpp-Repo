#ifndef __CONCURRENT_ALLOC_HPP
#define __CONCURRENT_ALLOC_HPP
#pragma once
#include "thread_cache.hpp"

// 并发申请thread_cache内存块
static void* concurrent_alloc(const size_t& size) {
	// 1. 如果线程对象首次申请thread_cache，分配自由链表哈希桶
	if (nullptr == pTLSThreadCache) {
		pTLSThreadCache = new ThreadCache();
		logMessage(NORMAL, "tid: %d--获取thread_cache成功，thread_cache对象地址: %p", std::this_thread::get_id(), pTLSThreadCache);
	}
	// 2. 不管该线程是否首次申请了桶，按需分配对应内存给它即可
	logMessage(NORMAL, "tid: %d--已存在thread_cache，地址为: %p, 现需要%d字节", std::this_thread::get_id(), pTLSThreadCache, size);
	return pTLSThreadCache->allocate(size);
}

// 并发释放thread_cache内存块，将申请到的内存块还回给对应自由链表上挂接起来
static void concurrent_dealloc(void* ptr, const size_t& size) {
	assert(ptr);
	// 将获取到的内存块归还给桶上对应内存区间的自由链表上，头插归还
	pTLSThreadCache->deallocate(ptr, size);
}

#endif