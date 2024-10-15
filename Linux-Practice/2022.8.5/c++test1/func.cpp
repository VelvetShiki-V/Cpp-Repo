#include"func.h"

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
