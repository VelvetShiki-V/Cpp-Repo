#include"func.h"

//int b;

void test1()
{
	Student s1;		//声明s1对象，类型为student
	s1.student_info_register();		//由类对象s1调用public成员函数
	//s1.student_info_print();		//由类对象s1调用public成员函数

	//teacher t;
	//doctor d;
	//t.a = 10;
	//t.b = 20;
	//d.x = 1;
	//d.y = 2;
}

void test2()
{
	int a = 0;
	Student s1;
	Student s2;
	Student s3;
	Student s4;

	cout << sizeof(s1) << " " << sizeof(s2) << " " << sizeof(s3) << " " << sizeof(s4) << endl;

	s1.student_info_register();		//验证公共函数代码区
	s2.student_info_register();
	s3.student_info_register();
	s4.student_info_register();
}

void test3()
{
	//int a, & b = a;		//引用未初始化的变量
	//a = 10;
	//b = 20;
	//cout << a << " " << b << endl;

	//extern int a;
	//extern int b;
	//a = 1;
	//b = 2;
	//cout << "a = " << a << "   &a = 0x" << &a << endl;
	//cout << "b = " << b << "   &b = 0x" << &b << endl;

	//get_global();
}

void test4()
{
	int i = 1;
	double j = 2.2;
	char k = 'c';

	void* p1 = &i;
	void* p2 = &j;
	void* p3 = &k;

	cout << p1 << endl;
	
}

void test5()
{
	//Date d1, d2, d3;				// 日期类对象定义
	//d1.date_init(2000, 1, 1);		// 日期初始化
	//d2.date_init(2010, 10, 1);
	//d3.date_init(2022, 9, 9);

	//d1.print_date();				// 打印日期
	//d2.print_date();
	//d3.print_date();

	Date* p = nullptr;
	p->print_current();
	//p->date_init(2000, 1, 1);
	//p->print_date();
}

int main()
{
	//test1();
	//test2();
	//test3();
	//test4();
	test5();

	return 0;
}