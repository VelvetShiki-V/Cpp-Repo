#include <iostream>
using namespace std;

template<class T>
struct ListNode {
	ListNode(){}
	ListNode(T value) :val(value){}
	ListNode* next = nullptr;
	ListNode* branch = nullptr;
	T val;
};


ListNode<int>* getNode(ListNode<int>* cur, int value) {
	while (cur->val != value) {
		cur = cur->next;
	}
	return cur;
}

void routeSelect(const int& n) {
	ListNode<int>* guard = new ListNode<int>(0);
	// 主路径 
	ListNode<int>* cur = guard;
	for (int i = 1; i <= n; ++i) {
		cur->next = new ListNode<int>(i);
		cur = cur->next;
	}
	// 路径1
	ListNode<int>* path1 = guard->next;
	path1->branch = new ListNode<int>(7);
	path1->branch->next = new ListNode<int>(8);
	path1->branch->next->branch = getNode(guard, 2);

	// 路径2
	getNode(guard, 2)->branch = getNode(path1->branch, 8);

	// 路径3
	ListNode<int>* path3 = getNode(guard, 4)->branch = new ListNode<int>(9);
	path3->branch = getNode(guard, 5);
}

int main() {
	routeSelect(6);
	return 0;
}