#include"func.h"

Date& Date::operator+=(int extradays)
{
    if (extradays < 0)
    {
        return (*this).operator-=(-extradays);
    }
    _day += extradays;
    while (_day > GetMonthDay(_year, _month))
    {
        _day -= GetMonthDay(_year, _month);
        _month++;
        if (_month == 13)
        {
            _year++;
            _month = 1;
        }
    }
    return *this;
}

Date& Date::operator-=(int pastdays)
{
    if (pastdays < 0)
    {
        return *this += -pastdays;
    }
    _day -= pastdays;
    while (_day <= 0)
    {
        _month--;
        if (_month == 0)
        {
            _year--;
            _month = 12;
        }
        _day += GetMonthDay(_year, _month);
    }
    return *this;
}

bool Date::operator==(const Date& d)const
{
    return _year == d._year && _month == d._month && _day == d._day;
}

bool Date::operator!=(const Date& d)const
{
    return !(*this == d);
}

Date& Date::operator++()
{
    return *this += 1;
}

int Date::operator-(const Date& d)const
{
    Date Start1(1, 1, 1);
    int count1 = 0;
    Date Start2(Start1);
    int count2 = 0;
    while (Start1 != *this)
    {
        ++Start1;
        ++count1;
    }
    while (Start2 != d)
    {
        Start2.operator++();
        ++count2;
    }
    return count1 - count2;
}

int Date::GetMonthDay(int year, int month)const
{
    static int days[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
    {
        if (month == 2)
        {
            return 29;
        }
    }
    return days[month];
}

void Date::WeekdayCheck()const
{
    Date d;
    static const char* weekdays[] = { "周天" , "周一", "周二", "周三", "周四", "周五", "周六" };
    int ret = (*this).operator-(d) % 7 - 1;
    if (ret < 0)
    {
        ret = 6;
    }
    cout << weekdays[ret] << endl;
}

ostream& operator<<(ostream& out, const Date& d)
{
    out << d._year << d._month << d._day;
    return out;
}

istream& operator>>(istream& in, Date& d)
{
    in >> d._year >> d._month >> d._day;
    return in;
}

/////////////////////////////////////////////////////////////////////////////////////////////
void Stack::StackPush(int x)
{
    if (_capacity == _top)
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
    if (!Stack::StackEmpty())
    {
        _top--;
    }
}

int Stack::StackTop()
{
    if (!Stack::StackEmpty())
    {
        return _arr[_top - 1];
    }
    return -1;
}
bool Stack::StackEmpty()
{
    return _top == 0;
}

void Stack::functest1()
{
    Stack* n1 = new Stack(10);
    n1->StackPush(1);
    n1->StackPush(2);
    cout << n1->StackTop() << endl;
    n1->StackPop();
    cout << n1->StackTop() << endl;
    n1->StackPop();
    delete n1;          //自己开辟，自己释放
}

void Stack::functest2()
{
    //Stack* n1 = new Stack[2];
    //delete n1;
    ;
}