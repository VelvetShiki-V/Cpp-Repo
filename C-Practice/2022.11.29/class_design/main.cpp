#include "class.h"

void test1() {
	//Singleton* pobj = Singleton::create();
	//void* p = pobj->alloc(10);
	//pobj->dealloc(p);

	// B b1;
	//B* b2 = new B;
	//b2->destroy();
	//B b3(*b2);		// 拷贝构造已禁止
	//B* b1 = B::create();
	//delete b1;

	StackOnly s = StackOnly::create();
	StackOnly s1(s);		// 允许拷贝构造
	//StackOnly* ps1 = new StackOnly(s);	// 非法，operator new已禁止
	//StackOnly* ps2 = new StackOnly;		// 非法，operator new已禁止
}

int main() {
	test1();
	return 0;
}