#include"func.h"

void test1()
{
	//�ú���ȫ��ʹ�������ռ䣨����ȫ��
	using namespace myspace1;
	s1 s;
	printf("%d\n", i);
	printf("%d\n", s.j);
	printf("%f\n", s.k);

	using namespace myspace1::myspace2;		//�ڲ������ռ�Ƕ��չ��
	s2 ss;
	printf("%d\n", ss.l);
	printf("%lf\n", ss.m);
}

void test2()
{
	//ʹ�ò��������ռ䣬��ȫ���������ռ��е���������չ�����ϰ�ȫ��
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
	cout << myspace1::i << endl;	//��Ҫʲô����ʱչ��ʲô��������չ���޷�ʹ��
	myspace1::myspace2::s2 ss;
	cout << ss.l << endl;
}

int main()
{
	//test1();
	//test2();
	test3();
}