#include"func.h"

int add(int a, int b)
{
    return a + b;
}

double add(double a, double b)
{
    return a + b;
}

void Swap(int& a, int& b)
{
    int tmp = a;
    a = b;
    b = tmp;
}
