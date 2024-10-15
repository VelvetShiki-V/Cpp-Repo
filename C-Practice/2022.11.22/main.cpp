#include "exception.h"

void test1() {
	while (1) {
		try {
			sqlConnection();
			dataHandle();
			websiteResponse();
		}
		catch (Exception& e) {
			//cout << typeid(e).name() << endl;		// 观察传入子类类型
			e.what();				// 打印子类重写错误函数信息和错误码
			e.errorid();
		}
		catch (...) {
			cout << "未知错误" << endl;
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
		cout << division(5, 7) << endl;			// 测试1——正常情况，资源将被释放
		//cout << division(5, 0) << endl;		// 测试2——除0出错抛异常，p1和p2资源将不会被释放，内存泄漏
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