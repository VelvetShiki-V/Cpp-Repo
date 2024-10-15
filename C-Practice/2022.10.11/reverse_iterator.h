#ifndef __REVERSE_ITERATOR_H
#define __REVERSE_ITERATOR_H
#pragma once
#include"list.h"

namespace myri {
	template<class iterator, class Ref, class Ptr>		// 反向迭代器为正向迭代器适配器，模板参数为正向迭代器
	struct __reverse_iterator {
		typedef __reverse_iterator<iterator, Ref, Ptr> reverse_iterator;

		iterator rit;
		__reverse_iterator(iterator i = nullptr)
			:rit(i)
		{}

		reverse_iterator& operator++() {
			--rit;
			return *this;
		}
		reverse_iterator operator++(int) {
			reverse_iterator tmp(*this);		// 对象默认拷贝构造给临时对象tmp
			--rit;
			return tmp;							// 默认析构，但不影响
		}
		reverse_iterator& operator--() {
			++rit;
			return *this;
		}
		reverse_iterator operator--(int) {
			reverse_iterator tmp(*this);
			++rit;
			return tmp;
		}

		Ref operator*() {
			iterator tmp(rit);		// 拷贝构造，默认构造都是可以的
			--tmp;					// 对称设计，需要访问当前指向结点的前一个进行数据的解引用访问
			return *tmp;
		}
		Ptr operator->() {
			return &(operator*());
		}

		bool operator==(const reverse_iterator& t) const {
			return rit == t.rit;
		}
		bool operator!=(const reverse_iterator& t) const {
			return !(operator==(t));
		}
	};
}
#endif //  __REVERSE_ITERATOR_H