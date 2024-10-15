#include"func.h"

void test1()
{
	//该函数全局使用命名空间（不安全）
	using namespace myspace1;
	s1 s;
	printf("%d\n", i);
	printf("%d\n", s.j);
	printf("%f\n", s.k);

	using namespace myspace1::myspace2;		//内部命名空间嵌套展开
	s2 ss;
	printf("%d\n", ss.l);
	printf("%lf\n", ss.m);
}

void test2()
{
	//使用部分命名空间，不全部将命名空间中的所有内容展开（较安全）
	using std::cout;
	using std::endl;
	using myspace1::i;
	std::cout << i << std::endl;
	using myspace1::myspace2::s2;
	s2 ss;
	cout << ss.m << endl;
}

void test3()
{
	using namespace std;	
	cout << myspace1::i << endl;	//需要什么就临时展开什么，后续不展开无法使用
	myspace1::myspace2::s2 ss;
	cout << ss.l << endl;
}

void test4()
{
	//int i, j;
	//float k;
	//char l, m;
	//using std::cin;
	//using std::cout;
	//cin >> i >> j >> k >> l >> m;
	//cout << i << " " << j << " " << k << " " << l << " " << m << std::endl;
	//std::cin >> i;
	//std::cin >> j;

	//using std::cin;
	//cin >> k;

	//using namespace std;
	//cin >> l >> m;

	using namespace std;
	//int arr[5] = { 0 };
	//cin >> arr[3];

	//for (int i = 0; i < 5; i++)
	//{
	//	cin >> arr[i];
	//}

	//vector<int> v1;
	//v1.resize(5);
	//int i = 0;
	//for (auto e : v1)
	//{
	//	cin >> v1[i];
	//	i++;
	//}
	//for (auto f : v1)
	//{
	//	cout << f << " ";
	//}
	//string s1;
	//cin >> s1;
	//cout << s1 << endl;

	//string s1("my name");
	//string s2 = "is";
	//string s3;
	//cin >> s3;
	//cout << s1 << " " << s2 << " " << s3 << endl;

	//string s1;
	//cin >> s1;
	//cout << s1 << endl;

	string s1;
	getline(cin, s1);
	cout << s1 << endl;
}

void test5()
{
	using namespace std;
	char arr[10] = { NULL };
	char arr1[10] = { 0 };
	cin.get(arr, 10);
	cin.clear();
	cin.ignore();
	cin.get(arr1, 10);
	cout << arr << endl;
	cout << arr1 << endl;



	//cin.getline(arr, 10);
	//cout << arr << endl;
	//cin.getline(arr1, 10);
	//cout << arr1 << endl;

	//string s1, s2;
	//getline(cin, s1);
	//cout << s1 << endl;
	//getline(cin, s2);
	//cout << s2 << endl;
 }

int main()
{
	//test1();
	//test2();
	//test3();
	//test4();
	test5();
	return 0;
}