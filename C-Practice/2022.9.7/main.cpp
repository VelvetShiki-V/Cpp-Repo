#include"func.h"

void test1()
{
	student s1;		//声明s1对象，类型为student
	s1.student_info_register();		//由类对象s1调用public成员函数
	s1.student_info_print();		//由类对象s1调用public成员函数

	teacher t;
	doctor d;
	t.a = 10;
	t.b = 20;
	//d.x = 1;
	//d.y = 2;
}

int main()
{
	test1();
	return 0;
}