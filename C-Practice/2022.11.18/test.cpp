#include<iostream>
#include<vector>
#include<string>
#include<map>
#include<set>
#include<array>
using namespace std;

void test1() {
	//int a = 1;
	//cout << typeid(a).name() << endl;
	//typeid(a).name() b = 2;		// 不能使用此种语法
	//decltype(a) b = 2;		// 等价于auto b = 2;

	//decltype(a) c = 5.5;
	//auto d = 5.5;
	//cout << typeid(c).name() << " " << c << endl;
	//cout << typeid(d).name() << " " << d << endl;
}

double GetMemory(size_t size)
{
	return size;
}

template<class T1, class T2>
T1 add(const T1& a, const T2& b){
	//auto tmp = a + b;
	decltype(a) tmp = a + b;
	cout << typeid(tmp).name() << endl;
	return tmp;
}

void test2() {
	//// 如果没有带参数，推导函数的类型
	//cout << typeid(decltype(GetMemory)).name() << endl;
	//// 如果带参数列表，推导的是函数返回值的类型,注意：此处只是推演，不会执行函数
	//cout << typeid(decltype(GetMemory(0))).name() << endl;
	int a = 10;
	double b = 20;
	auto ret = add(a, b);
	cout << typeid(ret).name() << endl;
}

class A {
public:
	~A() = delete;
};

void test3() {
	//array<int, 10> a = {1,2,3,4,5};
	//for (auto e : a) {
	//	cout << e << " ";
	//}
	//a[10];
	//a[10] = 1;

	//string s1("abcde");
	//string s2 = s1;
	//string s3 = move(s1);
	//cout << s1 << endl << s3 << endl;
	//A a1;
	A* pa = new A;
}

int main() {
	//test1();
	//test2();
	test3();
	return 0;
}