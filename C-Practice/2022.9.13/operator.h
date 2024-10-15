#ifndef __FUNC_H
#define __FUNC_H
#pragma once
#include<iostream>

class Date {
public:
	Date() {
		m_year = 2000;
		m_month = 1;
		m_day = 1;
	}
	bool operator==(const Date& d)const {
		return m_year == d.m_year && m_month == d.m_month && m_day == d.m_day;
	}
private:
	int m_year;
	int m_month;
	int m_day;
};

#endif  __FUNC_H