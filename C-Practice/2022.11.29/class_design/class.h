#pragma once
#include <iostream>
using namespace std;

// 无法被拷贝的类
class A {
public:
	A(const A& a) = delete;
	A& operator=(const A& a) = delete;
private:
	int a;
};

// 仅能在堆上创建对象1
//class B {
//public:
//	static B* create() {
//		cout << "create B through heap" << endl;
//		return new B;
//	}
//	~B() {
//		cout << "~B()" << endl;
//	}
//private:
//	B() {}
//	B(const B& b) {}
//	B& operator=(const B& b){}
//};

// 仅能在堆上创建对象2
class B {
public:
	B()
		:b(0)
	{
		cout << "B()" << endl;
	}
	void destroy() {
		delete this;
		cout << "delete this" << endl;
	}
	void print(){}
	B(const B& b) = delete;
	B& operator=(const B& b) = delete;
private:
	~B() {
		cout << "~B()" << endl;
	}
	int b;
};

// 只能在栈上创建的对象
class StackOnly {
public:
	static StackOnly create() {
		StackOnly s;
		return s;
	}
	void* operator new(size_t n) = delete;
	~StackOnly() {
		cout << "~StackOnly()" << endl;
	}
private:
	StackOnly()
		:a(0)
	{
		cout << "StackOnly()" << endl;
	}
	int a;
};


// 单例类
class Singleton {
public:
	static Singleton* create() {
		return m_obj;
	}
	void* alloc(size_t n) {
		return m_ptr;
	}
	void dealloc(void* ptr) {
		;
	}
	class Garbage {
	public:
		~Garbage() {
			if (m_obj) {
				delete m_obj;
				cout << "~Garbage()" << endl;
			}
		}
	};
private:
	Singleton()
	{}
	char* m_ptr;
	static Singleton* m_obj;
};
Singleton* Singleton::m_obj = new Singleton;
// main函数结束后，垃圾回收器对象会自动调用析构，以代为释放单例对象资源
static Singleton::Garbage gb;