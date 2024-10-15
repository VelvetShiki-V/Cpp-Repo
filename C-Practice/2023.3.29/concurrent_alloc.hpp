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
		PageCache::get_page_cache()->page_mtx.lock();
		Span* span = PageCache::get_page_cache()->get_a_span(pageNums);
		PageCache::get_page_cache()->page_mtx.unlock();
		void* getBunch = (void*)(span->page_id << PAGE_SHIFT);
		logMessage(NORMAL, "����Ĵ���ڴ�: %d�ֽ�������", alignSize);
		return getBunch;
	}
	// �Ǵ����ռ����룬��ͨ���ڴ����������
	// 1. ����̶߳����״�����thread_cache���������������ϣͰ
	if (nullptr == pTLSThreadCache) {
		static FixedMemoryPool<ThreadCache> fmp;
		pTLSThreadCache = fmp.acquire();
		logMessage(NORMAL, "tid: %d--���λ�ȡthread_cache�ɹ���thread_cache�����ַ: %p", std::this_thread::get_id(), pTLSThreadCache);
	}
	// 2. ���ܸ��߳��Ƿ��״�������Ͱ����������Ӧ�ڴ��������
	logMessage(NORMAL, "tid: %d--ӵ���ִ�thread_cache����ַΪ: %p, ����Ҫ%d�ֽ�", std::this_thread::get_id(), pTLSThreadCache, size);
	return pTLSThreadCache->allocate(size);
}

// �����ͷ�thread_cache�ڴ�飬�����뵽���ڴ�黹�ظ���Ӧ���������Ϲҽ�����
static void concurrent_dealloc(void* ptr, const size_t& size) {
	assert(ptr);
	// ���ڴ���ͷ�
	if (size > MAX_BYTES) {
		// ��ϣӳ���ͷ�span������ִ��
		PageCache* p = PageCache::get_page_cache();
		Span* span = p->span_belong_memory(ptr);
		p->page_mtx.lock();
		p->span_to_page_cache(span);
		p->page_mtx.unlock();
		logMessage(NORMAL, "����Ĵ���ڴ�: %d�ֽ����ͷ�", Alignment::space_round_up(size));
	}
	// ����ȡ�����ڴ��黹��Ͱ�϶�Ӧ�ڴ���������������ϣ�ͷ��黹
	else pTLSThreadCache->deallocate(ptr, size);
}

#endif