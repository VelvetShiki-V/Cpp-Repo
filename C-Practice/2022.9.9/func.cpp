#include"func.h"

void Student::student_info_register() {
	cout << "����������ѧ���������Ա������ѧ��" << endl;
	cin >> m_name >> m_sex >> m_age >> m_ID;
	cout << endl;
}

//void get_global() {
//	extern int a;
//	extern int b;
//	a = 3;
//	b = 4;
//	cout << "a = " << a << "   &a = 0x" << &a << endl;
//	cout << "b = " << b << "   &b = 0x" << &b << endl;
//}
