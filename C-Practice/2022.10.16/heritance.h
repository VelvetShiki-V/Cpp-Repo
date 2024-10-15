#ifndef __HERITANCE_H
#define __HERITANCE_H
#pragma once
#include<iostream>
#include<string>
using namespace std;

class Basic_info {
public:
	friend void printName(const Basic_info& b);
	Basic_info() {
		cout << "�����޲θ��๹�캯��" << endl;
	}
	Basic_info(string nm, string sx, short ag, int id)
		: m_Bname(nm)
		, m_Bsex(sx)
		, m_Bage(ag)
		, m_Bid(id)
	{
		cout << "������ȱʡ���๹�캯��" << endl;
	}
	Basic_info(const Basic_info& b)
		:m_Bname(b.m_Bname)
		,m_Bsex(b.m_Bsex)
		,m_Bage(b.m_Bage)
		,m_Bid(b.m_Bid)
	{
		cout << "���ø�����ʾ�������캯��" << endl;
		//group_owner = new char;
		//memcpy(group_owner, b.group_owner, 1);
	}
	Basic_info& operator=(const Basic_info& b) {
		cout << "���ø��ำֵ����" << endl;
		m_Bname = b.m_Bname;
		m_Bsex = b.m_Bsex;
		m_Bage = b.m_Bage;
		m_Bid = b.m_Bid;
		return *this;
	}
	~Basic_info() {
		cout << "���ø�����������" << endl;
	}
	//Basic_info(string nm = "who", string sx = "other", short ag = 0, int id = 456)
	//	:m_Bname(nm)
	//	,m_Bsex(sx)
	//	,m_Bage(ag)
	//	,m_Bid(id)
	//{
	//	cout << "���ø��๹�캯��" << endl;
	//}
	//void basic_print() {
	//	cout << "����: " << m_Bname << endl;
	//	cout << "�Ա�: " << m_Bsex << endl;
	//	cout << "����: " << m_Bage << endl;
	//	cout << endl;
	//}
protected:
	string m_Bname;
	string m_Bsex;
	short m_Bage;
	int m_Bid;
	//char* group_owner;
};

//void printName(const Basic_info& b, const Student& s) {
//	cout << b.m_Bname << endl;
//	cout << s.stu_grade << endl;
//}

class Student : public Basic_info {
public:
	Student()
	{
		cout << "�����޲����๹�캯��" << endl;
	}
	Student(int id, int gd, string dept, string p_nm, string p_sx, short p_ag, int p_id)
		:m_id(id)
		,stu_grade(gd)
		,stu_depart(dept)
		,Basic_info(p_nm, p_sx, p_ag, p_id)
	{
		cout << "������ȱʡ���๹�캯��" << endl;
	}
	Student(const Student& s) 
		:Basic_info(s)
		,m_id(s.m_id)
		,stu_grade(s.stu_grade)
		,stu_depart(s.stu_depart)
	{
		cout << "����������ʾ�������캯��" << endl;
	}
	Student& operator=(const Student& s) {
		Basic_info::operator=(s);
		cout << "�������ำֵ����" << endl;
		m_id = s.m_id;
		stu_grade = s.stu_grade;
		stu_depart = s.stu_depart;
		return *this;
	}
	~Student() {
		Basic_info::~Basic_info();
		cout << "����������������" << endl;
	}
	//Student(const Student& s) {
	//	cout << "����������ʾ�������캯��" << endl;
	//	m_id = s.m_id;
	//	stu_grade = s.stu_grade;
	//	stu_depart = s.stu_depart;
	//	m_Bname = s.m_Bname;
	//	m_Bsex = s.m_Bsex;
	//	m_Bage = s.m_Bage;
	//}

	void student_print() {
		cout << "������" << m_Bname << endl;
		cout << "�Ա�" << m_Bsex << endl;
		cout << "���䣺" << m_Bage << endl;
		cout << "ѧ��: " << Basic_info::m_Bid << endl;
		cout << "�꼶: " << stu_grade << endl;
		cout << "����: " << stu_depart << endl;
	}
	//void Student_input(int id, int grd, string dept, string nm, string sex, short age) {
	//	m_id = id;
	//	stu_grade = grd;
	//	stu_depart = dept;
	//	m_Bname = nm;
	//	m_Bsex = sex;
	//	m_Bage = age;
	//}
	//void info_modify(string name, string sex, short age, int id, int grade, string dept) {
	//	m_Bname = name;
	//	m_Bsex = sex;
	//	m_Bage = age;
	//	stu_id = id;
	//	stu_grade = grade;
	//	stu_depart = dept;
	//}
protected:
	int m_id;
	int stu_grade;
	char* stu_group;
	string stu_depart;
};

class Teacher : public Basic_info {
public:
	void Teacher_print() {
		cout << "��ʦ��: " << tea_id << endl;
		cout << "�꼶: " << staff << endl;
		cout << "����: " << depart << endl;
	}
	void Teacher_input(int id, string stf, string dept, string nm, string sex, short age) {
		tea_id = id;
		staff = stf;
		depart = dept;
		m_Bname = nm;
		m_Bsex = sex;
		m_Bage = age;
	}
protected:
	int tea_id = 00001;
	string staff = "doctor";
	string depart = "Artitecture";
};

class A {
public:
	int A1 = 1;
};

class B : virtual public A {
public:
	int B1 = 2;
};

class C : virtual public A {
public:
	int C1 = 3;
};

class D: public B, public C {
public:
	int D1 = 4;
};
#endif // __HERITANCE_H
