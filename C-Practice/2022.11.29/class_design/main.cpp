#include "class.h"

void test1() {
	//Singleton* pobj = Singleton::create();
	//void* p = pobj->alloc(10);
	//pobj->dealloc(p);

	// B b1;
	//B* b2 = new B;
	//b2->destroy();
	//B b3(*b2);		// ���������ѽ�ֹ
	//B* b1 = B::create();
	//delete b1;

	StackOnly s = StackOnly::create();
	StackOnly s1(s);		// ����������
	//StackOnly* ps1 = new StackOnly(s);	// �Ƿ���operator new�ѽ�ֹ
	//StackOnly* ps2 = new StackOnly;		// �Ƿ���operator new�ѽ�ֹ
}

int main() {
	test1();
	return 0;
}