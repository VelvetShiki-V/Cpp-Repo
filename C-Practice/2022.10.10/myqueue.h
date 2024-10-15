#pragma once
#include"stack.h"

namespace myqueue {
	template<class T, class Container = deque<T>>
	class queue {
	public:
		queue() {
			std::cout << "调用构造函数：queue()" << std::endl;
		}
		queue(const Container& cont)
			:m_cont(cont)
		{
			std::cout << "调用构造函数：queue(const Container& cont)" << std::endl;
		}
		void push(const T& x) {
			m_cont.push_back(x);
		}
		void pop() {
			m_cont.pop_front();
		}
		T& front() {
			return m_cont.front();
		}
		T& back() {
			return m_cont.back();
		}
		const T& front() const {
			return m_cont.front();
		}
		const T& back() const {
			return m_cont.back();
		}
		size_t size() const {
			return m_cont.size();
		}
		bool empty() const {
			return m_cont.empty();
		}
	private:
		Container m_cont;
	};
}