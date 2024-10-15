#pragma once
#include<iostream>
#include<vector>
#include<algorithm>
#include<functional>
#include<assert.h>

namespace mysp
{
	template<class T>
	class myvector
	{
	public:
		typedef T* iterator;		//typedef的模板类型需要放在public，否则默认在private无法被外界访问到（迭代器类型）
		typedef T* reverse_iterator;
		typedef const T* const_iterator;
		myvector()
			: _start(nullptr)
			, _finish(nullptr)
			, _end_of_storage(nullptr)
		{}

		~myvector()
		{
			delete[] _start;
			_start = _finish = _end_of_storage = nullptr;
		}

		iterator begin()
		{
			return _start;
		}

		iterator end()
		{
			return _finish;
		}

		const_iterator cbegin()const
		{
			return _start;
		}

		const_iterator cend()const
		{
			return _finish;
		}

		reverse_iterator rbegin()
		{
			return _finish - 1;
		}

		reverse_iterator rend()
		{
			return _start - 1;
		}

		size_t capacity()const
		{
			return _end_of_storage - _start;
		}

		size_t size()const
		{
			return _finish - _start;
		}

		T& operator[](size_t pos)
		{
			assert(pos < size());
			return *(_start + pos);
		}


		const T& operator[](size_t pos)const
		{
			assert(pos < size());
			return _start[pos];
		}

		void reserve(size_t n)
		{
			if (n > capacity())
			{
				size_t sz = size();					//提前将旧的顺序表有效个数备份，否则原表将被delete
				iterator tmp = new T[n];
				if (_start)
				{
					memcpy(tmp, _start, sizeof(T) * sz);
					delete[] _start;
				}
				_start = tmp;
				_finish = tmp + sz;					//将新的标识有效值的下一个地址更新
				_end_of_storage = _start + n;		//将成员变量更新
			}
		}

		void push_back(const T& data)			//使用引用，为了应对string，list等对象，const为了应对接收常量字符串或常性对象
		{
			//if (_finish == _end_of_storage)
			//{
			//	reserve(capacity() == 0 ? 4 : capacity() * 2);
			//}
			//*_finish = data;
			//_finish++;
			insert(end(), data);
		}

		void pop_back()
		{
			assert(_finish > _start);
			_finish--;
		}

		void insert(iterator pos, const T& data)		//不要加引用，与库模板保持一致
		{
			assert(pos >= _start && pos <= _finish);
			if (_finish == _end_of_storage)
			{
				size_t len = pos - _start;				//备份pos的相对位置
				reserve(capacity() == 0 ? 4 : capacity() * 2);
				pos = _start + len;						//更新pos，防止迭代器失效
			}
			reverse_iterator rit = rbegin();			//扩完容后转移至新空间，但是传入的pos仍然指向旧空间的某个位置
			for (rit; rit >= pos; rit--)
			{
				*(rit + 1) = *rit;
			}
			*(pos) = data;
			_finish++;
		}

		iterator erase(iterator pos)		//返回值为删除位置下一个位置的迭代器，为了容许连续erase操作的数据跳过问题
		{
			assert(pos >= _start && pos < _finish);
			if (size())
			{
				iterator begin = pos;
				while (begin <= _finish - 1)
				{
					*begin = *(begin + 1);
					begin++;
				}
				_finish--;
			}								//如果编译器采用缩容策略，时间换空间，则缩容时空间置换，迭代器可能会失效
			return pos;						//此时pos为原来的数据删除位置，被新数据覆盖，即为下一个位置（STL规定的）
		}

	private:
		iterator _start;			//迭代器对象，指向顺序表空间首地址
		iterator _finish;			//指向末有效元素的下一个空间地址
		iterator _end_of_storage;	//指向全部可用容量的下一个空间地址
	};
}