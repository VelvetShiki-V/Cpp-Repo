#pragma once
#include<iostream>
#include<string>
using namespace std;

class Student {
public:
	void student_info_register();
	//{
	//	cout << "����������ѧ���������Ա������ѧ��" << endl;
	//	cin >> name >> sex >> age >> ID;
	//	cout << endl;
	//}
	void student_info_print()
	{
		cout << "������" << m_name << endl << "�Ա�" << m_sex << endl << "���䣺" << m_age 
			<< endl << "ѧ�ţ�" << m_ID << endl;
	}
	bool student_verify(string name, string sex, short age, int ID)
	{
		return name == m_name && sex == m_sex
			&& age == m_age && ID == m_ID;
	}
private:
	string m_name;
	string m_sex;
	short m_age;
	int m_ID;
};

struct teacher
{
	int a;
	int b;
};

class doctor
{
	int x;
	int y;
};

//int a;
//extern int b;
static int a;
//void get_global();

// ����һ��������
class Date {
public:
	Date() {
		m_year = 2000;
		m_month = 1;
		m_day = 1;
	}

	Date(int year, int month, int day) {
		m_year = year;
		m_month = month;
		m_day = day;
	}

	void date_init(int year, int month, int day) {
		this->m_year = year;
		this->m_month = month;
		this->m_day = day;
	}
	void print_date() {
		cout << this->m_year << "��" << this->m_month << "��" << this->m_day << "��" << endl;
	}
	void print_current() {
		cout << "2022.9.9" << endl;
	}
private:
	int m_year;
	int m_month;
	int m_day;
};