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

	int& i = a, & j = a, & k = a;		//һ�����������ж������
	cout << i << " " << j << " " << k << endl;
	j -= 5;		//�Ա������޸ľ��ǶԱ����ñ���������޸ģ�Ҳ���������������޸�
	cout << a << " " << e << " " << i << " " << j << " " << k << endl;

	int x = 100;
	j = x;		//��ֵ����һ������ֻ������һ���������������ܸ����ñ�ı���
	cout << a << " " << e << " " << i << " " << j << " " << k << endl;
}

int main()
{
	//test1();
	//test2();
	//test3();
	test4();
	return 0;
}