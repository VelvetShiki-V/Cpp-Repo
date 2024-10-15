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

class A {
public:
	void func() {
		cout << "func" << endl;
	}
	 void func2() {
		cout << "func2" << endl;
	}
	 void func3() {
		cout << "func3" << endl;
	}
protected:
	int A_a = 0;
};

class B : public A{
public:

protected:
	int B_b = 8;
};

#endif // __POLY_TEST_H