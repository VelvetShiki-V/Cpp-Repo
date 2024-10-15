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

	Stack s1;					//直接构造
	Stack& s2 = s1;				//s1别名，不构造不拷贝
	s1.StackPush(1);			//s1对象可以使用类中的所有成员函数
	const Stack& s3 = s1;		//s1被s3引用，但s3是常对象，权限的缩小是允许的，不能使用s1中成员函数
	//s3.StackPush(1);的使用不被允许，即无法通过s3修改s1中的成员变量值		
	const Stack& s4 = 10;		//权限平移，常量10进行隐式类型转换，生成中间匿名对象Stack(10)，再被s4引用，不能使用该匿名对象中成员函数
	const Stack& s5(8);			//8隐式类型转换，默认构造出匿名对象Stack(8)，并被s5引用，但const修饰，不能使用该匿名对象中成员函数
	const Stack s6 = s1;		//权限缩小，s1对s6拷贝构造，但const修饰，不能使用对象中成员函数
	s3.~Stack();				//被const修饰的对象或引用仅能使用类中的默认析构
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
	Stack* s1 = new Stack[2]{7, 8};
	s1->StackPush(1);
	//s1.StackPush(2);		//s1是位于栈上的指向堆开辟的两个栈类空间的结构体指针
	s1[0].StackPush(3);
	s1[1].StackPush(1);
	s1[1].StackPush(2);
	//s1[1]->StackPush(3);	//s1[1]是s1指向的空间中位于下标[1]的类对象，不是指针，只能用.访问类中函数
	delete[] s1;
	s1 = nullptr;
}

void test7()
{
	Stack* p1 = (Stack*)malloc(sizeof(Stack) * 3);
	assert(p1);
	new(p1)Stack(8);
	new(p1 + 1)Stack(5);
	new(p1 + 2)Stack(4);
	//free(p1);				//free无法释放Stack中的_arr
	//free(p1->_arr);		//_arr私有，不可访问
	p1[2].StackPush(1);
	p1[2].StackPush(1);
	p1[2].StackPush(1);
	//类数组的销毁
	//delete[] p1;	
	//delete p1;
	//delete (p1 + 2);		//哪里malloc只能在哪个地址释放，中途释放是错误的
	//delete (p1 + 1);
	//free(p1);
	//p1[2].deleteARR();	//调用成员函数释放，效果等同于析构
	//p1[1].deleteARR();
	//p1->deleteARR();
	//free(p1);
	//p1 = nullptr;
	p1[2].~Stack();		//调用析构单独释放每个对象_arr
	p1[1].~Stack();
	p1->~Stack();
	free(p1);				//最后整体释放指针指向开辟的空间
}	

void test8()
{	
	//Stack* p = new Stack[10];			//通过调试观察前4个字节的额外空间
	//cout << sizeof(*p)*10 << endl;

	//int arr[10] = { 0 };
	//int sz = (sizeof(arr) / sizeof(int)) * 10;
	//cout << sz << endl;
	int* p1 = (int*)malloc(sizeof(int) * 5);
	int* p2 = (int*)malloc(sizeof(int) * 3);
	memset(p1, 0, sizeof(int) * 5);
	memset(p2, 0, sizeof(int) * 3);
	int* p3 = p1++;
	cout << p1 << endl;
	cout << p2 << endl;
	//swap(p3, p2);
	cout << p1 << endl;
	cout << p2 << endl;
	free(p3);
	free(p2);
}

int main()
{
	//test1(); 
	//test2();
	//test3();
	//test4();
	//test5();
	//test6();
	test7();
	//test8();
	return 0;
}