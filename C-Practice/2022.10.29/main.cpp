#include"func.h"

void test1() {
	using BST = key::Binary_Search_Tree<int>;
	BST b1;
	//vector<int> v{ 3,8,2,4,0,9,1};
	vector<int> v{ 5,3,6,2,4,7};
	for (auto e : v) {
		b1.insert(e);
	}
	b1.Inorder();
	cout << endl;

	b1.insertR(1);
	b1.insertR(10);
	b1.insertR(9);

	b1.Inorder();
	cout << endl;

	cout << b1.findR(1) << endl;
	cout << b1.findR(10) << endl;
	cout << b1.findR(9) << endl;
	cout << b1.findR(0) << endl;

	cout << "--------eraseR-------test" << endl;

	cout << b1.eraseR(1) << endl;
	cout << b1.eraseR(10) << endl;
	cout << b1.eraseR(0) << endl;
	b1.Inorder();
	//b1.erase(3);
	//cout << endl;
	//b1.empty();
	//b1.Inorder();

	//b1.erase(4);
	//cout << endl;
	//b1.empty();
	//b1.Inorder();

	//cout << b1.find(3) << endl;
	//b1.erase(3);
	//cout << endl;
	//b1.empty();
	//b1.Inorder();

	//b1.erase(4);
	//cout << endl;
	//b1.empty();
	//b1.Inorder();

	//b1.erase(8);
	//cout << endl;
	//b1.empty();
	//b1.Inorder();

	//b1.erase(9);
	//cout << endl;
	//b1.empty();
	//b1.Inorder();

	//b1.erase(0);
	//cout << endl;
	//b1.empty();
	//b1.Inorder();

	//b1.erase(2);
	//cout << endl;
	//b1.empty();
	//b1.Inorder();

	//b1.erase(1);
	//cout << endl;
	//b1.empty();
	//b1.Inorder();
}

void test2() {
	key::Binary_Search_Tree<int> b1;
	vector<int> v{ 5,3,6,2,4,7 };
	for (auto e : v) {
		b1.insert(e);
	}
	b1.Inorder();
	cout << endl;

	key::Binary_Search_Tree<int> b2 = b1, b3;		// 默认浅拷贝，将报错，必须显示拷贝构造
	b2.Inorder();
	b3 = b2;
	cout << endl;
	b3.Inorder();
}

void test3() {
	keyval::Binary_Search_Tree<string, string> b1;
	b1.insert("nice", "很好的");
	b1.insert("function", "函数");
	b1.insert("alien", "外星人");
	b1.insert("fold", "折叠的");
	b1.insert("tale", "故事");
	string str;
	bool ret;
	while (cin >> str) {
		if (ret = b1.find(str)) cout << b1.find(str)->val << endl;
		else cout << "没有词库" << endl;
	}
}

void test4() {
	keyval::Binary_Search_Tree<string, int> b;
	vector<string> vs{ "hello", "world", "hi", "hello", "name", "word", "hi", "hello", "tree", "int", "word", "word", "hello" };
	for (auto e : vs) {
		auto ret = b.find(e);
		if (ret) ret->val++;
		else b.insert(e, 1);
	}
	b.Inorder();
}

void test5() {

}

int main() {
	//test1();
	//test2();
	//test3();
	//test4();
	test5();
	return 0;
}