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
	bool operator==(const Date& d)const;			// ���ڼ�����
	bool operator!=(const Date& d)const;			// ���ڲ����
	Date operator+(const int extra_days)const;		// ���ڼ�����
	Date& operator+=(const int extra_days);			// ���ڱ��������
	Date operator-(const int past_days)const;		// ���ڼ�����
	Date& operator-=(const int past_days);			// ���ڱ��������
	Date& operator++();								// ���ڱ�������
	Date operator++(int);							// ���ں�������
	int operator-(const Date& d)const;				// ���ڼ�����
	void weekday_transfer()const;					// ����ת����

	// ͨ�ú���
	size_t get_month_days(const size_t year, const size_t month);

private:
	int m_year;
	int m_month;
	int m_day;
};

inline ostream& operator<<(ostream& out, const Date& d) {
	out << d.m_year << "��" << d.m_month << "��" << d.m_day << "��" << endl;
	return out;
}

inline istream& operator>>(istream& in, Date& d) {
	in >> d.m_year >>  d.m_month >> d.m_day;
	return in;
}

#endif  __FUNC_H