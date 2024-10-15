#include"func.h"

void idt::identityshow()
{
    cout << "请输入学生信息" << endl;
    cin >> _name >> _sex >> _age >> _ID;
    cout << _name << ' ' << _sex << ' ' << _age << ' ' << _ID << endl;
}

void Date::DateInput(int year, int month, int day)
{
    this->_year = year;
    this->_month = month;
    this->_day = day;
}

void Date::DateShow()
{
    cout << _year << "年" << _month << "月" << _day << "日" << endl;
}


void Stack::StackPush(int x)
{
    if(_capacity == _top)
    {
        int expand = _capacity * 2;
        int* tmp = (int*)realloc(_arr, expand * sizeof(int));
        assert(tmp);
        _arr = tmp;
        _capacity = expand;
    }
    _arr[_top++] = x;
}

void Stack::StackPop()
{
    if(!Stack::StackEmpty())
    {
        _top--;
    }
}

int Stack::StackTop()
{
    if(!Stack::StackEmpty())
    {
        return _arr[_top - 1];
    }
    return -1;
}
bool Stack::StackEmpty()
{
    return _top == 0;
}
