#include"func.h"

void test1() {
	Date d1, d2;
	cout << (d1 == d2) << endl;
	cout << d1.operator==(d2) << endl;		// ½âÊÍÎªd1.operator==(&d1, d2)
}

void test2() {
	Date d1;
	Date d2(2022, 9, 14);
	Date d3(1949, 10, 1);
	Date d4(d1);

	cout << (d1 == d2) << endl;
	cout << (d1 == d4) << endl;
	cout << d1.operator!=(d2) << endl;
	cout << ((d1 + 20000) - d2) << endl;
	cout << (d2 - d1) << endl;
	cout << (d3 - d2) << endl;
	cout << (d4 -= 1000) << endl;
	cout << (d3 - 10000) << endl;
	cout << "d1" << endl;
	d1.weekday_transfer();
	(++d1).weekday_transfer();
	(++d1).weekday_transfer();
	(++d1).weekday_transfer();
	(++d1).weekday_transfer();
	(++d1).weekday_transfer();
	(++d1).weekday_transfer();
	(++d1).weekday_transfer();
	cout << "d2" << endl;
	d2.weekday_transfer();
	(++d2).weekday_transfer();
	(++d2).weekday_transfer();
	(++d2).weekday_transfer();
	(++d2).weekday_transfer();
	(++d2).weekday_transfer();
	(++d2).weekday_transfer();
	(++d2).weekday_transfer();
	(++d2).weekday_transfer();
	cout << "d3" << endl;
	d3.weekday_transfer();
	(++d3).weekday_transfer();
	(++d3).weekday_transfer();
	(++d3).weekday_transfer();
	(++d3).weekday_transfer();
	(++d3).weekday_transfer();
	(++d3).weekday_transfer();
	(++d3).weekday_transfer();
	(++d3).weekday_transfer();
	cout << "d6" << endl;
	Date d6(1, 1, 1);
	cout << (Date(2022, 9, 15) - Date(1, 1, 1)) << endl;
	cout << (Date(2022, 9, 15) - 738412) << endl;
	d6.weekday_transfer();
}

void test3() {
	Date d1;
	Date d2(d1);
	Date d3(2022, 9, 15);

	Date d4 = d1.operator+(10);
	Date d5 = d2 + 100;
	d2 += 1000;
	d3 + 10000;
	Date d6 = d3 += 50000;
}

int main() {
	//test1();
	test2();
	//test3();
}