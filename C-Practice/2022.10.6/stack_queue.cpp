#include"stack.h"

void test1() {
	Stack<int, vector<int>> st;		// 使用vector容器的栈适配器
	st.push(1);
	st.push(2);
	st.push(3);
	st.push(4);
	while (!st.empty()) {
		cout << st.top() << endl;
		st.pop();
	}
	cout << endl;

	Stack<char, list<char>> st2;
	st2.push('a');
	st2.push('b');
	st2.push('c');
	st2.push('d');
	while (!st2.empty()) {
		cout << st2.top() << endl;
		st2.pop();
	}
}

void test2() {
	//Queue<int, vector<int>> q1;		// vector不能用作容器底层
	Queue<int> q1;		// list和默认的双端队列deque可以
	q1.push(1);
	q1.push(2);
	q1.push(3);
	q1.push(4);
	while (!q1.empty()) {
		cout << q1.front() << " " << q1.back() << endl;
		q1.pop();
	}
}

void test3() {
	//priority_queue<int> pq;		// 优先级队列，默认大根堆结构，取顶遍历自动降序
	priority_queue<int, vector<int>, greater<int>> pq;		// 仿函数建小堆排升序
	pq.push(1);
	pq.push(3);
	pq.push(8);
	pq.push(4);
	pq.push(0);
	while (!pq.empty()) {
		cout << pq.top() << " ";
		pq.pop();
	}
	cout << endl;

	Priority_queue<int> mypq;		// 模拟实现的优先级队列
	mypq.push(1);
	mypq.push(4);
	mypq.push(9);
	mypq.push(6);
	mypq.push(-1);
	while (!mypq.empty()) {
		cout << mypq.top() << " ";
		mypq.pop();
	}
	cout << endl;

	// 迭代器区间初始化
	vector<int> v{ 1,2,3,4,5 };
	Priority_queue<int> mypq2(v.begin(), v.end());
	while (!mypq2.empty()) {
		cout << mypq2.top() << " ";
		mypq2.pop();
	}
}

void test4() {
	//myfunctor::less<int> ls;
	//myfunctor::greater<int> ls2;
	//cout << ls(5, 6) << " " << ls2(5, 6) <<  endl;		// 像函数一样去使用，等价于ls.operator()(5, 6)

	Priority_queue<int, vector<int>, greater<int>> mypq;	// 建小堆，取顶输出排升序
	//Priority_queue<int, vector<int>, less<int>> mypq;		// 建大堆，取顶输出排降序
	mypq.push(5);
	mypq.push(3);
	mypq.push(8);
	mypq.push(6);
	mypq.push(0);
	mypq.push(1);
	mypq.push(9);
	mypq.push(10);
	while (!mypq.empty()) {
		cout << mypq.top() << " ";
		mypq.pop();
	}
}

int main() {
	//test1();
	//test2();
	//test3();
	test4();
}