#include"func.h"

void test1()		//ֻ����һ�����ֲ���
{
	vector<int> a1;
	a1.push_back(4);
	a1.push_back(1);
	a1.push_back(2);
	a1.push_back(1);
	a1.push_back(2);
	cout << NumAppearOnce().single_number(a1) << endl;		//�����������
}

void test2()		//����ֻ����һ�����ֲ���
{
	vector<int> a1;
	a1.push_back(1);
	a1.push_back(2);
	a1.push_back(1);
	a1.push_back(3);
	a1.push_back(2);
	a1.push_back(5);
	//a1.push_back(1);
	//a1.push_back(1);
	//a1.push_back(0);
	//a1.push_back(-2147483648);
	vector<int> a2 = TwoNumAPPearOnce().singleNumber(a1);
	for (auto e : a2)
	{
		cout << e << " ";
	}
}

void test3()			//�绰��ĸ�������
{
	string s1("23");
	vector<string>ret = Tele().letterCombinations(s1);
	for (auto k : ret)
	{
		cout << k << "  ";
	}
}

int main()
{
	//test1();
	//test2();
	test3();
	return 0;
}

