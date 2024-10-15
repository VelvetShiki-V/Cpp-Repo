#ifndef __RADIX_TREE_HPP
#define __RADIX_TREE_HPP
#pragma once
#include "common.hpp"
#include <string>

// 一层基数树
template<int PAGE_INDEX>			// PAGE_INDEX为32位下进程地址空间可分配页数(8kb)的个数的幂
class SingleRadix {
public:
	// 构造函数一次性将32位下可申请的所有页数映射桶下标开辟完全，并进行空间的初始化和置空
	SingleRadix()
		:arr_size(Alignment::space_round_up(arr_length * sizeof(void*)))
	{
		root_arr = (void**)system_alloc(arr_size >> PAGE_SHIFT);
		memset(root_arr, 0, arr_size);		// 每个桶下span*指针默认为nullptr
	}

	// 直接定址法，页号映射对应桶直接获取span地址（外部需要强转为Span*）
	void* get(PAGE_ID id) {
		if ((id >> PAGE_INDEX) > 0) return nullptr;		// 防止传入的页号大于32位下可申请的页桶映射上限
		return root_arr[id];
	}

	// 将内存地址转页号，再到对应页号下将span地址映射进去
	void set(PAGE_ID id, void* span) {
		root_arr[id] = span;
	}

	// 清除页号对应桶内数据
	void erase(PAGE_ID id) {
		root_arr[id] = nullptr;
	}
private:
	size_t arr_length = 1 << PAGE_INDEX;				// 一层基数树哈希桶长度
	size_t arr_size;				// 需要的空间大小（对齐后）
	void** root_arr;				// 存储span*的指针数组，等价于void* arr[]
};

//// 二层基数树
//template<int PAGE_INDEX>
//class DoubleRadix {
//public:
//	// 存储第二层页号映射span地址的spna地址哈希桶内部类
//	struct Branch {
//		void* branch_arr[branch_length];
//	};
//	DoubleRadix()
//		// 初始化第一层和第二层的桶长度和开辟空间
//		:root_length(root_index)
//		,root_size(Alignment::space_round_up(root_length * sizeof(Branch*)))
//		,branch_length(1 << branch_index)
//		,branch_size(Alignment::space_round_up(branch_length * sizeof(void*)))
//	{
//		// 第一层开辟空间并置空
//		root_arr = (Branch*)system_alloc(root_size >> PAGE_SHIFT);
//		std::string::bzero(root_arr, sizeof root_arr);
//		// 第二层分别开辟空间并置空
//		for (int i = 0; i < root_length; ++i) {
//			root_arr[i] = system_alloc(branch_size >> PAGE_SHIFT);
//			std::string::bzero(root_arr[i], sizeof root_arr[i]);
//		}
//	}
//	// 通过页号获取span地址
//	void* get(PAGE_ID id) {
//		// 获取第一层下标
//		int first = id >> branch_index;
//		// 获取第二层下标
//		int second = id & (branch_length - 1);
//		return root_arr[first]->branch_arr[second];
//	}
//
//	// 通过内存地址映射对应的span
//	void set(PAGE_ID id, void* span) {
//		// 获取第一层下标
//		int first = id >> branch_index;
//		// 获取第二层下标
//		int second = id & (branch_length - 1);
//		root_arr[first]->branch_arr[second] = span;
//	}
//private:
//	int root_index = 5;			// 规定第一层桶的个数为5
//	int root_length;			// 第一层桶长度
//	size_t root_size;			// 第一层桶的空间大小（指针数组，对齐后字节数）
//	int branch_index = PAGE_INDEX - root_index;		// 由第一层
//	int branch_length;					// 第二层分支桶长度
//	size_t branch_size;					// 第二层分支桶空间大小（存储span地址，下标由页号低14位控制）
//	Branch* root_arr[root_length];		// 第一层哈希桶
//};

#endif