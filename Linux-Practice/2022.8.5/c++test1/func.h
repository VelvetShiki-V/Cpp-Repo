#include<iostream>
#include<assert.h>
#include<stdlib.h>
using namespace std;
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
    public:
        Stack s1;
};

MyQueue& func1(MyQueue& q);
void func(MyQueue q);
MyQueue func2(MyQueue& q);
MyQueue& func3();
MyQueue func4();

///////////////////////////////////////////////////////////////////////////////////////////////
class Date
{
    public:
        Date(int year = 2000, int month = 1, int day = 1)
        {
           //cout << "我是构造，我只对用户显式定义内置类型初始化" << endl;
            _year = year;
            _month = month;
            _day = day;
        }
        ~Date()
        {
            //cout << "我是析构，我不对内置类型年月日进行清理" << endl;
        }
        Date(const Date& date)
        {
            //cout << "我是拷贝构造，我对内置类型逐字节拷贝，对自定义类型浅拷贝" << endl;
            _year = date._year;
            _month = date._month;
            _day = date._day;
        }
        void DateShow();
        bool operator==(const Date& d)
        {
            return _year == d._year && _month == d._month && _day == d._day;
        }
        int GetMonthDay(int year, int month)
        {
            static int days[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
            if((year % 4 == 0 && year % 100 != 0 ) || year % 400 == 0)
            {
                if(month == 2)
                {
                    return 29;
                }
            }
            return days[month];
        }

        Date operator+(int extradays)
        {
            Date ret(*this);
            ret._day += extradays;
            while(ret._day > GetMonthDay(ret._year, ret._month))
            {
                ret._day -= GetMonthDay(ret._year, ret._month);
                ret._month++;
                if(ret._month == 13)
                {
                    ret._year++;
                    ret._month = 1;
                }
            }
            return ret;
        }

        void operator+=(int extradays)
        {
            _day += extradays;
            while(_day > GetMonthDay(_year, _month))
            {
                _day -= GetMonthDay(_year, _month);
                _month++;
                if(_month == 13)
                {
                    _year++;
                    _month = 1;
                }
            }
        }

        Date operator-(int pastdays)
        {
            Date ret(*this);
            ret._day -= pastdays;
            while(ret._day <= 0)
            {
                ret._month--;
                if(ret._month == 0)
                {
                    ret._month = 12;
                    ret._year--;
                }
                ret._day += GetMonthDay(ret._year, ret._month);
            }
            return ret;
        }

        Date& operator-=(int pastdays)
        {
            _day -= pastdays;
            while(_day <= 0)
            {
                _month--;
                if(_month == 0)
                {
                    _year--;
                    _month = 12;
                }
                _day += GetMonthDay(_year, _month);
            }
            return *this;
        }
        
        int operator-(const Date& d)
        {
            Date day1(1, 1, 1);
            int count1 = 0;
            while(!day1.operator==(*this))
            {
                count1++;
                day1 += 1;
            }
            Date day2(1, 1, 1);
            int count2 = 0;
            while(!(day2 == d))
            {
                count2++;
                day2 += 1;
            }
            return count2 - count1;
        }

    private:
        int _year;
        int _month;
        int _day;
};

