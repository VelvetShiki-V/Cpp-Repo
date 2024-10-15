#include"func.h"

bool Date::operator==(const Date& d)const  {
	return m_year == d.m_year && m_month == d.m_month && m_day == d.m_day;
}

bool Date::operator!=(const Date& d)const {
	return !Date::operator==(d);
}

Date Date::operator+(const int extra_days)const {
	Date d(*this);
	return d += extra_days;
}

Date& Date::operator+=(const int extra_days) {
	m_day += extra_days;
	while (m_day > get_month_days(m_year, m_month)) {
		m_day -= get_month_days(m_year, m_month);
		m_month++;
		if (m_month > 12) {
			m_year++;
			m_month = 1;
		}
	}
	return *this;
}

Date& Date::operator-=(const int past_days) {
	m_day -= past_days;
	while (m_day <= 0) {
		m_month--;
		if (m_month == 0) {
			m_year--;
			m_month = 12;
		}
		m_day += get_month_days(m_year, m_month);
	}
	return *this;
}

Date Date::operator-(const int past_days)const {
	Date d(*this);
	return d -= past_days;
}

Date& Date::operator++() {
	return *this += 1;
}

Date Date::operator++(int) {
	Date d(*this);
	++(*this);
	return d;
}

int Date::operator-(const Date& d)const {
	Date Init(1, 1, 1), Init2(1, 1, 1);
	int count1 = 0, count2 = 0;
	while (Init != *this) {
		++Init;
		++count1;
	}
	while (Init2 != d) {
		Init2++;
		count2++;
	}
	return count1 - count2;
}

void Date::weekday_transfer()const {
	Date Init = (1, 1, 1);
	int days = (*this) - Init;
	cout << "ĞÇÆÚ" << (days % 7 + 1) << endl;
}

size_t Date::get_month_days(const size_t year, const size_t month) {
	static int days[] = { 0, 31, 28, 31, 30, 31,30, 31, 31, 30, 31, 30, 31 };
	int day = days[month];
	if (month == 2 && (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0))) {
		day += 1;
	}
	return day;
}