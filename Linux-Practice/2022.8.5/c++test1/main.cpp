#include"func.h"

void func(MyQueue q)
{
    ;
}

MyQueue& func1(MyQueue& q)
{
    return q;
}

MyQueue func2(MyQueue& q) 
{
    return q;
}

MyQueue& func3()
{
    static MyQueue q;
    return q;
}

MyQueue func4()
{
    static MyQueue q;
    return q;
}

void test1()
{
    MyQueue q1;
    //func(q1);
    //func1(q1);
    //func2(q1);
    //func3();
    //func4();
}

void test2()
{
    Date d1(2022, 8, 5);
    d1.DateShow();
    //Date d2(d1);
    Date d2 = d1;
    d2.DateShow();
}

void test3()
{
    //Date d1(2022, 8, 5);
    //Date d2;
    //Date d2(d1);
    //d1.DateShow();
    //d2.DateShow();
    //cout << d1.operator==(d2) << endl;
    //Date d3 = d1.operator+(20);
    //Date d4 = d2 + 50;           //相同运算符重载函数的不同写法
    //d1.operator+=(70);
    //d2 += 100; 

    //d3.DateShow();
    //d4.DateShow();
    //d1.DateShow();
    //d2.DateShow();
   //Date d3 = d1.operator-(3);
   //Date d4 = d2 - 30;
   //d3.DateShow();
   //d4.DateShow();
   //(d1 -= 500).DateShow();
   //(d2 -= 5000).DateShow();
   
    Date d1(2022, 8, 5);
    Date d2(d1);
    cout << "相差" <<  d1 - d2 << "天" <<  endl;
    Date d3(2012, 3, 15);
    cout << "相差" << d1.operator-(d3) << "天" << endl;
    Date d4(2030, 10, 1);
    cout << "相差" << d1.operator-(d4) << "天" << endl;
    Date d5;
    cout << "相差" << d5 - d1 << "天" <<  endl;
}
int main()
{
    //test1();
    //test 2();
    test3();
    return 0;
}
