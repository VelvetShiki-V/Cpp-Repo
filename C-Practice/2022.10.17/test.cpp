#include"poly_test.h"

void test1() {
	Phone p1;
	//p1.phone_name();
	Huawei p2;
	//p2.phone_name();
	Sumsang p3;
	//p3.phone_name();
	Xiaomi p4; 
	//p4.phone_name();
	print_brand(p1);
	print_brand(p2);
	print_brand(p3);
	print_brand(p4);
}

void test2() {
	A a1;
	a1.func();
	a1.func2();
	a1.func3();
	//cout << sizeof a1 << endl;
	B b1;
	cout << sizeof b1 << endl;
	b1.func();
	b1.func2();
	b1.func3();
}

int main() { 
	//test1();
	test2();
	return 0;
}