#include"func.h"

string stradd(const string& num1, const string& num2)
{
	string::const_reverse_iterator rit1 = num1.crbegin();
	string::const_reverse_iterator rit2 = num2.crbegin();
	string arr;
	int next = 0;
	while (rit1 != num1.crend() || rit2 != num2.crend())
	{
		char end1 = rit1 == num1.crend() ? '0' : *rit1;
		char end2 = rit2 == num2.crend() ? '0' : *rit2;
		int num = end1 + end2 - '0' * 2;
		if (next == 1)
		{
			num += 1;
			next--;
		}
		if (num >= 10)
		{
			next = 1;
		}
		arr += num % 10 + '0';
		if (rit1 != num1.crend())
			rit1++;
		if (rit2 != num2.crend())
			rit2++;
	}
	if (next == 1)
	{
		arr += '1';
	}
	reverse(arr.begin(), arr.end());
	return arr;
}

int lengthOfLastWord(string s)
{
	int end = s.size() - 1;
	while (s[end] == ' ')
		end--;
	int length = 0;
	while (end >= 0 && s[end] != ' ')
	{
		length++;
		end--;
	}
	return length;
}

int firstUniqChar(string s)
{
	int* ref = new int[26];
	memset(ref, 0, 26*sizeof(int));
	for (auto e : s)
	{
		ref[e - 97]++;
	}
	for (int i = 0; i < s.size(); i++)
	{
		if (ref[s[i] - 97] == 1)
		{
			return i;
		}
	}
	return -1;
}

bool isPalindrome(string s)
{
	string s1;
	for (auto e : s)
	{
		if (isalpha(e))
		{
			if (e >= 'A' && e <= 'Z')
				e += 32;
			s1 += e;
		}
		if (e >= '0' && e <= '9')
			s1 += e;
	}
	if (s1.size() == 0)
	{
		return true;
	}
	const char* left = s1.c_str(), * right = &(s1[s1.size() - 1]);
	//const char* left = &(s1.front()), * right = &(s1.back());
	//auto left = s1.begin(), right = s1.end() - 1;
	while (left < right)
	{
		if (*left != *right)
			return false;
		left++;
		right--;
	}
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
using namespace myspace;
char* mystring::begin()
{
	return &(_str[0]);
}

char* mystring::end()
{
	return &(_str[_size]) + 1;
}
char* mystring::rbegin()
{
	return &(_str[_size]);
}

char* mystring::rend()
{
	return &(_str[0]) - 1;
}

size_t mystring::size()
{
	return _size;
}

void mystring::reserve(size_t capacity)
{
	if (capacity < _capacity)
		return;
	_capacity = capacity;
	char* str = new char[_capacity];
	memcpy(str, _str, _size);
	_str = str;
}

void mystring::resize(size_t capacity)
{
	mystring::reserve(capacity);
}


size_t mystring::capacity()
{
	;
}

void mystring::clear()
{
	;
}

bool mystring::empty()
{
	;
}

char& mystring::operator[](size_t pos)
{
	;
}

const char& mystring:: mystring::operator[](size_t pos)const
{
	;
}

const char* mystring:: c_str()const
{
	if (_size == _capacity)
		mystring::reserve(_capacity + 1);
	_str[_size] = '\0';
	_size++;
	return _str;
}