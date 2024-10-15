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



void test2() {
	// static_cast
	//double a = 2.2;
	//int b = static_cast<int>(a);		// 相关类型隐式转换
	//cout << b << endl;

	//int* pb = &b;
	////int c = static_cast<int>(pb);		// 不相关类型无法隐式转换

	//// reinterpret_cast
	//int c = reinterpret_cast<int>(pb);		// 使用强制类型转换
	//cout << pb << endl;
	//printf("%x", c);

	// const_cast
	//const int a = 1;		// const类型变量不会被修改
	//int* pa = const_cast<int*>(&a);
	//*pa = 2;
	//cout << a << endl;
	//cout << *pa << endl;

	// dynamic_cast
	A aa;
	B bb;
	//bb = dynamic_cast<B>(aa);	// 父类对象无论如何都无法转为子类，非法

	A* a1 = new A;
	A* a2 = new B;
	B* b1 = dynamic_cast<B*>(a1);	// 指向父类本身的父类指针无法向下转换为子类指针，返回nullptr
	B* b2 = (B*)a1;					// C风格的强制类型转换，将父类指针强转为子类指针
	B* b3 = dynamic_cast<B*>(a2);	// 指向子类的父类指针可以向下转换为子类指针
	cout << a1 << " " << a2 << " " << b1 << " " << b2 << " " << b3 << endl;

	func(&aa);
	func(&bb);
}

void test3() {
	A a1;
	while (a1) {
		cin >> a1.a;
		cout << a1.a << endl;
	}
	//int b = A();
	//cout << b << endl;
}

void test4() {
	ifstream ifs("./log.txt", ifstream::in);
	//char c = ifs.get();
	//while (ifs.good()) {
	//	cout << c;
	//	c = ifs.get();
	//}
	string s, s1, s2;
	ifs >> s;
	getline(ifs, s1);
	//ifs.read((char*)s2.c_str(), sizeof ifs);
	cout << s << endl;
	cout << s1 << endl;
	//cout << s2 << endl;
	ifs.close();
}

int main() {
	//test1();
	//test2();
	//test3();
	test4();
	return 0;
}