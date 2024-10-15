#ifndef __FUNC_H
#define __FUNC_H
#pragma once
#include<iostream>
using namespace std;

class Time {
public:
	Time(int hour, int minute, int second) 
		:m_hour(hour)
		,m_minute(minute)
		,m_second(second)
	{}
	//void time_init(int hour, int minute, int second) {
	//	m_hour = hour;
	//	m_minute = minute;
	//	m_second = second;
	//	p1 = new int;
	//	p2 = new int;
	//}
	//~Time() {
	//	delete p1;
	//	delete p2;
	//}
private:
	int m_hour;
	int m_minute;
	int m_second;
	//int* p1;
	//int* p2;
};

class Date {
	friend ostream& operator<<(ostream& out, const Date& d);
	friend istream& operator>>(istream& in, Date& d);
public:
	//Date (int year = 2000, int month = 1, int day = 1)
	//	:m_year(year)
	//	,m_month(month)
	//	,m_day(day)
	//	,m_time(13, 56, 24)
	//{}
	Date(int year = 2000, int month = 1, int day = 1) {
		m_year = year;
		m_month = month;
		m_day = day;
		//Time m_time(13, 56, 24);		// �Ƿ���ʼ��
	}
	bool operator==(const Date& d)const;			// ���ڼ�����
	bool operator!=(const Date& d)const;			// ���ڲ����
	void date_check();								// ������Ч�Լ��
	Date& operator=(const Date& d);					// ��ֵ���������
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
	int m_year = 2000;
	int m_month = 1;
	int m_day = 1;
	//Time m_time;
};

inline ostream& operator<<(ostream& out, const Date& d) {
	out << d.m_year << "��" << d.m_month << "��" << d.m_day << "��" << endl;
	return out;
}

inline istream& operator>>(istream& in, Date& d) {
	in >> d.m_year >>  d.m_month >> d.m_day;
	return in;
}

class Stack
{
public:
	//��ʼ���б�
	//Stack(int capacity = 4)
	//	: m_arr(new int[capacity])
	//	//:m_arr((int*)malloc(sizeof(int)*capacity))		//������new��Ҳ������malloc����������������ʵʩ��Ա�����ĳ�ʼ������
	//	, m_top(0)
	//	, m_capacity(capacity)
	//{
	//	memset(m_arr, 0, sizeof(int) * m_capacity); 	    //memset���ֽڳ�ʼ�������ڷ�char����ֻ����0��ʼ��
	//}

	//Stack()
	//	: m_arr(new int[4])
	//	//:m_arr((int*)malloc(sizeof(int)*capacity))		//������new��Ҳ������malloc����������������ʵʩ��Ա�����ĳ�ʼ������
	//	, m_top(0)
	//	, m_capacity(4)
	//{
	//	//memset(m_arr, 0, sizeof(int) * m_capacity); 	    //memset���ֽڳ�ʼ�������ڷ�char����ֻ����0��ʼ��
	//}

	//Stack(int capacity = 4) {
	//	m_arr = new int[capacity];
	//	m_capacity = 4;
	//	m_top = 0;
	//}

	//Stack(const Stack& s)				//�������죨�����
	//{
	//	m_capacity = s.m_capacity;
	//	m_top = s.m_top;
	//	m_arr = new int[m_capacity];
	//	memcpy(m_arr, s.m_arr, sizeof(int) * m_top);		//memset���ֽڿ���
	//}
	void mem_set() {
		memset(m_arr, 0, sizeof(int) * m_capacity);
	}
private:
	//int* m_arr = new int[sizeof(int) * 4];
	//int* m_arr = nullptr;
	int m_capacity = 10;
	int* m_arr = new int[m_capacity];
	int m_top = 0;
};

class Order {
public:
	Order(int val = 10)
		:m_a(val)
		,m_b(m_a)
	{}
	void test() {
		cout << m_a << " " << m_b << endl;
	}
private:
	int m_b;
	int m_a;
};

#endif  __FUNC_H