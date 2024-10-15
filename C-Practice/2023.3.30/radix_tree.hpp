#ifndef __RADIX_TREE_HPP
#define __RADIX_TREE_HPP
#pragma once
#include "common.hpp"
#include <string>

// һ�������
template<int PAGE_INDEX>			// PAGE_INDEXΪ32λ�½��̵�ַ�ռ�ɷ���ҳ��(8kb)�ĸ�������
class SingleRadix {
public:
	// ���캯��һ���Խ�32λ�¿����������ҳ��ӳ��Ͱ�±꿪����ȫ�������пռ�ĳ�ʼ�����ÿ�
	SingleRadix()
		:arr_size(Alignment::space_round_up(arr_length * sizeof(void*)))
	{
		root_arr = (void**)system_alloc(arr_size >> PAGE_SHIFT);
		memset(root_arr, 0, arr_size);		// ÿ��Ͱ��span*ָ��Ĭ��Ϊnullptr
	}

	// ֱ�Ӷ�ַ����ҳ��ӳ���ӦͰֱ�ӻ�ȡspan��ַ���ⲿ��ҪǿתΪSpan*��
	void* get(PAGE_ID id) {
		if ((id >> PAGE_INDEX) > 0) return nullptr;		// ��ֹ�����ҳ�Ŵ���32λ�¿������ҳͰӳ������
		return root_arr[id];
	}

	// ���ڴ��ַתҳ�ţ��ٵ���Ӧҳ���½�span��ַӳ���ȥ
	void set(PAGE_ID id, void* span) {
		root_arr[id] = span;
	}

	// ���ҳ�Ŷ�ӦͰ������
	void erase(PAGE_ID id) {
		root_arr[id] = nullptr;
	}
private:
	size_t arr_length = 1 << PAGE_INDEX;				// һ���������ϣͰ����
	size_t arr_size;				// ��Ҫ�Ŀռ��С�������
	void** root_arr;				// �洢span*��ָ�����飬�ȼ���void* arr[]
};

//// ���������
//template<int PAGE_INDEX>
//class DoubleRadix {
//public:
//	// �洢�ڶ���ҳ��ӳ��span��ַ��spna��ַ��ϣͰ�ڲ���
//	struct Branch {
//		void* branch_arr[branch_length];
//	};
//	DoubleRadix()
//		// ��ʼ����һ��͵ڶ����Ͱ���ȺͿ��ٿռ�
//		:root_length(root_index)
//		,root_size(Alignment::space_round_up(root_length * sizeof(Branch*)))
//		,branch_length(1 << branch_index)
//		,branch_size(Alignment::space_round_up(branch_length * sizeof(void*)))
//	{
//		// ��һ�㿪�ٿռ䲢�ÿ�
//		root_arr = (Branch*)system_alloc(root_size >> PAGE_SHIFT);
//		std::string::bzero(root_arr, sizeof root_arr);
//		// �ڶ���ֱ𿪱ٿռ䲢�ÿ�
//		for (int i = 0; i < root_length; ++i) {
//			root_arr[i] = system_alloc(branch_size >> PAGE_SHIFT);
//			std::string::bzero(root_arr[i], sizeof root_arr[i]);
//		}
//	}
//	// ͨ��ҳ�Ż�ȡspan��ַ
//	void* get(PAGE_ID id) {
//		// ��ȡ��һ���±�
//		int first = id >> branch_index;
//		// ��ȡ�ڶ����±�
//		int second = id & (branch_length - 1);
//		return root_arr[first]->branch_arr[second];
//	}
//
//	// ͨ���ڴ��ַӳ���Ӧ��span
//	void set(PAGE_ID id, void* span) {
//		// ��ȡ��һ���±�
//		int first = id >> branch_index;
//		// ��ȡ�ڶ����±�
//		int second = id & (branch_length - 1);
//		root_arr[first]->branch_arr[second] = span;
//	}
//private:
//	int root_index = 5;			// �涨��һ��Ͱ�ĸ���Ϊ5
//	int root_length;			// ��һ��Ͱ����
//	size_t root_size;			// ��һ��Ͱ�Ŀռ��С��ָ�����飬������ֽ�����
//	int branch_index = PAGE_INDEX - root_index;		// �ɵ�һ��
//	int branch_length;					// �ڶ����֧Ͱ����
//	size_t branch_size;					// �ڶ����֧Ͱ�ռ��С���洢span��ַ���±���ҳ�ŵ�14λ���ƣ�
//	Branch* root_arr[root_length];		// ��һ���ϣͰ
//};

#endif