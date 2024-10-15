#include<iostream>
#include<string>
#include<string.h>
using namespace std;

void test1()
{
    string s1;
    getline(cin, s1);
    cout << s1 << endl;
}
void test2()
{
    char* arr = new char[10];
    cout << strlen(arr) << endl;
}

int main()
{
    //test1();
    test2();
    return 0;
}
