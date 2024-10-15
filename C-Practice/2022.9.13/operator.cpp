#include"func.h"
using namespace std;

void test1() {
	Date d1, d2;
	cout << (d1 == d2) << endl;
	cout << d1.operator==(d2) << endl;		// ½âÊÍÎªd1.operator==(&d1, d2)
}

int main() {
	test1();
}