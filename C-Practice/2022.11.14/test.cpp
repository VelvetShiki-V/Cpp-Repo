#include"Bitset.h"
#include"BloomFilter.h"

void test1() {
	mybitset::bitset<100> b1;
	b1.set(0);
	b1.set(5);
	b1.set(17);
	b1.set(35);
	b1.set(99);
	b1.reset(7);
	b1.reset(17);
	b1.reset(35);
	b1.reset(99);
	cout << b1.test(0) << " " << b1.test(99) << endl;
}

void test2() {
	mybitset::twobitset<50> b1;	
	vector<unsigned int> v1{ 1,1,1,2,2,3,3,3,4,5,5,6,7};
	for (auto& e : v1) {
		b1.set(e);
	}
	b1.testOnce();		// 可以达到排序+去重功能
}

void test3() {
	vector<string> vs{ "a", "b", "c", "d", "e", "f", "g"};
	BloomFilter<10> b1;
	for (auto& e : vs) {
		b1.set(e);
	}
	cout << b1.test("ca") << endl;
}

int main() {
	//test1();
	//test2();
	test3();
	return 0;
}