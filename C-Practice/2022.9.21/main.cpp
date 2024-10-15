#include"func.h"
using namespace std;

void test1() {			// 链表尾插，头插，正反迭代器
	list<int> t;
	t.push_back(1);
	t.push_back(2);
	t.push_back(3);
	t.push_back(4);
	t.push_back(5);
	t.push_front(0);
	t.push_front(-1);
	t.push_front(-2);
	t.pop_back();
	t.pop_back();

	list<int>::iterator it = t.begin();
	for (it; it != t.end(); it++) {
		cout << (*it * 2) << " ";
	}
	cout << endl;
	for (auto e : t) {
		cout << e << " ";
	}

	//it = t.begin();
	//list<int>::reverse_iterator rit = t.rbegin();
	//t.insert(it, 1);
}

void test2() {			// 验证find算法和insert函数
	list<int> t;
	t.push_back(1);
	t.push_back(2);
	t.push_back(3);
	t.push_back(4);
	t.push_back(5);

	auto start = t.begin();
	auto end = t.end();
	list<int>::iterator pos = find(start, end, 3);
	if (pos != end) {
		t.insert(pos, 30);		// 不会失效，因为链表不存在数据挪位置，pos始终指向数值3的地址
	}
	pos = find(start, end, 30);
	if (pos != end) {
		pos = t.erase(pos);		// pos返回值为擦除值后指向的后一个值，不能不使用返回值更新pos时就连续使用erase，否则erase指向的地址被释放成为野指针，会报错
		t.erase(pos);
	}

	for (auto e : t) {
		cout << e << " ";
	}
	cout << endl;
	t.push_front(8);
	t.push_front(9);
	t.push_front(1);
	t.push_front(5);
	t.push_front(3);
	t.sort();
	for (auto e : t) {
		cout << e << " ";
	}
}

using namespace mylist;
void func1(const List<int>& lt) {					// 传list的const对象遍历测试
	List<int>::const_iterator cit = lt.cbegin();
	while (cit != lt.cend()) {
		cout << *cit << " ";
		cit++;
	}
	//for (auto e : lt) {
	//	cout << e << " ";
	//}
}
void test3() {
	List<int> lt1;
	lt1.push_back(1);
	lt1.push_back(2);
	lt1.push_back(3);
	lt1.push_back(4);
	lt1.push_back(5);
	List<int>::iterator it = lt1.begin();
	auto end = lt1.end();
	for (it; it != end; ++it) {
		cout << *it << " ";
	}
	cout << endl;
	for (auto e : lt1) {
		cout << e * 2 << " ";
	}
	cout << endl;
	func1(lt1);
}

int main() {
	//test1();
	//test2();
	test3();
}