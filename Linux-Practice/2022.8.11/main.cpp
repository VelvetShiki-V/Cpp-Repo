#include"func.h"

void test1()
{
    string s1;
    string s2(s1);
    string s3("hello world");
    string s4 = s3;
    string s5 = "hello";
    string s6;
    cin >> s6;
    cout << s1 << " " << s1.empty() << " "<< s1.size() << " " << s1.capacity() << endl;
    cout << s2 << " " << s2.empty() << " "<< s2.size() << " " << s2.capacity() << endl;
    cout << s3 << " " << s3.empty() << " "<< s3.size() << " " << s3.capacity() << endl;
    cout << s4 << " " << s4.empty() << " "<< s4.size() << " " << s4.capacity() << endl;
    cout << s5 << " " << s5.empty() << " "<< s5.size() << " " << s5.capacity() << endl;
    cout << s6 << " " << s6.empty() << " "<< s6.size() << " " << s6.capacity() << endl;

    string s7(s6, 3);
    cout << s7 << " " << s7.empty() << " "<< s7.size() << " " << s7.capacity() << endl;

    string s8(s7, 2, 3);
    cout << s8 << " " << s8.empty() << " "<< s8.size() << " " << s8.capacity() << endl;

    string s9(20, 'p');
    cout << s9 << " " << s9.empty() << " "<< s9.size() << " " << s9.capacity() << endl;
}

void test2()
{
    string s1("c++stringtest");
    s1[2] = '-';
    s1.operator[](0) = 'b';
    s1.at(5) = 'p';
    const string s2 = "linuxtest";

    cout << s1 << endl;
    cout << (s1.operator[](5)) << endl;
    cout << s1.at(3) << endl;
    cout << s2 << endl;
    cout << s2.at(4) << endl;
    cout << s2.operator[](7) << endl;

    for(size_t i = 0; i < s1.size(); i++)
    {
        cout << s1[i] << " ";
    }
    
}

void test3()
{
    string s1("hello my name is shiki!");
    string s2(s1, 17);
    //string::iterator it = s1.begin();
    //for(it; it != s1.end(); it++)
    //{
    //   cout << *it << " "; 
    //}
    //cout << endl;
    //auto it2 = s2.begin();
    //while(it2 != s2.end())
    //{
    //    cout << *it2 << " ";
    //    it2++;
    //}
    //cout << endl;
    //for(auto e : s1)
    //{
    //    cout << e << " ";
    //}
    //cout << endl;
    //for(auto e2 : s2)
    //{
    //    cout << e2 << " ";
    //}
    //cout << endl;
    string::reverse_iterator rit = s1.rbegin();
    auto rit2 = s2.rbegin();
    while(rit != s1.rend())
    {
        cout << *rit << " ";
        rit++;
    }
    cout << endl;
    while(rit2 != s2.rend())
    {
        cout << *rit2 << " ";
        rit2++;
    }
    cout << endl;
}

void test4()
{
    string s1("my name");
    s1.push_back(' ');
    s1.push_back('i');
    s1.push_back('s');
    s1.push_back(' ');
    s1.append("Shiki");
    cout << s1 << endl;

    string s2 = "I am a student";
    s1 += ',';
    s1 += "and ";
    s1 += s2;
    cout << s1 << endl;

    string s3("I'm 16 years old");
    s1.insert(17, s3);
    s1.insert(33, 1, ',');
    s1.insert(37, "well, ");
    s1.insert(s1.size(), 5, '.');
    cout << s1 << endl;

    string s4(s1.begin() + 11, s1.end() - 15);
    cout << s4 << endl;
}

void test5()
{
    string s1;
    s1.reserve(500);
    string s2;
    s2.resize(500);
    cout << s1 << " " << s1.size() << " " << s1.capacity() << endl;
    cout << s2 << " " << s2.size() << " " << s2.capacity() << endl;
    s1.resize(1000);
    s2.resize(1000, 'x');
    cout << s1 << " " << s1.size() << " " << s1.capacity() << endl;
    cout << s2 << " " << s2.size() << " " << s2.capacity() << endl;
    s1.resize(10, 'p');
    s2.resize(20);
    cout << s1 << " " << s1.size() << " " << s1.capacity() << endl;
    cout << s2 << " " << s2.size() << " " << s2.capacity() << endl;
    s1 += "sssssssssss";
    cout << s1 << endl;
    cout << s2 << endl;
}

void test6()
{
    string s1("123454321");
    string s2("543212345");
    string s3 = stradd(s1, s2);
    cout << s3 << endl;
}

int main()
{
    //test1();
    //test2();
    //test3();
    //test4();
    //test5();
    test6();
}
