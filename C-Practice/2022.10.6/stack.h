#ifndef __STACK_H
#define __STACK_H
#pragma once
#include<iostream>
#include<algorithm>
#include<vector>
#include<list>
#include<stack>
#include<deque>
#include<queue>
#include<functional>		// 仿函数
#include"queue.h"
#include"priority_queue.h"
using namespace std;

template<class T, class Container = deque<T>>			// container有缺省参数deque，双端队列
class Stack
{
public:
	void push(const T& x) {
		m_cont.push_back(x);
	}
	void pop() {
		m_cont.pop_back();
	}
	T& top() {
		return m_cont.back();
	}
	const T& top() const{
		return m_cont.back();
	}
	bool empty() const{
		return m_cont.empty();
	}
	size_t size() const{
		return m_cont.size();
	}

private:
	Container m_cont;
};




#endif //  __STACK_H