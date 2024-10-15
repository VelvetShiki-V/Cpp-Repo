#pragma once
#include<iostream>
#include<string>
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
		mystring(const char* str = "")
		{
			_size = strlen(str);
			_capacity = _size;
			_str = new char[_size];
			strcpy(_str, str);
		}
		mystring(const mystring& str)
		{
			_size = str._size;
			_capacity = str._capacity;
			_str = new char[_size];
			memcpy(_str, str._str, _size);
		}
		~mystring()
		{
			delete[] _str;
			_str = nullptr;
			_size = _capacity = 0;
		}
		char* begin();
		char* end();
		char* rbegin();
		char* rend();
		size_t size();
		void reserve(size_t capacity);
		void resize(size_t capacity);
		size_t capacity();
		void clear();
		bool empty();
		char& operator[](size_t pos);
		const char& operator[](size_t pos)const;
		const char* c_str()const;


	private:
		char* _str;
		size_t _size;
		size_t _capacity;
	};
}