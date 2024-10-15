#pragma once
#include"stack.h"
using namespace std;									// less�Ǵ�ѣ�greater��С��
template<class T, class Container = vector<T>, class Compare = less<T>>
class Priority_queue {
public:
	// ����������
	Priority_queue() {
		;
	}
	template<class InputIterator>
	Priority_queue(InputIterator first, InputIterator last) {
		while (first != last) {
			m_cont.push_back(*first);
			first++;
		}
		// ���½���
		int root = (m_cont.size() - 2) / 2;
		while (root >= 0) {
			adjust_down(root);
			root--;
		}
	}

	// ���
	void push(const T& x) {
		m_cont.push_back(x);
		adjust_up(m_cont.size() - 1);
	}
	// �����ϵ�����ʱ��O(logN)
	void adjust_up(int child) {
		int parent = (child - 1) / 2;
		Compare COM;
		while (child) {
			if (COM(m_cont[parent], m_cont[child])) {
				swap(m_cont[child], m_cont[parent]);
				child = parent;
				parent = (parent - 1) / 2;
			}
			else {
				break;
			}
		}
	}
	void pop() {
		swap(m_cont.front(), m_cont.back());
		m_cont.pop_back();
		adjust_down(0);
	}
	// �����µ�����ʱ��O(logN)
	void adjust_down(int parent) {
		int child = parent * 2 + 1;
		Compare COM;
		while (child < m_cont.size()) {
			if (child + 1 < m_cont.size() && COM(m_cont[child], m_cont[child + 1])) {
				child++;
			}
			if (COM(m_cont[parent], m_cont[child])) {
				swap(m_cont[parent], m_cont[child]);
				parent = child;
				child = child * 2 + 1;
			}
			else {
				break;
			}
		}
	}
	const T& top() {		// ������const���������޸�
		return m_cont[0];
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

namespace myfunctor {
	template<class T>		// ��С
	class less {
	public:
		bool operator()(const T& a, const T& b) const {
			return a < b;
		}
	};

	template<class T>
	class greater {			// �ȴ�
	public:
		bool operator()(const T& a, const T& b) const {
			return a > b;
		}
	};
}