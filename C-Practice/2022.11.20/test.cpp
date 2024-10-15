#include<iostream>
#include<functional>
#include <algorithm>
#include<vector>
#include <list>
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

//template<class T1, class T2>
//T1 add(const T1& a, const T2& b){
//	//auto tmp = a + b;
//	decltype(a) tmp = a + b;
//	cout << typeid(tmp).name() << endl;
//	return tmp;
//}

void test2() {
	//// 如果没有带参数，推导函数的类型
	//cout << typeid(decltype(GetMemory)).name() << endl;
	//// 如果带参数列表，推导的是函数返回值的类型,注意：此处只是推演，不会执行函数
	//cout << typeid(decltype(GetMemory(0))).name() << endl;
	//int a = 10;
	//double b = 20;
	//auto ret = add(a, b);
	//cout << typeid(ret).name() << endl;
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

void func2() {
	cout << endl;
}

template<class T, class ...Args>
void func2(const T& cur, Args... args) {
	cout << "当前识别参数为: " << cur << " " << "剩余参数包个数: " << sizeof...(args) << endl;
	func2(args...);
}

template<class T>
int print(const T& x) {
	cout << x << " ";
	return 0;
}

template<class ...Args>
void func3(Args... args) {
	int a[] = { print(args)... };
	cout << endl;
}

void test4() {
	//func2();
	//func2(1);
	//func2(1, 2, 3);
	//func2("abc", make_pair(3, 4), 2.2);
	//func2("abc", 'a', 'c', "test", 5.5);
	func3("abc", 'a', 'c', "test", 5.5);
	func3(1, 2, 3, 4, 5, 6, 7, 8, 9);
}

class Student {
public:
	Student(string name, string sex, int id, short age)
		:m_name(name)
		,m_sex(sex)
		,m_identity(id)
		,m_age(age)
	{
		//cout << "Student构造函数" << endl;
	}
	Student(const Student& s) {
		m_name = s.m_name;
		m_sex = s.m_sex;
		m_identity = s.m_identity;
		m_age = s.m_age;
		//cout << "Student拷贝构造函数" << endl;
	}
	void printStudent() {
		cout << m_name << endl << m_sex << endl << m_identity << endl << m_age << endl;
	}
	string m_name;
	string m_sex;
	int m_identity;
	short m_age;
};

void test5() {
	list<Student> l;
	l.push_back(Student(string("shiki"), string("male"), 1234, 18));
	cout << endl;
	l.emplace_back("velvet", "female", 5678, 19);
	cout << endl;
	for (auto& e : l) {
		e.printStudent();
		cout << endl;
	}
	//vector<pair<int, int>> v1;
	//v1.push_back(make_pair(1, 1));
	//v1.emplace(v1.begin(), 3, 3);		// 头插
	//v1.emplace_back(2, 2);		// 尾插
	//for (auto e: v1) {
	//	cout << e.first << " " << e.second << endl;
	//}
}

void test6() {
	//auto add = [](int a, int b)->int{return a + b; };
	//auto multi = [](int a, int b){return a * b; };
	//int a = add(10, 20);
	//int b = multi(10, 10);
	//cout << a << " " << b << endl;

	//auto Swap = [](int& a, int& b) {
	//	int tmp = a;
	//	a = b;
	//	b = tmp;
	//};
	//Swap(a, b);
	//cout << a << " " << b << endl;
	vector<Student> vs;
	vs.emplace_back("asgard", "male", 1, 10);
	vs.emplace_back("velvet", "female", 3, 15);
	vs.emplace_back("shiki", "male", 2, 8);
	vs.emplace_back("kratos", "male", 5, 47);
	vs.emplace_back("calpis", "female", 4, 24);
	sort(vs.begin(), vs.end(), [](const Student& s1, const Student& s2) {
		return s1.m_age > s2.m_age;		// 条件可变，此处根据年龄降序排序
		}
	);
	for (auto& k : vs) {
		k.printStudent();
		cout << endl;
	}
}

void test7() {
	int a = 0, b = 1, c = 2;
	auto f1 = [=]{cout << a << " " << b << " " << c << endl; };
	f1();
	auto f2 = [&] {
		a += 10;
		b += a;
	};
	f2();
	cout << a << " " << b << endl << endl;

	// 混合捕捉
	cout << "a: " << &a << endl << "b: " << &b << endl << endl;
	auto f3 = [=, &a] {
		cout << "lambda中: " << endl;
		cout << "引用a: " << & a << endl << "局部b: " << &b << endl;
	};
	f3();
}



template<class Func, class T>
T calc(Func f, T t1, T t2) {
	static int cnt;
	cnt++;
	cout << typeid(f).name() << endl;
	cout << "该模板类调用次数：" << cnt << endl;
	return f(t1, t2);
}


struct division2 {
	double operator()(double a, double b) {
		return a / b;
	}
};

int subtraction(int a, int b) {
	return a - b;
}

class sum {
public:
	static int add_s(int a, int b) {
		return a + b;
	}
	int add(int a, int b) {
		return a + b;
	}
};

void test8() {
	//calc(division, 1.1, 2.2);
	//calc(division2(), 2.2, 3.3);
	//calc([](double a, double b)->double {return a / b; }, 3.3, 4.4);
	//function<double(double, double)> f1 = division;
	//function<double(double, double)> f2 = division2();
	//function<double(double, double)> f3 = [](double a, double b)->double {return a / b; };
	//calc(f1, 5.5, 3.3);
	//calc(f2, 6.6, 3.5);
	//calc(f3, 10.0, 2.1);
	function<int(int, int)> f4 = sum::add_s;
	auto ret = f4(1, 1);
	function<int(sum, int, int)> f5 = &sum::add;
	auto ret2 = f5(sum(), 1, 2);
	cout << ret << " " << ret2 << endl;
}

int multi(int a, int b, int c) {
	cout << "a: " << a << " " << "b: " << b << " " << "c: " << c << endl;
	return a * b * c;
}

void test9() {
	using namespace placeholders;
	//cout << division(5, 10) << endl;
	//function<double(double, double)> adjustOrder = bind(division, _2, _1);
	//cout << adjustOrder(5, 10) << endl;
	function<int(int, int)> add1 = bind(&sum::add, sum(), _1, _2);
	function<int(int, int)> sub2 = bind(subtraction, _2, _1);
	function<int(int, int)> multi3 = bind(multi, 5, _1, _2);
	//function<int(int, int)> multi3 = bind(multi, _1, 5, _2);
	cout << multi3(10, 20) << endl;
	//map<char, function<int(int, int)>> add_sub = { {'+', add1}, {'-', sub2} };
	//char ch;
	//int a, b;
	//while (cin >> a >> b >> ch) {
	//	switch (ch) {
	//	case '+': cout << add_sub[ch](a, b) << endl; break;
	//	case '-': cout << add_sub[ch](a, b) << endl; break;
	//	}
	//}
}

class Exception {
public:
	Exception(const string& s, int err)
		:error_message(s)
		,error_id(err)
	{}
	void what() const {
		cout << error_message << endl;
	}
	void errorid() const {
		cout << error_id << endl;
	}
private:
	string error_message;
	int error_id;
};

double division(double a, double b) {
	//if (b == 0) throw string("denominator shall not be zero");
	if (b == 0) {
		Exception e(string("denominator shall not be zero"), 1);
		throw e;
	}
	return a / b;
}

void test10() {
	try {
		int a, b;
		cin >> a >> b;
		cout << division(a, b) << endl;
	}
	catch (const Exception& e) {		// 接收中间Exception对象
		e.what();
	}
	catch (...) {
		cout << "未知异常" << endl;
	}
	string s1 = "abc";
	cout << s1 << endl;
}

int main() {
	//test1();
	//test2();
	//test3();
	//test4();
	//test5();
	//test6();
	//test7();
	//test8();
	//test9();
	test10();
	return 0;
}