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
	memcpy(tmp, _str, _capacity + 1);			//+1将'\0'也拷贝过去
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
		mystring::erase(newsize);			//值得一提
		_size = newsize;
	}
}

//push_back普通写法
//void mystring::push_back(char c)
//{
//	if (_capacity == _size)
//	{
//		mystring::reserve(_capacity == 0 ? 4 : _capacity * 2);		//复用reserve扩容
//	}
//	_str[_size++] = c;
//	_str[_size] = '\0';			//必须要注意末尾隐含的\0，否则字符串后边会有乱码（如使用cout读取）
//}

//push_back使用insert复用
void mystring::push_back(char c)
{
	mystring::insert(_size, c);
}

//+=的push_back复用
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
	//mystring::erase(0);		//将当前string._str中所有字符擦除
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

//流提取+=写法，如果输入数据量太大则每次扩容消耗大
//istream& myspace::operator>>(istream& in, mystring& s)
//{
//	char c = in.get();
//	//不能用in >> ch，因为不会忽略空格和换行
//	while(c != ' ' && c != '\n')
//	{
//		s += c;
//		c = in.get();
//	}
//	return in;
//}

istream& myspace::operator>>(istream& in, mystring& s)
{
	s.clear();							//为了同步std::cout功能，如果流提取前的s存在已有字符串，则清空原字符串再提取
	char c = in.get();
	const size_t N = 32;				//如果直接给s开辟reserve，则无法控制大小，开多会空间浪费，开小又要+=
	char buffer[N];						//作为实参string的输入缓冲
	size_t i = 0;
	while (c != ' ' && c != '\n')
	{
		buffer[i++] = c;
		if (i == N - 1)					//字符通过一次性开辟好空间的临时字符数组存入，如果数据满了，将数据一次性+=到string中
		{
			buffer[i] = '\0';			//预留一个位置给\0，实参传递后，将下标归0，用于下一次形参模板
			s += buffer;
			i = 0;
		}
		c = in.get();
	}
	buffer[i] = '\0';					//当遇到空格或回车，表示当前string输入完毕，则将形参数组buffer加上结束符后整体+=给实参string
	s += buffer;						//当出函数时Buffer销毁，开销较小
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
	return npos;		//如果找不到，返回最大值
}

//find子串自己实现
//size_t myspace::mystring::find(const char* str, size_t pos) const
//{
//	assert(pos <= _size);
//	size_t len = strlen(str);
//	if (len > _size - pos)			//如果带匹配字符串大于自pos位置起的有效字符串长度，则一定不能匹配
//		return npos;
//	else
//	{
//		for (size_t i = pos; i + len <= _size; i++)		//先找首字符相同位置i，循环结束条件为pos+len=_size
//		{
//			if (_str[i] != *str)
//			{
//				continue;
//			}
//			else
//			{
//				size_t j = i, round = len;				//找到后再从该位置循环len次，逐个比对
//				const char* cmp = str;					//使用三个临时变量将外部变量保护起来
//				while (round)							//循环条件为全部找到使round置0，或只要一个不相等就返回npos
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

//strstr库算法find写法
size_t myspace::mystring::find(const char* str, size_t pos) const
{
	assert(pos <= _size);
	char* ptr = strstr(_str + pos, str);		//还可以使用kmp算法或bm算法
	if (ptr == nullptr)
		return npos;
	else
		return ptr - _str;
	return npos;
}

mystring myspace::mystring::substr(size_t pos, size_t len) const
{
	assert(pos <= _size);						//值得一提
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

//mystring赋值传统写法
//mystring& myspace::mystring::operator=(mystring str)
//{
//	if (this != &s)									//防止自己赋值
//	{
//		char* tmp = new char[s._capacity + 1];		//capacity是实际存储有效数据容量，开空间要多开一个给\0
//		memcpy(tmp, s._str, s._capacity + 1);		//使用memcpy必须用capacity拷贝，否则将无法定位到\0
//		delete[] _str;								//tmp是为了防止new空间失败所做的防护措施
//		_str = tmp;
//		_size = s._size;
//		_capacity = s._capacity;
//	}
//	return *this;
//}

//mystring赋值现代写法1
//mystring& myspace::mystring::operator=(mystring str)
//{
//	if (this != &str)
//	{
//		myspace::mystring::swap(str._str);
//		swap(tmp);									//交给tmp析构清理原空间
//	}
//	return *this;
//}

//mystring赋值现代写法2
mystring& myspace::mystring::operator=(mystring str)					//传参拷贝构造再交换，出函数析构形参
{
	myspace::mystring::swap(str);			//使用的是成员函数swap，不是std的swap
	return *this;
}

bool myspace::mystring::operator>(const mystring& s) const
{
	//或可以用strcmp直接判断
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
	//或可以用strcmp直接判断
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