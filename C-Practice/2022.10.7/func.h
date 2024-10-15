#ifndef __FUNC_H
#define __FUNC_H
#pragma once
#include<iostream>
#include<list>
#include<algorithm>
#include<assert.h>

namespace mylist {							// listģ��ʵ�ֵ������ռ�
	// ��������
	template<class T>
	struct List_node {						// ���ṹ��struct�����Թ������ڸ�listȡֵ
		List_node (const T& data = T())		// �����ֵ��ȱʡ��ʼ��Ϊ��������Ĭ��ֵ
			:m_data(data)
			,m_next(nullptr)				// �ṹ��ָ����ÿ�
			,m_prev(nullptr)
		{}
		// �������
		T m_data;
		List_node<T>* m_next;				// ���ṹ��ָ��
		List_node<T>* m_prev;
	};

	// ��������
	template<class T, class Ref, class Ptr>	// ����ģ������ṩ����
	struct __List_iterator {
		typedef List_node<T> Node;
		typedef __List_iterator<T, Ref, Ptr> iterator;
		__List_iterator(Node* node)			// ������Ĭ�Ϲ��캯������ĳ�����ĵ�ַ��Ϊ��ʼֵ����ȱʡ
			:m_node(node)
		{}

		iterator& operator++() {			// ������ǰ������
			m_node = m_node->m_next;
			return *this;
		}

		iterator operator++(int) {		// ��������������
			iterator tmp = *this;		// Ҳ����дΪiterator tmp(*this)
			m_node = m_node->m_next;
			return tmp;
		}

		iterator& operator--() {			// ������ǰ���Լ�
			m_node = m_node->m_prev;
			return *this;
		}

		iterator operator--(int) {			// �����Լ�
			iterator tmp(*this);
			m_node = m_node->m_prev;
			return tmp;
		}

		Ref operator*() {					// �����������ã�����ֵΪģ�������������ͨ��������const��������->ͬ��
			return m_node->m_data;
		}

		Ptr operator->() {					// �ṹ����ʲ��������أ����������⴦������ʱʡ��һ��->(Ϊ�˿ɶ���)
			return &(operator*());			// ���ص�ַ
		}

		bool operator!=(const iterator& it)const {		// ������ֵ�Ա�
			return m_node != it.m_node;
		}

		bool operator==(const iterator& it)const {
			return m_node == it.m_node;
		}

		// ���������ԣ�������
		Node* m_node;
	};

	// �����������
	template<class iterator, class Ref, class Ptr>
	struct __Reverse_iterator {
		typedef __Reverse_iterator<iterator, Ref, Ptr> Riterator;

		iterator m_cur;

		// ���������Ĭ�Ϲ���
		__Reverse_iterator(iterator it)
			:m_cur(it)
		{}

		// �������������
		Riterator operator++() {
			--m_cur;
			return *this;
		}
		Riterator operator++(int) {
			auto tmp = m_cur;
			--m_cur;
			return Riterator(tmp);
		}

		// ����������Լ�
		Riterator operator--() {
			++m_cur;
			return *this;
		}
		Riterator operator--(int) {
			auto tmp = m_cur;
			++m_cur;
			return Riterator(tmp);
		}

		// ���������������
		Ref operator*() {
			auto tmp = m_cur;
			--tmp;
			return *tmp;
		}
		Ptr operator->() {
			return &(m_cur.operator*());
		}

		// ��������Ȼ򲻵�
		bool operator==(const Riterator& rit) const {
			return m_cur == rit.m_cur;
		}
		bool operator!=(const Riterator& rit) const {
			return m_cur != rit.m_cur;
		}
	};

	// ������
	template<class T>
	class List {
	public:
		// ��������
		typedef List_node<T> Node;
		// ���������ģ����
		typedef __List_iterator<T, T&, T*> iterator;
		typedef __List_iterator<T, const T&, const T*> const_iterator;
		// ���������ģ����
		typedef __Reverse_iterator<iterator, T&, T*> reverse_iterator;
		typedef __Reverse_iterator<const_iterator, const T&, const T*> const_reverse_iterator;

		// �����޲�Ĭ�Ϲ���
		List() {
			empty_initialization();
		}

		// ͨ������������Ĭ�Ϲ���
		template<class InputIterator>
		List(InputIterator first, InputIterator last) {
			empty_initialization();
			while (first != last) {
				push_back(*first);
				first++;
			}
		}

		// �ڱ�λͷ����ʼ��
		void empty_initialization() {
			m_head = new Node;
			m_head->m_next = m_head;
			m_head->m_prev = m_head;
		}

		// ��������
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

		// ��������
		List(const List<T>& lt) {		// ģ�����List��<T>���Բ���Щ����Ϊ��������������������д�ϣ����ִ�����ͳһ
			empty_initialization();
			List<T> tmp(lt.cbegin(), lt.cend());
			swap(tmp);
		}

		// ������
		void swap(List<T>& x) {
			std::swap(m_head, x.m_head);
		}

		// ��ֵ����
		List<T>& operator=(List<T> lt) {
			swap(lt);
			return *this;
		}

		// β��
		void push_back(const T& data) {				// ����β��
			//Node* newnode = new Node(data);
			//newnode->m_next = m_head;
			//newnode->m_prev = m_head->m_prev;
			//m_head->m_prev->m_next = newnode;
			//m_head->m_prev = newnode;
			insert(end(), data);					// ����insert
		}

		void push_front(const T& data) {			// ͷ��
			insert(begin(), data);
		}

		void pop_back() {
			erase(--end());
		}

		void pop_front() {
			erase(begin());
		}

		iterator begin() {							// ��������,��ͷ����һ��
			return iterator(m_head->m_next);
		}

		iterator end() {							// ������β����ͷ���
			return iterator(m_head);
		}

		const_iterator cbegin()const {
			return const_iterator(m_head->m_next);
		}

		const_iterator cend()const {
			return const_iterator(m_head);
		}

		reverse_iterator rbegin() {
			return reverse_iterator(end());
		}

		reverse_iterator rend() {
			return reverse_iterator(begin());
		}

		const_reverse_iterator crbegin() {
			return const_reverse_iterator(cend());
		}

		const_reverse_iterator crend() {
			return const_reverse_iterator(cbegin());
		}

		// ������
		iterator insert(iterator pos, const T& data) {
			Node* newnode = new Node(data);
			newnode->m_next = pos.m_node;
			newnode->m_prev = pos.m_node->m_prev;
			pos.m_node->m_prev->m_next = newnode;
			pos.m_node->m_prev = newnode;
			return iterator(newnode);
		}
		
		// �������
		iterator erase(iterator pos) {
			assert(pos != end());		// ���ܲ�ͷ���
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