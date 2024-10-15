#pragma once
#include<iostream>
#include<string>
//#include<stdlib.h>

using namespace std;

class Student {
public:
	void student_info_register();
	//{
	//	cout << "请依次输入学生姓名，性别，年龄和学号" << endl;
	//	cin >> name >> sex >> age >> ID;
	//	cout << endl;
	//}
	void student_info_print()
	{
		cout << "姓名：" << m_name << endl << "性别：" << m_sex << endl << "年龄：" << m_age 
			<< endl << "学号：" << m_ID << endl;
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

// 定义一个日期类
class Date {
public:
	Date() {
		m_year = 2000;
		m_month = 10;
		m_day = 1;
		//m_ptr = (int*)malloc(10);
		cout << "调用默认构造函数Date()" << endl;
	}
	//Date(int year = 2000, int month = 1, int day = 10) {
	//	m_year = year;
	//	m_month = month;
	//	m_day = day;
	//}
	~Date() {
		//free(m_ptr);		 // 堆上显示开辟的内存空间必须手动清理，在析构函数中定义交给编译器自动完成
		//m_ptr = nullptr;	 // 手动置空好习惯，也方便观察
		m_year = 0;			 // 栈上成员变量可选择性清理置空，因为会随着函数销毁而自动清理
		m_month = 0;
		m_day = 0;
		cout << "调用默认析构函数~Date()" << endl;
	}

	Date(const Date& d) {
		m_year = d.m_year;
		m_month = d.m_month;
		m_day = d.m_day;
		cout << "调用传引用的拷贝构造Date(const Date& d)" << endl;
	}
	Date(const Date* d) {
		m_year = d->m_year;
		m_month = d->m_month;
		m_day = d->m_day;
		cout << "调用传指针的拷贝构造Date(const Date* d)" << endl;
	}

	//Date(int year, int month, int day) {
	//	m_year = year;
	//	m_month = month;
	//	m_day = day;
	//}

	void date_init(int year, int month, int day) {
		this->m_year = year;
		this->m_month = month;
		this->m_day = day;
	}
	void print_date() {
		cout << this->m_year << "年" << this->m_month << "月" << this->m_day << "日" << endl;
	}
	void print_current() {
		cout << "2022.9.9" << endl;
	}
private:
	int m_year;
	int m_month;
	int m_day;
	//int* m_ptr;
	//int m_year = 2000;
	//int m_month = 1;
	//int m_day = 1;
};

class B {
public:
	B() {
		p1 = (int*)malloc(10);
		p2 = (int*)malloc(10);
		cout << "B()" << endl;
	}
	~B() {
		free(p1);
		free(p2);
		p1 = nullptr;
		p2 = nullptr;
		cout << "~B()" << endl;
	}
private:
	int* p1;
	int* p2;
};

class A {
public:
	void print() {
		cout << a << " " << b << endl;
	}
private:
	int a;
	int b;
	B c;
};