#include"func.h"
using namespace std;

void test1() {			// ����β�壬ͷ�壬����������
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

void test2() {			// ��֤find�㷨��insert����
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
		t.insert(pos, 30);		// ����ʧЧ����Ϊ������������Ųλ�ã�posʼ��ָ����ֵ3�ĵ�ַ
	}
	pos = find(start, end, 30);
	if (pos != end) {
		pos = t.erase(pos);		// pos����ֵΪ����ֵ��ָ��ĺ�һ��ֵ�����ܲ�ʹ�÷���ֵ����posʱ������ʹ��erase������eraseָ��ĵ�ַ���ͷų�ΪҰָ�룬�ᱨ��
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
void func1(const List<int>& lt) {					// ��list��const�����������
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