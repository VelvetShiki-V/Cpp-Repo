#include"func.h"

void test1()
{
	student s1;		//����s1��������Ϊstudent
	s1.student_info_register();		//�������s1����public��Ա����
	s1.student_info_print();		//�������s1����public��Ա����

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