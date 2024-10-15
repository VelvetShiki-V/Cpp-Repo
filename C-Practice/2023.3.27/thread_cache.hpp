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
			logMessage(DEBUG, "thread cache[%d]Ͱ�ڽ��Ϊ�գ���ʼ��central cache��Ҫcache", fl[memory_locate], fl[memory_locate].freelist_size());
			void* newMemory = fetch_from_central_cache(memory_get, memory_locate); 
			logMessage(NORMAL, "����%d�ֽ��ڴ����central cache��ȡ�ڴ�ɹ������ؽ���׵�ַ: %p",memory_get, std::this_thread::get_id(), memory_locate, newMemory);
			logMessage(NORMAL, "----------------------------\n");
			return newMemory;
		}
		else {
			// 3. ����ֱ��ȡ���ڴ��
			void* pGet = fl[memory_locate].pop();
			logMessage(NORMAL, "[%d]Ͱthread cacheʣ��cache����: %d��, ��ȡ1����СΪ[%d]�ֽ�cache�ɹ�", memory_locate, fl[memory_locate].freelist_size(), memory_get);
			logMessage(NORMAL, "----------------------------\n");
			return pGet;
		}
		// 4. ��������ʧ��
		return nullptr;
	}

	// �����ڴ治���������Ļ����������(���ýӿ�Ϊfetch_blocks)
	void* fetch_from_central_cache(const size_t& size, const size_t& location) {
		// 1. ����cache�ڴ���������޺Ͷ�ӦͰ
		size_t fetch_limit = Alignment::caches_limit(size);
		// 2. ʵ�����롪������ʼ
		size_t fetch_num = min(fl[location].max_nodes(), fetch_limit);
		if (fl[location].max_nodes() == fetch_num) {
			++fl[location].max_nodes();					// ����ÿ�λ�ȡ���Ľ�����+1����಻����limit��
		}
		// 3. ����ɹ���һ�����ػ����ҽ�
		logMessage(DEBUG, "��central cache���������뿪ʼ����������thread cache�����: %d��������������: %d��", fetch_num, fetch_limit);
		CentralCache* p_central = CentralCache::get_cenctral_cache();
		void* start = nullptr, * end = nullptr;
		size_t actual_fetch = p_central->fetch_blocks(start, end, fetch_num, size);		// �����ȡ�Ľ�㷶Χ����Ҫ����Ľ��������������ڴ��С����λcentralͰ��
		// 4. ��ʵ�����뵽�Ľ���������1�������׽�㣬����ҽӵ�thread cache��Ӧ�ڴ浥Ԫ����������
		if(actual_fetch > 1) fl[location].push_batch(next_node(start), end, actual_fetch - 1);
		return start;
	}

	// �̻߳���thread cache�ڴ�
	void deallocate(void* ptr, const size_t& size) {
		assert(ptr);
		assert(size <= MAX_BYTES);
		size_t memory_pos = Alignment::bucket_locate(size);
		fl[memory_pos].push(ptr);
		logMessage(DEBUG, "%d�ֽ�cache�黹��%d��Ͱ�ϣ���Ͱʣ��cache����: %d��", size, memory_pos, fl[memory_pos].freelist_size());
		// ��������ҽӹ���ʱ����Ҫ����central cache�������жϣ����ҽ������������������������
		if (fl[memory_pos].freelist_size() >= fl[memory_pos].max_nodes()) {
			freelist_payback(fl[memory_pos], fl[memory_pos].max_nodes());		// ��һ����������Ľ����thread cacheͰ��ȡ��
		}
	}

	// ��������ҽӹ�������һ�������������cache������Ӧ�ڴ��central cacheͰ�е�span��
	void freelist_payback(FreeList& fl, const size_t& size) {
		// �ӳ������н�ȡ���������Ľ��ȡ��������span
		void* begin, * end;
		fl.pop_batch(begin, end, size);
		logMessage(DEBUG, "��ַ��%p--%p��һ�������������ڴ�鹲: %d��cache��thread cache[%d]Ͱ��ȡ����׼���黹central cache��span��",
			begin, end, size, Alignment::bucket_locate(size));
		CentralCache::get_cenctral_cache()->cache_to_span(fl.get_head(), size);
	}
private:
	FreeList fl[MAX_BUCKETS];		// ��������Ͱ����208�����ֶζ���
};

// TLSָ����߳�������ȡ�ٽ���Դ
static _declspec(thread)ThreadCache* pTLSThreadCache = nullptr;

#endif