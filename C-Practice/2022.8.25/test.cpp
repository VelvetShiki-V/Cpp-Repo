#include"func.h"

void test1()
{
	//字符串转整数
	Solution s1;
	string s2("+12345");
	int a = s1.StrToInt(s2);
	cout << a << endl;
}

void test2()
{
	Solution4 s4;
	//string s1("123456789");
	//string s2("987654321");
	//string s1("0");
	//string s2("0");
	string s1("498828660196");
	string s2("840477629533");
	cout << s4.multiply(s1, s2) << endl;
}

void test3()
{
	//Solution6 s6;
	//string s("Let's take LeetCode contest");
	//cout << s6.reverseWords(s) << endl;

	Solution7 s7;
	//string s1("123");
	//string s2("456");
	//string s1("17039");
	//string s2("7218");
	string s1("498828660196");
	string s2("840477629533");
	//string s1("0");
	//string s2("0");
	cout << s7.multiply(s1, s2) << endl;
}

void test4()
{
	//vector<int>array;
	//array.push_back(100);
	//array.push_back(300);
	//array.push_back(300);
	//array.push_back(300);
	//array.push_back(300);
	//array.push_back(500);
	//vector<int>::iterator itor;
	//for (itor = array.begin(); itor != array.end(); itor++)
	//{
	//	if (*itor == 300)		//迭代器失效
	//	{
	//		itor = array.erase(itor);
	//	}
	//}
	//for (itor = array.begin(); itor != array.end(); itor++)
	//{
	//	cout << *itor << " ";
	//}

	//int arr[] = { 1,2,3,4,5 };
	//int sz = sizeof(arr) / sizeof(int);
	//vector<int> v(arr, arr + sz);
	//cout << v.size() << " " << v.capacity() << endl;

	Solution8 y;
	size_t num = 8;
	vector<vector<int>> x = y.generate(num);
	//for (int i = 0; i < num; i++)				//杨辉三角形式
	//{
	//	for (int j = 0; j < x[i].size(); j++)
	//	{
	//		cout << x[i][j] << " ";
	//	}
	//	cout << endl;
	//}
	cout << "[";
	for (size_t i = 0; i < num; i++)				//二维数组形式
	{
		cout << "[";
		for (size_t j = 0; j < x[i].size(); j++)
		{
			cout << x[i][j];
			if (j < x[i].size() - 1)
			{
				cout << ",";
			}
		}
		cout << "]";
	}
	cout << "]" << endl;
}

void test5()
{
	//Solution9 s9;
	//vector<int> v1;
	//v1.push_back(1);
	//v1.push_back(1);
	//v1.push_back(2);
	//cout << s9.removeDuplicates(v1) << endl;

	Solution10 s10;
	vector<int> v1;
	v1.push_back(3);
	v1.push_back(3);
	v1.push_back(3);
	v1.push_back(3);
	v1.push_back(3);
	v1.push_back(2);
	v1.push_back(2);
	v1.push_back(2);
	v1.push_back(2);
	cout << s10.MoreThanHalfNum_Solution(v1) << endl;
}

void test6()
{
	Solution11 s11;
	vector<int> v1;
	v1.push_back(30);
	v1.push_back(5);
	v1.push_back(10);
	v1.push_back(30);
	v1.push_back(10);
	v1.push_back(30);
	v1.push_back(10);
	cout << s11.singleNumber(v1) << endl;
}

int main()
{
	//test1();
	//test2();
	//test3();
	//test4();
	//test5();
	test6();
	return 0;
}

//计算最后一个字符串长度
//int lencal(string s)
//{
//	int ret = s.size() - 1;
//	while (ret >= 0 && s[ret] != ' ')
//	{
//		ret--;
//	}
//	return s.size() - ret - 1;
//}
//
//int main() {
//	string s;
//	getline(cin, s);		//getline无视空格支持多个字符串输入
//	int len = lencal(s);
//	cout << len << endl;
//	return 0;
//}