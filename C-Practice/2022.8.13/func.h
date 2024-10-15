#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
#include<assert.h>
using namespace std;

string stradd(const string& num1, const string& num2);
int lengthOfLastWord(string s);
int firstUniqChar(string s);
bool isPalindrome(string s);

///////////////////////////////////////////////////////////////////////////////////
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

		//��������ķǴ�ͳд����tmp���ˣ�
		mystring(const mystring& str)					
			:_str(nullptr)
			, _size(0)
			, _capacity(0)
		{
			mystring tmp(str._str);
			swap(tmp);									//�ɶ�����õ�this->swap(tmp);
		}

		void swap(mystring& tmp)						//���Աswap����
		{
			std::swap(_str, tmp._str);
			::swap(_size, tmp._size);					//Ĭ���޶���::Ϊȫ��swap��std�ɼӿɲ���
			::swap(_capacity, tmp._capacity);
		}

		~mystring()
		{
			delete[] _str;
			_str = nullptr;
			_size = _capacity = 0;
		}

		//mystring��ֵ��ͳд��
		//mystring& operator=(const mystring& s)
		//{
		//	if (this != &s)									//��ֹ�Լ���ֵ
		//	{
		//		char* tmp = new char[s._capacity + 1];		//capacity��ʵ�ʴ洢��Ч�������������ռ�Ҫ�࿪һ����\0
		//		memcpy(tmp, s._str, s._capacity + 1);		//ʹ��memcpy������capacity�����������޷���λ��\0
		//		delete[] _str;								//tmp��Ϊ�˷�ֹnew�ռ�ʧ�������ķ�����ʩ
		//		_str = tmp;
		//		_size = s._size;
		//		_capacity = s._capacity;
		//	}
		//	return *this;
		//}

		//mystring��ֵ�ִ�д��1
		//mystring& operator=(const mystring& str)
		//{
		//	if (this != &str)
		//	{
		//		mystring tmp(str._str);
		//		swap(tmp);									//����tmp��������ԭ�ռ�
		//	}
		//	return *this;
		//}

		//mystring��ֵ�ִ�д��2
		mystring& operator=(mystring str)					//���ο��������ٽ����������������β�
		{
			swap(str);
			return *this;
		}
		typedef char* iterator;
		typedef char* reverse_iterator;
		typedef const char* const_iterator;

		iterator begin();
		iterator end();
		reverse_iterator rbegin();
		reverse_iterator rend();
		const_iterator cbegin();
		const_iterator cend();
		size_t size()const;
		void reserve(size_t capacity);
		void resize(size_t capacity);
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

	private:
		char* _str;
		size_t _size;
		size_t _capacity;
		static size_t npos;		//��̬����ֻ�������ⶨ�壬����const static���Ը�ȱʡֵ���ڳ�ʼ���б��壨������
	};
	ostream& operator<<(ostream& out, const mystring& s);		//����ȡ�Ͳ��벻һ����Ϊ�����Ԫ����
	istream& operator>>(istream& in, mystring& s);
}