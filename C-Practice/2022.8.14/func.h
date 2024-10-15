#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include<iostream>
#include<string>
#include<assert.h>
using namespace std;

namespace myspace
{
	class mystring
	{
	public:
		mystring(const char* str = "")			//不使用初始化列表，因为它严格按照声明顺序定义
		{
			_size = strlen(str);
			_capacity = _size;
			_str = new char[_capacity + 1];
			strcpy(_str, str);
		}

		//拷贝构造传统写法
		//mystring(const mystring& str)
		//	:_str(new char[str._capacity + 1])			//capacity是实际存储有效数据容量，开空间要多开一个给\0
		//	,_capacity(str._capacity)
		//	,_size(str._size)
		//{		
		//	memcpy(_str, str._str, _capacity + 1);		//使用memcpy必须用capacity拷贝，否则将无法定位到\0
		//	//strcpy(_str, str._str);
		//}

		//拷贝构造现代写法（tmp打工人）
		mystring(const mystring& str)					
			:_str(nullptr)
			, _size(0)
			, _capacity(0)
		{
			mystring tmp(str._str);
			swap(tmp);									//由对象调用的this->swap(tmp);
		}

		~mystring()
		{
			delete[] _str;
			_str = nullptr;
			_size = _capacity = 0;
		}


		typedef char* iterator;
		typedef char* reverse_iterator;
		typedef const char* const_iterator;

		//string成员函数
		iterator begin();
		iterator end();
		reverse_iterator rbegin();
		reverse_iterator rend();
		const_iterator cbegin();
		const_iterator cend();
		size_t size()const;
		void reserve(size_t capacity);
		void resize(size_t newsize, char c = '\0');
		void push_back(char c);
		mystring& operator+=(char c);
		mystring& operator+=(const char* str);
		size_t capacity()const;
		void append(const char* s);
		mystring& insert(size_t pos, char c);
		mystring& insert(size_t pos, const char* s);
		mystring& erase(size_t pos, size_t len = npos);
		void clear();
		bool empty();
		char& operator[](size_t pos);
		const char& operator[](size_t pos)const;
		const char* c_str()const;
		size_t find(char c, size_t pos = 0)const;
		size_t find(const char* str, size_t pos = 0)const;
		mystring substr(size_t pos = 0, size_t len = npos) const;
		mystring& operator=(mystring str);
		bool operator>(const mystring& s)const;
		bool operator==(const mystring& s)const;
		bool operator<(const mystring& s)const;
		bool operator>=(const mystring& s)const;
		bool operator<=(const mystring& s)const;
		bool operator!=(const mystring& s)const;
		inline void swap(mystring& tmp)						//类成员swap函数
		{
			std::swap(_str, tmp._str);
			::swap(_size, tmp._size);						//默认限定符::为全局swap，std可加可不加
			::swap(_capacity, tmp._capacity);
		}
		static size_t npos;		//静态变量只能在类外定义，但是const static可以给缺省值，在初始化列表定义（特例）
	private:
		char* _str;
		size_t _size;
		size_t _capacity;
	};
	ostream& operator<<(ostream& out, const mystring& s);		//流提取和插入不一定成为类的友元函数
	istream& operator>>(istream& in, mystring& s);
}