#include"func.h"

void test1()
{
	//string s1("");
	string s1("1");
	//string s2("543212345");
	string s2("999999999");
	string s3 = stradd(s1, s2);
	cout << s3 << endl;
}

void test2()
{
	//string s1("  fly me to the moon ");
	//cout << s1.size() << endl;
	//string s1("Hello World");
	string s1("a");
	cout << lengthOfLastWord(s1) << endl;
}

void test3()
{
	//string s1("123");
	//string s1("abc");
	//s1 = to_string(12.345);
	//int val = stoi(s1);
	//cout << s1 << endl;
	//cout << val << endl;

	//string s2("leetcode");
	//cout << firstUniqChar(s2) << endl;

	string s1("A man, a plan, a canal: Panama");
	string s2("   ");
	string s3("0P");
	cout << isPalindrome(s3) << endl;
}

void test4()
{
	
}

int main()
{
	//test1();
	//test2();
	//test3();
	test4();
}