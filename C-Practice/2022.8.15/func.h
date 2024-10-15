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
		typedef T* iterator;		//typedef��ģ��������Ҫ����public������Ĭ����private�޷��������ʵ������������ͣ�
		typedef const T* const_iterator;
		typedef const T* reverse_iterator;
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
				size_t sz = size();					//��ǰ���ɵ�˳�����Ч�������ݣ�����ԭ����delete
				iterator tmp = new T[n];
				if (_start)
				{
					memcpy(tmp, _start, sizeof(T) * sz);
					delete[] _start;
				}
				_start = tmp;
				_finish = tmp + sz;					//���µı�ʶ��Чֵ����һ����ַ����
				_end_of_storage = _start + n;		//����Ա��������
			}
		}

		void push_back(const T& data)			//ʹ�����ã�Ϊ��Ӧ��string��list�ȶ���constΪ��Ӧ�Խ��ճ����ַ������Զ���
		{
			if (_finish == _end_of_storage)
			{
				reserve(capacity() == 0 ? 4 : capacity() * 2);
			}
			*_finish = data;
			_finish++;
		}

		void pop_back()
		{
			assert(_finish > _start);
			_finish--;
		}

		void insert(iterator pos, const T& data)
		{
			assert(pos <= size());
			if (_finish == _end_of_storage)
			{
				reserve(capacity() == 0 ? 4 : capacity() * 2);
			}
			reverse_iterator rit = rbegin();
			for (rit; rit != pos - 1; rit--)
			{
				*(rit + 1) = *rit;
			}
			*(rit + 1) = data;
			_finish++;
		}

		void erase(iterator pos)
		{

		}

	private:
		iterator _start;			//����������ָ��˳���ռ��׵�ַ
		iterator _finish;			//ָ��ĩ��ЧԪ�ص���һ���ռ��ַ
		iterator _end_of_storage;	//ָ��ȫ��������������һ���ռ��ַ
	};
}