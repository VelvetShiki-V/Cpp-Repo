#include"hash_table.h"
#include"hash_bucket.h"

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

void test3() {
	HashBucket::HashTable<string, int> h1;
	vector<string> vs{ "abc", "dba", "dcb", "cb", "jkl", "j", "kj", "kl" };
	for (auto& e : vs) {
		auto p = h1.find(e);
		if (p) {
			p->m_data.second++;
		}
		else {
			h1.insert(make_pair(e, 1));
		}
	}
	//srand((unsigned int)time(0));
	//size_t num = 30;		// 9 
	//for (size_t i = 0; i < num; ++i) {
	//	int insertNum = rand() % 100;
	//	h1.insert(make_pair(insertNum, i));
	//}
	h1.print();
	cout << endl;
	cout << "size: " << h1.size() << endl;
	//cout << h1.erase("dba") << endl;
	//h1.print();
	for (auto k : vs) {
		cout << h1.erase(k) << endl;
		cout << "size: " << h1.size() << endl;
	}
	h1.~HashTable();
}

int main() {
	//test1();
	//test2();
	test3();
	return 0;
}