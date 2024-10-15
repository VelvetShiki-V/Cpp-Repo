#ifndef __PAGE_CACHE_HPP
#define __PAGE_CACHE_HPP
#pragma once
#include "common.hpp"
#include "memoy_pool.hpp"
#include "radix_tree.hpp"

class PageCache {
public:
	// ��ȡ����page cache�����ַ
	static PageCache* get_page_cache() {
		return &pPage;
	}

	// ��ȡһ���ռ�ΪpageNumsҳ����С��span��ҳ����page cacheͰ�±꣩
	Span* get_a_span(const size_t& pageNums) {
		assert(pageNums > 0);
		// ��������ҳ�ڴ泬�����ҳ��ֱ�ӵ���ϵͳ���루���轨����ϣӳ�䣬ֱ�����뼴�ɣ�
		if (pageNums > MAX_PAGES - 1) {
			void* getMemory = system_alloc(pageNums);
			Span* span = pFmp.acquire();		// ��span�Ӷ����ڴ��������õ�������ռ��ƹ�mallocֱ����ϵͳ����system_alloc
			span->page_id = (PAGE_ID)getMemory >> PAGE_SHIFT;
			span->page_nums = pageNums;			// ����span���״̬
			span->isServing = true;
			logMessage(DEBUG, "tid: %d������ڴ泬�����ҳ: %d����Ҫ����ϵͳ�����룬ʵ�ʷ���õ�ҳ��: %d", std::this_thread::get_id(), MAX_PAGES, pageNums);
			logMessage(DEBUG, "����õ�span�׵�ַ: %p��span�ڴ洢����ڴ��׵�ַ: %p", span, (void*)(span->page_id << PAGE_SHIFT));
			return span;
		}
		// 1. �����ӦҳͰ�д��ڿ���span��ֱ�ӷ���
		if (!page_splist[pageNums].isEmpty()) {
			Span* span = page_splist[pageNums].pop_front();		// ��span�����״̬��central cache�н�������
			// ����span��ÿҳ�ڴ����span������ϣӳ���ϵ�������span�е�ÿһҳ�ڴ涼�����ڸ�span������central cache����thread cacheʱ�����Ӧspan��
			for (PAGE_ID i = 0; i < span->page_nums; ++i) {
				//idSpan[span->page_id + i] = span;
				idTree.set(span->page_id + i, span);		// �������Ż�ҳ����span*ӳ���ϵ����ʹ��map��unordered_map�Լ��ٻ���������ʱ�䣨�ռ任ʱ�䣩
			}
			logMessage(DEBUG, "tid: %d��page cache[%d]ҳͰ���ҵ�����span������span���ظ�central cache", std::this_thread::get_id(), pageNums);
			return span;
		}
		// 2. ��Ͱ���޿���span�������±�����ȡ����ҳͰ��Դ
		logMessage(DEBUG, "��Ӧҳ��Ϊ%dͰ��ʣ��span���������ҳ����", pageNums);
		for (size_t i = pageNums + 1; i < MAX_PAGES; ++i) {
			// logMessage(DEBUG, "������%d��Ͱ", i);
			if (!page_splist[i].isEmpty()) {
				// 3. �����±���ҳͰ��Ϊ�գ���ʱ�ɽ���ҳ���
				Span* src_span = page_splist[i].pop_front();
				//idSpan.erase(src_span->page_id);			// ԭͰspanȡ��ӳ�䣬�����ӳ��
				idTree.erase(src_span->page_id);
				Span* aim_span = pFmp.acquire();
				// 3.1 ҳ�ſ��������ڴ浥Ԫ��ҳ�������ڴ�����
				aim_span->page_id = src_span->page_id;		// Ŀ��span��ҳ���ɸ���ҳ���裨ͷ�У���ַ�����ҳ�ű�ʶ�ÿ��ڴ��Ψһ�ԣ�
				aim_span->page_nums = pageNums;				// Ŀ��span��ҳ�������������span�ܴ�С
				src_span->page_id += pageNums;				// ����ҳspan��Ϊͷ�зֶ�����˸�С��span��ҳ������ƶ�
				src_span->page_nums -= pageNums;			// �ᱻ���ൽ��С��ҳͰ�У�ҳ����Ӧ��С��
				// 3.2 ������Ϊ��С�Ļ���ʱδ��ʹ�õ�src_spanͷ�嵽��С��ҳͰ��
				logMessage(DEBUG, "%d��Ͱ��Ϊ�գ�����Ͱ�¿���span�ָ�Ϊ%d��%d����ҳ��Ͱ��span��Ŀ��Ͱ��span��ַΪ: %p"
					, i, aim_span->page_nums, src_span->page_nums, aim_span);
				logMessage(DEBUG, "��span���ҳ�����Դ���ڴ�ռ���ʼ��ַΪ: %p", (void*)(aim_span->page_id << PAGE_SHIFT));
				page_splist[src_span->page_nums].push_front(src_span);
				// 3.3 ��δʹ�õ��ķָ���span��βҳ�����span��ַ������ϣӳ�䣬�������page cache�ĺϲ�����
				//idSpan[src_span->page_id] = src_span;
				//idSpan[src_span->page_id + src_span->page_nums - 1] = src_span;
				idTree.set(src_span->page_id, src_span);
				idTree.set(src_span->page_id + src_span->page_nums - 1, src_span);
				// 3.4 ��Ŀ��span��ÿҳ�ڴ����span������ϣӳ���ϵ�������span�е�ÿһҳ�ڴ涼�����ڸ�span������central cache����thread cacheʱ�����Ӧspan��
				for (PAGE_ID i = 0; i < aim_span->page_nums; ++i) {
					//idSpan[aim_span->page_id + i] = aim_span;		// ����������span�Ĺ�ϵ����span�ڷ���õ��Ĵ��ռ�Ĺ�ϵ
					idTree.set(aim_span->page_id + i, aim_span);
				}
				logMessage(DEBUG, "aim_span��%dҳ��ҳ�ܴ�СΪ%d�ֽڵ�cache�ڴ��ɹ����span������ϣӳ�䣬span��ַΪ: %p", aim_span->page_nums, aim_span->page_nums << PAGE_SHIFT, aim_span);
				return aim_span;
			}
		}
		// 4. �������������ˣ�˵��ҳͰ������ȫ���޿���span��һ������ڳ���ճ�ʼ�����ڴ����ʱ��
		logMessage(DEBUG, "ҳͰȫ��Ϊ�գ�����ѷ�������");
		Span* bunchs_memory = pFmp.acquire();
		void* ptr = system_alloc(MAX_PAGES - 1);
		bunchs_memory->page_id = (PAGE_ID)ptr >> PAGE_SHIFT;	// ��ַҲ����ֵ��ţ�ǿתΪ��ֵ������8�ֽڣ��õ�ҳ��
		bunchs_memory->page_nums = MAX_PAGES - 1;				// ���뵽�����ҳͰ�궨��ҳ���ڴ�
		// 5. �Ѿ����뵽�����ҳ�Ĵ���ڴ棬ͷ�������ҳspanlist�У���������ϣӳ��
		page_splist[MAX_PAGES - 1].push_front(bunchs_memory);
		//idSpan[bunchs_memory->page_id] = bunchs_memory;
		idTree.set(bunchs_memory->page_id, bunchs_memory);
		logMessage(DEBUG, "system_alloc����ѿռ�ɹ�����%dҳͰ�д���ҳ��Ϊ%d, ҳ��Ϊ%d���ڴ�", MAX_PAGES - 1, bunchs_memory->page_id, bunchs_memory->page_nums);
		return get_a_span(pageNums);
	}

	// ����һ���ڴ�ĵ�ַ�ҵ����Ӧspan�׵�ַ
	Span* span_belong_memory(void* cache_addr) {
		assert(cache_addr);
		PAGE_ID id = (PAGE_ID)cache_addr >> PAGE_SHIFT;		// �����ڴ���׵�ַ����������洢�ռ�span��ҳ�ţ��ٸ���ҳ�Ų������Ӧspan��ַ
		//std::unique_lock<std::mutex> lock;				// RAII������
		//std::unordered_map<PAGE_ID, Span*>::iterator it = idSpan.find(id);
		//if (it != idSpan.end()) {
		//	logMessage(DEBUG, "tid: %d�黹�ڴ棬���ҵ���ַΪ: %p��cache�ڴ���Ӧspanӳ�䣬���׵�ַΪ: %p", std::this_thread::get_id(), cache_addr, it->second);
		//	return it->second;
		//}
		// �������Ż�ҳ����span*ӳ���ϵ����ʹ��map��unordered_map�Լ��ٻ���������ʱ�䣨�ռ任ʱ�䣩
		Span* span_obtain = (Span*)idTree.get(id);
		assert(span_obtain);
		return span_obtain;
	}

	// central cache��span�黹��page cache
	void span_to_page_cache(Span* span) {
		assert(span);
		// ������ڴ泬�����ҳ������ϵͳ�ӿ�ֱ���ͷţ�����ȡ����ϣӳ�䣬ֱ���ͷż��ɣ�
		if (span->page_nums > MAX_PAGES - 1) {
			void* ptr = (void*)(span->page_id << PAGE_SHIFT);
			system_free(ptr);
			logMessage(DEBUG, "tid: %d�������ҳ�Ĵ���ڴ����ϵͳ�ӿ��ͷţ���С��%d�ֽڣ�ҳ��: %d", std::this_thread::get_id(), span->page_nums << PAGE_SHIFT, span->page_nums);
			pFmp.restore(span);
			return;
		}
		// 1. ��ǰ�ϲ���3������޷��ϲ�������ǰҳ�޿���span������ʹ���У��ϲ���ҳ������MAX_PAGES��
		logMessage(DEBUG, "��ǰspan�ѹ黹��page cache�У�ҳ��: %d, ҳ��: %d�����ǰ��ҳ�Ƿ��пɺϲ�cache", span->page_id, span->page_nums);
		while (true) {
			//auto prevSpan = idSpan.find(span->page_id - 1);
			Span* prevSpan = (Span*)idTree.get(span->page_id - 1);
			if (nullptr == prevSpan) {
				logMessage(DEBUG, "��ǰspan��ǰ�޿��úϲ�page span");
				break;
			}
			if (prevSpan->isServing) {
				logMessage(DEBUG, "ǰһ��span����ռ���У��޷��ϲ�page");
				break;
			}
			if (span->page_nums + prevSpan->page_nums > MAX_PAGES - 1) {
				logMessage(DEBUG, "��ǰ�ϲ�ҳ���������ҳ���޷��ϲ�page");
				break;
			}
			// ���Ժϲ����ϲ���span������ϲ����ԭͰ
			//idSpan.erase(span->page_id);
			idTree.erase(span->page_id);				// �ϲ�ǰ��ԭspanȥҳ�����ַӳ��
			span->page_id = prevSpan->page_id;			// �ı䵱ǰspanҳ��Ϊ����ǰҳ��ҳ��
			span->page_nums += prevSpan->page_nums;		// ������ҳ����Ŀ��Ͱ
			page_splist[prevSpan->page_nums].erase(prevSpan);		// ����ԭͰ
			idTree.erase(prevSpan->page_id);
			pFmp.restore(prevSpan);
			logMessage(DEBUG, "��ǰ�ϲ��ɹ����ϲ���ҳ��: %d, ҳ��: %d", span->page_id, span->page_nums);
		}
		// 2. ���ϲ�
		while (true) {
			//auto nextSpan = idSpan.find(span->page_id + span->page_nums);
			Span* nextSpan = (Span*)idTree.get(span->page_id + span->page_nums);
			if (nullptr == nextSpan) {
				logMessage(DEBUG, "��ǰspan����޿��úϲ�page span");
				break;
			}
			if (nextSpan->isServing) {
				logMessage(DEBUG, "��һ��span����ռ���У��޷��ϲ�page");
				break;
			}
			if (span->page_nums + nextSpan->page_nums > MAX_PAGES - 1) {
				logMessage(DEBUG, "���ϲ�ҳ���������ҳ���޷��ϲ�page");
				break;
			}
			// ���Ժϲ����ϲ���span������ϲ����ԭͰ
			//idSpan.erase(span->page_id);
			idTree.erase(span->page_id);
			span->page_nums += nextSpan->page_nums;
			page_splist[nextSpan->page_nums].erase(nextSpan);
			idTree.erase(nextSpan->page_id);
			pFmp.restore(nextSpan);
			logMessage(DEBUG, "���ϲ��ɹ����ϲ���ҳ��: %d, ҳ��: %d", span->page_id, span->page_nums);
		}
		// 3. �ϲ������ϲ�span���룬״̬�ı䣩
		page_splist[span->page_nums].push_front(span);
		span->isServing = false;
		//idSpan[span->page_id] = span;
		//idSpan[span->page_id + span->page_nums - 1] = span;
		idTree.set(span->page_id, span);		// ���ºϲ����spanҳ��������β��ַӳ���ϵ
		idTree.set(span->page_id + span->page_nums - 1, span);
		logMessage(DEBUG, "tid: %d�ϲ����չ�ϣӳ�䴦��ɹ�����ǰspanҳ��: %d, ҳ��: %d��ӳ��span��ַΪ: %p", std::this_thread::get_id(), span->page_id, span->page_nums, span);
	}
public:
	std::mutex page_mtx;
private:
	PageCache(){}
	PageCache(const PageCache& page) = delete;
	PageCache& operator=(const PageCache& page) = delete;
private:
	static PageCache pPage;
	SpanList page_splist[MAX_PAGES];
	//std::unordered_map<PAGE_ID, Span*> idSpan;
	SingleRadix<32 - PAGE_SHIFT> idTree;		// �������Ż�ҳ����span*ӳ���ϵ����ʹ��map��unordered_map�Լ��ٻ���������ʱ�䣨�ռ任ʱ�䣩
	FixedMemoryPool<Span> pFmp;
};

PageCache PageCache::pPage;

#endif