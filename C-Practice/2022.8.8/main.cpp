#include"func.h"

void test1()
{
	Date d1(2024, 2, 29);
	Date d2;
	d1.WeekdayCheck();
	d2.WeekdayCheck();
}

void test2()
{
	//int arr[] = { 1,2,3 };
	//int* p = arr;
	//cout << typeid(*p).name() << endl;
	//cout << typeid(*arr).name() << endl;
	//cout << (*arr) << endl;

	Stack* s1 = new Stack(10);
}

void test3()
{
	//MyQueue q1;
	int* n1 = new int(5);
	int* n2 = new int[3];
	char* n3 = new char[10];
	char* n4 = new char[5]{'a','b','c'};

	delete n1;
	delete n2;
	delete n3;
	n3 = nullptr;
	delete n4;
	n4 = nullptr;
}

void test4()
{
	//Stack s1(5);
	//Stack s2 = 6;
	//s1.functest1();

	Stack s1;					//ֱ�ӹ���
	Stack& s2 = s1;				//s1�����������첻����
	s1.StackPush(1);			//s1�������ʹ�����е����г�Ա����
	const Stack& s3 = s1;		//s1��s3���ã���s3�ǳ�����Ȩ�޵���С������ģ�����ʹ��s1�г�Ա����
	//s3.StackPush(1);��ʹ�ò����������޷�ͨ��s3�޸�s1�еĳ�Ա����ֵ		
	const Stack& s4 = 10;		//Ȩ��ƽ�ƣ�����10������ʽ����ת���������м���������Stack(10)���ٱ�s4���ã�����ʹ�ø����������г�Ա����
	const Stack& s5(8);			//8��ʽ����ת����Ĭ�Ϲ������������Stack(8)������s5���ã���const���Σ�����ʹ�ø����������г�Ա����
	const Stack s6 = s1;		//Ȩ����С��s1��s6�������죬��const���Σ�����ʹ�ö����г�Ա����
	s3.~Stack();				//��const���εĶ�������ý���ʹ�����е�Ĭ������
	s4.~Stack();
	s6.~Stack();
}
int MyQueue::_nic = 10;
int MyQueue::_n = 10;

void test5()
{
	//Stack(5);
	//cout << (Stack(6)).StackTop() << endl;

	MyQueue s1;
	MyQueue s2(s1);
	cout << ++s1._nic << endl;
	cout << ++s2._nic << endl;
	cout << MyQueue(1)._nic << endl;
	//cout << s1._n << endl;
	//cout << s1._nic << endl;
}

void test6()
{
	Stack* s1 = new Stack[2];
	s1->StackPush(1);
	s1[1].StackPush(1);
	s1[1].StackPush(2);
	s1[1].StackPush(3);
	//s1->~Stack();
	//s1[1].~Stack();
	delete s1;
}

int main()
{
	//test1(); 
	//test2();
	//test3();
	//test4();
	//test5();
	test6();
	return 0;
}