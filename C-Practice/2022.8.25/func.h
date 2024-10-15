#pragma once
#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;

//字符串转整型，带正负号
class Solution {
public:
    int StrToInt(string str) {
        int flag = 1, ret = 0, multi = 1;
        if (str[0] == '-')
        {
            flag = -1;
        }
        string::reverse_iterator rit = str.rbegin();
        for (rit; rit != str.rend(); rit++)
        {
            if ((str[0] == '+' || str[0] == '-') && (rit == str.rend() - 1))
            {
                break;
            }
            if (*rit > '9' || *rit < '0')
            {
                return 0;
            }
            ret += (*rit - '0') * multi;
            multi *= 10;
        }
        if (flag == -1)
        {
            ret *= flag;
        }
        return ret;
    }
};

//字符串相加
class Solution1 {
public:
	string addStrings(string num1, string num2) {
		string::const_reverse_iterator rit1 = num1.rbegin();
		string::const_reverse_iterator rit2 = num2.rbegin();
		string arr;
		int next = 0;
		while (rit1 != num1.rend() || rit2 != num2.rend())
		{
			char end1 = rit1 == num1.rend() ? '0' : *rit1;
			char end2 = rit2 == num2.rend() ? '0' : *rit2;
			int num = end1 + end2 - '0' * 2;
			if (next == 1)
			{
				num += 1;
				next--;
			}
			if (num >= 10)
			{
				next = 1;
			}
			arr += num % 10 + '0';
			if (rit1 != num1.rend())
				rit1++;
			if (rit2 != num2.rend())
				rit2++;
		}
		if (next == 1)
		{
			arr += '1';
		}
		reverse(arr.begin(), arr.end());
		return arr;
	}
};

//字符串全部反转
class Solution2 {
public:
	void reverseString(vector<char>& s) {
		for (int i = 0; i < s.size() / 2; i++)
		{
			swap(s[i], s[s.size() - 1 - i]);
		}
	}
};

//找单身狗
class Solution3 {
public:
	int firstUniqChar(string s) {
		int* ref = new int[26];
		memset(ref, 0, 26 * sizeof(int));
		for (auto e : s)
		{
			ref[e - 97]++;
		}
		for (int i = 0; i < s.size(); i++)
		{
			if (ref[s[i] - 97] == 1)
			{
				return i;
			}
		}
		return -1;
	}
};

//字符串相乘（不适合大数字）
class Solution4 {
public:
	unsigned long long StrtoInt(string& num)
	{
		unsigned long long ret = 0, multi = 1;
		std::string::reverse_iterator rit = num.rbegin();
		for (rit; rit != num.rend(); rit++)
		{
			ret += (*rit - '0') * multi;
			multi *= 10;
		}
		return ret;
	}
	void InttoStr(unsigned long long n, string& s)
	{
		while (n != 0)
		{
			unsigned long long tmp = n % 10;
			s.insert(s.begin(), tmp + '0');
			n /= 10;
		}
		if (s.empty())
		{
			s += '0';
		}
	}
	string multiply(string num1, string num2) {
		unsigned long long n1 = StrtoInt(num1);
		unsigned long long n2 = StrtoInt(num2);
		unsigned long long n3 = n1 * n2;
		string s;
		InttoStr(n3, s);
		return s;
	}
};

//反转部分字符串
class Solution5 {
public:
	void swapstr(string& s, int begin, int end)
	{
		while (begin < (end + begin + 1) / 2)
		{
			swap(s[begin], s[end]);
			begin++;
			end--;
		}
	}

	string reverseStr(string s, int k) {
		size_t begin = 0, end = (2 * k - 1);
		while (end <= s.size())
		{
			swapstr(s, begin, begin + k - 1);
			begin = end + 1;
			end += k * 2;
		}
		if (s.size() - begin >= k)
		{
			swapstr(s, begin, begin + k - 1);
		}
		if (s.size() - begin < k)
		{
			swapstr(s, begin, s.size() - 1);
		}
		return s;
	}
};

//反转字符串中的每个单词
class Solution6 {
public:
	void revStr(string& s, int begin, int end)
	{
		while (begin < (begin + end + 1) / 2)
		{
			swap(s[begin], s[end]);
			begin++;
			end--;
		}
	}
	string reverseWords(string s) {
		int begin = 0, end = 0;
		while (begin < s.size())
		{
			while (end < s.size() && s.at(end) != ' ')
			{
				end++;
			}
			revStr(s, begin, end - 1);
			begin = end++ + 1;
		}
		return s;
	}
};

//字符串相乘（大小数字通吃）
class Solution7 {
public:
	//字符串相加
	string addStrings(string num1, string num2) {
		string::const_reverse_iterator rit1 = num1.rbegin();
		string::const_reverse_iterator rit2 = num2.rbegin();
		string arr;
		int next = 0;
		while (rit1 != num1.rend() || rit2 != num2.rend())
		{
			char end1 = rit1 == num1.rend() ? '0' : *rit1;
			char end2 = rit2 == num2.rend() ? '0' : *rit2;
			int num = end1 + end2 - '0' * 2;
			if (next == 1)
			{
				num += 1;
				next--;
			}
			if (num >= 10)
			{
				next = 1;
			}
			arr += num % 10 + '0';
			if (rit1 != num1.rend())
				rit1++;
			if (rit2 != num2.rend())
				rit2++;
		}
		if (next == 1)
		{
			arr += '1';
		}
		reverse(arr.begin(), arr.end());
		return arr;
	}

	//字符串相乘
	string multiply(string num1, string num2) {
		std::string::reverse_iterator rit1 = num1.rbegin();
		std::string::reverse_iterator rit2 = num2.rbegin();
		string ret, ret1;
		if (num1[0] == '0' || num2[0] == '0')		//如果传入的字符串中其中一个数值为0，则相乘结果为0
		{
			ret += '0';
			return ret;
		}
		int tmp = 0, next = 0, i = 0;				//tmp存储每次单趟乘积结果，next为进位标识，i为补'0'标识
		for (rit1; rit1 != num1.rend(); rit1++)
		{
			for (rit2 = num2.rbegin(); rit2 != num2.rend(); rit2++)
			{
				tmp = (*rit1 - '0') * (*rit2 - '0');
				tmp += next;
				if (tmp >= 9)						//如果该位同上次的进位相加后越界，进位
				{
					next = tmp / 10;
					tmp %= 10;
				}
				else
				{
					next = 0;						//如果没发生进位，则将进位值置0
				}
				ret1 += to_string(tmp);				//将每次循环相乘的结果存储为字符串
				//ret1.insert(0, to_string(tmp));
			}
			if (next > 0)							//如果进位发生在最高位，则跳出循环后将剩余的一个进位补全
			{
				ret1 += to_string(next);
				next = 0;
				//ret1.insert(0, to_string(next));
			}
			reverse(ret1.begin(), ret1.end());		//因为除法结果从低到高位是逆序的，所以对+=处理的字符串需要逆序处理
			for (int j = 0; j < i; j++)
			{
				ret1 += '0';
			}
			i++;
			ret = addStrings(ret, ret1);			//将每次得到的字符串先补‘0’，再字符串相加
			ret1.clear();
		}
		return ret;
	}
};

//杨慧三角
class Solution8 {
public:
	vector<vector<int>> generate(int numRows) {
		vector<vector<int>> vv;
		vv.resize(numRows);
		int i = 0;
		while (i < numRows)
		{
			vv[i].resize(i + 1);
			vv[i].front() = vv[i].back() = 1;
			i++;
		}
		if (numRows >= 3)
		{
			for (i = 2; i < numRows; i++)
			{
				for (int j = 1; j < vv[i].size() - 1; j++)
				{
					vv[i][j] = vv[i - 1][j - 1] + vv[i - 1][j];
				}
			}
		}
		return vv;
	}
};

//删除有序数组的重复项
class Solution9 {
public:
	int removeDuplicates(vector<int>& nums) {
		if (nums.empty())
			return 0;
		int i = 0;
		vector<int>::iterator it = nums.begin();
		for (it; it != nums.end(); it++)
		{
			if (*it == nums[i])
			{
				continue;
			}
			else
			{
				nums[++i] = *it;
			}
		}
		nums.resize(i + 1);
		return i + 1;
	}
};

//数组中出现次数超过一半的数字
class Solution10 {
public:
	int MoreThanHalfNum_Solution(vector<int> numbers) {
		sort(numbers.begin(), numbers.end());
		int half = numbers.size() / 2, count = 0, tmp = numbers[0];
		for (auto e : numbers)
		{
			if (e == tmp)
				count++;
			else
			{
				count = 1;
				tmp = e;
			}
			if (count > half)
				return e;
		}
		return 0;
	}
};

//只出现一次的数字 II
class Solution11 {
public:
	int singleNumber(vector<int>& nums) {
		sort(nums.begin(), nums.end());
		int tmp = nums[0], count = 0;
		vector<int>::iterator it = nums.begin();
		for (it; it != nums.end(); it++)
		{
			if (tmp == *it)
			{
				count++;
			}
			else if (tmp != *it && count > 1)
			{
				count = 0;
				tmp = *it;
			}
			else
			{
				return *(it - 1);
			}
		}
		return *(it - 1);
	}
};