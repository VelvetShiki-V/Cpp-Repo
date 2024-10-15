#ifndef __MY_PRIORITY_QUEUE_H
#define __MY_PRIORITY_QUEUE_H
#pragma once
#include"stack.h"

namespace myfunctor {
	template<class T>
	struct less {
		bool operator()(const T& left, const T& right) {
			return left < right;
		}
	};

	template<class T>
	struct greater {
		bool operator()(const T& left, const T& right) {
			return left > right;
		}
	};
}

namespace mypq {
	template<class T, class Container = vector<T>, class Compare = myfunctor::less<T>>
	class priority_queue {
	public:
		priority_queue() {
			std::cout << "调用构造函数：priority_queue()" << std::endl;
		}
		template<class InputIterator>
		priority_queue(InputIterator first, InputIterator last) {
			std::cout << "调用构造函数：priority_queue(InputIterator first, InputIterator last)" << std::endl;
			while (first != last) {
				m_cont.push_back(*first);
				++first;
			}
			int root = (m_cont.size() - 2) / 2;
			while (root >= 0) {
				adjustdown(root);
				--root;
			}
		}
		void push(const T& x) {
			m_cont.push_back(x);
			if(m_cont.size() > 1) adjustup(m_cont.size() - 1);
		}
		void adjustup(size_t child) {
			size_t parent = (child - 1) / 2;
			Compare COM;
			while (child) {
				if (COM(m_cont[parent], m_cont[child])) {
					std::swap(m_cont[child], m_cont[parent]);
					child = parent;
					parent = (parent - 1) / 2;
				}
				else {
					break;
				}
			}
		}
		void pop() {
			std::swap(m_cont[0], m_cont.back());
			m_cont.pop_back();
			adjustdown(0);
		}
		void adjustdown(size_t parent) {
			size_t lchild = parent * 2 + 1;
			Compare COM;
			while (lchild < m_cont.size()) {
				size_t rchild = lchild + 1;
				if (rchild < m_cont.size() && COM(m_cont[lchild], m_cont[rchild])) {
					lchild++;
				}
				if (COM(m_cont[parent], m_cont[lchild])) {
					std::swap(m_cont[lchild], m_cont[parent]);
					parent = lchild;
					lchild = lchild * 2 + 1;
				}
				else {
					break;
				}
			}
		}
		T& top() {
			return m_cont[0];
		}
		const T& top() const {
			return m_cont[0];
		}
		const size_t size() const {
			return m_cont.size();
		}
		bool empty() const {
			return m_cont.empty();
		}
	private:
		Container m_cont;
	};
}
#endif //  __MY_PRIORITY_QUEUE_H