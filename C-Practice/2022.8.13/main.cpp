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
	using myspace::mystring;
	mystring s1;
	mystring s2(s1);
	mystring s3("12345");
	mystring s4(s3);
	mystring s5("abcdefg");

	s3 = s5;
	s2.operator=(s4);
}

void test5()
{
	myspace::mystring s1;
	s1.push_back('a');
	s1.push_back('b');
	s1.push_back('c');
	s1.push_back('c');
	s1.push_back('c');
	myspace::mystring s2("hello world");
	s2.push_back('!');
	s2 += '!';
	s2 += '!';
	s2.reserve(5);
	s2.reserve(50);
	using myspace::mystring;

	//std::cout << s1.capacity() << " " << s1.size() << endl;
	//std::cout << s2.capacity() << " " << s2.size() << endl;

	//mystring s3;
	//s3.append("abc");
	//std::cout << s3.capacity() << " " << s3.size() << endl;
	//s3.append("defghijk");
	//std::cout << s3.capacity() << " " << s3.size() << endl;
	//s3.append("lmnopqrstuvwxyz123456789");
	//std::cout << s3.capacity() << " " << s3.size() << endl;
	//s3 += "54321";
	//std::cout << s3.capacity() << " " << s3.size() << endl;

	//mystring s3;
	//s3.insert(0, 'a');
	//s3.insert(0, 'b');
	//s3.insert(0, 'c');
	//s3.insert(1, 'd');
	//s3.insert(2, 'e');
	//s3.insert(3, 'f');

	//mystring s4("hello");
	//s4.insert(0, 'x');

	mystring s5("hello world");
	s5.insert(2, "abc");
	s5.insert(0, "12345");
	s5.insert(10, "aaaaa");
	s5.insert(1, "bbbbb");

	s5.erase(1, 5);
	s5.erase(10, 5);
	s5.erase(0, 5);
	s5.erase(2, 3);
	s5.erase(5, 10);
	s5.erase(4, 1);
	s5.erase(3, 1);
	s5.erase(3);
}

void test6()
{
	//string s1, s2, s3;
	//cin >> s1 >> s2;
	//cin >> s3;
	//cout << s1 << " " << s2 << " " << s3 << endl;
	using namespace myspace;
	mystring s1;
	mystring s2("hello world");
	mystring s3(s2);
	cout << s1 << " " << s2 << " " << s3 << endl;
	s2.clear();
	s3.clear();
	cin >> s1 >> s2;
	cin >> s3;
	cout << s1 << "\0" << s2 << " " << s3 << endl;
}

void test7()
{
	using namespace myspace;
	mystring s1("my name is shiki");
	cout << s1 << "！！size: " << s1.size() << " capacity: " << s1.capacity() << endl;
	cout << s1.c_str() << endl;
	s1 += '\0';
	s1 += "!!!!!!!!";
	cout << s1 << "！！size: " << s1.size() << " capacity: " << s1.capacity() << endl;
	cout << s1.c_str() << endl;
	s1[1] = '\0';
	cout << s1 << endl;
	cout << s1.c_str() << endl;
}

int main()
{
	//test1();
	//test2();
	//test3();
	//test4();
	//test5();
	//test6();
	test7();
}