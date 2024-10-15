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
	memcpy(tmp, _str, _capacity + 1);			//+1��'\0'Ҳ������ȥ
	delete[] _str;
	_str = tmp;
}

void mystring::resize(size_t capacity)			//����reserve
{
	mystring::reserve(capacity);
}

//��ͨд��
//void mystring::push_back(char c)
//{
//	if (_capacity == _size)
//	{
//		mystring::reserve(_capacity == 0 ? 4 : _capacity * 2);		//����reserve����
//	}
//	_str[_size++] = c;
//	_str[_size] = '\0';			//����Ҫע��ĩβ������\0�������ַ�����߻������루��ʹ��cout��ȡ��
//}

//ʹ��insert����
void mystring::push_back(char c)
{
	mystring::insert(_size, c);
}

//push_back����
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
	if (len > (_capacity - _size))				//�ж���Ҫ������ַ����Ƿ���ڵ�ǰʣ��ռ䣬һ���Կ���
	{											//���ٿ�size + len���ռ�
		mystring::reserve(_size + len);
	}
	strcpy(_str + _size, s);					//Ҳ������strcat����Ч�ʺܵͣ�Ҫ��\0��
	_size += len;
	//while (*s != '\0')						//����+=����
	//{
	//	(*this) += *s;
	//	s++;
	//}
}

mystring& mystring::operator+=(const char* str)	//����append�ַ���
{
	mystring::append(str);
	return *this;
}

mystring& mystring::insert(size_t pos, char c)
{
	assert(pos <= _size);				//��Ϊ��size_t�����ö��Լ��pos >= 0����Ϊ���޷�����
	if (_capacity == _size)
	{
		mystring::reserve(_capacity == 0 ? 4 : _capacity * 2);
	}
	size_t end = _size + 1;				//Ϊ��ͬʱŲ��'\0'���������1������Ҫ������ֶ�ʹ++_size�ÿ���Ϊ������
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

//��Ų�����ݣ�����append���Ƿ�
mystring& mystring::insert(size_t pos, const char* s)
{
	assert(pos <= _size);
	size_t len = strlen(s);
	if (len >= _capacity - _size)
	{
		mystring::reserve(_size += len);
	}
	mystring tmp(_str + pos);			//Ҳ������ϣ��˼·
	_size -= _size - pos;
	mystring::append(s);				//����д������ʹappend����insert��������ѭ��
	mystring::append(tmp._str);
	return *this;
}

size_t mystring::npos = -1;			//��̬��Ա���������ⶨ��
mystring& mystring::erase(size_t pos, size_t len)
{
	assert(pos < _size);
	if (len == -1 || len >= _size - pos)				//�жϴ���Ĵ�ɾ���ַ������ڵ�ǰposλ������Ƿ�ɾ
	{
		strncpy(_str + pos, "\0", _capacity);			//�����������pos��������ַ��ÿ�
		_size = pos;
	}
	else
	{
		mystring tmp(_str + pos + len);					//���������len����ַ����ݣ�Ȼ�󸲸ǵ�pos��len�ַ��ϣ�֮���ÿ�	
		strncpy(_str + pos, tmp._str, _capacity);		//Ҳ������ǰ�����һ���ַ���ϣ��˼·
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