#include"stack.h"

void test1() {
	Stack<int, vector<int>> st;		// ʹ��vector������ջ������
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
	//Queue<int, vector<int>> q1;		// vector�������������ײ�
	Queue<int> q1;		// list��Ĭ�ϵ�˫�˶���deque����
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
	//priority_queue<int> pq;		// ���ȼ����У�Ĭ�ϴ���ѽṹ��ȡ�������Զ�����
	priority_queue<int, vector<int>, greater<int>> pq;		// �º�����С��������
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

	Priority_queue<int> mypq;		// ģ��ʵ�ֵ����ȼ�����
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

	// �����������ʼ��
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
	//cout << ls(5, 6) << " " << ls2(5, 6) <<  endl;		// ����һ��ȥʹ�ã��ȼ���ls.operator()(5, 6)

	Priority_queue<int, vector<int>, greater<int>> mypq;	// ��С�ѣ�ȡ�����������
	//Priority_queue<int, vector<int>, less<int>> mypq;		// ����ѣ�ȡ������Ž���
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