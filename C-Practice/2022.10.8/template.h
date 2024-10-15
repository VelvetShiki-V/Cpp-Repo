#ifndef __TEMPLATE_H
#define __TEMPLATE_H
#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<list>
using namespace std;

// 函数模板标准
template<class T>
bool LESS(T a, T b) {
	return a < b;
}
// int*特化
template<>
bool LESS<int*>(int* a, int* b) {
	return *a < *b;
}
// char*特化
template<>
bool LESS<char*>(char* a, char* b) {
	return *a < *b;
}

// 多类型函数模板标准
template<class T1, class T2>
void print(T1 a, T2 b) {
	cout << a << " " << b << endl;
}

// double, string特化
template<>
void print<double, string>(double a, string b) {
	cout << a << " " << b << endl;
}

// string, string特化
template<>
void print<string, string>(string a, string b) {
	for (auto e : a) {
		cout << e << " ";
	}
	cout << endl;
	for (auto f : b) {
		cout << f << " ";
	}
	cout << endl;
}

// vector<int>, list<int>特化
template<>
void print<vector<int>, list<int>>(vector<int> a, list<int> b) {
	for(auto e : a) {
		cout << e << " ";
	}
	cout << endl;
	for (auto f : b) {
		cout << f << " ";
	}
}

// vector<char>, list<string>特化
template<>
void print<vector<char>, list<string>>(vector<char> a, list<string> b) {
	for (auto e : a) {
		cout << e;
	}
	for (auto f : b) {
		cout << f << " ";
	}
}

// 类模板原型
template<class T1, class T2>
class template_specialization {
public:
	template_specialization(const T1& val1, const T2& val2) {		// 必须显示传值初始化，否则默认构造歧义
		m_mem1 = val1;
		m_mem2 = val2;
		cout << "默认构造类型：template_specialization(const T1& val1, const T2& val2)" << endl;
	}
private:
	T1 m_mem1;
	T2 m_mem2;
};

// int*, char*模板特化（全特化）
template<>
class template_specialization<int*, char*> {
public:
	template_specialization(int*& val1, char*& val2)
		:m_mem1(val1)
		,m_mem2(val2)
	{
		cout << "全特化构造类型：template_specialization(int*& val1, char*& val2)" << endl;
	}
private:
	int* m_mem1;
	char* m_mem2;
};

// 模板偏特化
template<class T>
class template_specialization<T, vector<int>> {
public:
	template_specialization(T& val1, vector<int>& val2)
		:m_mem1(val1)
		,m_mem2(val2)
	{
			cout << "偏特化构造类型：template_specialization(const T& val1, vector<int>& val2)" << endl;
	}
private:
	T m_mem1;
	vector<int> m_mem2;
};

// 模板参数限制偏特化
template<class T1, class T2>
class template_specialization<T1*, T2*> {
public:
	template_specialization(T1*& val1, T2*& val2)
		:m_mem1(val1)
		,m_mem2(val2)
	{
		cout << "偏特化构造类型：template_specialization(T1*& val1, T2*& val2)" << endl;
	}
private:
	T1* m_mem1;
	T2* m_mem2;
};
#endif // __TEMPLATE_H