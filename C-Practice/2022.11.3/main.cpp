#include"AVLTree.h"
#include"RBTree.h"

void test1() {
	vector<int> v{ 4, 2, 6, 1, 3, 5, 15, 7, 16, 14 };
	//vector<int> v{ 16, 3, 7, 11, 9, 26, 18, 14, 15 };
	AVLTree<int, int> t1;
	for (auto& e : v) {
		t1.insert(make_pair(e, e));
	}
	t1.Inorder();
	cout << endl;
	cout << "balanced? : " << t1.isBalanced() << endl;
}

void test2() {
	AVLTree<int, int> t1;
	srand(0);
	size_t N = 100, cnt = 0;
	for (size_t i = 0; i < N; i++) {
		size_t x = rand();
		t1.insert(make_pair(x, x));
		cnt++;
	}
	t1.Inorder();
	cout << "balanced? : " << t1.isBalanced() << endl;
	cout << cnt << endl;
}

void test3() {
	vector<int> v{ 1,2,3,4,5,6,7,8,9};
	//vector<int> v{ 4, 2, 6, 1, 3, 5, 15, 7, 16, 14 };
	//vector<int> v{ 16, 3, 7, 11, 9, 26, 18, 14, 15 };
	RBTree<int, int> r1;
	for (auto& e : v) {
		r1.insert(make_pair(e, e));
	}
	r1.Inorder();
	cout << r1.isBalanced() << endl;
}

void test4() {
	RBTree<int, int> t1;
	srand((unsigned int)time(0));
	size_t N = 1000, cnt = 0;
	for (size_t i = 0; i < N; i++) {
		size_t x = rand();
		t1.insert(make_pair(x, i));
		cnt++;
	}
	t1.Inorder();
	cout << "balanced? : " << t1.isBalanced() << endl;
	cout << cnt << endl;
}

int main() {
	//test1();
	//test2();
	//test3();
	test4();
	return 0;
}