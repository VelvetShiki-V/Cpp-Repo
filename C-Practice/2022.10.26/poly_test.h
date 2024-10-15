#ifndef __POLY_TEST_H
#define __POLY_TEST_H
#pragma once
#include<iostream>
using namespace std;

class Phone {
public:
	virtual	Phone& phone_name() {
		cout << "普通手机" << endl;
		return *this;
	}
protected:
	string p_name;
};

class Huawei : public Phone {
public:
	virtual Huawei& phone_name() {
		cout << "华为手机" << endl;
		return *this;
	}
};

class Sumsang : public Phone {
public:
	virtual Phone& phone_name() {
		cout << "三星手机" << endl;
		return *this;
	}
};

class Xiaomi : public Phone {
public:
	virtual Phone& phone_name() {
		cout << "小米手机" << endl;
		return *this;
	}
};

void print_brand(Phone& p) {
	p.phone_name();
}

//class A {
//public:
//	virtual void func() {
//		cout << "class A : func" << endl;
//	}
//	virtual void func2() {
//		cout << "class A : func2" << endl;
//	}
//	virtual void func3() {
//		cout << "class A : func3" << endl;
//	}
//protected:
//	int A_a = 1;
//};
//
//typedef void(*VFTPTR)();
//void printFunc(VFTPTR table[]) {
//	for (size_t i = 0; table[i] != nullptr; i++) {
//		printf("VFtable[%d] : 0x%p  ", i, table[i]);
//		table[i]();
//		printf("\n");
//	}
//}
//
//class B {
//public:
//	virtual void func() {
//		cout << "class B : func()" << endl;
//	}
//	virtual void func4() {
//		cout << "class B : func4" << endl;
//	}
//protected:
//	int B_b = 2;
//};
//
//class C : public A , public B {
//public:
//	virtual void func() {
//		cout << "class C : func()" << endl;
//	}
//	virtual void func4() {
//		cout << "class C : func4" << endl;
//	}
//	virtual void func5() {
//		cout << "class C : func5" << endl;
//	}
//protected:
//	int C_c = 3;
//};

class Machine {
public:
	virtual void components() = 0;
};

class Elevator : public Machine {
public:
	virtual void components() {
		cout << "virtual void components()" << endl;
	}
};

// 菱形继承
class A {
public:
	void virtual func1() {
		cout << "class A::func1()" << endl;
	}
protected:
	int A_a1 = 0;
};

class B : virtual public A {
public:
	void virtual func1() {
		cout << "class B::func1()" << endl;
	}
protected:
	int B_b1 = 1;
};

class C : virtual public A {
public:
	void virtual func1() {
		cout << "class C::func1()" << endl;
	}
protected:
	int C_c1 = 2;
};

class D : public B, public C {
public:
	void virtual func1() {				// 菱形继承的子类必须重写父类函数
		cout << "class D::func1()" << endl;
	}
protected:
	int D_d1 = 3;
};

#endif // __POLY_TEST_H