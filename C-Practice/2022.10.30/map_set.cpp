#include"map_set_func.h"

void test1() {
	vector<int> v1{ 5,7,2,4,9,8,6,1,0,0,5,6,5 };
	//set<int> s1(v1.begin(), v1.end());		// 默认升序，即仿函数less<int>
	set<int, greater<int>> s1(v1.begin(), v1.end());		// 显示模板参数greater，降序
	for (auto e : s1) {		// 底层是二叉搜索树（中序遍历）
		cout << e << " ";	// 不允许使用引用来间接修改，因为二叉搜索树不能修改值，否则破坏二叉搜索树结构
	}
	cout << endl;
	//s1.erase(5);
	//auto it = s1.begin();
	//for (it; it != s1.end(); it++) {
	//	cout << *it << " ";
	//}
	//cout << endl;
	multiset<int> s2{ 3,5,2,7,7,9,1,0,2,2,4 };
	for (auto e : s2) {
		cout << e << " ";
	}
	cout << endl;
	multiset<int>::iterator pos = s2.find(2);
	while (pos != s2.end()) {
		cout << *pos << " ";
		pos++;
	}
}

void test2() {
	map<string, string> dict;
	pair<string, string> p1("hello", "你好");
	pair<string, string> p2("world", "世界");
	dict.insert(p1);
	dict.insert(p2);
	dict.insert(pair<string, string>("front", "前面的"));	// 匿名对象，不能用auto
	typedef pair<string, string> pss;
	dict.insert(pss("nice", "美好的"));
	dict.insert(pss("nice", "很好的"));
	dict.insert(pss("beautiful", "美好的"));
	dict.insert(pss("gorgeous", "美丽的"));
	dict.insert(make_pair("spectacular", "宏伟的"));
	dict.insert(make_pair("noble", "出名的"));
	dict.insert(make_pair("luxury", "奢侈的"));
	map<string, string>::iterator it = dict.begin();
	for (it; it != dict.end(); ++it) {
		cout << (*it).first << " : " << (*it).second << endl;
		// 或可以写为it>first， it->second
	}
	cout << endl;
	for (const auto& e : dict) {
		cout << e.first << " : " << e.second << endl;
	}
}

void test3() {
	//vector<string> vs{"a", "b", "c", "a", "c", "d", "j", "k", "a", "d", "b", "k", "z"};
	//map<string, int> m2;
	// 方法1
	//for (const auto& e : vs) {
	//	map<string, int>::iterator mit = m1.find(e);
	//	if(mit != m1.end()) mit->second++;
	//	else m1.insert(make_pair(e, 1));
	//	//map<string, int>::iterator mit = m1.begin();
	//	//while (mit != m1.end()) {
	//	//	if (e == mit->first) mit->second++;
	//	//	mit++;
	//	//}
	//	//if (mit == m1.end()) m1.insert(make_pair(e, 1));
	//}

	// 方法2——operator[]
	//for (auto& e : vs) {
	//	m1[e]++;
	//}
	//for (const auto& k : m1) {
	//	cout << k.first << ": " << k.second << endl;
	//}
}

void test4() {
	multimap<string, string> mmp;
	mmp.insert(make_pair("computer", "电脑"));
	mmp.insert(make_pair("computer", "计算机"));
	mmp.insert(make_pair("computer", "PC"));
	mmp.insert(make_pair("computer", "个人计算机"));
	for (const auto& k : mmp) {
		cout << k.first << ": " << k.second << endl;
	}
}

int main() {
	//test1();
	//test2();
	//test3();
	test4();
	return 0;
}