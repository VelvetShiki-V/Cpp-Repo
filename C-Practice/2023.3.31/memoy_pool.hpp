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
		if (free_list) {			// ������ڹ黹�����������е��ڴ�飬����ʹ�ã�����ͷɾ��
			void* next = next_node(free_list);
			obj = (T*)free_list;
			free_list = next;
		}
		else {
			if (sizeof(T) > memory_remain) {		// ���ʣ���ڴ�ؿռ䲻�����䣬�򿪱��µ�һ���ռ�
				// һ������128kb����ڴ�ȴ����䣨ʹ��common�е�ϵͳ��������system_alloc��
				memory_remain = 128 * 1024;			
				head_addr = (char*)system_alloc(memory_remain >> PAGE_SHIFT);
				if (nullptr == head_addr) throw std::bad_alloc();
			}
			// ���ʣ��ռ��㹻���䣬����䲢ͳ��ʣ����ֵ
			obj = (T*)head_addr;
			// ��ֹ������ڴ���С�й�����Ƭ
			size_t obj_size = sizeof(T) < sizeof(void*) ? sizeof(void*) : sizeof(T);	
			// ��������ռ��ͷָ����ƣ�������ʣ���ڴ�ռ�
			head_addr += obj_size;	
			memory_remain -= obj_size;
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
		next_node(obj) = free_list;		// �ڴ�С���ͷ4/8�ֽ����ڴ洢��һ�ڴ�С��Ľ���ַ
		free_list = obj;				// ������������ڴ���׵�ַ����ͷ�壬Ч�ʸ���
	}
private:
	char* head_addr = nullptr;			// ��λ�ڴ��ָ��
	void* free_list = nullptr;			// ��������ͷָ��
	int memory_remain;					// �ڴ��зֵ�ʣ���С
};

#endif