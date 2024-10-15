#ifndef __FUNC_H
#define __FUNC_H
#pragma once
#include<iostream>
using namespace std;

class Date {
	friend ostream& operator<<(ostream& out, const Date& d);
	friend istream& operator>>(istream& in, Date& d);
public:
	Date(int year = 2000, int month = 1, int day = 1) {
		m_year = year;
		m_month = month;
		m_day = day;
	}
	bool operator==(const Date& d)const;			// 日期加天数
	bool operator!=(const Date& d)const;			// 日期不相等
	Date operator+(const int extra_days)const;		// 日期加天数
	Date& operator+=(const int extra_days);			// 日期本身加天数
	Date operator-(const int past_days)const;		// 日期减天数
	Date& operator-=(const int past_days);			// 日期本身减天数
	Date& operator++();								// 日期本身自增
	Date operator++(int);							// 日期后置自增
	int operator-(const Date& d)const;				// 日期减日期
	void weekday_transfer()const;					// 日期转星期

	// 通用函数
	size_t get_month_days(const size_t year, const size_t month);

private:
	int m_year;
	int m_month;
	int m_day;
};

inline ostream& operator<<(ostream& out, const Date& d) {
	out << d.m_year << "年" << d.m_month << "月" << d.m_day << "日" << endl;
	return out;
}

inline istream& operator>>(istream& in, Date& d) {
	in >> d.m_year >>  d.m_month >> d.m_day;
	return in;
}

#endif  __FUNC_H