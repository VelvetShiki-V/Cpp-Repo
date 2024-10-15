#ifndef __CENTRAL_CACHE_HPP
#define __CENTRAL_CACHE_HPP
#pragma once
#include"common.hpp"
#include "page_cache.hpp"

// 中心缓存类
class CentralCache {
public:
	// central cache无可用span，从page cache中获取一个span
	Span* get_span(SpanList& sl, const size_t& size) {			// size用于计算所需申请的page页桶
		// 1. 定位需要申请的页号桶（以页数为基础的映射规则）
		size_t page_index = Alignment::page_locate(size);
		logMessage(DEBUG, "定位到页数为%d页桶", page_index);
		// 2. page cache单例获取（加锁执行），并从该page cache对象中获取一个span再解锁（其他线程不会访问到该span）
		PageCache* pCache = PageCache::get_page_cache();
		pCache->page_mtx.lock();
		Span* span = pCache->get_a_span(page_index);			// 对应桶下标获取span
		span->isServing = true;
		pCache->page_mtx.unlock();
		// 3. 将获取到的span信息展开（大内存起始地址和总大小），由char指针控制首尾并细分
		char* start = (char*)(span->page_id << PAGE_SHIFT);		// 根据页号对应开辟的span * 8kb得到的大内存块首地址，逐字节获取并切割
		size_t memory_size = span->page_nums << PAGE_SHIFT;		// 将页数展开，页数 * 8kb得到该块大内存的总大小（字节）
		char* end = start + memory_size;			// 根据大内存首地址与大小可以得到该内存的首尾地址
		logMessage(DEBUG, "获取到一个span地址为: %p, 页号: %d, 页数: %d, 对应内存块首地址: %p，尾地址: %p，大内存大小: %d", span, span->page_id, span->page_nums, start, end, memory_size);
		// 4. 将获取到的span切成cache小块挂接到对应central cache内存单元的spanlist中
		span->freelist = start;
		void* tail = span->freelist;
		start += size;
		size_t node_count = 1;
		size_t memory_remain = (size_t)(end - start);
		size_t alloc = memory_remain / size;
		while (start < end && alloc) {				// 尾插结点，每个内存块结点大小为size，需要考虑不能整切的情况（如分配24字节，48字节的内碎片问题）
			next_node(tail) = start;
			tail = start;
			start += size;
			++node_count;
			memory_remain = (size_t)(end - start);
			alloc = memory_remain / size;
		}
		span->node_counts += node_count;		// 统计span内结点个数
		if (start != end) {
			logMessage(WARNING, "span中内存不能完整切分，理论获取内存总大小: %d字节，实际获得: %d字节，产生了内碎片", memory_size, size * span->node_counts);
		}
		logMessage(DEBUG, "页数为%d，共切分了size为:%d字节的%d个cache小块",span->page_nums, size, span->node_counts);
		next_node(tail) = nullptr;
		// 5. 将切好小块的span头插到对应splist中（加锁操作，防止其他线程可能正在桶内获取span，将在函数外解锁）
		sl.sl_mtx.lock();
		sl.push_front(span);
		logMessage(DEBUG, "将小块头插到central cache: size为%d的[%d]号桶中", size, Alignment::bucket_locate(size));
		return span;
	}

	// 寻找一个桶中是否存在非空span结点
	Span* span_check(SpanList& sp, const size_t& size) {
		// 1. 若splist为空，表示桶中无可用span结点内存块，返回空
		if (sp.isEmpty()) {
			logMessage(ERRO, "该splist中无span");
		}
		else {
			// 2. 若桶不为空，遍历桶双向链表，可能存在或不存在可用span结点，存在返回span地址，不存在返回空
			Span* start = sp.begin();
			while (start != sp.end()) {
				if (start->freelist == nullptr) {
					start = start->next;
				}
				else {
					logMessage(NORMAL, "span check发现桶有剩余可用span结点，该size为:%d的span内存在%d个剩余cache，首地址为: %p\n", size, start->node_counts, start);
					return start;
				}
			}
		}
		return nullptr;
	}

	// 从span中获取thread cache所需内存块
	size_t fetch_blocks(void*& start, void*& end, const size_t& batch_num,const size_t& size) {
		// 1. 加桶锁访问central cache，定位cache桶
		size_t list_locate = Alignment::bucket_locate(size);
		sp_list[list_locate].sl_mtx.lock();		// 加锁
		logMessage(DEBUG, "spanlist定位至%d号桶，开始检查是否有剩余span结点", list_locate);
		Span* span = nullptr;
		if (!(span = span_check(sp_list[list_locate], size))) {
			// 2. 若桶内无可用span，移至page cache申请一个span
			logMessage(DEBUG, "桶内无可用span结点，开始向page cache获取一个可用span");
			sp_list[list_locate].sl_mtx.unlock();			// 先解锁，再去page cache获取span，防阻塞（防止其他线程向central cache该桶还内存被堵住）
			span = get_span(sp_list[list_locate], size);	// 在获取span过程中，将结点插入splist的时候需要加锁
		}
		// 3. 此时span应获取到对应内存，否则抛异常
		assert(span);
		start = end = span->freelist;
		size_t actual_get = 1;		// 实际取得的thread cache结点个数
		size_t count = 0;
		// 4. 从span中提取结点地址范围，并链接取走的后续剩余结点为新的span中freelist首结点
		while (count < batch_num - 1  && next_node(end)) {
			end = next_node(end);
			actual_get++;
			count++;
		}
		// 5. 链接首结点，并将取走的最后一个结点后续链空
		span->use_count += actual_get;			// 分配一个给thread cache，use_count++
		span->node_counts -= actual_get;		// DEBUG，监视span内剩余结点数量
		span->freelist = next_node(end);		// 将取走结点的后一个结点作为当前span的首结点继续链住
		next_node(end) = nullptr;
		logMessage(DEBUG, "thread cache实际获得: %d个", actual_get);
		sp_list[list_locate].sl_mtx.unlock();		// 解锁
		logMessage(DEBUG, "central cache[%d]桶内span中剩余thread cache结点个数: %d个", list_locate, span->node_counts);
		return actual_get;
	}

	// 释放逻辑
	// 从thread cache接收到还回的内存块
	void cache_to_span(void* start, const size_t& nodeNums, const size_t& index) {
		// 1. 若都还回来了，将整一个span归还给page cache，定位桶，加锁执行
		sp_list[index].sl_mtx.lock();
		// 2. 定位span地址
		// 3. 将批量cache头插到该span中
		while (start) {
			void* next = next_node(start);			// 提前备份好需归还内存的下一个结点地址
			Span* span = PageCache::get_page_cache()->span_belong_memory(start);		// 每个结点所属span或许不一致，需要单独计算
			next_node(start) = span->freelist;		// 头插归还
			span->freelist = start;
			span->use_count--;
			if (0 == span->use_count) {
				sp_list[index].erase(span);			// span清理（页号页数不能清理，暂存至page cache待后续使用）
				span->freelist = nullptr;			
				span->next = span->prev = nullptr;
				span->node_counts = 0;
				sp_list[index].sl_mtx.unlock();
				logMessage(DEBUG, "thread cache结点全部归还至central cache下[%d]桶地址为%p的span内，将取走该span归还至page cache中" , index, span);
				PageCache::get_page_cache()->page_mtx.lock();
				PageCache::get_page_cache()->span_to_page_cache(span);
				span->isServing = false;
				PageCache::get_page_cache()->page_mtx.unlock();
				sp_list[index].sl_mtx.lock();
			}
			start = next;		// 向后迭代至空
		}
		// 4. 若该span所有分配出去的thread cache都归还，则将该span做一定清理后归还给page cache（归还前先将central cache桶锁解开，加上page cache锁，归还后再解锁）
		sp_list[index].sl_mtx.unlock();
	}

	// 单例模式获取接口
	static CentralCache* get_cenctral_cache() {
		return &pCentral;
	}
private:
	CentralCache(){}
	CentralCache(const CentralCache& cache) = delete;
	CentralCache& operator=(const CentralCache& cache) = delete;
private:
	SpanList sp_list[MAX_BUCKETS];
	static CentralCache pCentral;		// 单例对象
};

CentralCache CentralCache::pCentral;	// 静态初始化定义

#endif