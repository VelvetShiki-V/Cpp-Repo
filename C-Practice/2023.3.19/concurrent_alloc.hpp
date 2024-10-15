#ifndef __CONCURRENT_ALLOC_HPP
#define __CONCURRENT_ALLOC_HPP
#pragma once
#include "thread_cache.hpp"

// ��������thread_cache�ڴ��
static void* concurrent_alloc(const size_t& size) {
	// 1. ����̶߳����״�����thread_cache���������������ϣͰ
	if (nullptr == pTLSThreadCache) {
		pTLSThreadCache = new ThreadCache();
		logMessage(NORMAL, "tid: %d--��ȡthread_cache�ɹ���thread_cache�����ַ: %p", std::this_thread::get_id(), pTLSThreadCache);
	}
	// 2. ���ܸ��߳��Ƿ��״�������Ͱ����������Ӧ�ڴ��������
	logMessage(NORMAL, "tid: %d--�Ѵ���thread_cache����ַΪ: %p, ����Ҫ%d�ֽ�", std::this_thread::get_id(), pTLSThreadCache, size);
	return pTLSThreadCache->allocate(size);
}

// �����ͷ�thread_cache�ڴ�飬�����뵽���ڴ�黹�ظ���Ӧ���������Ϲҽ�����
static void concurrent_dealloc(void* ptr, const size_t& size) {
	assert(ptr);
	// ����ȡ�����ڴ��黹��Ͱ�϶�Ӧ�ڴ���������������ϣ�ͷ��黹
	pTLSThreadCache->deallocate(ptr, size);
}

#endif