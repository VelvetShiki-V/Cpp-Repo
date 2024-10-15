#include<iostream>
using namespace std;

class Date
{
    friend ostream& operator<<(ostream& out, const Date& d);
    friend istream& operator>>(istream& in, Date& d);
    public:
        void DateCheck(int& year, int& month, int& day)
        {
            if(year < 1)
            {
                cout << "年份输入错误，已修正为公元1年" << endl;
                year = 1;
            }
            if(month > 12 || month < 1)
            {
                cout << "月份输入错误，已修正为1月" << endl;
                month = 1;
            }
            if(day < 1 || day > GetMonthDay(year, month))
            {
                cout << "日期输入错误，已修正为1日" << endl;
                day = 1;
            }
        }
        Date(int year = 2000, int month = 1, int day = 1)
        {
            DateCheck(year, month, day);
            _year = year;
            _month = month;
            _day = day;
        }
        Date(const Date& d)
        {
            _year = d._year;
            _month = d._month;
            _day = d._day;
        }
        void DateShow()const
        {
            cout << _year << "年" << _month << "月" << _day << "日" << endl;
        }
        int GetMonthDay(int year, int month)
        {
            static int days[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
            if((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
            {
                if(month == 2)
                {
                    return 29;
                }
            }
            return days[month];
        }
        bool operator==(const Date& d)const
        {
            return _year == d._year && _month == d._month && _day == d._day;
        }
        Date& operator+=(int extradays)
        {
            if(extradays < 0)
            {
                return (*this).operator-=(-extradays);
            }
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
            return *this;
        }
        Date operator+(int extradays)const
        {
            Date d(*this);
            d += extradays;
            return d;
        }
        Date& operator-=(int pastdays)
        {
            if(pastdays < 0)
            {
                return *this += -pastdays;
            }
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
        Date operator-(int pastdays)const
        {
            Date d = *this;
            d.operator-=(pastdays);
            return d;
        }
        bool operator!=(const Date& d)const
        {
            return !(*this == d);
        }
        Date& operator++()
        {
            return *this += 1;
        }
        Date operator++(int)        //如果不加参数，仅按返回值无法构成重载函数
        {
            Date d(*this);
            *this += 1;
            return d;
        }
        int operator-(const Date& d)const
        {
            Date Start1(1, 1, 1);
            int count1 = 0;
            Date Start2(Start1);
            int count2 = 0;
            while(Start1 != *this)
            {
                ++Start1;
                ++count1;
            }
            while(Start2 != d)
            {
                Start2.operator++();
                ++count2;
            }
            return count2 - count1;
        }
    private:
        int _year;
        int _month;
        int _day;
};

inline ostream& operator<<(ostream& out, const Date& d)
{
   out << d._year << "年" << d._month << "月" << d._day << "日" << endl;
   return out;
}
inline istream& operator>>(istream& in, Date& d)
{
    in >> d._year >> d._month >> d._day;
    d.DateCheck(d._year, d._month, d._day);
    return in;
}
