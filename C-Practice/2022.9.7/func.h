#pragma once
#include<iostream>
#include<string>
using namespace std;

class student
{
public:
	void student_info_register();
	//{
	//	cout << "����������ѧ���������Ա������ѧ��" << endl;
	//	cin >> name >> sex >> age >> ID;
	//	cout << endl;
	//}
	void student_info_print()
	{
		cout << "������" << name << endl << "�Ա�" << sex << endl << "���䣺" << age 
			<< endl << "ѧ�ţ�" << ID << endl;
	}
private:
	string name;
	string sex;
	short age;
	int ID;
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