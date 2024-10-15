#include<iostream>
using namespace std;
void func(int a = 0, int b = 1, int c = 2)
{
    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
    cout << "c = " << c << endl;
}
int main()
{
    int a, b, c;
    cout << "请输入a, b, c的整数值" << endl;
    cin >> a >> b >> c;
    func(a, b);
    return 0;
}
