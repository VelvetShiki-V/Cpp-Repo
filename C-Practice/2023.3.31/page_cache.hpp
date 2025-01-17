#ifndef __PAGE_CACHE_HPP
#define __PAGE_CACHE_HPP
#pragma once
#include "common.hpp"
#include "memoy_pool.hpp"
#include "radix_tree.hpp"

class PageCache {
public:
	// 获取单例page cache对象地址
	static PageCache* get_page_cache() {
		return &pPage;
	}

	// 获取一个空间为pageNums页数大小的span（页数即page cache桶下标）
	Span* get_a_span(const size_t& pageNums) {
		assert(pageNums > 0);
		// 如果申请的页内存超过最大页，直接调用系统申请（无需建立哈希映射，直接申请即可）
		if (pageNums > MAX_PAGES - 1) {
			void* getMemory = system_alloc(pageNums);
			Span* span = pFmp.acquire();		// 该span从定长内存池中申请得到，所需空间绕过malloc直接向系统申请system_alloc
			span->page_id = (PAGE_ID)getMemory >> PAGE_SHIFT;
			span->page_nums = pageNums;			// 设置span相关状态
			span->isServing = true;
			logMessage(DEBUG, "tid: %d申请的内存超过最大页: %d，需要调用系统堆申请，实际分配得到页数: %d", std::this_thread::get_id(), MAX_PAGES, pageNums);
			logMessage(DEBUG, "分配得到span首地址: %p，span内存储大块内存首地址: %p", span, (void*)(span->page_id << PAGE_SHIFT));
			return span;
		}
		// 1. 如果对应页桶中存在可用span，直接返回
		if (!page_splist[pageNums].isEmpty()) {
			Span* span = page_splist[pageNums].pop_front();		// 该span的相关状态在central cache中将被设置
			// 将该span中每页内存与该span建立哈希映射关系，代表该span中的每一页内存都隶属于该span，方便central cache回收thread cache时插入对应span中
			for (PAGE_ID i = 0; i < span->page_nums; ++i) {
				//idSpan[span->page_id + i] = span;
				idTree.set(span->page_id + i, span);		// 基数树优化页号与span*映射关系，不使用map或unordered_map以减少互斥锁阻塞时间（空间换时间）
			}
			logMessage(DEBUG, "tid: %d在page cache[%d]页桶中找到可用span，将该span返回给central cache", std::this_thread::get_id(), pageNums);
			return span;
		}
		// 2. 若桶内无可用span，将向下遍历获取可用页桶资源
		logMessage(DEBUG, "对应页数为%d桶无剩余span，将向更大页申请", pageNums);
		for (size_t i = pageNums + 1; i < MAX_PAGES; ++i) {
			// logMessage(DEBUG, "遍历至%d号桶", i);
			if (!page_splist[i].isEmpty()) {
				// 3. 若向下遍历页桶不为空，此时可进行页拆分
				Span* src_span = page_splist[i].pop_front();
				//idSpan.erase(src_span->page_id);			// 原桶span取消映射，添加新映射
				idTree.erase(src_span->page_id);
				Span* aim_span = pFmp.acquire();
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
				//idSpan[src_span->page_id] = src_span;
				//idSpan[src_span->page_id + src_span->page_nums - 1] = src_span;
				idTree.set(src_span->page_id, src_span);
				idTree.set(src_span->page_id + src_span->page_nums - 1, src_span);
				// 3.4 将目标span中每页内存与该span建立哈希映射关系，代表该span中的每一页内存都隶属于该span，方便central cache回收thread cache时插入对应span中
				for (PAGE_ID i = 0; i < aim_span->page_nums; ++i) {
					//idSpan[aim_span->page_id + i] = aim_span;		// 建立的是与span的关系而非span内分配得到的大块空间的关系
					idTree.set(aim_span->page_id + i, aim_span);
				}
				logMessage(DEBUG, "aim_span共%d页，页总大小为%d字节的cache内存块成功与该span建立哈希映射，span地址为: %p", aim_span->page_nums, aim_span->page_nums << PAGE_SHIFT, aim_span);
				return aim_span;
			}
		}
		// 4. 若程序运行至此，说明页桶遍历完全均无可用span（一般出现于程序刚初始化无内存分配时）
		logMessage(DEBUG, "页桶全部为空，将向堆发起申请");
		Span* bunchs_memory = pFmp.acquire();
		void* ptr = system_alloc(MAX_PAGES - 1);
		bunchs_memory->page_id = (PAGE_ID)ptr >> PAGE_SHIFT;	// 地址也是数值编号，强转为数值并除以8字节，得到页号
		bunchs_memory->page_nums = MAX_PAGES - 1;				// 申请到了最大页桶标定的页数内存
		// 5. 已经申请到了最大页的大块内存，头插入最大页spanlist中，并建立哈希映射
		page_splist[MAX_PAGES - 1].push_front(bunchs_memory);
		//idSpan[bunchs_memory->page_id] = bunchs_memory;
		idTree.set(bunchs_memory->page_id, bunchs_memory);
		logMessage(DEBUG, "system_alloc申请堆空间成功，向%d页桶中存入页号为%d, 页数为%d的内存", MAX_PAGES - 1, bunchs_memory->page_id, bunchs_memory->page_nums);
		return get_a_span(pageNums);
	}

	// 根据一块内存的地址找到其对应span首地址
	Span* span_belong_memory(void* cache_addr) {
		assert(cache_addr);
		PAGE_ID id = (PAGE_ID)cache_addr >> PAGE_SHIFT;		// 根据内存块首地址计算属于其存储空间span的页号，再根据页号查找其对应span地址
		//std::unique_lock<std::mutex> lock;				// RAII智能锁
		//std::unordered_map<PAGE_ID, Span*>::iterator it = idSpan.find(id);
		//if (it != idSpan.end()) {
		//	logMessage(DEBUG, "tid: %d归还内存，已找到地址为: %p的cache内存块对应span映射，其首地址为: %p", std::this_thread::get_id(), cache_addr, it->second);
		//	return it->second;
		//}
		// 基数树优化页号与span*映射关系，不使用map或unordered_map以减少互斥锁阻塞时间（空间换时间）
		Span* span_obtain = (Span*)idTree.get(id);
		assert(span_obtain);
		return span_obtain;
	}

	// central cache的span归还给page cache
	void span_to_page_cache(Span* span) {
		assert(span);
		// 申请的内存超过最大页，调用系统接口直接释放（无需取消哈希映射，直接释放即可）
		if (span->page_nums > MAX_PAGES - 1) {
			void* ptr = (void*)(span->page_id << PAGE_SHIFT);
			system_free(ptr);
			logMessage(DEBUG, "tid: %d超过最大页的大块内存调用系统接口释放，大小共%d字节，页数: %d", std::this_thread::get_id(), span->page_nums << PAGE_SHIFT, span->page_nums);
			pFmp.restore(span);
			return;
		}
		// 1. 向前合并（3种情况无法合并：相邻前页无可用span；正在使用中；合并后页数超过MAX_PAGES）
		logMessage(DEBUG, "当前span已归还至page cache中，页号: %d, 页数: %d，检查前后页是否有可合并cache", span->page_id, span->page_nums);
		while (true) {
			//auto prevSpan = idSpan.find(span->page_id - 1);
			Span* prevSpan = (Span*)idTree.get(span->page_id - 1);
			if (nullptr == prevSpan) {
				logMessage(DEBUG, "当前span向前无可用合并page span");
				break;
			}
			if (prevSpan->isServing) {
				logMessage(DEBUG, "前一个span正在占用中，无法合并page");
				break;
			}
			if (span->page_nums + prevSpan->page_nums > MAX_PAGES - 1) {
				logMessage(DEBUG, "向前合并页数超过最大页，无法合并page");
				break;
			}
			// 可以合并，合并该span并清理合并后的原桶
			//idSpan.erase(span->page_id);
			idTree.erase(span->page_id);				// 合并前的原span去页号与地址映射
			span->page_id = prevSpan->page_id;			// 改变当前span页号为相邻前页的页号
			span->page_nums += prevSpan->page_nums;		// 并增加页数至目标桶
			page_splist[prevSpan->page_nums].erase(prevSpan);		// 清理原桶
			idTree.erase(prevSpan->page_id);
			pFmp.restore(prevSpan);
			logMessage(DEBUG, "向前合并成功，合并后页号: %d, 页数: %d", span->page_id, span->page_nums);
		}
		// 2. 向后合并
		while (true) {
			//auto nextSpan = idSpan.find(span->page_id + span->page_nums);
			Span* nextSpan = (Span*)idTree.get(span->page_id + span->page_nums);
			if (nullptr == nextSpan) {
				logMessage(DEBUG, "当前span向后无可用合并page span");
				break;
			}
			if (nextSpan->isServing) {
				logMessage(DEBUG, "后一个span正在占用中，无法合并page");
				break;
			}
			if (span->page_nums + nextSpan->page_nums > MAX_PAGES - 1) {
				logMessage(DEBUG, "向后合并页数超过最大页，无法合并page");
				break;
			}
			// 可以合并，合并该span并清理合并后的原桶
			//idSpan.erase(span->page_id);
			idTree.erase(span->page_id);
			span->page_nums += nextSpan->page_nums;
			page_splist[nextSpan->page_nums].erase(nextSpan);
			idTree.erase(nextSpan->page_id);
			pFmp.restore(nextSpan);
			logMessage(DEBUG, "向后合并成功，合并后页号: %d, 页数: %d", span->page_id, span->page_nums);
		}
		// 3. 合并后处理（合并span插入，状态改变）
		page_splist[span->page_nums].push_front(span);
		span->isServing = false;
		//idSpan[span->page_id] = span;
		//idSpan[span->page_id + span->page_nums - 1] = span;
		idTree.set(span->page_id, span);		// 更新合并后的span页号与其首尾地址映射关系
		idTree.set(span->page_id + span->page_nums - 1, span);
		logMessage(DEBUG, "tid: %d合并回收哈希映射处理成功，当前span页号: %d, 页数: %d，映射span地址为: %p", std::this_thread::get_id(), span->page_id, span->page_nums, span);
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
	SingleRadix<32 - PAGE_SHIFT> idTree;		// 基数树优化页号与span*映射关系，不使用map或unordered_map以减少互斥锁阻塞时间（空间换时间）
	FixedMemoryPool<Span> pFmp;
};

PageCache PageCache::pPage;

#endif