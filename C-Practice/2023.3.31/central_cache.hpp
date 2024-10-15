#ifndef __CENTRAL_CACHE_HPP
#define __CENTRAL_CACHE_HPP
#pragma once
#include"common.hpp"
#include "page_cache.hpp"

// ���Ļ�����
class CentralCache {
public:
	// central cache�޿���span����page cache�л�ȡһ��span
	Span* get_span(SpanList& sl, const size_t& size) {			// ������size���ڼ������������pageҳͰ
		// 1. ��λ��Ҫ�����ҳ��Ͱ����ҳ��Ϊ������ӳ�����
		size_t page_index = Alignment::page_locate(size);
		logMessage(DEBUG, "tid: %d׼����page cache����һ������span����λ��ҳ��Ϊ%dҳͰ", std::this_thread::get_id(), page_index);
		// 2. page cache������ȡ������ִ�У������Ӹ�page cache�����л�ȡһ��span�ٽ����������̲߳�����ʵ���span��
		PageCache* pCache = PageCache::get_page_cache();
		pCache->page_mtx.lock();
		Span* span = pCache->get_a_span(page_index);	// ��ӦͰ�±��ȡspan������¼��span��״̬��ʹ���У�С���ڴ��С��
		span->isServing = true;
		span->cache_size = size;
		pCache->page_mtx.unlock();
		// 3. ����ȡ����span��Ϣչ�������ڴ���ʼ��ַ���ܴ�С������charָ�������β��ϸ��
		char* start = (char*)(span->page_id << PAGE_SHIFT);		// ����ҳ�Ŷ�Ӧ���ٵ�span * 8kb�õ��Ĵ��ڴ���׵�ַ����size���ֽڻ�ȡ���и�
		size_t memory_size = span->page_nums << PAGE_SHIFT;		// ��ҳ��չ����ҳ�� * 8kb�õ��ÿ���ڴ���ܴ�С���ֽڣ�
		char* end = start + memory_size;			// ���ݴ��ڴ��׵�ַ���С���Եõ����ڴ����β��ַ
		logMessage(DEBUG, "tid: %d��ȡ��һ��span��ַΪ: %p, ҳ��: %d, ҳ��: %d, ��Ӧ�ڴ���׵�ַ: %p��β��ַ: %p�����ڴ��С: %d", std::this_thread::get_id(), span, span->page_id, span->page_nums, start, end, memory_size);
		// 4. ����ȡ����span�г�cacheС��ҽӵ���Ӧcentral cache�ڴ浥Ԫ��spanlist��
		span->freelist = start;
		void* tail = span->freelist;
		start += size;				// start��size���ֽ������������иtail���ڿ���ǰ��cache���������
		size_t node_count = 1;		// node_count���ڼ�¼�зֵ�cache�ܸ�������Ϊstart��ǰ�ƶ���Ĭ���Ѿ������һ��cache
		size_t memory_remain = (size_t)(end - start);
		size_t alloc = memory_remain / size;
		while (start < end && alloc) {				// β���㣬ÿ���ڴ�����СΪsize����Ҫ���ǲ������е�����������24�ֽڣ�48�ֽڵ�����Ƭ���⣩
			next_node(tail) = start;
			tail = start;
			start += size;
			++node_count;
			memory_remain = (size_t)(end - start);
			alloc = memory_remain / size;		// �þ����ڵ��Թ۲�ʣ���ڴ�Ӧ���зֵõ���cache����
		}
		span->node_counts += node_count;		// ͳ��span�ڽ�����
		if (start != end) {
			logMessage(WARNING, "span���ڴ治�������з֣����ۻ�ȡ�ڴ��ܴ�С: %d�ֽڣ�ʵ�ʻ��: %d�ֽڣ�����������Ƭ", memory_size, size * span->node_counts);
		}
		logMessage(DEBUG, "tid: %d�õ�spanҳ��Ϊ%d�����з���sizeΪ:%d�ֽڵ�%d��cacheС��", std::this_thread::get_id(), span->page_nums, size, span->node_counts);
		next_node(tail) = nullptr;
		// 5. ���к�С���spanͷ�嵽��Ӧsplist�У�������������ֹ�����߳̿�������Ͱ�ڻ�ȡspan�����ں����������
		//sl.sl_mtx.lock();			// ���Դ���[��1]����Ӧ������[87-88]��Ͱ����������Ҫ�����Խ��к�����cache�ҽӵ�central��span��
		sl.push_front(span);
		logMessage(DEBUG, "tid: %d������cache sizeΪ: %d�ֽڵ�%d��cache��spanͷ�嵽spanlist[%d]��Ͱ��", std::this_thread::get_id(), size, span->node_counts, Alignment::bucket_locate(size));
		return span;
	}

	// Ѱ��һ��Ͱ���Ƿ���ڷǿ�span���
	Span* span_check(SpanList& sp, const size_t& size) {
		// 1. ��splistΪ�գ���ʾͰ���޿���span����ڴ�飬���ؿ�
		if (sp.isEmpty()) {
			logMessage(DEBUG, "tid: %d���splist����span", std::this_thread::get_id());
		}
		else {
			// 2. ��Ͱ��Ϊ�գ�����Ͱ˫���������ܴ��ڻ򲻴��ڿ���span��㣬���ڷ���span��ַ�������ڷ��ؿ�
			Span* start = sp.begin();
			while (start != sp.end()) {
				if (start->freelist == nullptr) {
					start = start->next;
				}
				else {
					logMessage(NORMAL, "tid: %d, span check����Ͱ��ʣ�����span��㣬��sizeΪ:%d��span�ڴ���%d��ʣ��cache���׵�ַΪ: %p", std::this_thread::get_id(), size, start->node_counts, start);
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
		sp_list[list_locate].sl_mtx.lock();		// central�ڲ���Ͱ��������cache�Ļ�ȡ
		logMessage(DEBUG, "tid: %d���central-spanlist��λ��%d��Ͱ����ʼ����Ƿ���ʣ��span���", std::this_thread::get_id(), list_locate);
		Span* span = nullptr;
		// ��ָ��cache��СͰ���м��
		if (!(span = span_check(sp_list[list_locate], size))) {
			// 2. ��Ͱ���޿���span������page cache����һ��span
			logMessage(DEBUG, "tid: %d����Ͱ���޿���span��㣬��ʼ��page cache��ȡһ������span", std::this_thread::get_id());
			// ���Դ���[��1]����λ�ڴ˴���central cacheͰ���⿪�����߳̽���ͬ����page cacheͬʱ����span��������ɿռ���˷�
			//sp_list[list_locate].sl_mtx.unlock();			// �����ŵ�Ϊ�Ƚ�������ȥpage cache��ȡspan������������ֹ�����߳���central cache��Ͱ���ڴ汻��ס��
			span = get_span(sp_list[list_locate], size);	// �ڻ�ȡspan�����У���������splist��ʱ����Ҫ����
		}
		// 3. ��ʱspanӦ��ȡ����Ӧ�ڴ棬�������쳣
		assert(span);
		// start��endΪ����Ͳ���������ȡһ����һ��cache��ȡ��ַ��Χ����thread cache�йҽӵ���ӦͰ����������
		start = end = span->freelist;
		size_t actual_get = 1;		// ʵ��ȡ�õ�thread cache��������batch_numΪ������ȡ��������span���������㣬���м�����ȡ����cache
		size_t count = 0;
		// 4. ��span����ȡ����ַ��Χ��������ȡ�ߵĺ���ʣ����Ϊ�µ�span��freelist�׽��
		while (count < batch_num - 1  && next_node(end)) {
			end = next_node(end);
			actual_get++;
			count++;		// countѭ����batch_num - 1����㴦���ɽ��������յ�ͬʱ������һ��cache��Ϊ�׽��ӵ���ǰspan������������
		}
		// 5. �����׽�㣬����ȡ�ߵ����һ������������
		span->use_count += actual_get;			// ����һ����thread cache��use_count++
		span->node_counts -= actual_get;		// DEBUG������span��ʣ��������
		span->freelist = next_node(end);		// ��ȡ�߽��ĺ�һ�������Ϊ��ǰspan���׽�������ס
		next_node(end) = nullptr;
		logMessage(DEBUG, "tid: %d, thread cacheʵ�ʻ��: %d��", std::this_thread::get_id(), actual_get);
		sp_list[list_locate].sl_mtx.unlock();		// central cacheͰ������
		logMessage(DEBUG, "tid: %d���central cache[%d]Ͱ��span��ʣ��thread cache������: %d��", std::this_thread::get_id(), list_locate, span->node_counts);
		return actual_get;
	}

	// �ͷ��߼�
	// ��thread cache���յ����ص��ڴ��
	void cache_to_span(void* start, const size_t& nodeNums, const size_t& index) {
		// 1. �����������ˣ�����һ��span�黹��page cache����λͰ������ִ��
		sp_list[index].sl_mtx.lock();
		// 2. ��λspan��ַ
		// 3. ������cacheͷ�嵽��span��
		while (start) {
			void* next = next_node(start);			// ��ǰ���ݺ���黹�ڴ����һ������ַ
			Span* span = PageCache::get_page_cache()->span_belong_memory(start);		// ����ִ�У�ÿ���������span����һ�£���Ҫ��������
			next_node(start) = span->freelist;		// ͷ��黹
			span->freelist = start;
			span->use_count--;
			if (0 == span->use_count) {				// һ��span��use_count�������thread cacheȫ��ʹ����Ϲ黹����
				sp_list[index].erase(span);			// span����ҳ��ҳ�����������ݴ���page cache������ʹ�ã�
				span->freelist = nullptr;			
				span->next = span->prev = nullptr;
				span->node_counts = 0;
				sp_list[index].sl_mtx.unlock();		// ��central cache��spanд����ϣ���ʹ�������߳�����
				logMessage(DEBUG, "tid: %d��thread cache���ȫ���黹��central cache��[%d]Ͱ��ַΪ%p��span�ڣ���ȡ�߸�span�黹��page cache��" , std::this_thread::get_id(), index, span);
				PageCache::get_page_cache()->page_mtx.lock();
				PageCache::get_page_cache()->span_to_page_cache(span);		// ��span�黹��page cacheҳͰ�йҽ����������ȴ��ϲ����������ִ��
				PageCache::get_page_cache()->page_mtx.unlock();
				sp_list[index].sl_mtx.lock();		// �˴�Ӧ������ѭ������Ͱ����������ֹ��δ������Ͱ��������
			}
			start = next;		// ����������
		}
		// 4. ����span���з����ȥ��thread cache���黹���򽫸�span��һ�������黹��page cache���黹ǰ�Ƚ�central cacheͰ���⿪������page cache�����黹���ٽ�����
		sp_list[index].sl_mtx.unlock();
	}

	// ��ȡ����ӦͰ
	SpanList* get_bucket(const size_t& index) {
		return &sp_list[index];
	}

	// ����ģʽ��ȡ�ӿ�
	static CentralCache* get_cenctral_cache() {
		return &pCentral;
	}
private:
	CentralCache(){}
	CentralCache(const CentralCache& cache) = delete;		// ������ֹ�����͸�ֵ
	CentralCache& operator=(const CentralCache& cache) = delete;
private:
	SpanList sp_list[MAX_BUCKETS];
	static CentralCache pCentral;		// ��������
};

CentralCache CentralCache::pCentral;	// ��̬��ʼ������

#endif