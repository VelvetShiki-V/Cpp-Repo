#include"stack.h"

void test1() {
	//// mystack测试
	//mystack::stack<int> st1;
	//st1.push(1);
	//st1.push(2);
	//st1.push(3);
	//st1.push(4);
	//while (!st1.empty()) {
	//	cout << st1.top() << " ";
	//	st1.pop();
	//}
	//cout << endl;

	//mystack::stack<char, vector<char>> st2;
	//st2.push('a');
	//st2.push('b');
	//st2.push('c');
	//st2.push('d');
	//cout << "vector_stack size : " << st2.size() << endl;
	//while (!st2.empty()) {
	//	cout << st2.top() << " ";
	//	st2.pop();
	//}
	//cout << endl;

	//std::list<double> ls{ 1.1,2.2,3.3 };
	//mystack::stack<double, list<double>> st3(ls);
	//while (!st3.empty()) {
	//	cout << st3.top() << " ";
	//	st3.pop();
	//}

	// queue测试
	std::queue<int> q0;

	std::list<int> ls1(10);
	std::deque<string> ls2{ "hello", "world", "!!!" };

	std::queue<int, list<int>> q1(ls1);		// 显示list容器
	std::queue<string> q2(ls2);				// 默认deque容器，通过对象初始化

	myqueue::queue<int> q3;
	q3.push(1);
	q3.push(2);
	q3.push(3);
	q3.push(4);
	q3.push(5);
	cout << "队首：" << q3.front() << endl;
	cout << "队尾：" << q3.back() << endl;
	while (!q3.empty()) {
		cout << q3.front() << " ";
		q3.pop();
	}
	cout << endl;

	myqueue::queue<int, list<int>> q4(ls1);
	cout << "队首：" << q4.front() << endl;
	cout << "个数：" << q4.size() << endl;
	while (!q4.empty()) {
		cout << q4.front() << " ";
		q4.pop();
	}
	cout << endl;

	myqueue::queue<string> q5(ls2);
	cout << "队首：" << q5.front() << endl;
	cout << "队尾：" << q5.back() << endl;
	cout << "个数：" << q5.size() << endl;
	while (!q5.empty()) {
		cout << q5.front() << " ";
		q5.pop();
	}
	cout << endl;
}

void test2() {
	mypq::priority_queue<int> pq1;
	pq1.push(1);
	pq1.push(2);
	pq1.push(3);
	pq1.push(4);
	pq1.push(5);
	cout << "less降序取顶输出" << endl;
	while (!pq1.empty()) {
		cout << pq1.top() << " ";
		pq1.pop();
	}
	cout << endl;

	//std::priority_queue<char, list<char>> pq2;		// 优先级队列不能用list实现，因为底层堆不支持operator[]
	//pq2.push('a');
	//pq2.push('b');
	//pq2.push('c');
	//while (!pq2.empty()) {
	//cout << pq2.top() << " ";
	//pq2.pop();

	mypq::priority_queue<char, string, myfunctor::greater<char>> pq2;
	pq2.push('j');
	pq2.push('a');
	pq2.push('z');
	pq2.push('k');
	pq2.push('d');
	cout << "优先级队列pq2总个数：" << pq2.size() << endl;
	cout << "greater升序取顶输出" << endl;
	while (!pq2.empty()) {
		cout << pq2.top() << " ";
		pq2.pop();
	}
	cout << endl;

	deque<string> d = { "abc", "abcd", "bc", "cde", "hello", "dowrl" };
	mypq::priority_queue<string, deque<string>, myfunctor::less<string>> pq3(d.begin(), d.end());
	cout << "优先级队列pq3总个数：" << pq3.size() << endl;
	cout << "less降序取顶输出" << endl;
	while (!pq3.empty()) {
		cout << pq3.top() << " ";
		pq3.pop();
	}
	cout << endl;
}

int main() {
	//test1();
	test2();
	return 0;
}