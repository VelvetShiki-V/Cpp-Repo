#ifndef __FUNC_H
#define __FUNC_H
#pragma once
#include<iostream>
#include<vector>
#include<string>
#include<vector>
#include<list>
#include<queue>
#include<math.h>
#include<stack>


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

int StrToInt(string str) {
    if (str.empty()) return 0;
    bool flag = false;
    if (str[0] == '+') str.erase(str.begin());
    else if (str[0] == '-') {
        flag = true;
        str.erase(str.begin());
    }
    int multi = 1;
    long long num = 0;
    string::reverse_iterator rit = str.rbegin();
    for (rit; rit != str.rend(); ++rit) {
        if (*rit > 57 || *rit < 48) {
            break;
        }
        else {
            num += multi * (int)(*rit - 48);
            multi *= 10;
        }
    }
    if (rit != str.rend()) return 0;
    else {
        if (flag == true)
            return -num;
        else
            return num;
    }
}

class Parenthesis {
public:
    bool chkParenthesis(string A, int n) {
        // write code here
        if (n <= 1) return false;
        if (A[0] == ')') return false;
        bool flag = true;
        stack<char> st;
        for (auto e : A) {
            if (e == '(' || e == ')');
            else return false;
            if (e == '(') {
                st.push(e);
            }
            else {
                if (st.empty()) return false;
                st.pop();
            }
        }
        if (!st.empty()) return false;
        return true;
    }
};

#endif // __FUNC_H