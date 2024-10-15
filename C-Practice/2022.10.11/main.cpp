#include"list.h"
#include<list>

void test1() {
	mylist::list<int> ls1;
	ls1.push_back(1);
	ls1.push_back(2);
	ls1.push_back(3);
	ls1.push_back(4);
	ls1.push_back(5);
	cout << "size: " << ls1.size() << "  empty?: " << ls1.empty() << endl;
	for (auto e : ls1) {
		cout << e << " ";
	}
	cout << endl << "front->7: " << (ls1.front() = 7) << "  back->9: " << (ls1.back() = 9);
	cout << endl;

	ls1.resize(10, 0);
	//ls1.resize(3, 0);
	cout << endl <<  "size: " << ls1.size() << endl;
	for (auto e : ls1) {
		cout << e << " ";
	}
	cout << endl << "front: " << ls1.front() << "  back: " << ls1.back();
	cout << endl;

	ls1.pop_back();
	ls1.pop_back();
	ls1.pop_back();
	cout << endl << "size: " << ls1.size() << endl;
	for (auto e : ls1) {
		cout << e << " ";
	}
	cout << endl << "front: " << ls1.front() << "  back: " << ls1.back();
	cout << endl;

	ls1.pop_front();
	ls1.pop_front();
	ls1.pop_front();
	ls1.pop_front();
	cout << endl << "size: " << ls1.size() << endl;
	for (auto e : ls1) {
		cout << e << " ";
	}
	cout << endl << "front: " << ls1.front() << "  back: " << ls1.back();
	cout << endl;

	mylist::list<int>::iterator it = ls1.begin();
	while (*it != 0) {
		it++;
	}
	ls1.insert(it, 8);			// 链表迭代器不会失效，因为不存在挪动数据，it一直指向对应结点
	ls1.insert(it, 88);
	it = ls1.insert(it, 7);		// 只有接收返回值才会将迭代器更新到插入的结点地址上
	it = ls1.insert(it, 77);
	cout << endl << "size: " << ls1.size() << endl;
	for (auto e : ls1) {
		cout << e << " ";
	}
	cout << endl << "front: " << ls1.front() << "  back: " << ls1.back();
	cout << endl;

	ls1.push_front(5);
	ls1.push_front(5);
	ls1.push_front(5);
	cout << endl << "size: " << ls1.size() << endl;
	for (auto e : ls1) {
		cout << e << " ";
	}
	cout << endl << "front: " << ls1.front() << "  back: " << ls1.back();
	cout << endl;

	ls1.clear();
	cout << endl << "size: " << ls1.size() << "  empty?: " << ls1.empty() << endl;

	//list<char> ls2('a', 'b');
	//list<char> ls2 = { 'c', 'd' };

	cout << "NICEEEE" << endl;

	vector<char> v = { 'a', 'b', 'c' };
	mylist::list<char> ls2(v.begin(), v.end());
	cout << endl << "size: " << ls2.size() << endl;
	for (auto e : ls2) {
		cout << e << " ";
	}
	cout << endl;
	
	ls2.push_front('o');
	ls2.push_front('l');
	ls2.push_front('l');
	mylist::list<char>::iterator it2 = ls2.begin();
	it2 = ls2.insert(it2, 'e');
	it2 = ls2.insert(it2, 'h');
	cout << endl << "size: " << ls2.size() << endl;
	for (auto e : ls2) {
		cout << e;
	}
	cout << endl;

	ls2.erase(ls2.begin());
	ls2.erase(ls2.begin());
	ls2.erase(--ls2.end());
	ls2.erase(--ls2.end());
	cout << endl << "size: " << ls2.size() << endl;
	for (auto e : ls2) {
		cout << e;
	}
	cout << endl << endl;
	
	ls1.push_front(3);
	ls1.push_front(2);
	ls1.push_front(1);
	mylist::list<int> ls3 = ls1;
	cout << "size: " << ls3.size() << endl;
	for (auto e : ls3) {
		cout << e << " ";
	}
	cout << endl << endl;

	mylist::list<int> ls4;
	ls4 = ls3;
	cout << endl;
}

void test2() {
	mylist::list<string> ls1;
	ls1.push_back("he");
	ls1.push_back("llo");
	ls1.push_back(" ");
	ls1.push_back("wor");
	ls1.push_back("ld");
	mylist::list<string>::reverse_iterator rit = ls1.rbegin();
	for (rit; rit != ls1.rend(); ++rit) {
		cout << *rit;
	}
	cout << endl;
	auto it = ls1.begin();
	for (it; it != ls1.end(); it++) {
		cout << *it;
	}
	cout << endl;
}

int main() {
	test1();
	//test2();
	return 0;
}