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
	for (size_t i = 0; i < s.size(); i++)
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
mystring::iterator mystring::begin()
{
	return _str;
}

mystring::iterator mystring::end()
{
	return _str + _size;
}

mystring::reverse_iterator mystring::rbegin()
{
	return _str + _size;
}

mystring::reverse_iterator mystring::rend()
{
	return _str - 1;
}

mystring::const_iterator mystring::cbegin()
{
	return _str;
}

mystring::const_iterator mystring::cend()
{
	return _str + _size;
}

size_t mystring::size()const
{
	return _size;
}

void mystring::reserve(size_t capacity)
{
	if (capacity <= _capacity)
		return;
	_capacity = capacity;
	char* tmp = new char[_capacity + 1];
	memcpy(tmp, _str, _capacity + 1);			//+1将'\0'也拷贝过去
	delete[] _str;
	_str = tmp;
}

void mystring::resize(size_t capacity)			//复用reserve
{
	mystring::reserve(capacity);
}

//普通写法
//void mystring::push_back(char c)
//{
//	if (_capacity == _size)
//	{
//		mystring::reserve(_capacity == 0 ? 4 : _capacity * 2);		//复用reserve扩容
//	}
//	_str[_size++] = c;
//	_str[_size] = '\0';			//必须要注意末尾隐含的\0，否则字符串后边会有乱码（如使用cout读取）
//}

//使用insert复用
void mystring::push_back(char c)
{
	mystring::insert(_size, c);
}

//push_back复用
mystring& mystring::operator+=(char c)
{
	mystring::push_back(c);
	return *this;
}

size_t mystring::capacity()const
{
	return _capacity;
}

void mystring::append(const char* s)
{
	size_t len = strlen(s);
	if (len > (_capacity - _size))				//判断所要插入的字符串是否大于当前剩余空间，一次性开辟
	{											//至少开size + len个空间
		mystring::reserve(_size + len);
	}
	strcpy(_str + _size, s);					//也可以用strcat，但效率很低（要找\0）
	_size += len;
	//while (*s != '\0')						//复用+=单个
	//{
	//	(*this) += *s;
	//	s++;
	//}
}

mystring& mystring::operator+=(const char* str)	//复用append字符串
{
	mystring::append(str);
	return *this;
}

mystring& mystring::insert(size_t pos, char c)
{
	assert(pos <= _size);				//因为是size_t，不用断言检查pos >= 0，因为是无符号数
	if (_capacity == _size)
	{
		mystring::reserve(_capacity == 0 ? 4 : _capacity * 2);
	}
	size_t end = _size + 1;				//为了同时挪动'\0'，如果不加1，则需要在最后手动使++_size置空作为结束符
	while (end > pos)
	{
		_str[end] = _str[end - 1];
		end--;
	}
	_str[pos] = c;
	++_size;
	//_str[++_size] = '\0';
	return *this;
}

//不挪动数据，复用append覆盖法
mystring& mystring::insert(size_t pos, const char* s)
{
	assert(pos <= _size);
	size_t len = strlen(s);
	if (len >= _capacity - _size)
	{
		mystring::reserve(_size += len);
	}
	mystring tmp(_str + pos);			//也可以用希尔思路
	_size -= _size - pos;
	mystring::append(s);				//此种写法不能使append复用insert，否则将死循环
	mystring::append(tmp._str);
	return *this;
}

size_t mystring::npos = -1;			//静态成员变量在类外定义
mystring& mystring::erase(size_t pos, size_t len)
{
	assert(pos < _size);
	if (len == -1 || len >= _size - pos)				//判断传入的待删除字符个数在当前pos位置向后是否够删
	{
		strncpy(_str + pos, "\0", _capacity);			//如果不够，将pos后的所有字符置空
		_size = pos;
	}
	else
	{
		mystring tmp(_str + pos + len);					//如果够，将len后的字符备份，然后覆盖到pos的len字符上，之后都置空	
		strncpy(_str + pos, tmp._str, _capacity);		//也可以用前面插入一个字符的希尔思路
		_size -= len;
	}
	return *this;
}

void mystring::clear()
{
	mystring::erase(0);
}

bool mystring::empty()
{
	return _size == 0;
}

char& mystring::operator[](size_t pos)
{
	assert(pos < _size);
	return _str[pos];
}

const char& mystring:: mystring::operator[](size_t pos)const
{
	assert(pos < _size);
	return _str[pos];
}

ostream& myspace::operator<<(ostream& out, const mystring& s)	
{
	for (size_t i = 0; i < s.size(); i++)
	{
		out << s[i];
	}
	return out;
}

istream& myspace::operator>>(istream& in, mystring& s)
{
	char c = in.get();
	while(c != ' ' && c != '\n')
	{
		s += c;
		c = in.get();
	}
	return in;
}

const char* mystring::c_str()const
{
	return _str;
}