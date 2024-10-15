#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <map>
using namespace std;

class newSpace {
public:
	int a = 0;
	newSpace()
		:p1(new int[5])
		,p2(new int)
	{
		//cout << "newSpace()" << endl;
	}
	~newSpace() {
		cout << "~newSpace()" << endl;
		delete[] p1;
		delete p2;
	}
private:
	int* p1;
	int* p2;
};

// 定制删除器仿函数
template<class T>
struct deleteSpace {
	void operator()(T* p) {
		cout << "delete[] p" << endl;
		delete[] p;
	}
};

template<class T>
struct deleteSg {
	void operator()(T* p) {
		cout << "delete p" << endl;
		delete p;
	}
};

template<class T>
struct Free {
	void operator()(T* p) {
		cout << "Free T" << endl;
		free(p);
	}
};

struct FileDelete {
	void operator()(FILE* fp) {
		cout << "FileDelete" << endl;
		fclose(fp);
	}
};

namespace myptr {
	template<class T, class D = deleteSg<T>>
	class shared_ptr {
	public:
		// 构造给缺省，计数指针默认为1，表示该资源区共有1次被管理
		shared_ptr(T* p = nullptr)
			:m_ptr(p)
			,cnt(new int(1))
		{
			//cout << "shared_ptr(T*& p)" << endl;
		}
		// 拷贝构造将拷贝源智能指针对象的资源空间和计数指针都浅拷贝，并将指针计数++
		shared_ptr(const shared_ptr<T>& sp)
			:m_ptr(sp.m_ptr)
			,cnt(sp.cnt)
		{
			(*cnt)++;
			cout << "shared_ptr(const shared_ptr<T>& sp)" << endl;
		}
		// 赋值重载需要注意拷贝目标智能指针对象是否已经存在掌管资源区，若存在需要做如下处理
		shared_ptr<T>& operator=(const shared_ptr<T>& sp) {
			if (m_ptr == sp.m_ptr) return *this;
			if (--(*cnt) == 0) {
				D()(m_ptr);		// 单个对象默认default_delete,多个对象使用定制删除器
				delete cnt;
				//cout << "最后一个智能指针对象，先清理资源再被赋值" << endl;
			}
			// 计数器自减后不为0，说明该智能指针对象要么为空，要么所管理资源仍有其他指针指向管理
			m_ptr = sp.m_ptr;
			cnt = sp.cnt;
			(*cnt)++;
			return *this;
		}
		// 当指针计数自减为0时，需要对资源区清理和释放
		~shared_ptr() {
			if (--*(cnt) == 0) {
				D()(m_ptr);
				delete cnt;
				cout << "~shared_ptr()" << endl;
			}
			else cout << "--*(cnt)" << endl;
		}
		// 智能指针具有像指针一样的行为功能
		T& operator*() {
			return *m_ptr;
		}
		T* operator->() {
			return m_ptr;
		}
		int use_count() {
			return *(cnt);
		}
		T* get() {
			return m_ptr;
		}
	private:
		T* m_ptr;
		int* cnt;
		//static int cnt = 0;		// 不能使用静态变量，因为它是类内全局域的，所有智能指针对象都可使用
	};
	
	template<class T>
	class weak_ptr {
	public:
		// 无参构造，shared_ptr构造
		weak_ptr()
			:m_ptr(nullptr)
		{}
		weak_ptr(const shared_ptr<T>& sp)
			:m_ptr(sp.get())
		{}
		// 拷贝构造
		weak_ptr(const weak_ptr<T>& wp)
			:m_ptr(wp.m_ptr)
		{}
		// 赋值重载
		weak_ptr<T>& operator=(shared_ptr<T>& sp) {
			m_ptr = sp.get();
			return *this;
		}
		// weak_ptr不参与资源的管理释放，此处打印仅为了观察
		~weak_ptr() {
			cout << "~weak_ptr" << endl;
		}
		// 具有指针一样的行为
		T& operator*() {
			return *m_ptr;
		}
		T* operator->() {
			return m_ptr;
		}
	private:
		T* m_ptr;
	};
}

template<class T>
struct Node {
	T val;
	myptr::weak_ptr<Node> next;		// weak_ptr不参与资源释放，交给shared_ptr的析构delete处理释放
	myptr::weak_ptr<Node> prev;
	~Node() {						// 为了观察，是否被delete识别调用析构并释放
		cout << "~Node()" << endl;
	}
	//shared_ptr<Node> next;		// 不能用shared_ptr，否则将增加计数，造成循环引用
	//shared_ptr<Node> prev;
};