#pragma once
#include<iostream>
#include<string>
using namespace std;

class student
{
public:
	void student_info_register();
	//{
	//	cout << "请依次输入学生姓名，性别，年龄和学号" << endl;
	//	cin >> name >> sex >> age >> ID;
	//	cout << endl;
	//}
	void student_info_print()
	{
		cout << "姓名：" << name << endl << "性别：" << sex << endl << "年龄：" << age 
			<< endl << "学号：" << ID << endl;
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