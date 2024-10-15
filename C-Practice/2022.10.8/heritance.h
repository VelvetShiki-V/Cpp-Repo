#ifndef __HERITANCE_H
#define _HERITANCE_H
#pragma once
#include<iostream>
#include<string>
using namespace std;

class Basic_info {
public:
	void basic_print() {
		cout << "名字: " << m_Bname << endl;
		cout << "性别: " << m_Bsex << endl;
		cout << "年龄: " << m_Bage << endl;
	}
protected:
	string m_Bname = "who";
	string m_Bsex = "other";
	short m_Bage = 0;
	int m_id = 456;
};

class Student : public Basic_info {
public:
	void student_print() {
		cout << "学号: " << Basic_info::m_id << endl;
		cout << "年级: " << stu_grade << endl;
		cout << "部门: " << stu_depart << endl;
	}
	//void info_modify(string name, string sex, short age, int id, int grade, string dept) {
	//	m_Bname = name;
	//	m_Bsex = sex;
	//	m_Bage = age;
	//	stu_id = id;
	//	stu_grade = grade;
	//	stu_depart = dept;
	//}
protected:
	int m_id = 123;
	int stu_grade = 1;
	string stu_depart = "Science";
};

class Teacher : public Basic_info {
public:
	void Teacher_print() {
		cout << "学号: " << tea_id << endl;
		cout << "年级: " << staff << endl;
		cout << "部门: " << depart << endl;
	}
protected:
	int tea_id = 00001;
	string staff = "doctor";
	string depart = "Artitecture";
};
#endif // __HERITANCE_H
