#ifndef __FUNC_H
#define __FUNC_H
#pragma once
#include<iostream>
#include<list>
#include<algorithm>
#include<assert.h>

namespace mylist {							// list模拟实现的命名空间
	// 链表结点类
	template<class T>
	struct List_node {						// 结点结构体struct，属性公开便于给list取值
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
	template<class T, class Ref, class Ptr>	// 三个模板参数提供泛型
	struct __List_iterator {
		typedef List_node<T> Node;
		typedef __List_iterator<T, Ref, Ptr> iterator;
		__List_iterator(Node* node)			// 迭代器默认构造函数，以某个结点的地址作为初始值，无缺省
			:m_node(node)
		{}

		iterator& operator++() {			// 迭代器前置自增
			m_node = m_node->m_next;
			return *this;
		}

		iterator operator++(int) {		// 迭代器后置自增
			iterator tmp = *this;		// 也可以写为iterator tmp(*this)
			m_node = m_node->m_next;
			return tmp;
		}

		iterator& operator--() {			// 迭代器前置自减
			m_node = m_node->m_prev;
			return *this;
		}

		iterator operator--(int) {			// 后置自减
			iterator tmp(*this);
			m_node = m_node->m_prev;
			return tmp;
		}

		Ref operator*() {					// 迭代器解引用，返回值为模板参数，兼容普通迭代器和const迭代器，->同理
			return m_node->m_data;
		}

		Ptr operator->() {					// 结构体访问操作符重载，编译器特殊处理，调用时省略一个->(为了可读性)
			return &(operator*());			// 返回地址
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
		typedef List_node<T> Node;
		typedef __List_iterator<T, T&, T*> iterator;
		typedef __List_iterator<T, const T&, const T*> const_iterator;

		// 链表无参默认构造
		List() {
			empty_initialization();
		}

		// 通过迭代器区间默认构造
		template<class InputIterator>
		List(InputIterator first, InputIterator last) {
			empty_initialization();
			while (first != last) {
				push_back(*first);
				first++;
			}
		}

		// 哨兵位头结点初始化
		void empty_initialization() {
			m_head = new Node;
			m_head->m_next = m_head;
			m_head->m_prev = m_head;
		}

		// 链表析构
		~List() {
			clear();
			delete m_head;
			m_head = nullptr;
		}

		void clear() {
			iterator it = begin();
			while (it != end()) {
				it = erase(it);
			}
		}

		// 拷贝构造
		List(const List<T>& lt) {		// 模板参数List的<T>可以不用些，因为编译器会作处理，但建议写上，保持代码风格统一
			empty_initialization();
			List<T> tmp(lt.cbegin(), lt.cend());
			swap(tmp);
		}

		// 链表交换
		void swap(List<T>& x) {
			std::swap(m_head, x.m_head);
		}

		// 赋值重载
		List<T>& operator=(List<T> lt) {
			swap(lt);
			return *this;
		}

		// 尾插
		void push_back(const T& data) {				// 链表尾插
			//Node* newnode = new Node(data);
			//newnode->m_next = m_head;
			//newnode->m_prev = m_head->m_prev;
			//m_head->m_prev->m_next = newnode;
			//m_head->m_prev = newnode;
			insert(end(), data);					// 复用insert
		}

		void push_front(const T& data) {			// 头插
			insert(begin(), data);
		}

		void pop_back() {
			erase(--end());
		}

		void pop_front() {
			erase(begin());
		}

		iterator begin() {							// 迭代器首,即头结点后一个
			return iterator(m_head->m_next);
		}

		iterator end() {							// 迭代器尾，即头结点
			return iterator(m_head);
		}

		const_iterator cbegin()const {
			return const_iterator(m_head->m_next);
		}

		const_iterator cend()const {
			return const_iterator(m_head);
		}

		// 插入结点
		iterator insert(iterator pos, const T& data) {
			Node* newnode = new Node(data);
			newnode->m_next = pos.m_node;
			newnode->m_prev = pos.m_node->m_prev;
			pos.m_node->m_prev->m_next = newnode;
			pos.m_node->m_prev = newnode;
			return iterator(newnode);
		}
		
		// 擦除结点
		iterator erase(iterator pos) {
			assert(pos != end());		// 不能擦头结点
			pos.m_node->m_prev->m_next = pos.m_node->m_next;
			pos.m_node->m_next->m_prev = pos.m_node->m_prev;
			Node* next = pos.m_node->m_next;
			delete pos.m_node;
			return iterator(next);
		}
	private:
		Node* m_head;
	};
}

#endif	// __FUNC_H