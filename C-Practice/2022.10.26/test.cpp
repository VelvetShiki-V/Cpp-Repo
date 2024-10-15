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

//void test2() {
//	//A a1;
//	//a1.func();
//	//a1.func2();
//	//a1.func3();
//	////cout << sizeof a1 << endl;
//	//B b1;
//	//cout << sizeof b1 << endl;
//	//b1.func();
//	//b1.func2();
//	//b1.func3();
//	B b1;
//	printFunc((VFTPTR*)*(int*)&b1);
//}
//
//void test3() {
//	// Machine m;
//	//Elevator e;
//	//e.components();
//
//	//Machine* p1 = new Elevator;
//	//p1->components();
//}
//
//void test4() {
//	C c1;
//	//cout << sizeof c1 << endl;
//	cout << "class A继承虚函数成员：" << endl;
//	printFunc((VFTPTR*)*(int*)&c1);
//	cout << "class B继承虚函数成员：" << endl;
//	B* p = &c1;
//	printFunc((VFTPTR*)*(int*)p);
//
//	cout << endl;
//	printf("C::func()的地址：0x%p\n", &C::func);
//
//	//A* p1 = &c1;
//	//p1->func();
//	//B* p2 = &c1;
//	//p2->func();
//}

void test5() {
	D d1;
	d1.func1();
}

int main() { 
	//test1(); 
	//test2();
	//test3();
	//test4();
	test5();
	return 0;
}