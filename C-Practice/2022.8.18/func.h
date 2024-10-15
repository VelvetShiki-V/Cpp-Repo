#pragma once
#include<iostream>
#include<vector>
using namespace std;

class NumAppearOnce {
public:
    int single_number(vector<int>& nums) {
        int ret = 0;            //����һ���������ڽ��������
        for (auto e : nums)     //����vector�������������
        {
            ret ^= e;
        }
        return ret;
    }
};

class TwoNumAPPearOnce {
public:
	vector<int> singleNumber(vector<int>& nums) {
		int sum = 0;
		for (auto e : nums)
		{
			sum ^= e;
		}
		long long mask = sum == INT_MIN ? INT_MIN : sum & (-sum);
		vector<int> ret(2);
		for (auto i : nums)
		{
			if ((i & mask) == 0)
				ret[0] ^= i;
			else
				ret[1] ^= i;
		}
		return ret;
	}
};

class Tele {
public:
    void arrange_compos(string& digits, int d, vector<string>& ret, string combineStr)
    {
        if (d == digits.size())
        {
            ret.push_back(combineStr);
            return;
        }
        int num = digits[d] - '0';
        string Str = refer[num];
        for (auto i : Str)
        {
            arrange_compos(digits, d + 1, ret, combineStr + i);
        }
    }

    vector<string> letterCombinations(string digits) {
        vector<string> ret;
        if (digits.empty())
        {
            return ret;
        }
        string Str;
        arrange_compos(digits, 0, ret, Str);
        return ret;
    }
private:
    vector<string> refer = { "", "", "abc", "def", "ghi", "jkl", "mno",
                            "pqrs", "tuv", "wxyz" };
};