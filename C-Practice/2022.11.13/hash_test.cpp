//#include"hash_table.h"
//#include"hash_bucket.h"
#include"my_unordered_map_set.h"
//#include<unordered_map>
using namespace std;

//void test1() {
//	vector<int> v1{ 1,11,4,15,26,7,44,9,66,16,36,46 };
//	HashTable<int, int> h1;
//	for (auto& e : v1) {
//		h1.insert(make_pair(e, e));
//	}
//	h1.print();
//	cout << endl;
//	h1.erase(4);
//	h1.erase(11);
//	h1.erase(26);
//	cout << endl;
//	cout << h1.find(1)->m_data.first << endl;
//	cout << h1.find(66)->m_data.first << endl;
//	cout << h1.find(26) <<endl;
//
//	cout << endl;
//	h1.print();
//}
//
//void test2() {
//	vector<string> vs{ "abcd", "dbca", "dcba", "cadb", "jkl", "lkj", "klj", "kjl"};
//	HashTable<string, int> h1;
//	HashKey<string> hash;
//	for (auto& e : vs) {
//		cout << e << " : " << hash(e) << endl;
//		auto p = h1.find(e);
//		if (p) {
//			p->m_data.second++;
//		}
//		else {
//			h1.insert(make_pair(e, 1));
//		}
//	}
//	h1.print();
//}
//
//void test3() {
//	//HashBucket::HashTable<string, int> h1;
//	//vector<string> vs{ "abc", "dba", "dcb", "cb", "jkl", "j", "kj", "kl" };
//	//for (auto& e : vs) {
//	//	auto p = h1.find(e);
//	//	if (p) {
//	//		p->m_data.second++;
//	//	}
//	//	else {
//	//		h1.insert(make_pair(e, 1));
//	//	}
//	//}
//	HashBucket::HashTable<int, int> h1;
//	srand((unsigned int)time(0));
//	size_t num = 10000;		// 9 
//	for (size_t i = 0; i < num; ++i) {
//		int insertNum = rand();
//		h1.insert(make_pair(insertNum, i));
//	}
//	h1.print();
//	cout << endl;
//	cout << "size: " << h1.size() << endl;
//	//cout << h1.erase("dba") << endl;
//	//h1.print();
//	//for (auto k : vs) {
//	//	cout << h1.erase(k) << endl;
//	//	cout << "size: " << h1.size() << endl;
//	//}
//	//h1.~HashTable();
//	//cout << "size: " << h1.size() << endl;
//}

void test4() {
	//myhash::unordered_map<int, int> um1;
	////vector<int> v1{ 1,11,31,41,51,2,42,62,3,30,300};
	//vector<int> v1{ 1,11,4,15,26,7,44,9,66,16,36,46,21,31,46 };
	//for (auto& e : v1) {
	//	um1.insert(make_pair(e, e));
	//}
	//myhash::unordered_map<int, int>::iterator it = um1.begin();
	//for (it; it != um1.end(); ++it) {
	//	cout << um1.bucket(it->first) << " : " << it->first << endl;
	//}
	//cout << endl;
	//cout << "size: " << um1.size() << "  capacity: " << um1.max_size() << endl;

	myhash::unordered_set<string> us1;
	vector<string> vs{ "abcd", "abcd", "abcd", "dbcsda", "dcloea", "cabgcdb", "jkl", "lsdfbgfkj", "klj", "kj34l" };
	for (auto& j : vs) {
		us1.insert(j);
	}
	HashBucket::HashKey<string> cal;
	for (auto& l : us1) {
		cout << us1.bucket(l) << " : " << l << " -ASCֵ: " << cal(l) << endl;
	}
	cout << us1.empty() << " " << us1.size() << " " << us1.max_bucket_count() << " " << us1.load_factor() << endl;
	cout << us1.max_size() << " " << (us1.find("dcloea")).m_node->m_data << " " << us1.bucket_count() << " " << us1.bucket_size(4) << endl;
	cout << us1.bucket("abcd") << endl;
	myhash::unordered_set<string>::iterator it2 = us1.begin();
	for (it2; it2 != us1.end(); ++it2) {
		cout << *it2 << " ";
	}
}

void test5() {
	vector<string> vs{ "a", "b", "c", "a", "c", "d", "j", "k", "a", "d", "b", "k", "z" };
	myhash::unordered_map<string, int> m1;
	for (auto& e : vs) {
		m1[e]++;
	}
	myhash::unordered_map<string, int>::iterator it = m1.begin();
	for (it; it != m1.end(); ++it) {
		cout << it->first << " : " << it->second << endl;
	}
	cout << "data size: " << m1.size() << " capacity: " << m1.max_size() << endl;
	m1.rehash(50);
	cout << "data size: " << m1.size() << " capacity: " << m1.max_size() << endl;
}

int main() {
	//test1();
	//test2();
	//test3();
	//test4();
	test5();
	return 0;
}