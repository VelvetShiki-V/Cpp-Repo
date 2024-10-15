#include"func.h"
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

void myspace::mystring::resize(size_t newsize, char c)
{
	if (newsize > _size)
	{
		mystring::reserve(newsize);
		for (size_t i = _size; i < newsize; i++)
		{
			_str[i] = c;
		}
		_size = newsize;
		_str[newsize] = '\0';
	}
	else
	{
		mystring::erase(newsize);			//ֵ��һ��
		_size = newsize;
	}
}

//push_back��ͨд��
//void mystring::push_back(char c)
//{
//	if (_capacity == _size)
//	{
//		mystring::reserve(_capacity == 0 ? 4 : _capacity * 2);		//����reserve����
//	}
//	_str[_size++] = c;
//	_str[_size] = '\0';			//����Ҫע��ĩβ������\0�������ַ�����߻������루��ʹ��cout��ȡ��
//}

//push_backʹ��insert����
void mystring::push_back(char c)
{
	mystring::insert(_size, c);
}

//+=��push_back����
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
	//mystring::erase(0);		//����ǰstring._str�������ַ�����
	_size = 0;
	_str[0] = '\0';
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

//����ȡ+=д�����������������̫����ÿ���������Ĵ�
//istream& myspace::operator>>(istream& in, mystring& s)
//{
//	char c = in.get();
//	//������in >> ch����Ϊ������Կո�ͻ���
//	while(c != ' ' && c != '\n')
//	{
//		s += c;
//		c = in.get();
//	}
//	return in;
//}

istream& myspace::operator>>(istream& in, mystring& s)
{
	s.clear();							//Ϊ��ͬ��std::cout���ܣ��������ȡǰ��s���������ַ����������ԭ�ַ�������ȡ
	char c = in.get();
	const size_t N = 32;				//���ֱ�Ӹ�s����reserve�����޷����ƴ�С�������ռ��˷ѣ���С��Ҫ+=
	char buffer[N];						//��Ϊʵ��string�����뻺��
	size_t i = 0;
	while (c != ' ' && c != '\n')
	{
		buffer[i++] = c;
		if (i == N - 1)					//�ַ�ͨ��һ���Կ��ٺÿռ����ʱ�ַ�������룬����������ˣ�������һ����+=��string��
		{
			buffer[i] = '\0';			//Ԥ��һ��λ�ø�\0��ʵ�δ��ݺ󣬽��±��0��������һ���β�ģ��
			s += buffer;
			i = 0;
		}
		c = in.get();
	}
	buffer[i] = '\0';					//�������ո��س�����ʾ��ǰstring������ϣ����β�����buffer���Ͻ�����������+=��ʵ��string
	s += buffer;						//��������ʱBuffer���٣�������С
	return in;
}

const char* mystring::c_str()const
{
	return _str;
}

size_t myspace::mystring::find(char c, size_t pos) const
{
	assert(pos <= _size);
	for (pos; pos <= _size; pos++)
	{
		if (_str[pos] == c)
		{
			return pos;
		}
	}
	return npos;		//����Ҳ������������ֵ
}

//find�Ӵ��Լ�ʵ��
//size_t myspace::mystring::find(const char* str, size_t pos) const
//{
//	assert(pos <= _size);
//	size_t len = strlen(str);
//	if (len > _size - pos)			//�����ƥ���ַ���������posλ�������Ч�ַ������ȣ���һ������ƥ��
//		return npos;
//	else
//	{
//		for (size_t i = pos; i + len <= _size; i++)		//�������ַ���ͬλ��i��ѭ����������Ϊpos+len=_size
//		{
//			if (_str[i] != *str)
//			{
//				continue;
//			}
//			else
//			{
//				size_t j = i, round = len;				//�ҵ����ٴӸ�λ��ѭ��len�Σ�����ȶ�
//				const char* cmp = str;					//ʹ��������ʱ�������ⲿ������������
//				while (round)							//ѭ������Ϊȫ���ҵ�ʹround��0����ֻҪһ������Ⱦͷ���npos
//				{
//					if (_str[j] != *cmp)
//						return npos;
//					j++;
//					cmp++;
//					round--;
//				}
//				if (round == 0)
//					return i;
//			}
//		}
//	}
//	return npos;
//}

//strstr���㷨findд��
size_t myspace::mystring::find(const char* str, size_t pos) const
{
	assert(pos <= _size);
	char* ptr = strstr(_str + pos, str);		//������ʹ��kmp�㷨��bm�㷨
	if (ptr == nullptr)
		return npos;
	else
		return ptr - _str;
	return npos;
}

mystring myspace::mystring::substr(size_t pos, size_t len) const
{
	assert(pos <= _size);						//ֵ��һ��
	if (len > _size - pos)
		len = _size - pos;
	mystring sub;
	size_t i = 0;
	while (i < len)
	{
		sub += *(_str + pos + i);
		i++;
	}
	return sub;
}

//mystring��ֵ��ͳд��
//mystring& myspace::mystring::operator=(mystring str)
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
//mystring& myspace::mystring::operator=(mystring str)
//{
//	if (this != &str)
//	{
//		myspace::mystring::swap(str._str);
//		swap(tmp);									//����tmp��������ԭ�ռ�
//	}
//	return *this;
//}

//mystring��ֵ�ִ�д��2
mystring& myspace::mystring::operator=(mystring str)					//���ο��������ٽ����������������β�
{
	myspace::mystring::swap(str);			//ʹ�õ��ǳ�Ա����swap������std��swap
	return *this;
}

bool myspace::mystring::operator>(const mystring& s) const
{
	//�������strcmpֱ���ж�
	if ((*this).size() > s.size())
		return true;
	else if ((*this).size() < s.size())
		return false;
	else
	{
		for (size_t i = 0; i < s.size(); i++)
		{
			size_t ret = (*this)[i] >= s[i] ? 0 : 1;
			if (ret)
			{
				return false;
			}
		}
	}
	return true;
}

bool myspace::mystring::operator==(const mystring& s) const
{
	//�������strcmpֱ���ж�
	if((*this).size() > s.size() || (*this).size() < s.size())
		return false;
	else
	{
		for (size_t i = 0; i < s.size(); i++)
		{
			size_t ret = (*this)[i] == s[i] ? 0 : 1;
			if (ret)
			{
				return false;
			}
		}
	}
	return true;
}

bool myspace::mystring::operator<(const mystring& s) const
{
	return !(myspace::mystring::operator>(s));
}

bool myspace::mystring::operator>=(const mystring& s) const
{
	return !(myspace::mystring::operator<(s));
}

bool myspace::mystring::operator<=(const mystring& s) const
{
	return !(myspace::mystring::operator>(s));
}

bool myspace::mystring::operator!=(const mystring& s) const
{
	return !(myspace::mystring::operator==(s));
}