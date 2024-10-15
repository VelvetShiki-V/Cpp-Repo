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
	// ��������
	template<class T>
	struct __list_node {
		typedef __list_node<T> Node;

		//public��������
		T data;
		Node* next;
		Node* prev;

		// ���캯��
		__list_node(const T& x = T())		// Ĭ�Ϲ���Ϊ����ȱʡ����ֵ�ͽ��ָ���ʼ��
			:data(x)
			,next(nullptr)
			,prev(nullptr)
		{
			// cout << "���ý�㹹�캯��: __list_node(const T& x = T())" << endl;
		}
	};

	// ���������������
	template<class T, class Ref, class Ptr>		// ����ģ��������ֱ��ṩ�������ͣ�const���const���ú�ָ��
	struct __list_iterator {
		typedef __list_iterator<T, Ref, Ptr> iterator;		// ʹ�õ�����ഴ����Ա����iter����Ϊ�����������ǽ��ָ��
		typedef __list_node<T> Node;
		Node* iter;
		__list_iterator(Node* node = nullptr)	// ������Ĭ�Ϲ��죬��������begin��end�����������������ַ
			:iter(node)
		{
			// cout << "���õ��������캯��: __list_iterator(Node* node = nullptr)" << endl;
		}
		iterator& operator++() {		// ���÷��ؿ�����ʹ��
			iter = iter->next;
			return *this;
		}
		iterator operator++(int) {
			Node* tmp = iter;			// ����Ĭ�Ͽ����������ʱ����tmp	
			iter = iter->next;
			return iterator(tmp);		// Ĭ�������������󣬵���Ӱ��
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
		Ref operator*() {				// ���ʵ�����ָ��������
			return iter->data;
		}
		Ptr operator->() {				// ��ȡ����ڲ����ݵ�ַ
			return &(operator*());
		}
		bool operator==(const iterator& it) const {
			return iter == it.iter;
		}
		bool operator!=(const iterator& it) const {
			return !(operator==(it));
		}
	};

	// ������
	template<class T>
	class list {
	public:
		// ����������
		typedef __list_node<T> Node;
		typedef __list_iterator<T, T&, T*> iterator;
		typedef __list_iterator<T, const T&, const T*> const_iterator;		// ֻ��T&, T*���أ���const���ν�ֹ�޸�
		typedef myri::__reverse_iterator<iterator, T&, T*> reverse_iterator;			// ���������
		typedef myri::__reverse_iterator<iterator, const T&, const T*> const_reverse_iterator;		// ���������const

		list() {							// �޲ι���
			cout << "���ù��캯��: list()" << endl;
			empty_initialization();
		}
		void empty_initialization() {
			m_head = new Node;
			m_head->next = m_head;
			m_head->prev = m_head;
		}

		template<class InputIterator>		// �����������ʼ������
		list(InputIterator first, InputIterator last) {
			cout << "���ù��캯��: list(InputIterator first, InputIterator last)" << endl;
			empty_initialization();
			while (first != last) {
				push_back(*first);
				++first;
			}
		}

		list(const list<T>& ls) {			// ��������
			cout << "���ÿ������캯��: list(const list<T>& ls)" << endl;
			empty_initialization();
			list<T> tmp(ls.cbegin(), ls.cend());
			swap(tmp);
		}

		~list() {
			cout << "������������: ~list()" << endl;
			clear();
			delete m_head;
			m_head = nullptr;
		}

		list& operator=(const list& x) {
			cout << "���ø�ֵ����: list& operator=(const list& x)" << endl;
			list<T> tmp(x.cbegin(), x.cend());
			swap(tmp);
			return *this;
		}

		void swap(list& x) {
			std::swap(m_head, x.m_head);
		}

		void push_back(const T& x) {		// ����β��
			//Node* new_node = new Node(x);
			//Node* tail = m_head->prev;
			//new_node->next = m_head;
			//new_node->prev = tail;
			//tail->next = new_node;
			//m_head->prev = new_node;
			insert(end(), x);				// insertΪ��ָ��pos��ǰһ��λ�ò���
		}
		void pop_back() {
			//if (empty()) {
			//	return;
			//}
			//Node* tail = m_head->prev, *new_tail = tail->prev;
			//delete tail;
			//new_tail->next = m_head;
			//m_head->prev = new_tail;
			erase(--end());					// eraseΪ����pos��㣬������ǰ���˫����
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

		// ���������
		iterator begin() {
			return iterator(m_head->next);
		}
		const_iterator cbegin() const {			// ����const��������
			return const_iterator(m_head->next);
		}
		iterator end() {
			return iterator(m_head);
		}
		const_iterator cend() const {
			return const_iterator(m_head);
		}

		// ���������
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

		// ����
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