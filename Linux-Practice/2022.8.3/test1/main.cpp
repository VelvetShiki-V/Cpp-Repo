#include"func.h"
#include<typeinfo>

void test1(int a, int b, double c, double d)
{
   // cout << "a + b =" << add(a, b) << endl;
   // cout << "c + d =" << add(c, d) << endl;
}

void test2(int a = 1, int b = 2, double c = 5.5, double d = 10.0)
{
    int& x = a;
    double& y = c;
    char e = '5';
    //cout << "a is " << typeid(a).name() << endl;
    //cout << "x is " << typeid(x).name() << endl;
    //cout << "c is " << typeid(c).name() << endl;
    //cout << "y is " << typeid(y).name() << endl;
    //cout << "e is " << typeid(e).name() << endl;

    //cout << "a is " << sizeof(a) << endl;
    //cout << "x is " << sizeof(x) << endl;
    //cout << "c is " << sizeof(c) << endl;
    //cout << "y is " << sizeof(y) << endl;
    //cout << "e is " << sizeof(e) << endl;

    //cout << "a is " << &a << endl;
    //cout << "x is " << &x << endl;
    //cout << "c is " << &c << endl;
    //cout << "y is " << &y << endl;
    //cout << "e is " << &e << endl;

    x = 100;
    y = 50.123;
    //cout << "a is" << a << endl;
    //cout << "x is" << x << endl;
    //cout << "c is" << c << endl;
    //cout << "y is" << y << endl;

    int& z = x;                   //给int a的别名x起别名z
    const double& k = z;          //给别名z取别名k，且类型为double 
    const int& j = y;             //给double c的别名y取别名j，类型为int
    
    cout << "z is " << z << endl;
    cout << "k is " << k << endl;
    cout << "j is " << j << endl;
    cout << "y is " << y << endl;
}

void test3()
{
    int x = 10, y = 20;
    cout << "x = " << x << endl << "y = " << y << endl;
    Swap(x, y);
    cout << "x = " << x << endl << "y = " << y << endl;
}

int main()
{
    int a = 5, b = 3;
    double c = 2.0, d = 3.5;

    //test1(a, b, c, d);
    //test2(a, b, c);
    test3();
    return 0;
}
