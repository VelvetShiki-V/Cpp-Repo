#ifndef __MEMORY_POOL_HPP
#define __MEMORY_POOL_HPP
#pragma once

#include "common.hpp"
using std::cout;
using std::endl;

template<class T>
class FixedMemoryPool {
public:
	T* acquire() {
		T* obj = nullptr;
		if (free_list) {			// 如果存在归还的自由链表中的内存块，优先使用（链表头删）
			void* next = next_node(free_list);
			obj = (T*)free_list;
			free_list = next;
		}
		else {
			if (sizeof(T) > memory_remain) {		// 如果剩余内存池空间不够分配，则开辟新的一大块空间
				// 一次申请128kb大块内存等待分配（使用common中的系统调用申请system_alloc）
				memory_remain = 128 * 1024;			
				head_addr = (char*)system_alloc(memory_remain >> PAGE_SHIFT);
				if (nullptr == head_addr) throw std::bad_alloc();
			}
			// 如果剩余空间足够分配，则分配并统计剩余数值
			obj = (T*)head_addr;
			// 防止申请的内存块大小有过多碎片
			size_t obj_size = sizeof(T) < sizeof(void*) ? sizeof(void*) : sizeof(T);	
			// 将分配掉空间的头指针后移，并修正剩余内存空间
			head_addr += obj_size;	
			memory_remain -= obj_size;
		}
		// 定位new来初始化在内存池中申请到空间的对象
		new(obj)T;
		return obj;
	}

	// 归还之前申请的内存空间小块，并使用链表结构相互连接方便重复利用
	void restore(T* obj) {
		// 归还空间前先清理空间中的对象——显示调用
		obj->~T();
		// 归还空间，并用链表相连
		next_node(obj) = free_list;		// 内存小块的头4/8字节用于存储下一内存小块的结点地址
		free_list = obj;				// 传入申请过的内存池首地址，并头插，效率更高
	}
private:
	char* head_addr = nullptr;			// 定位内存的指针
	void* free_list = nullptr;			// 自由链表头指针
	int memory_remain;					// 内存切分的剩余大小
};

#endif