#ifndef __STACK_H
#define __STACK_H
#pragma once
#include<iostream>
#include<vector>
#include<list>
#include<queue>
#include<functional>
#include"myqueue.h"
#include"my_priority_queue.h"
using namespace std;

namespace mystack {
	template<class T, class Container = deque<T>>
	class stack {
	public:
		stack(){
			std::cout << "调用构造函数：stack()" << std::endl;
		}
		stack(const Container& cont)
			:m_cont(cont)
		{
			std::cout << "调用构造函数：stack(const Container& cont)" << std::endl;
		}
		void push(const T& x) {
			m_cont.push_back(x);
		}
		void pop() {
			m_cont.pop_back();
		}
		T& top() {
			return m_cont.back();
		}
		const T& top() const {
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


#endif // __STACK_H