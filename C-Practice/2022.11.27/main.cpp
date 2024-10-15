#include "class.h"

void test1() {
	newSpace* n = new newSpace;
	myptr::shared_ptr<newSpace> p1(n);
	p1->a++;
	myptr::shared_ptr<newSpace> p2(p1);
	myptr::shared_ptr<newSpace> p3;
	p3 = p1;
	cout << (*p1).a++ << endl;
	cout << (*p2).a << endl;
	cout << endl;
	cout << endl;

	myptr::shared_ptr<newSpace> p4(new newSpace);
	myptr::shared_ptr<newSpace> p5(new newSpace);
	myptr::shared_ptr<newSpace> p6(p5);
	p4 = p1;
	p6 = p1;

	cout << endl;
	cout << endl;
	//int* pp1, * pp2;
	//pp1 = new int;
	//pp2 = pp1;
	//cout << pp1 << " " << pp2 << endl;

	//std::shared_ptr<newSpace> p7 = new newSpace;
	std::shared_ptr<newSpace> p8(new newSpace);
}

void test2() {
	Node<int>* n1 = new Node<int>;
	myptr::shared_ptr<Node<int>> p1(n1);
	myptr::shared_ptr<Node<int>> p2(new Node<int>);
	//shared_ptr<Node<int>> p1(n1);
	//shared_ptr<Node<int>> p2(new Node<int>);
	cout << p1.use_count() << endl;
	cout << p2.use_count() << endl;
	p1->next = p2;
	p2->prev = p1;
	cout << p1.use_count() << endl;
	cout << p2.use_count() << endl;
}

int main() {
	//test1();
	test2();
	return 0;
}