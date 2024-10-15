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
		if (free_list) {			// ������ڹ黹���ڴ�飬����ʹ��
			obj = (T*)free_list;
			free_list = *(void**)obj;
		}
		else {
			if (sizeof T > memory_remain) {		// ���ʣ���ڴ�ؿռ䲻�����䣬�򿪱��µ�һ���ռ�(128kb)
				memory_remain = 128 * 1024;
				head_addr = (char*)malloc(memory_remain);
				if (nullptr == head_addr) throw std::bad_alloc();
			}
			// ���ʣ��ռ��㹻���䣬����䲢ͳ��ʣ����ֵ
			obj = (T*)head_addr;
			size_t obj_size = sizeof obj < sizeof(void*) ? sizeof(void*) : sizeof(obj);		// ��ֹ������ڴ���С�й�����Ƭ
			head_addr += sizeof obj_size;
			memory_remain -= sizeof obj_size;
		}
		// ��λnew����ʼ�����ڴ�������뵽�ռ�Ķ���
		new(obj)T;
		return obj;
	}

	// �黹֮ǰ������ڴ�ռ�С�飬��ʹ������ṹ�໥���ӷ����ظ�����
	void restore(T* obj) {
		// �黹�ռ�ǰ������ռ��еĶ��󡪡���ʾ����
		obj->~T();
		// �黹�ռ䣬������������
		*(void**)obj = free_list;		// �ڴ�С���ͷ4/8�ֽ����ڴ洢��һ�ڴ�С��Ľ���ַ
		free_list = obj;				// ������������ڴ���׵�ַ����ͷ�壬Ч�ʸ���
	}
private:
	char* head_addr = nullptr;
	void* free_list = nullptr;
	int memory_remain;
};

#endif