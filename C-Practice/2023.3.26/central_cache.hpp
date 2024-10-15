#ifndef __CENTRAL_CACHE_HPP
#define __CENTRAL_CACHE_HPP
#pragma once
#include"common.hpp"
#include "page_cache.hpp"

// ���Ļ�����
class CentralCache {
public:
	// central cache�޿���span����page cache�л�ȡһ��span
	Span* get_span(SpanList& sl, const size_t& size) {			// size���ڼ������������pageҳͰ
		// 1. ��λ��Ҫ�����ҳ��Ͱ����ҳ��Ϊ������ӳ�����
		size_t page_index = Alignment::page_locate(size);
		logMessage(DEBUG, "��λ��ҳ��Ϊ%dҳͰ", page_index);
		// 2. page cache������ȡ������ִ�У������Ӹ�page cache�����л�ȡһ��span�ٽ����������̲߳�����ʵ���span��
		PageCache* pCache = PageCache::get_page_cache();
		pCache->page_mtx.lock();
		Span* span = pCache->get_a_span(page_index);			// ��ӦͰ�±��ȡspan
		pCache->page_mtx.unlock();
		// 3. ����ȡ����span��Ϣչ�������ڴ���ʼ��ַ���ܴ�С������charָ�������β��ϸ��
		char* start = (char*)(span->page_id << PAGE_SHIFT);		// ����ҳ�Ŷ�Ӧ���ٵ�span * 8kb�õ��Ĵ��ڴ���׵�ַ�����ֽڻ�ȡ���и�
		size_t span_size = span->page_nums << PAGE_SHIFT;		// ��ҳ��չ����ҳ�� * 8kb�õ��ÿ���ڴ���ܴ�С���ֽڣ�
		char* end = start + span_size;			// ���ݴ��ڴ��׵�ַ���С���Եõ����ڴ����β��ַ
		logMessage(DEBUG, "��ȡ��һ�����ڴ�span��ַΪ: %p, ҳ��: %d, ҳ��: %d, ��Ӧ�ڴ���׵�ַ: %p��β��ַ: %p", span, span->page_id, span->page_nums, start, end);
		// 4. ����ȡ����span�г�cacheС��ҽӵ���Ӧcentral cache�ڴ浥Ԫ��spanlist��
		span->freelist = start;
		void* tail = span->freelist;
		start += size;
		size_t node_count = 0;
		while (start <= end) {			// β���㣬ÿ���ڴ�����СΪsize
			next_node(tail) = start;
			tail = start;
			start += size;
			++node_count;
		}
		span->use_count += node_count;		// ͳ��span�ڽ�����
		logMessage(DEBUG, "ҳ��Ϊ%d�����з���sizeΪ:%d��%d��cacheС��",span->page_nums, size, node_count);
		next_node(tail) = nullptr;
		// 5. ���к�С���spanͷ�嵽��Ӧsplist�У�������������ֹ�����߳̿�������Ͱ�ڻ�ȡspan�����ں����������
		// sl.sl_mtx.lock();
		sl.push_front(span);
		logMessage(DEBUG, "��С��ͷ�嵽central cache: sizeΪ%d��[%d]��Ͱ��", size, Alignment::bucket_locate(size));
		return span;
	}

	// Ѱ��һ��Ͱ���Ƿ���ڷǿ�span���
	Span* span_check(SpanList& sp, const size_t& size) {
		// 1. ��splistΪ�գ���ʾͰ���޿���span����ڴ�飬���ؿ�
		if (sp.isEmpty()) {
			logMessage(ERRO, "��splist����span");
		}
		else {
			// 2. ��Ͱ��Ϊ�գ�����Ͱ˫���������ܴ��ڻ򲻴��ڿ���span��㣬���ڷ���span��ַ�������ڷ��ؿ�
			Span* start = sp.begin();
			while (start != sp.end()) {
				if (start->freelist == nullptr) {
					start->next = start;
				}
				else {
					logMessage(NORMAL, "span check����Ͱ��ʣ�����span��㣬��sizeΪ:%d��span�ڴ���%d��ʣ��cache���׵�ַΪ: %p", size, FreeList::nodes_count(start->freelist), start);
					return start;
				}
			}
		}
		return nullptr;
	}

	// ��span�л�ȡthread cache�����ڴ��
	size_t fetch_blocks(void*& start, void*& end, const size_t& batch_num,const size_t& size) {
		// 1. ��Ͱ������central cache����λcacheͰ
		size_t list_locate = Alignment::bucket_locate(size);
		// sp_list[list_locate].sl_mtx.lock();		// ����
		logMessage(DEBUG, "spanlist��λ��%d��Ͱ����ʼ����Ƿ���ʣ��span���", list_locate);
		Span* span = nullptr;
		if (!(span = span_check(sp_list[list_locate], size))) {
			// 2. ��Ͱ���޿���span������page cache����һ��span
			logMessage(DEBUG, "Ͱ���޿���span��㣬��ʼ��page cache��ȡһ������span");
			// sp_list[list_locate].sl_mtx.unlock();			// �Ƚ�������ȥpage cache��ȡspan������������ֹ�����߳���central cache��Ͱ���ڴ汻��ס��
			span = get_span(sp_list[list_locate], size);	// �ڻ�ȡspan�����У���������splist��ʱ����Ҫ����
		}
		// 3. ��ʱspanӦ��ȡ����Ӧ�ڴ棬�������쳣
		assert(span);
		start = end = span->freelist;
		size_t actual_get = 0;		// ʵ��ȡ�õ�thread cache������
		size_t count = 0;
		// 4. ��span����ȡ����ַ��Χ��������ȡ�ߵĺ���ʣ����Ϊ�µ�span��freelist�׽��
		while (count <= batch_num - 1  && end != nullptr) {
			end = next_node(end);
			actual_get++;
			count++;
		}
		// 5. �����׽�㣬����ȡ�ߵ����һ������������
		span->freelist = static_cast<FreeList*>(next_node(end));
		next_node(end) = nullptr;
		//sp_list[list_locate].sl_mtx.unlock();		// ����
		return actual_get;
	}

	// ����ģʽ��ȡ�ӿ�
	static CentralCache* get_cenctral_cache() {
		return &pCentral;
	}
private:
	CentralCache(){}
	CentralCache(const CentralCache& cache) = delete;
	CentralCache& operator=(const CentralCache& cache) = delete;
private:
	SpanList sp_list[MAX_BUCKETS];
	static CentralCache pCentral;		// ��������
};

CentralCache CentralCache::pCentral;	// ��̬��ʼ������

#endif