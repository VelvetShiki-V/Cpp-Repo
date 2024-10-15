#ifndef __CONCURRENT_ALLOC_HPP
#define __CONCURRENT_ALLOC_HPP
#pragma once
#include "thread_cache.hpp"
#include "central_cache.hpp"
#include "page_cache.hpp"
#include "common.hpp"
// ��������thread_cache�ڴ��
static void* concurrent_alloc(const size_t& size) {
	// ���������ڴ��С������MAX_BYTES��ֱ����page cache���룬������thread cache
	if (size > MAX_BYTES) {
		// ����������ռ�������page cacheֱ�ӻ�ȡspan��������span�д洢���ڴ���׵�ַ
		size_t alignSize = Alignment::space_round_up(size);
		size_t pageNums = Alignment::page_locate(alignSize);
		logMessage(DEBUG, "�����������ڴ�: %d�ֽڣ�ʵ�ʷ�������ֽ�: %d�ֽڣ���λ��page cacheҳͰ[%d]", size, alignSize, pageNums);
		PageCache::get_page_cache()->page_mtx.lock();		// ���ڴ����룬��page cache��ȡ�ռ���Ҫ����ִ��
		Span* span = PageCache::get_page_cache()->get_a_span(pageNums);
		span->cache_size = alignSize;		// ������cache size��������
		PageCache::get_page_cache()->page_mtx.unlock();
		void* getBunch = (void*)(span->page_id << PAGE_SHIFT);
		logMessage(NORMAL, "tid: %d����Ĵ���ڴ�: %d�ֽ�������\n", std::this_thread::get_id(), alignSize);
		return getBunch;
	}
	// �Ǵ����ռ����룬��ͨ���ڴ����������
	// 1. ����̶߳����״�����thread_cache�����������ÿ���̵߳��������������ϣͰ
	if (nullptr == pTLSThreadCache) {
		FixedMemoryPool<ThreadCache> fmp;		// ÿ���̻߳�ȡ�����Լ���128kb�����ڴ��
		pTLSThreadCache = fmp.acquire();		// �������л�ȡ��������ThreadCache
		logMessage(NORMAL, "tid: %d--���λ�ȡthread_cache�ɹ���thread_cache�����ַ: %p", std::this_thread::get_id(), pTLSThreadCache);
	}
	// 2. ���ܸ��߳��Ƿ��״�������Ͱ����������Ӧ�ڴ��������
	logMessage(NORMAL, "tid: %d--ӵ���ִ�thread_cache����ַΪ: %p, ����Ҫ%d�ֽ�", std::this_thread::get_id(), pTLSThreadCache, size);
	return pTLSThreadCache->allocate(size);
}

// �����ͷ�thread_cache�ڴ�飬�����뵽���ڴ�黹�ظ���Ӧ���������Ϲҽ�����
static void concurrent_dealloc(void* ptr) {
	assert(ptr);
	// 1. �����ڴ���Ӧcache��С�������ͷ�
	size_t size = PageCache::get_page_cache()->span_belong_memory(ptr)->cache_size;
	// 2. ���ڴ���ͷ�
	if (size > MAX_BYTES) {
		// ��ϣӳ���ͷ�span������ִ��
		PageCache* p = PageCache::get_page_cache();
		Span* span = p->span_belong_memory(ptr);
		p->page_mtx.lock();
		p->span_to_page_cache(span);
		p->page_mtx.unlock();
		logMessage(NORMAL, "tid: ����Ĵ���ڴ�: %d�ֽ����ͷ�", std::this_thread::get_id(), Alignment::space_round_up(size));
	}
	// ����ȡ�����ڴ��黹��Ͱ�϶�Ӧ�ڴ���������������ϣ�ͷ��黹
	else pTLSThreadCache->deallocate(ptr, size);
}

#endif