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
		logMessage(DEBUG, "对应页数为%d桶无剩余span，将向更大页申请", pageNums);
		for (size_t i = pageNums + 1; i < MAX_PAGES; ++i) {
			// logMessage(DEBUG, "遍历至%d号桶", i);
			if (!page_splist[i].isEmpty()) {
				// 3. 若向下遍历页桶不为空，此时可进行页拆分
				Span* src_span = page_splist[i].pop_front();
				Span* aim_span = new Span;
				// 3.1 页号控制所需内存单元，页数控制内存数量
				aim_span->page_id = src_span->page_id;		// 目标span的页号由更大页赋予（头切，地址代表的页号标识该块内存的唯一性）
				aim_span->page_nums = pageNums;				// 目标span的页数即所需申请的span总大小
				src_span->page_id += pageNums;				// 更大页span因为头切分而变成了更小的span，页号向后移动
				src_span->page_nums -= pageNums;			// 会被分类到更小的页桶中（页数相应减小）
				// 3.2 将减少为更小的还暂时未被使用的src_span头插到更小的页桶中
				logMessage(DEBUG, "%d号桶不为空，将该桶下可用span分割为%d和%d两个页数桶中span，目标桶内span地址为: %p"
					, i, aim_span->page_nums, src_span->page_nums, aim_span);
				logMessage(DEBUG, "该span获得页号所对大块内存空间起始地址为: %p", (void*)(aim_span->page_id << PAGE_SHIFT));
				page_splist[src_span->page_nums].push_front(src_span);
				// 3.3 将未使用到的分割后的span首尾页号与该span地址建立哈希映射，方便进行page cache的合并操作
				


				// 3.4 将目标span中每页内存与该span建立哈希映射关系，代表该span中的每一页内存都隶属于该span，方便central cache回收thread cache时插入对应span中
				for (PAGE_ID i = 0; i < aim_span->page_nums; ++i) {
					idSpan[aim_span->page_id + i] = aim_span;		// 建立的是与span的关系而非span内分配得到的大块空间的关系
				}
				logMessage(DEBUG, "aim_span共%d页，每页大小为%d字节的cache内存块成功与该span建立哈希映射，span地址为: %p", aim_span->page_nums, aim_span->page_nums << PAGE_SHIFT, aim_span);
				return aim_span;
			}
		}
		// 4. 若程序运行至此，说明页桶遍历完全均无可用span（一般出现于程序刚初始化无内存分配时）
		logMessage(DEBUG, "页桶全部为空，将向堆发起申请");
		Span* bunchs_memory = new Span;
		void* ptr = system_alloc(MAX_PAGES - 1);
		bunchs_memory->page_id = (PAGE_ID)ptr >> PAGE_SHIFT;	// 地址也是数值编号，强转为数值并除以8字节，得到页号
		bunchs_memory->page_nums = MAX_PAGES - 1;				// 申请到了最大页桶标定的页数内存
		// 5. 已经申请到了最大页的大块内存，头插入最大页spanlist中
		page_splist[MAX_PAGES - 1].push_front(bunchs_memory);
		logMessage(DEBUG, "system_alloc申请堆空间成功，向%d页桶中存入页号为%d, 页数为%d的内存", MAX_PAGES - 1, bunchs_memory->page_id, bunchs_memory->page_nums);
		return get_a_span(pageNums);
	}

	// 根据一块内存的地址找到其对应span首地址
	Span* span_belong_memory(void* cache_addr) {
		assert(cache_addr);
		PAGE_ID id = ((PAGE_ID)cache_addr) >> PAGE_SHIFT;		// 根据内存块首地址计算属于其存储空间span的页号，再根据页号查找其对应span地址
		std::unordered_map<PAGE_ID, Span*>::iterator it = idSpan.find(id);
		if (it != idSpan.end()) {
			logMessage(DEBUG, "已找到%p内存块对应span，其首地址为: %p", cache_addr, it->second);
			return it->second;
		}
		assert(false);
		return nullptr;
	}

	// central cache的span归还给page cache
	void span_to_page_cache(Span* span) {
		assert(span);
		// 1. 向前合并
		// 2. 向后合并
		// 3. 合并后处理
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