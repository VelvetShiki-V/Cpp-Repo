#include"func.h"

void test1()
{   
    idt student1;
    student1.identityshow();
    cout << "该学生信息类的大小为" << sizeof(idt) << endl;
}

void test2()
{
    cout << sizeof(idt) << endl << sizeof(idt1) << endl << sizeof(idt2)<< endl; 
}

void test3()
{
    Date d1, d2;
    d1.DateInput(2022, 8, 4);
    d1.DateShow();
    d2.DateInput();
    d2.DateShow();
}

void test4()
{
    //Date d1(2022, 8, 4);
    //Date d2;
    //Date d3(1998);
    Date d1, d2, d3;
    d1.DateShow();
    d2.DateShow();
    d3.DateShow();
}

void test5()
{
    Date d1;
    d1.DateShow();
}
void test6()
{
    int max =100;
    AddN a1;
    int ret = a1.add(max);
    cout << ret << endl;
}

void test7()
{
    Stack s1;
    s1.StackPush(1);
    s1.StackPush(2);
    s1.StackPush(3);
    cout << s1.StackTop() << endl;
    s1.StackPush(4);
    s1.StackPush(5);
    cout << s1.StackTop() << endl;
    s1.StackPop();
    cout << s1.StackTop() << endl;
    s1.StackPop();
    s1.StackPop();
    cout << s1.StackTop() << endl;
    s1.StackPop();
    s1.StackPop();
    s1.StackPop();
    s1.StackPop();
    cout << s1.StackTop() << endl;
}

//Stack s1(1);

void test8()
{
    Stack s2(2);
    static Stack s3(3);
    static Stack s4(4);
    Stack s5(5);
}

void test9()
{
    MyQueue q1;
}

int main()
{
    //test1();
    //test2();
    //test3();
    //test4();
    //test5();
    //test6();
    //test7();
    //test8();
    test9();
    return 0;
}
