#pragma once
#include <iostream>
using namespace std;

// �޷�����������
class A {
public:
	A(const A& a) = delete;
	A& operator=(const A& a) = delete;
private:
	int a;
};

// �����ڶ��ϴ�������1
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

// �����ڶ��ϴ�������2
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

// ֻ����ջ�ϴ����Ķ���
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


// ������
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
// main��������������������������Զ������������Դ�Ϊ�ͷŵ���������Դ
static Singleton::Garbage gb;