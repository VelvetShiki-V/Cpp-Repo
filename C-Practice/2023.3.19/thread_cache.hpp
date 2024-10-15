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
		// 1. ����ʵ������Ŀռ��С���ڴ����ڹ�ϣ����
		size_t memory_get = Alignment::space_round_up(size);
		size_t memory_locate = Alignment::bucket_locate(size);
		logMessage(DEBUG, "������Ҫ%d�ֽڣ�ʵ�ʷ���%d�ֽڣ��ڴ涨λ��%d��Ͱ", size, memory_get, memory_locate);
		// 2. ���thread_cacheͰ�������������ڴ�飬�������ڴ�����
		if (fl[memory_locate].empty()) fetch_from_centralCache(size);
		else {
			// 3. ����ֱ��ȡ���ڴ��
			return fl[memory_locate].pop();
		}
		// 4. δ���
		return nullptr;
	}
	void deallocate(void* ptr, const size_t& size){
		assert(ptr);
		assert(size <= MAX_BYTES);
		size_t memory_pos = Alignment::bucket_locate(size);
		logMessage(DEBUG, "%d�ֽڹ黹��%d��Ͱ��", size, memory_pos);
		fl[memory_pos].push(ptr);
	}
	void fetch_from_centralCache(const size_t& size) {}
private:
	FreeList fl[MAX_BUCKETS];		// ��������Ͱ����208�����ֶζ���
};

// TLSָ����߳�������ȡ�ٽ���Դ
static _declspec(thread)ThreadCache* pTLSThreadCache = nullptr;

#endif