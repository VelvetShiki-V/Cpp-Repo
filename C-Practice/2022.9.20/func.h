#ifndef __FUNC_H
#define __FUNC_H
#pragma once
#include<iostream>
#include<list>
#include<algorithm>

namespace mylist {							// list模拟实现命名空间
	// 链表结点类
	template<class T>
	struct List_node {						// 结点结构体
		List_node (const T& data = T())		// 结点数值域缺省初始化为内置类型默认值
			:m_data(data)
			,m_next(nullptr)				// 结构体指针均置空
			,m_prev(nullptr)
		{}
		// 结点属性
		T m_data;
		List_node<T>* m_next;				// 结点结构体指针
		List_node<T>* m_prev;
	};

	// 迭代器类
	template<class T>
	struct __List_iterator {
		typedef List_node<T> Node;
		typedef __List_iterator<T> iterator;
		__List_iterator(Node* node)		// 迭代器默认构造函数，以某个结点的地址作为初始值，无缺省
			:m_node(node)
		{}

		iterator operator++() {			// 迭代器前置自增
			m_node = m_node->m_next;
			return *this;
		}

		iterator operator++(int) {		// 迭代器后置自增
			Node* tmp = *this;			// 也可以写为Node* tmp(*this)
			m_node = m_node->m_next;
			return tmp;
		}

		T& operator*() {				// 迭代器解引用
			return m_node->m_data;
		}

		bool operator!=(const iterator& it)const {		// 迭代器值对比
			return m_node != it.m_node;
		}

		bool operator==(const iterator& it)const {
			return m_node == it.m_node;
		}

		// 迭代器属性（公共域）
		Node* m_node;
	};

	// 链表类
	template<class T>
	class List {
	public:
		typedef __List_iterator<T> iterator;
		List()										// 链表无参默认构造
		{
			m_head = new Node;
			m_head->m_next = m_head;
			m_head->m_prev = m_head;
		}

		void push_back(const T& data) {				// 链表尾插 tail  head  next
			Node* newnode = new Node(data);
			newnode->m_next = m_head;
			newnode->m_prev = m_head->m_prev;
			m_head->m_prev->m_next = newnode;
			m_head->m_prev = newnode;
		}

		iterator begin()const {						// 迭代器首
			return iterator(m_head->m_next);
		}

		iterator end()const {						// 迭代器尾
			return iterator(m_head);
		}
	private:
		typedef List_node<T> Node;
		Node* m_head;
	};
}

#endif	// __FUNC_H