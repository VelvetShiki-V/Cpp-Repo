#include "func.h"

void output(char x = 'w', char x1 = 'o', char x2 = 'r', char x3 = 'l', char x4 = 'd')
{
	cout << x << x1 << x2 << x3 << x4 << endl;
}

void test1()
{
	char x = 'h', x1 = 'e', x2 = 'l', x3 = 'l', x4 = 'o';
	output(x, x1, x2, x3, x4);
	output();
}

void test2()
{
	ST Bot;
	StackInitial(&Bot);
}

void test3()
{
	int a = 2, b = 3;
	swap(a, b);
	float c = 5.3, d = 2.5;
	swap(c, d);
	double e = 9.8, f = 13.1;
	swap(e, f);
	cout << a << " " << b << endl;
	cout << c << " " << d << endl;
	cout << e << " " << f << endl;
	//auto x = multi(a, b);
	//auto y = multi(c, d);
	//cout << x << " " << typeid(x).name() << endl;
	//cout << y << " " << typeid(y).name() << endl;
	//cout << multi(e, f) << endl;

}

void test4()
{
	int a = 10;
	char b = 'x';
	int c[10] = { NULL };
	int* d = c;

	int& e = a;
	char& f = b;
	int(&g)[10] = c;
	int*& h = d;

	cout << a << " " << e << endl;
	++a;
	cout << a << " " << e << endl;
	++e;
	cout << a << " " << e << endl;

	int& i = a, & j = a, & k = a;		//一个变量可以有多个引用
	cout << i << " " << j << " " << k << endl;
	j -= 5;		//对别名的修改就是对被引用变量本身的修改，也即对其他别名的修改
	cout << a << " " << e << " " << i << " " << j << " " << k << endl;

	int x = 100;
	j = x;		//赋值——一个引用只能引用一个变量，后续不能改引用别的变量
	cout << a << " " << e << " " << i << " " << j << " " << k << endl;
}

void test5()
{
	int a = 10;
	const double& b = a;
	const int& c = 100;

	ST Bot;
	StackInitial1(Bot);
	StackPushBack(Bot, 1);
	StackPushBack(Bot, 2);
	StackPushBack(Bot, 3);
	StackPushBack(Bot, 4);
	cout << Bot.capacity << " " << Bot.top << endl;
	while (Bot.top)
	{
		cout << Bot.arr[Bot.top - 1] << " ";
		Bot.top--;
	}
}

const int& add(const int& a, const int& b)
{
	static const int c = a + b;
	return c;
}

void test6()
{
	const int& ret = add(1, 2);		//常变量引用，函数返回值初始化
	cout << ret << endl;
	cout << ret << endl;
}

void func(int)
{
	cout << "f(int)" << endl;
}

void func(int*)
{
	cout << "f(int*)" << endl;
}

void test7()
{
	int* p = NULL;
	int* p1 = nullptr;
	cout << p << " " << p1 << endl;
	cout << typeid(NULL).name() << endl;
	cout << typeid(nullptr).name() << endl;
	func(p);
	func(p1);
	func(0);
	func(NULL);
	func(nullptr);
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

	return 0;
}

//void func1(int x)
//{}
//void func2(int& x)
//{}
//void func3(const int& x)
//{}

//int main()
//{
//	int a = 10;
//	const int b = a;
//
//	func1(a);
//	func1(b);
//	func1(20);
//
//	func2(a);
//	//func2(b);
//	//func2(20);
//
//	func3(a);
//	func3(b);
//	func3(20);
//
//	double c = 10.01;
//	func1(c);	
//	//func2(c);
//	func3(c);
//}