#include"func.h"

void test1()
{
	myspace::mystring s1;
	//myspace::mystring s2;
	//cout << (s1 == s2) << endl;

	using namespace myspace;
	mystring s3("abc");
	mystring s4("bcdefghi");
	//mystring s4(s3);
	//cout << s3.operator==(s4) << endl;

	//cout << s3.find('a', 0) << endl;
	//cout << s3.find('a', 1) << endl;
	//cout << s3.find('c', 1) << endl;

	//cout << s4.find('a', 0) << endl;
	//cout << s4.find('a', 1) << endl;
	//cout << s4.find('g') << endl;
	//cout << s4.find('h', 3) << endl;
	
	//cout << s4.find('i', 9) << endl;		//³¬¹ýsize
	//cout << s4.find('z', 9) << endl;
	//cout << s1.find('c') << endl;
	//cout << s1.find('c', 1) << endl;

	cout << s1.find("abc", 0) << endl;
	cout << s3.find("bc") << endl;
	cout << s3.find("abc", 1) << endl;
	cout << s3.find("bc", 1) << endl;
	cout << s3.find("ac") << endl;

	cout << s4.find("bcd") << endl;
	cout << s4.find("defgh", 0) << endl;
	cout << s4.find("bcd", 5) << endl;
	cout << s4.find("ghi", 5) << endl;
	cout << s4.find("efgh", 3) << endl;
	cout << s4.find("cde", 2) << endl;
}

void test2()
{
	using namespace myspace;
	mystring s1("abcdefg");
	mystring s2 = s1.substr(0);
	cout << s2 << endl;
	s2 = s1.substr(1, 3);
	cout << s2 << endl;
	s2 = s1.substr(3);
	cout << s2 << endl;
	s2 = s1.substr(5, 2);
	cout << s2 << endl;
	s2 = s1.substr(0, 4);
	cout << s2 << endl;
	s2 = s1.substr(6, 1);
	cout << s2 << endl;
	s2 = s1.substr(7);
	cout << s2 << endl;
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

void test3()
{
	using namespace myspace;
	mystring s1;
	s1.resize(10, 'z');
	s1.resize(20, 'x');
	cout << s1 << endl;
	s1.resize(50, 'p');
	cout << s1 << endl;
 	s1.resize(5, 'y');
	cout << s1 << endl;
	//string s1;
	//s1.resize(10);
	//s1.resize(20, 'x');
	//cout << s1 << endl;
	//s1.resize(50, 'p');
	//cout << s1 << endl;
	//s1.resize(5, 'y');
	//cout << s1 << endl;
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
	cout << s1 << "¡ª¡ªsize: " << s1.size() << " capacity: " << s1.capacity() << endl;
	cout << s1.c_str() << endl;
	s1 += '\0';
	s1 += "!!!!!!!!";
	cout << s1 << "¡ª¡ªsize: " << s1.size() << " capacity: " << s1.capacity() << endl;
	cout << s1.c_str() << endl;
	s1[1] = '\0';
	cout << s1 << endl;
	cout << s1.c_str() << endl;
}

int main()
{
	//test1();
	//test2();
	test3();
	//test4();
	//test5();
	//test6();
	//test7();
}