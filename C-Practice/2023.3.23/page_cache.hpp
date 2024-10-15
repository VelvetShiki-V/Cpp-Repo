#ifndef __PAGE_CACHE_HPP
#define __PAGE_CACHE_HPP
#pragma once
#include "common.hpp"

class PageCache {
public:
	static PageCache* get_page_cache() {
		return &pPage;
	}
	// 获取一个具有k页的span（页数即page cache桶下标）
	Span* get_a_span(const size_t& pageNums) {
		// 1. 如果对应页桶中存在可用span，直接返回
		if (!page_splist[pageNums].isEmpty()) return page_splist[pageNums].pop_front();
		// 2. 若桶内无可用span，将向下遍历获取可用页桶资源
		logMessage(DEBUG, "page对应桶无span，将向更大页申请");
		for (size_t i = pageNums + 1; i < MAX_PAGES; ++i) {
			if (!page_splist[pageNums].isEmpty()) {
				// 3. 若向下遍历页桶不为空，此时可进行页拆分
				Span* src_span = page_splist[pageNums].pop_front();
				Span* aim_span = new Span;
				// 3.1 页号控制所需内存单元，页数控制内存数量
				aim_span->page_id = src_span->page_id;		// 目标span的页号由更大页赋予（头切，地址代表的页号标识该块内存的唯一性）
				aim_span->page_nums = pageNums;				// 目标span的页数即所需申请的span总大小
				src_span->page_id += pageNums;				// 更大页span因为头切分而变成了更小的span，页号向后移动
				src_span->page_nums -= pageNums;			// 会被分类到更小的页桶中（页数相应减小）
				// 3.2 将减少为更小的还暂时未被使用的src_span头插到更小的页桶中
				page_splist[src_span->page_nums].push_front(src_span);
				return aim_span;
			}
		}
		// 4. 若程序运行至此，说明页桶遍历完全均无可用span（一般出现于程序刚初始化无内存分配时）
		Span* bunchs_memory = new Span;
		void* ptr = system_alloc(MAX_PAGES - 1);
		bunchs_memory->page_id = (PAGE_ID)ptr >> PAGE_SHIFT;	// 地址也是数值编号，强转为数值并除以8字节，得到页号
		bunchs_memory->page_nums = MAX_PAGES - 1;				// 申请到了最大页桶标定的页数内存
		// 5. 已经申请到了最大页的大块内存，头插入最大页spanlist中
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