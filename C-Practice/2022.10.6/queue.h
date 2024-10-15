#ifndef __QUEUE_H
#define __QUEUE_H
#pragma once
#include"stack.h"

template<class T, class Container = deque<T>>			// container有缺省参数deque，双端队列
class Queue
{
public:
	void push(const T& x) {
		m_cont.push_back(x);
	}
	void pop() {
		m_cont.pop_front();		// 因为vector没有pop_front，所以vector不能用作queue的容器底层
	}
	T& back() {
		return m_cont.back();
	}
	T& front() {
		return m_cont.front();
	}
	bool empty() const {
		return m_cont.empty();
	}
	size_t size() const {
		return m_cont.size();
	}

private:
	Container m_cont;
};




#endif // __QUEUE_H