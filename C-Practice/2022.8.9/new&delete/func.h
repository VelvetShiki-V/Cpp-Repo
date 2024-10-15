#pragma once
#include<iostream>
#include<assert.h>
#include<string.h>
#include<stdlib.h>
using namespace std;

class Date
{
public:
	friend ostream& operator<<(ostream& out, const Date& d);
	friend istream& operator>>(istream& in, Date& d);
	Date(int year = 2000, int month = 1, int day = 1)
		:_year(year)
		,_month(month)
		,_day(day)
	{}
	int GetMonthDay(int year, int month)const;
	void WeekdayCheck()const;
	int operator-(const Date& d)const;
	Date& operator++();
	bool operator==(const Date& d)const;
	bool operator!=(const Date& d)const;
	Date& operator+=(int extradays);
	Date& operator-=(int pastdays);
private:
	int _year;
	int _month;
	int _day;
};

class Stack
{
public:
    Stack(int capacity = 4)
        :_arr(new int[capacity])
        //:_arr((int*)malloc(sizeof(int)*capacity))
        //:_arr = new int[]
        ,_top(0)
        ,_capacity(capacity)
    {
        //_arr = (int*)malloc(sizeof(int) * capacity);
        //_arr = new int[capacity];
        memset(_arr, 0, sizeof(int) * _capacity);       //memset逐字节拷贝，对于非char数组只能用0初始化
        cout << "直接构造，容量初始化为" << capacity << endl;
    }
    Stack(const Stack& s)
    {
        _capacity = s._capacity;
        _top = s._top;
        _arr = new int[_capacity];
        memcpy(_arr, s._arr, sizeof(int) * _top);
        cout << "我是拷贝构造" << endl;
    }
    ~Stack()
    {
        delete[] _arr;
        _arr = nullptr;
        _top = _capacity = 0;
        cout << "~Stack()" << endl;
    }
    void StackPush(int x);
    void StackPop();
    int StackTop();
    bool StackEmpty();
    void deleteARR();
private:
    int* _arr;
    int _top;
    int _capacity;
};

class MyQueue
{
public:
    friend void test5();
    MyQueue(int ni = 10)
        :s1(5)
        ,_nice(5)
        ,_ni(5)
    {}
    Stack s1;
    int _ni;
    static int _n;
private:
    int _nice;
    static int _nic;
};