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
		cout << "newSpace()" << endl;
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

namespace myptr {
	template<class T>
	class shared_ptr {
	public:
		// �����ȱʡ������ָ��Ĭ��Ϊ1����ʾ����Դ������1�α�����
		shared_ptr(T* p = nullptr)
			:m_ptr(p)
			,cnt(new int(1))
		{
			cout << "shared_ptr(T*& p = nullptr)" << endl;
		}
		// �������콫����Դ����ָ��������Դ�ռ�ͼ���ָ�붼ǳ����������ָ�����++
		shared_ptr(const shared_ptr<T>& sp)
			:m_ptr(sp.m_ptr)
			,cnt(sp.cnt)
		{
			(*cnt)++;
			cout << "shared_ptr(const shared_ptr<T>& sp)" << endl;
		}
		// ��ֵ������Ҫע�⿽��Ŀ������ָ������Ƿ��Ѿ������ƹ���Դ������������Ҫ�����´���
		shared_ptr<T>& operator=(const shared_ptr<T>& sp) {
			if (m_ptr == sp.m_ptr) return *this;
			if (--(*cnt) == 0) {
				delete m_ptr;
				delete cnt;
				//cout << "���һ������ָ�������������Դ�ٱ���ֵ" << endl;
			}
			// �������Լ���Ϊ0��˵��������ָ�����ҪôΪ�գ�Ҫô��������Դ��������ָ��ָ�����
			m_ptr = sp.m_ptr;
			cnt = sp.cnt;
			(*cnt)++;
			return *this;
		}
		// ��ָ������Լ�Ϊ0ʱ����Ҫ����Դ��������ͷ�
		~shared_ptr() {
			if (--*(cnt) == 0) {
				delete m_ptr;
				delete cnt;
				cout << "~shared_ptr()" << endl;
			}
			else cout << "--*(cnt)" << endl;
		}
		// ����ָ�������ָ��һ������Ϊ����
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
		//static int cnt = 0;		// ����ʹ�þ�̬��������Ϊ��������ȫ����ģ���������ָ����󶼿�ʹ��
	};
	
	template<class T>
	class weak_ptr {
	public:
		// �޲ι��죬shared_ptr����
		weak_ptr()
			:m_ptr(nullptr)
		{}
		weak_ptr(const shared_ptr<T>& sp)
			:m_ptr(sp.get())
		{}
		// ��������
		weak_ptr(const weak_ptr<T>& wp)
			:m_ptr(wp.m_ptr)
		{}
		// ��ֵ����
		weak_ptr<T>& operator=(shared_ptr<T>& sp) {
			m_ptr = sp.get();
			return *this;
		}
		// weak_ptr��������Դ�Ĺ����ͷţ��˴���ӡ��Ϊ�˹۲�
		~weak_ptr() {
			cout << "~weak_ptr" << endl;
		}
		// ����ָ��һ������Ϊ
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
	myptr::weak_ptr<Node> next;		// weak_ptr��������Դ�ͷţ�����shared_ptr������delete�����ͷ�
	myptr::weak_ptr<Node> prev;
	~Node() {						// Ϊ�˹۲죬�Ƿ�deleteʶ������������ͷ�
		cout << "~Node()" << endl;
	}
	//shared_ptr<Node> next;		// ������shared_ptr���������Ӽ��������ѭ������
	//shared_ptr<Node> prev;
};