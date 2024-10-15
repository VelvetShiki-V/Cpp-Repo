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
	// �̴߳Ӹ��Ե�thread cache�л�ȡ�ڴ�
	void* allocate(const size_t& size){
		// 1. ����ʵ������Ŀռ��С���ڴ����ڹ�ϣ����
		size_t memory_get = Alignment::space_round_up(size);
		size_t memory_locate = Alignment::bucket_locate(size);
		logMessage(DEBUG, "tid: %d������Ҫ%d�ֽڣ�ʵ�ʷ���%d�ֽڣ�����%d�ֽڵ�cache��%d�����ڴ涨λ��%d��Ͱ", std::this_thread::get_id(), size, memory_get, memory_get, 1, memory_locate);
		// 2. ���thread_cacheͰ�������������ڴ�飬��central cache����
		if (fl[memory_locate].empty()) {
			// ��central cache��Ӧ�ڴ�Ͱ�ϻ�ȡ���������������θ�cache���
			logMessage(DEBUG, "tid: %d���thread cache[%d]Ͱ�ڽ��Ϊ�գ���ʼ��central cache��Ҫcache", std::this_thread::get_id(), memory_locate);
			void* newMemory = fetch_from_central_cache(memory_get, memory_locate);
			logMessage(NORMAL, "tid: %d����%d�ֽ��ڴ����central cache��ȡ�ڴ�ɹ������ؽ���׵�ַ: %p", std::this_thread::get_id(), memory_get, std::this_thread::get_id(), memory_locate, newMemory);
			return newMemory;
		}
		else {
			// 3. ����ֱ��ȡ���ڴ��
			void* pGet = fl[memory_locate].pop();
			logMessage(NORMAL, "tid: %d��[%d]Ͱthread cacheʣ��cache����: %d��, ��ȡ1����СΪ[%d]�ֽ�cache�ɹ�", std::this_thread::get_id(), memory_locate, fl[memory_locate].freelist_size(), memory_get);
			return pGet;
		}
		// 4. ��������ʧ��
		return nullptr;
	}

	// �����ڴ治���������Ļ����������(���ýӿ�Ϊfetch_blocks)
	void* fetch_from_central_cache(const size_t& size, const size_t& location) {
		// 1. ����cache�ڴ���������޺Ͷ�ӦͰ
		size_t fetch_limit = Alignment::caches_limit(size);
		// 2. ʵ�����롪������ʼ��һ��������ȡ�Ľ�����޸�������1��ʼ����ε�����ÿ���߳�ÿ��Ͱ�������ţ�
		size_t fetch_num = min(fl[location].max_nodes(), fetch_limit);
		if (fl[location].max_nodes() == fetch_num) {
			++fl[location].max_nodes();					// ����ÿ�λ�ȡ���Ľ�����+1����಻����limit��
		}
		// 3. ����ɹ���һ�����ػ����ҽ�
		logMessage(DEBUG, "tid: %d��central cache���������뿪ʼ����������thread cache�����: %d��������������: %d��", std::this_thread::get_id(), fetch_num, fetch_limit);
		CentralCache* p_central = CentralCache::get_cenctral_cache();		// ����ģʽ���central cache�����ַ
		void* start = nullptr, * end = nullptr;		// ���巶Χָ�룬׼����������central cache����������㷶Χ
		size_t actual_fetch = p_central->fetch_blocks(start, end, fetch_num, size);		// �����ȡ�Ľ�㷶Χ����Ҫ����Ľ��������������ڴ��С����λcentralͰ��
		// 4. ��ʵ�����뵽�Ľ���������1������һ������cache���̣߳�λ���׽���ϣ�����ҽӵ�thread cache��Ӧ�ڴ浥Ԫ����������
		if (actual_fetch == 1) {
			assert(start == end);
		}
		else fl[location].push_batch(next_node(start), end, actual_fetch - 1);		// �����ҽ�ʣ��cache��㵽��Ӧ�ڴ��С������������
		return start;
	}

	// �̻߳���thread cache�ڴ�
	void deallocate(void* ptr, const size_t& size) {
		assert(ptr);
		assert(size <= MAX_BYTES);
		size_t memory_pos = Alignment::bucket_locate(size);
		fl[memory_pos].push(ptr);		// ��ʹ����ϵĸ�cache�ڴ��ͷ��ҽӵ���Ӧ�ڴ��С������������
		logMessage(DEBUG, "tid: %d����%d�ֽڣ�ʵ������%d�ֽ�cache�ѹ黹��%d��Ͱ�ϣ��黹���Ͱʣ��cache����: %d��", std::this_thread::get_id(), size, Alignment::space_round_up(size), memory_pos, fl[memory_pos].freelist_size());
		// ��������ҽӹ���ʱ����Ҫ����central cache�������жϣ����ҽ������������������������
		if (fl[memory_pos].freelist_size() >= fl[memory_pos].max_nodes()) {
			logMessage(DEBUG, "[%d]Ͱ��ǰ�ҽӽ����: %d�����Ѵﵽһ�������������������: %d����tid: %d��ʼ�������������黹��central cache", memory_pos, fl[memory_pos].freelist_size(),fl[memory_pos].max_nodes(), std::this_thread::get_id());
			freelist_payback(fl[memory_pos], fl[memory_pos].max_nodes(), memory_pos);		// ��һ����������Ľ����thread cacheͰ��ȡ��
		}
	}

	// ��������ҽӹ�������һ�������������cache������Ӧ�ڴ��central cacheͰ�е�span��
	void freelist_payback(FreeList& fl, const size_t& nodeNums, const size_t& pos) {
		// �ӳ������н�ȡ���������Ľ��ȡ��������span
		void* begin, * end;
		fl.pop_batch(begin, end, nodeNums);
		logMessage(DEBUG, "tid: %d��ַ��%p--%p��һ�������������ڴ�鹲: %d��cache��thread cache[%d]Ͱ��ȡ����׼���黹central cache��span��",
			std::this_thread::get_id(), begin, end, nodeNums, pos);
		CentralCache::get_cenctral_cache()->cache_to_span(begin, nodeNums, pos);		// ���������黹cache��central cache��span�ӿڽ����ڴ�黹
	}
private:
	FreeList fl[MAX_BUCKETS];		// ÿ���̶߳�ӵ�ж����Լ�����������Ͱ��ÿ��Ͱ��208���ڴ��ϵӳ��
};

// TLSָ����߳�������ȡ�ٽ���Դ
static _declspec(thread)ThreadCache* pTLSThreadCache = nullptr;

#endif