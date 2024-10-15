#ifndef __REVERSE_ITERATOR_H
#define __REVERSE_ITERATOR_H
#pragma once
#include"list.h"

namespace myri {
	template<class iterator, class Ref, class Ptr>		// ���������Ϊ�����������������ģ�����Ϊ���������
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
			reverse_iterator tmp(*this);		// ����Ĭ�Ͽ����������ʱ����tmp
			--rit;
			return tmp;							// Ĭ������������Ӱ��
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
			iterator tmp(rit);		// �������죬Ĭ�Ϲ��춼�ǿ��Ե�
			--tmp;					// �Գ���ƣ���Ҫ���ʵ�ǰָ�����ǰһ���������ݵĽ����÷���
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