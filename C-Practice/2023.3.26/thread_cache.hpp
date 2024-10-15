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
	// �̴߳Ӹ��Ե�thread cache�л�ȡ�ڴ�
	void* allocate(const size_t& size){
		// 1. ����ʵ������Ŀռ��С���ڴ����ڹ�ϣ����
		size_t memory_get = Alignment::space_round_up(size);
		size_t memory_locate = Alignment::bucket_locate(size);
		logMessage(DEBUG, "������Ҫ%d�ֽڣ�ʵ�ʷ���%d�ֽڣ�����%d�ֽڵ�cache��%d�����ڴ涨λ��%d��Ͱ", size, memory_get, memory_get, 1, memory_locate);
		// 2. ���thread_cacheͰ�������������ڴ�飬��central cache����
		if (fl[memory_locate].empty()) { 
			// ��ָ��Ͱ�ϻ�ȡ�����ڴ�
			logMessage(DEBUG, "%d��ͰΪ�գ���ʼ��central cache��Ҫcache", fl[memory_locate]);
			void* newMemory = fetch_from_central_cache(memory_get, memory_locate); 
			logMessage(NORMAL, "����%d�ֽ��ڴ����central cache��ȡ�ڴ�ɹ������ؽ���׵�ַ: %p",memory_get, std::this_thread::get_id(), memory_locate, newMemory);
			logMessage(NORMAL, "----------------------------\n");
			return newMemory;
		}
		else {
			// 3. ����ֱ��ȡ���ڴ��
			
			logMessage(NORMAL, "[%d]Ͱthread cache��Ϊ��, ��ȡ1��cache�ɹ�����Ͱ��ʣ��cache: %d��", memory_locate, FreeList::nodes_count(fl[memory_locate].get_head()) - 1);
			logMessage(NORMAL, "----------------------------\n");
			return fl[memory_locate].pop();
		}
		// 4. ��������ʧ��
		return nullptr;
	}

	// �̻߳���thread cache�ڴ�
	void deallocate(void* ptr, const size_t& size){
		assert(ptr);
		assert(size <= MAX_BYTES);
		size_t memory_pos = Alignment::bucket_locate(size);
		logMessage(DEBUG, "%d�ֽڹ黹��%d��Ͱ��", size, memory_pos);
		fl[memory_pos].push(ptr);
	}

	// �����ڴ治���������Ļ����������(���ýӿ�Ϊfetch_blocks)
	void* fetch_from_central_cache(const size_t& size, const size_t& location) {
		// 1. ����cache�ڴ���������޺Ͷ�ӦͰ
		size_t fetch_limit = Alignment::caches_limit(size);
		// 2. ʵ�����롪������ʼ
		static size_t max = fl[location].max_nodes();
		size_t fetch_num = min(max, fetch_limit);
		if(max == fetch_num) ++max;		// ����ÿ�λ�ȡ���Ľ�����+1����಻����limit��
		// 3. ����ɹ���һ�����ػ����ҽ�
		CentralCache* p_central = CentralCache::get_cenctral_cache();
		void* start = nullptr, * end = nullptr;
		size_t actual_fetch = p_central->fetch_blocks(start, end, fetch_num, size);		// �����ȡ�Ľ�㷶Χ����Ҫ����Ľ��������������ڴ��С����λcentralͰ��
		logMessage(DEBUG, "ʵ�ʻ��cache: %d����start: %p, end: %p", actual_fetch, start, end);
		// 4. ��ʵ�����뵽�Ľ���������1�������׽�㣬����ҽӵ���Ӧ�ڴ浥Ԫ����������
		if(actual_fetch > 1) fl[location].push_batch(next_node(start), end);
		return start;
	}
private:
	FreeList fl[MAX_BUCKETS];		// ��������Ͱ����208�����ֶζ���
};

// TLSָ����߳�������ȡ�ٽ���Դ
static _declspec(thread)ThreadCache* pTLSThreadCache = nullptr;

#endif