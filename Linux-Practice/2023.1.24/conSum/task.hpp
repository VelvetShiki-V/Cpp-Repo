#pragma once
#include <iostream>
#include <functional>
using namespace std;
typedef function<int(int, int)> func_t;

class Task{
public:
    Task(){}
    Task(int x, int y, func_t function)
        :a(x)
        ,b(y)
        ,func(function)
        {}
    int operator()() {
        return func(a, b);
    }
private:
    int a;
    int b;
    func_t func;
};