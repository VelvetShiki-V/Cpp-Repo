#include"func.h"

void test1()
{
    int a = 5, b = 7;
    double c = 2.2, d = 1.4;
    Swap(a, b);
    Swap(c, d);
    cout << a << ' ' << b << endl;
    cout << c << ' ' << d << endl;
}

void test2()
{
    Stack<int> s1;
    Stack<int> s2(s1);
    s1.Push(1);
    cout << s1.Top() << endl;
    s2.Push(5);
    s2.Push(7);
    cout << s2.Top() << endl;
    Stack<double> s3(10);
    s3.Push(1.1);
    s3.Push(2.2);
    cout << s3.Top() << endl;
    s3.Pop();
    cout << s3.Size() << endl;
    cout << s3.Empty() << endl;
    s3.Push(3.3);
    s3.Push(4.4);

    cout << s3.Top() << endl;
    cout << s3.Size() << endl;
    cout << s3.Empty() << endl;
}

int main()
{
    //test1();
    test2();
}
