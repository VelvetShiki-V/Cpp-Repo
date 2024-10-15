#include<iostream>
#include<assert.h>
#include<string.h>
#include<stdlib.h>
using namespace std;

template<typename T>
void Swap(T& a, T& b)
{
    T tmp = a;
    a = b;
    b = tmp;
}

template<class T>
class Stack
{
    public:
        Stack(int capacity = 4)
            :_arr(new T[capacity])
            ,_top(0)
            ,_capacity(capacity)
    {
        cout << "调用默认构造" << endl;
    }
        void Push(const T& data);
        const T& Top()
        {
            assert(_top > 0);
            return _arr[_top - 1];
        }
        void Pop()
        {
            assert(_top > 0);
            _top--;
        }
        bool Empty()
        {
            return _top == 0;
        }
        Stack(const Stack& s)
        {
            _top = s._top;
            _capacity = s._capacity;
            _arr = new T[_capacity];
            memcpy(_arr, s._arr, sizeof(T) * s._top);
            cout << "调用拷贝构造" << endl;
        }
        const int& Size()const
        {
            return _top;
        }
        ~Stack()
        {
            delete[] _arr;
            _top = _capacity = 0;
            cout << "调用析构" << endl;
        }
    private:
        T* _arr;
        int _top;
        int _capacity;
};

template<class T>
void Stack<T>::Push(const T& data)
{
    if(_top == _capacity)
    {
        int expand = _capacity == 0 ? 4 : _capacity * 2;
        T* tmp = new T(expand);
        if(_arr)
        {
            memcpy(tmp, _arr, _top * sizeof(T));
            _capacity = expand;
            _arr = tmp;
        }
        else
        {
            _arr = tmp;
            _capacity = expand;
        }
    }
    _arr[_top++] = data;
}
