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
		logMessage(DEBUG, "page��ӦͰ��span���������ҳ����");
		for (size_t i = pageNums + 1; i < MAX_PAGES; ++i) {
			if (!page_splist[pageNums].isEmpty()) {
				// 3. �����±���ҳͰ��Ϊ�գ���ʱ�ɽ���ҳ���
				Span* src_span = page_splist[pageNums].pop_front();
				Span* aim_span = new Span;
				// 3.1 ҳ�ſ��������ڴ浥Ԫ��ҳ�������ڴ�����
				aim_span->page_id = src_span->page_id;		// Ŀ��span��ҳ���ɸ���ҳ���裨ͷ�У���ַ�����ҳ�ű�ʶ�ÿ��ڴ��Ψһ�ԣ�
				aim_span->page_nums = pageNums;				// Ŀ��span��ҳ�������������span�ܴ�С
				src_span->page_id += pageNums;				// ����ҳspan��Ϊͷ�зֶ�����˸�С��span��ҳ������ƶ�
				src_span->page_nums -= pageNums;			// �ᱻ���ൽ��С��ҳͰ�У�ҳ����Ӧ��С��
				// 3.2 ������Ϊ��С�Ļ���ʱδ��ʹ�õ�src_spanͷ�嵽��С��ҳͰ��
				page_splist[src_span->page_nums].push_front(src_span);
				return aim_span;
			}
		}
		// 4. �������������ˣ�˵��ҳͰ������ȫ���޿���span��һ������ڳ���ճ�ʼ�����ڴ����ʱ��
		Span* bunchs_memory = new Span;
		void* ptr = system_alloc(MAX_PAGES - 1);
		bunchs_memory->page_id = (PAGE_ID)ptr >> PAGE_SHIFT;	// ��ַҲ����ֵ��ţ�ǿתΪ��ֵ������8�ֽڣ��õ�ҳ��
		bunchs_memory->page_nums = MAX_PAGES - 1;				// ���뵽�����ҳͰ�궨��ҳ���ڴ�
		// 5. �Ѿ����뵽�����ҳ�Ĵ���ڴ棬ͷ�������ҳspanlist��
		page_splist[MAX_PAGES - 1].push_front(bunchs_memory);
		return get_a_span(pageNums);
	}
public:
	static std::mutex page_mtx;
private:
	PageCache(){}
	PageCache(const PageCache& page) = delete;
	PageCache& operator=(const PageCache& page) = delete;
private:
	static PageCache pPage;
	SpanList page_splist[MAX_PAGES];
};

PageCache PageCache::pPage;

#endif