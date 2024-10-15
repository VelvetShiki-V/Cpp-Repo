#ifndef __PAGE_CACHE_HPP
#define __PAGE_CACHE_HPP
#pragma once
#include "common.hpp"

class PageCache {
public:
	static PageCache* get_page_cache() {
		return &pPage;
	}

	// ��ȡһ������kҳ��span��ҳ����page cacheͰ�±꣩
	Span* get_a_span(const size_t& pageNums) {
		// 1. �����ӦҳͰ�д��ڿ���span��ֱ�ӷ���
		if (!page_splist[pageNums].isEmpty()) return page_splist[pageNums].pop_front();
		// 2. ��Ͱ���޿���span�������±�����ȡ����ҳͰ��Դ
		logMessage(DEBUG, "��Ӧҳ��Ϊ%dͰ��ʣ��span���������ҳ����", pageNums);
		for (size_t i = pageNums + 1; i < MAX_PAGES; ++i) {
			// logMessage(DEBUG, "������%d��Ͱ", i);
			if (!page_splist[i].isEmpty()) {
				// 3. �����±���ҳͰ��Ϊ�գ���ʱ�ɽ���ҳ���
				Span* src_span = page_splist[i].pop_front();
				Span* aim_span = new Span;
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
				


				// 3.4 ��Ŀ��span��ÿҳ�ڴ����span������ϣӳ���ϵ�������span�е�ÿһҳ�ڴ涼�����ڸ�span������central cache����thread cacheʱ�����Ӧspan��
				for (PAGE_ID i = 0; i < aim_span->page_nums; ++i) {
					idSpan[aim_span->page_id + i] = aim_span;		// ����������span�Ĺ�ϵ����span�ڷ���õ��Ĵ��ռ�Ĺ�ϵ
				}
				logMessage(DEBUG, "aim_span��%dҳ��ÿҳ��СΪ%d�ֽڵ�cache�ڴ��ɹ����span������ϣӳ�䣬span��ַΪ: %p", aim_span->page_nums, aim_span->page_nums << PAGE_SHIFT, aim_span);
				return aim_span;
			}
		}
		// 4. �������������ˣ�˵��ҳͰ������ȫ���޿���span��һ������ڳ���ճ�ʼ�����ڴ����ʱ��
		logMessage(DEBUG, "ҳͰȫ��Ϊ�գ�����ѷ�������");
		Span* bunchs_memory = new Span;
		void* ptr = system_alloc(MAX_PAGES - 1);
		bunchs_memory->page_id = (PAGE_ID)ptr >> PAGE_SHIFT;	// ��ַҲ����ֵ��ţ�ǿתΪ��ֵ������8�ֽڣ��õ�ҳ��
		bunchs_memory->page_nums = MAX_PAGES - 1;				// ���뵽�����ҳͰ�궨��ҳ���ڴ�
		// 5. �Ѿ����뵽�����ҳ�Ĵ���ڴ棬ͷ�������ҳspanlist��
		page_splist[MAX_PAGES - 1].push_front(bunchs_memory);
		logMessage(DEBUG, "system_alloc����ѿռ�ɹ�����%dҳͰ�д���ҳ��Ϊ%d, ҳ��Ϊ%d���ڴ�", MAX_PAGES - 1, bunchs_memory->page_id, bunchs_memory->page_nums);
		return get_a_span(pageNums);
	}

	// ����һ���ڴ�ĵ�ַ�ҵ����Ӧspan�׵�ַ
	Span* span_belong_memory(void* cache_addr) {
		assert(cache_addr);
		PAGE_ID id = ((PAGE_ID)cache_addr) >> PAGE_SHIFT;		// �����ڴ���׵�ַ����������洢�ռ�span��ҳ�ţ��ٸ���ҳ�Ų������Ӧspan��ַ
		std::unordered_map<PAGE_ID, Span*>::iterator it = idSpan.find(id);
		if (it != idSpan.end()) {
			logMessage(DEBUG, "���ҵ�%p�ڴ���Ӧspan�����׵�ַΪ: %p", cache_addr, it->second);
			return it->second;
		}
		assert(false);
		return nullptr;
	}

	// central cache��span�黹��page cache
	void span_to_page_cache(Span* span) {
		assert(span);
		// 1. ��ǰ�ϲ�
		// 2. ���ϲ�
		// 3. �ϲ�����
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
	std::unordered_map<PAGE_ID, Span*> idSpan;
};

PageCache PageCache::pPage;

#endif