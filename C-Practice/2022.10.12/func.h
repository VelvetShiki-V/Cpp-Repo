#ifndef __FUNC_H
#define __FUNC_H
#pragma once
#include<iostream>
#include<vector>
#include<string>
#include<vector>
#include<list>
#include<queue>
using namespace std;

int MTH(vector<int>& numbers) {
    // write code here
    int g_e = 0;
    sort(numbers.begin(), numbers.end());
    size_t cnt = 0;
    int prev = numbers[0];
    for (auto e : numbers) {
        if (prev == e) {
            cnt++;
            if (cnt > numbers.size() / 2) {
                cout << e;
                g_e = e;
                break;
            }
        }
        else {  
            cnt = 1;
            prev = e;
        }
    }
    return g_e;
}

#endif // __FUNC_H