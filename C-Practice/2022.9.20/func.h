#ifndef __FUNC_H
#define __FUNC_H
#pragma once
#include<iostream>
#include<list>
#include<algorithm>

namespace mylist {							// listģ��ʵ�������ռ�
	// ��������
	template<class T>
	struct List_node {						// ���ṹ��
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
	template<class T>
	struct __List_iterator {
		typedef List_node<T> Node;
		typedef __List_iterator<T> iterator;
		__List_iterator(Node* node)		// ������Ĭ�Ϲ��캯������ĳ�����ĵ�ַ��Ϊ��ʼֵ����ȱʡ
			:m_node(node)
		{}

		iterator operator++() {			// ������ǰ������
			m_node = m_node->m_next;
			return *this;
		}

		iterator operator++(int) {		// ��������������
			Node* tmp = *this;			// Ҳ����дΪNode* tmp(*this)
			m_node = m_node->m_next;
			return tmp;
		}

		T& operator*() {				// ������������
			return m_node->m_data;
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

	// ������
	template<class T>
	class List {
	public:
		typedef __List_iterator<T> iterator;
		List()										// �����޲�Ĭ�Ϲ���
		{
			m_head = new Node;
			m_head->m_next = m_head;
			m_head->m_prev = m_head;
		}

		void push_back(const T& data) {				// ����β�� tail  head  next
			Node* newnode = new Node(data);
			newnode->m_next = m_head;
			newnode->m_prev = m_head->m_prev;
			m_head->m_prev->m_next = newnode;
			m_head->m_prev = newnode;
		}

		iterator begin()const {						// ��������
			return iterator(m_head->m_next);
		}

		iterator end()const {						// ������β
			return iterator(m_head);
		}
	private:
		typedef List_node<T> Node;
		Node* m_head;
	};
}

#endif	// __FUNC_H