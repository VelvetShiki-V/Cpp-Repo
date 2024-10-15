#include"func.h"

void test1()
{
    SGL n1;
    SGLInit(n1);
    SGLPushBack(n1, 0);
    SGLPushBack(n1, 1);
    SGLPushBack(n1, 2);
    SGLPushFront(n1, 5);
    SGLPushFront(n1, 4);
    SGLPushFront(n1, 3);
    SGLPrint(n1);
}

int test2()
{
    int tmp = 10;
    return tmp;
}

int& test3()
{
    int tmp1 = 20;
    return tmp1;
}

int& test4()
{
    static int tmp = 30;
    return tmp;
}

void test5()
{
    SL n1;

}
int main()
{
    //test1();
    int a = test2();
    int b = test3();
    int c = test4();
    cout << "a is " << a << endl;
    cout << "b is " << b << endl;
    cout << "b is " << b << endl;
    cout << "c is " << c << endl;
    test5();
    return 0;
}
