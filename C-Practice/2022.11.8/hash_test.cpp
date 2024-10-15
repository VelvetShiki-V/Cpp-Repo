#include"hash_table.h"

void test1() {
	vector<int> v1{ 1,11,4,15,26,7,44,9,66,16,36,46 };
	HashTable<int, int> h1;
	for (auto& e : v1) {
		h1.insert(make_pair(e, e));
	}
	h1.print();
	cout << endl;
	h1.erase(4);
	h1.erase(11);
	h1.erase(26);
	cout << endl;
	cout << h1.find(1)->m_data.first << endl;
	cout << h1.find(66)->m_data.first << endl;
	cout << h1.find(26) <<endl;

	cout << endl;
	h1.print();
}

void test2() {
	vector<string> vs{ "abcd", "dbca", "dcba", "cadb", "jkl", "lkj", "klj", "kjl"};
	HashTable<string, int> h1;
	HashKey<string> hash;
	for (auto& e : vs) {
		cout << e << " : " << hash(e) << endl;
		auto p = h1.find(e);
		if (p) {
			p->m_data.second++;
		}
		else {
			h1.insert(make_pair(e, 1));
		}
	}
	h1.print();
}

int main() {
	//test1();
	test2();
	return 0;
}