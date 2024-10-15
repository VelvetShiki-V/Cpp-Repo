#ifndef __LIST_H
#define __LIST_H 
#pragma once
#include<iostream>
#include<assert.h>
#include<vector>
#include<string>
#include"reverse_iterator.h"
using namespace std;

namespace mylist {
	// 链表结点类
	template<class T>
	struct __list_node {
		typedef __list_node<T> Node;

		//public域结点属性
		T data;
		Node* next;
		Node* prev;

		// 构造函数
		__list_node(const T& x = T())		// 默认构造为类型缺省的数值和结点指针初始化
			:data(x)
			,next(nullptr)
			,prev(nullptr)
		{
			// cout << "调用结点构造函数: __list_node(const T& x = T())" << endl;
		}
	};

	// 链表正向迭代器类
	template<class T, class Ref, class Ptr>		// 三个模板参数，分别提供数据类型，const或非const引用和指针
	struct __list_iterator {
		typedef __list_iterator<T, Ref, Ptr> iterator;		// 使用到结点类创建成员属性iter，因为迭代器本质是结点指针
		typedef __list_node<T> Node;
		Node* iter;
		__list_iterator(Node* node = nullptr)	// 迭代器默认构造，接收来自begin或end传来的匿名对象结点地址
			:iter(node)
		{
			// cout << "调用迭代器构造函数: __list_iterator(Node* node = nullptr)" << endl;
		}
		iterator& operator++() {		// 引用返回可连续使用
			iter = iter->next;
			return *this;
		}
		iterator operator++(int) {
			Node* tmp = iter;			// 对象默认拷贝构造给临时对象tmp	
			iter = iter->next;
			return iterator(tmp);		// 默认析构匿名对象，但不影响
		}
		iterator& operator--() {
			iter = iter->prev;
			return *this;
		}
		iterator operator--(int) {
			iterator tmp(iter);
			iter = iter->prev;
			return tmp;
		}
		Ref operator*() {				// 访问迭代器指向结点数据
			return iter->data;
		}
		Ptr operator->() {				// 获取结点内部数据地址
			return &(operator*());
		}
		bool operator==(const iterator& it) const {
			return iter == it.iter;
		}
		bool operator!=(const iterator& it) const {
			return !(operator==(it));
		}
	};

	// 链表类
	template<class T>
	class list {
	public:
		// 引用其他类
		typedef __list_node<T> Node;
		typedef __list_iterator<T, T&, T*> iterator;
		typedef __list_iterator<T, const T&, const T*> const_iterator;		// 只有T&, T*返回，加const修饰禁止修改
		typedef myri::__reverse_iterator<iterator, T&, T*> reverse_iterator;			// 反向迭代器
		typedef myri::__reverse_iterator<iterator, const T&, const T*> const_reverse_iterator;		// 反向迭代器const

		list() {							// 无参构造
			cout << "调用构造函数: list()" << endl;
			empty_initialization();
		}
		void empty_initialization() {
			m_head = new Node;
			m_head->next = m_head;
			m_head->prev = m_head;
		}

		template<class InputIterator>		// 迭代器区间初始化构造
		list(InputIterator first, InputIterator last) {
			cout << "调用构造函数: list(InputIterator first, InputIterator last)" << endl;
			empty_initialization();
			while (first != last) {
				push_back(*first);
				++first;
			}
		}

		list(const list<T>& ls) {			// 拷贝构造
			cout << "调用拷贝构造函数: list(const list<T>& ls)" << endl;
			empty_initialization();
			list<T> tmp(ls.cbegin(), ls.cend());
			swap(tmp);
		}

		~list() {
			cout << "调用析构函数: ~list()" << endl;
			clear();
			delete m_head;
			m_head = nullptr;
		}

		list& operator=(const list& x) {
			cout << "调用赋值重载: list& operator=(const list& x)" << endl;
			list<T> tmp(x.cbegin(), x.cend());
			swap(tmp);
			return *this;
		}

		void swap(list& x) {
			std::swap(m_head, x.m_head);
		}

		void push_back(const T& x) {		// 链表尾插
			//Node* new_node = new Node(x);
			//Node* tail = m_head->prev;
			//new_node->next = m_head;
			//new_node->prev = tail;
			//tail->next = new_node;
			//m_head->prev = new_node;
			insert(end(), x);				// insert为在指定pos的前一个位置插入
		}
		void pop_back() {
			//if (empty()) {
			//	return;
			//}
			//Node* tail = m_head->prev, *new_tail = tail->prev;
			//delete tail;
			//new_tail->next = m_head;
			//m_head->prev = new_tail;
			erase(--end());					// erase为擦除pos结点，并链接前后的双向结点
		}
		void push_front(const T& x) {
			//Node* first = m_head->next;
			//Node* new_first = new Node(x);
			//new_first->next = first;
			//new_first->prev = m_head;
			//first->prev = new_first;
			//m_head->next = new_first;
			insert(begin(), x);
		}
		void pop_front() {
			//if (empty()) return;
			//Node* first = m_head->next, * new_first = first->next;
			//delete first;
			//m_head->next = new_first;
			//new_first->prev = m_head;
			erase(begin());
		}
		T& front() {
			assert(!empty());			// Calling this function on an empty container causes undefined behavior.
			return m_head->next->data;
		}
		T& back() {
			assert(!empty());
			return m_head->prev->data;
		}
		const T& front() const {
			assert(!empty());
			return m_head->next->data;
		}
		const T& back() const {
			assert(!empty());
			return m_head->prev->data;
		}
		bool empty() {
			return !size();
		}
		size_t size() {
			size_t cnt = 0;
			for (auto e : *this) {
				++cnt;
			}
			return cnt;
		}

		// 正向迭代器
		iterator begin() {
			return iterator(m_head->next);
		}
		const_iterator cbegin() const {			// 加上const可以重载
			return const_iterator(m_head->next);
		}
		iterator end() {
			return iterator(m_head);
		}
		const_iterator cend() const {
			return const_iterator(m_head);
		}

		// 反向迭代器
		reverse_iterator rbegin() {
			return reverse_iterator(m_head);
		}
		reverse_iterator rend() {
			return reverse_iterator(m_head->next);
		}
		const_reverse_iterator crbegin() const {
			return reverse_iterator(m_head);
		}
		const_reverse_iterator crend() const {
			return reverse_iterator(m_head->next);
		}

		// 插入
		iterator insert(iterator pos, const T& x) {
			Node* pos_node = pos.iter, * pos_front = pos_node->prev;
			Node* insert_node = new Node(x);
			insert_node->next = pos_node;
			insert_node->prev = pos_front;
			pos_front->next = insert_node;
			pos_node->prev = insert_node;
			return iterator(insert_node);
		}
		iterator erase(iterator pos) {
			assert(pos != end());
			Node* pos_node = pos.iter;
			Node* pos_front = pos_node->prev, * pos_back = pos_node->next;
			delete pos_node;
			pos_front->next = pos_back;
			pos_back->prev = pos_front;
			return iterator(pos_back);
		}
		void clear() {
			iterator it = begin();
			while (!empty()) {
				it = erase(it);
			}
		}
		void resize(size_t n, T val = T()) {
			assert(n >= 0);
			iterator it = begin();
			if (n > size()) {
				size_t cnt = n - size();
				while (cnt) {
					it = insert(end(), val);
					--cnt;
				}
			}
			else if (n < size()) {
				for (size_t i = 0; i < n; i++) {
					it++;
				}
				while(it != end())
					it = erase(it);
			}
		}
	private:
		Node* m_head;
	};
}
#endif //  __LIST_H