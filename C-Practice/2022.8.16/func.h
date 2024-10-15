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

		void insert(iterator pos, const T& data)		//��Ҫ�����ã����ģ�屣��һ��
		{
			assert(pos >= _start && pos <= _finish);
			if (_finish == _end_of_storage)
			{
				size_t len = pos - _start;				//����pos�����λ��
				reserve(capacity() == 0 ? 4 : capacity() * 2);
				pos = _start + len;						//����pos����ֹ������ʧЧ
			}
			reverse_iterator rit = rbegin();			//�����ݺ�ת�����¿ռ䣬���Ǵ����pos��Ȼָ��ɿռ��ĳ��λ��
			for (rit; rit >= pos; rit--)
			{
				*(rit + 1) = *rit;
			}
			*(pos) = data;
			_finish++;
		}

		iterator erase(iterator pos)		//����ֵΪɾ��λ����һ��λ�õĵ�������Ϊ����������erase������������������
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
			}								//����������������ݲ��ԣ�ʱ�任�ռ䣬������ʱ�ռ��û������������ܻ�ʧЧ
			return pos;						//��ʱposΪԭ��������ɾ��λ�ã��������ݸ��ǣ���Ϊ��һ��λ�ã�STL�涨�ģ�
		}

	private:
		iterator _start;			//����������ָ��˳���ռ��׵�ַ
		iterator _finish;			//ָ��ĩ��ЧԪ�ص���һ���ռ��ַ
		iterator _end_of_storage;	//ָ��ȫ��������������һ���ռ��ַ
	};
}