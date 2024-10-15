#define _CRT_SECURE_NO_WARNINGS 1
#include "class.h"

//void test1() {
//	newSpace* n = new newSpace;
//	myptr::shared_ptr<newSpace> p1(n);
//	p1->a++;
//	myptr::shared_ptr<newSpace> p2(p1);
//	myptr::shared_ptr<newSpace> p3;
//	p3 = p1;
//	cout << (*p1).a++ << endl;
//	cout << (*p2).a << endl;
//	cout << endl;
//	cout << endl;
//
//	myptr::shared_ptr<newSpace> p4(new newSpace);
//	myptr::shared_ptr<newSpace> p5(new newSpace);
//	myptr::shared_ptr<newSpace> p6(p5);
//	p4 = p1;
//	p6 = p1;
//
//	cout << endl;
//	cout << endl;
//	//int* pp1, * pp2;
//	//pp1 = new int;
//	//pp2 = pp1;
//	//cout << pp1 << " " << pp2 << endl;
//
//	//std::shared_ptr<newSpace> p7 = new newSpace;
//	std::shared_ptr<newSpace> p8(new newSpace);
//}

//void test2() {
//	Node<int>* n1 = new Node<int>;
//	myptr::shared_ptr<Node<int>> p1(n1);
//	myptr::shared_ptr<Node<int>> p2(new Node<int>);
//	//shared_ptr<Node<int>> p1(n1);
//	//shared_ptr<Node<int>> p2(new Node<int>);
//	cout << p1.use_count() << endl;
//	cout << p2.use_count() << endl;
//	p1->next = p2;
//	p2->prev = p1;
//	cout << p1.use_count() << endl;
//	cout << p2.use_count() << endl;
//}

void test3() {
	//shared_ptr<int> sp(new int[10]);		// 最好匹配，否则不同编译器可能报错
	//shared_ptr<int> sp2(new int[10], [](int* p) {delete[] p; });		// 匹配删除器
	//shared_ptr<int> sp3((int*)malloc(10));		// 匹配删除器
	//shared_ptr<int> sp3((int*)malloc(10), [](int* p) {free(p); });		// 匹配删除器
	//shared_ptr<newSpace> sp1(new newSpace[3], [](newSpace* s) {delete[] s; });			// lambda表达式
	//shared_ptr<Node<int>> n1(new Node<int>);
	////shared_ptr<Node<int>> n1(new Node<int>[5]);
	//shared_ptr<Node<int>> n2(new Node<int>[5], delNode<Node<int>>());
	//shared_ptr<Node<int>> n3(new Node<int>[5], [](Node<int>* p) {delete[] p; });		// lambda表达式
	//shared_ptr<FILE> sp4(fopen("log.txt", "r"), [](FILE* fp) {fclose(fp); });

	//shared_ptr<int> sp(new int);
	//shared_ptr<int> sp1(new int[10], [](int* p) {delete[] p; });
	//shared_ptr<int> sp2((int*)malloc(10));
	//shared_ptr<newSpace> sp3(new newSpace);
	//shared_ptr<newSpace> sp4(new newSpace[3], [](newSpace* s) {delete[] s; });
	//shared_ptr<Node<int>> sp5(new Node<int>);
	//shared_ptr<Node<int>> sp6(new Node<int>[5], delNode<Node<int>>());
	//shared_ptr<FILE> sp7(fopen("log.txt", "r"), [](FILE* fp) {fclose(fp); });

	//unique_ptr < Node<int>> p1(new Node<int>[5]);
	//unique_ptr < Node<int>, deleteSpace<Node<int>>> p1(new Node<int>[5]);
}

void test4() {
	//myptr::shared_ptr<newSpace> sp1(new newSpace);

	//myptr::shared_ptr<newSpace, deleteSpace<newSpace>> sp2(new newSpace[5]);

	//myptr::shared_ptr<int, deleteSpace<int>> sp3(new int[3]);

	//myptr::shared_ptr<int, Free<int>> sp4((int*)malloc(4));

	myptr::shared_ptr<FILE, FileDelete> sp5(fopen("log.txt", "w"));
}

int main() {
	//test1();
	//test2();
	//test3();
	test4();
	return 0;
}