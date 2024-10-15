#include "exception.h"

void test1() {
	while (1) {
		try {
			sqlConnection();
			dataHandle();
			websiteResponse();
		}
		catch (Exception& e) {
			//cout << typeid(e).name() << endl;		// �۲촫����������
			e.what();				// ��ӡ������д��������Ϣ�ʹ�����
			e.errorid();
		}
		catch (...) {
			cout << "δ֪����" << endl;
		}
		cout << endl;
		Sleep(1000);
	}
}

double division(const double& a, const double& b) {
	if (b == 0) throw(string("denominator shall not be zero"));
	return a / b;
}

void test2() {
	try {
		int* p1 = new int;
		int* p2 = new int;
		Smart_ptr<int> spt1(p1);
		Smart_ptr<int> spt2(p2);
		cout << division(5, 7) << endl;			// ����1���������������Դ�����ͷ�
		//cout << division(5, 0) << endl;		// ����2������0�������쳣��p1��p2��Դ�����ᱻ�ͷţ��ڴ�й©
		*spt1 = 10;
		*spt2 = 20;
		cout << *p1 << " " << *spt2 << endl;
	}
	catch (const string& s) {
		cout << s << endl;
	}
}

int main() {
	//test1();
	test2();
	return 0;
}