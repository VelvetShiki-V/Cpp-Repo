#include<iostream>
#include<assert.h>
#include<stdlib.h>
using namespace std;

///////////////////////////////////////////////////////////////////////////
class idt
{
    public:
    void identityshow();

    private:
    char _name[20];
    char _sex[10];
    int _age;
    int _ID;
};

class idt1
{
    void identityshow();
};

class idt2
{
    
};

class Today
{
    public:
        Today()
        {
            cout << "I'm today!" << endl;
            _year = 2022;
            _month = 8;
            _day = 4;
            _hour = 15;
            _min = 44;
        }
    private:
        int _year;
        int _month;
        int _day;
        int _hour;
        int _min;
};

/////////////////////////////////////////////////////////////////////////////
class Date
{
    public:
        //Date(int year = 2000, int month = 1, int day = 1)
        //{
        //    _year = year;
        //    _month = month;
        //    _day = day;
        //}
        //Date(int year, int month, int day)
        //{
        //    _year = year;
        //    _month = month;
        //    _day = day;
        //}
        //Date()
        //{
        //    _year = 2000;
        //    _month = 1;
        //    _day = 1;
        //}
        void DateInput(int year = 2000, int month = 1, int day = 1);
        void DateShow();
    private:
        int _year = 2000;
        int _month = 1;
        int _day = 1;
        Today _y;
};

///////////////////////////////////////////////////////////////////////
static int sum = 0;
static int i = 1;
class SUM
{
    public:
        SUM()
        {
            sum += i;
            i++;
        }
};

class AddN
{
    public:
        int add(int max)
        {
            SUM arr[max];
            return sum;
        }
};

///////////////////////////////////////////////////////////////////////
class Stack
{
    public:
        Stack(int capacity = 4)
        {
            _arr = (int*)malloc(sizeof(int)*capacity);
            assert(_arr);
            _top = 0;
            _capacity = capacity;
            cout << "我是构造，我被初始化为" << capacity << endl;
        }
        ~Stack()
        {
            free(_arr);
            _arr = nullptr;
            _top = _capacity = 0;
            cout << "我是析构" << _capacity << endl;
        }
        void StackPush(int x);
        void StackPop();
        int StackTop();
        bool StackEmpty();
    private:
        int* _arr;
        int _top;
        int _capacity;
};

class MyQueue
{
    private:
        Stack s1;
};
