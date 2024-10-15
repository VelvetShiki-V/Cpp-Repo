#include"func.h"

void test1()
{
	//该函数全局使用命名空间（不安全）
	using namespace myspace1;
	s1 s;
	printf("%d\n", i);
	printf("%d\n", s.j);
	printf("%f\n", s.k);

	using namespace myspace1::myspace2;		//内部命名空间嵌套展开
	s2 ss;
	printf("%d\n", ss.l);
	printf("%lf\n", ss.m);
}

void test2()
{
	//使用部分命名空间，不全部将命名空间中的所有内容展开（较安全）
	using std::cout;
	using std::endl;
	using myspace1::i;
	std::cout << i << std::endl;
	using myspace1::myspace2::s2;
	s2 ss;
	cout << ss.m << endl;
}

void test3()
{
	using namespace std;	
	cout << myspace1::i << endl;	//需要什么就临时展开什么，后续不展开无法使用
	myspace1::myspace2::s2 ss;
	cout << ss.l << endl;
}

int main()
{
	//test1();
	//test2();
	test3();
}