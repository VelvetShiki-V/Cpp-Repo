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
		mystring(const char* str = "")			//��ʹ�ó�ʼ���б���Ϊ���ϸ�������˳����
		{
			_size = strlen(str);
			_capacity = _size;
			_str = new char[_capacity + 1];
			strcpy(_str, str);
		}

		//�������촫ͳд��
		//mystring(const mystring& str)
		//	:_str(new char[str._capacity + 1])			//capacity��ʵ�ʴ洢��Ч�������������ռ�Ҫ�࿪һ����\0
		//	,_capacity(str._capacity)
		//	,_size(str._size)
		//{		
		//	memcpy(_str, str._str, _capacity + 1);		//ʹ��memcpy������capacity�����������޷���λ��\0
		//	//strcpy(_str, str._str);
		//}

		//���������ִ�д����tmp���ˣ�
		mystring(const mystring& str)					
			:_str(nullptr)
			, _size(0)
			, _capacity(0)
		{
			mystring tmp(str._str);
			swap(tmp);									//�ɶ�����õ�this->swap(tmp);
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

		//string��Ա����
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
		inline void swap(mystring& tmp)						//���Աswap����
		{
			std::swap(_str, tmp._str);
			::swap(_size, tmp._size);						//Ĭ���޶���::Ϊȫ��swap��std�ɼӿɲ���
			::swap(_capacity, tmp._capacity);
		}
		static size_t npos;		//��̬����ֻ�������ⶨ�壬����const static���Ը�ȱʡֵ���ڳ�ʼ���б��壨������
	private:
		char* _str;
		size_t _size;
		size_t _capacity;
	};
	ostream& operator<<(ostream& out, const mystring& s);		//����ȡ�Ͳ��벻һ����Ϊ�����Ԫ����
	istream& operator>>(istream& in, mystring& s);
}