#ifndef __MEMORY_POOL_HPP
#define __MEMORY_POOL_HPP
#pragma once

#include <iostream>
#include <string>
#include <ctime>
#include <vector>
using std::cout;
using std::endl;

template<class T>
class MemoryPool {
public:
	T* acquire() {
		T* obj;
		if (free_list) {			// 如果存在归还的内存块，优先使用
			obj = (T*)free_list;
			free_list = *(void**)obj;
		}
		else {
			if (sizeof T > memory_remain) {		// 如果剩余内存池空间不够分配，则开辟新的一大块空间(128kb)
				memory_remain = 128 * 1024;
				head_addr = (char*)malloc(memory_remain);
				if (nullptr == head_addr) throw std::bad_alloc();
			}
			// 如果剩余空间足够分配，则分配并统计剩余数值
			obj = (T*)head_addr;
			size_t obj_size = sizeof obj < sizeof(void*) ? sizeof(void*) : sizeof(obj);		// 防止申请的内存块大小有过多碎片
			head_addr += sizeof obj_size;
			memory_remain -= sizeof obj_size;
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
		*(void**)obj = free_list;		// 内存小块的头4/8字节用于存储下一内存小块的结点地址
		free_list = obj;				// 传入申请过的内存池首地址，并头插，效率更高
	}
private:
	char* head_addr = nullptr;
	void* free_list = nullptr;
	int memory_remain;
};

#endif