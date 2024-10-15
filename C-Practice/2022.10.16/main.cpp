#include"template.h"
#include"heritance.h"
void test1() {
	// ��ģ������
	//int a = 1, b = 2;
	//int* pa = &a, * pb = &b;
	//cout << LESS(a, b) << endl;
	//cout << LESS(pa, pb) << endl;	// �����ػ�����ģ��ȽϽ�����ֵ
	//char c = 'c', d = 'd';
	//char* pc = &c, * pd = &d;
	//cout << LESS(c, d) << endl;
	//cout << LESS(pc, pd) << endl;	// �����ػ�����ģ��ȽϽ�����ֵ

	// ��ģ������
	int e = 10, f = 20;
	double g = 2.5, h = 3.3;
	char i = 'j', j = 'k';
	string s1("hello"), s2("world");
	print(e, f);
	print(e, g);
	print(g, h);
	print(i, j);
	print(g, s1);		// double, string�ػ�
	print(s1, s2);		// string, string�ػ�

	vector<int> v1;
	v1.push_back(1);
	v1.push_back(2);
	v1.push_back(3);
	v1.push_back(4);
	v1.push_back(5);
	list<int> ls1;
	ls1.push_back(6);
	ls1.push_back(7);
	ls1.push_back(8);
	ls1.push_back(9);
	ls1.push_back(10);
	print(v1, ls1);		// vector<int>, list<int>�ػ�
	cout << endl;

	vector<char> v2;
	v2.push_back('c');
	v2.push_back('y');
	list<string> ls2;
	ls2.push_back("ber");
	ls2.push_back("punk");
	print(v2, ls2);		// ������ػ���������
}

void test2() {
	using IC = template_specialization<int, char>;
	using II = template_specialization<int, int>;
	typedef template_specialization<char, char> CC;
	typedef template_specialization<int*, char*> PIPC;				// �������͵�ȫ�ػ�ģ��
	//typedef template_specialization<class T, vector<int>> TV;		// ��ȷ�����͵�ƫ�ػ�ģ�壬������ʾ��������
	using PIPI = template_specialization<int*, int*>;				// �������Ƶ�ƫ�ػ�ģ��
	using PCPC = template_specialization<char*, char*>;				// �������Ƶ�ƫ�ػ�ģ��
	//using TT = template_specialization<class T1, class T2>;		// ���������Ƶ���ͨ��ģ�壬������ʾ��������

	int a = 10, b = 20;
	char c = 'c', d = 'd';
	int* pa = &a, * pb = &b;
	char* pc = &c, * pd = &d;
	vector<int> v1{ 1,2,3,4,5 };
	IC t1(1, 'a');			// ��ͨģ��
	II t2(1, 3);			// ��ͨģ��
	CC t3('a', 'b');		// ��ͨģ��
	PIPC t4(pa, pc);		// ��ȷ�������ȫ�ػ�ģ��
	template_specialization<int*, vector<int>> t5(pa, v1);			// ��ȷ���������͵�ƫ�ػ�ģ��
	PIPI t6(pa, pb);		// �������Ƶ�ƫ�ػ�ģ��
	PCPC t7(pc, pd);		// �������Ƶ�ƫ�ػ�ģ��
}

void test3() {
	//Basic_info b1;
	//b1.basic_print();
	//cout << endl;
	//Student s1;
	//s1.m_Bname = "Elon";			// ��Ϊprotected���޷�����
	//s1.m_Bsex = "female";
	//s1.m_Bage = 18;
	//s1.basic_print();
	//s1.Student_print();
	//cout << endl;
	//Teacher t1;
	//t1.m_Bname = "Musk";
	//t1.m_Bage = 30;
	//t1.m_Bsex = "male";
	//t1.basic_print();
	//t1.Teacher_print();

	//Student s2;
	//s2.info_modify("Steve", "Male", 18, 2003, 3, "Art");
	//s2.basic_print();
	//s2.student_print();

	//Student s3;
	//s3.student_print();
}

void test4() {
	//Basic_info origin, *origin1;
	//Student s1;
	//Teacher t1;
	//s1.Student_input(9, 3, "chemistry", "Jack", "Female", 16);
	//t1.Teacher_input(1001, "assistant", "AI", "Pauli", "Male", 33);
	//origin = s1;				// ��������Ƭ��ֵ������
	//origin1 = &t1;				// ��ַ��ֵ
	//Basic_info& origin2 = t1;	// ���ó�ʼ��
	//origin.basic_print();
	//(*origin1).basic_print();
	//origin2.basic_print();
}

void test5() {
	//char a = 'A';
	//char b = 'B';
	//char* p1 = &a;
	//char* p2 = &b;
	//Student s1(1, 2, p1, "Science", "Shiki", "Male", 3, 1004, p2);
	Student s1(1, 2, "Science", "Shiki", "Male", 3, 1004);
	Student s2;
	Basic_info b;
	b = s1;
	//printName(b);
	//printName(s1);
	//s2 = s1;

	//s2.student_print();
	//Student s2(s1);
	//s1.student_print();
	//cout << endl;
	//s2.student_print();
	//cout << sizeof(b) << endl;
	//cout << sizeof(s) << endl;
	//cout << sizeof(t) << endl;
}

void test6() {
	//A a1;
	//B b1;
	//cout << sizeof(a1) << endl;
	//cout << sizeof(b1) << endl;
	//cout << &a1.A2 << endl;
	//cout << &b1.A2 << endl;
	//cout << "a1�г�Ա����A1��" << a1.A1 << endl;
	//a1.A1++;
	//a1.A1++;
	//a1.A1++;
	//cout << "b1�м̳е�A1���ԣ�" << b1.A1 << endl << endl;

	//cout << "a1�о�̬��Ա����A2��" << a1.A2 << endl;
	//a1.A2++;
	//a1.A2++;
	//a1.A2++;
	//cout << "b1�м̳еľ�̬A1���ԣ�" << b1.A2 << endl << endl;
	//cout << "��ʱ�ٻ�ͷ�۲츸��a1��̬���ԣ�" << a1.A2 << endl << endl;


}

void test7() {
	D d1;
	d1.A1 = 8;
	//d1.B::A1 = 1;
}

int main() {
	//test1();
	//test2();
	//test3();
	//test4();
	//test5();
	//test6();
	test7();
	return 0;
}