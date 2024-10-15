#pragma once
#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;

//�ַ���ת���ͣ���������
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

//�ַ������
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

//�ַ���ȫ����ת
class Solution2 {
public:
	void reverseString(vector<char>& s) {
		for (int i = 0; i < s.size() / 2; i++)
		{
			swap(s[i], s[s.size() - 1 - i]);
		}
	}
};

//�ҵ���
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

//�ַ�����ˣ����ʺϴ����֣�
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

//��ת�����ַ���
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

//��ת�ַ����е�ÿ������
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

//�ַ�����ˣ���С����ͨ�ԣ�
class Solution7 {
public:
	//�ַ������
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

	//�ַ������
	string multiply(string num1, string num2) {
		std::string::reverse_iterator rit1 = num1.rbegin();
		std::string::reverse_iterator rit2 = num2.rbegin();
		string ret, ret1;
		if (num1[0] == '0' || num2[0] == '0')		//���������ַ���������һ����ֵΪ0������˽��Ϊ0
		{
			ret += '0';
			return ret;
		}
		int tmp = 0, next = 0, i = 0;				//tmp�洢ÿ�ε��˳˻������nextΪ��λ��ʶ��iΪ��'0'��ʶ
		for (rit1; rit1 != num1.rend(); rit1++)
		{
			for (rit2 = num2.rbegin(); rit2 != num2.rend(); rit2++)
			{
				tmp = (*rit1 - '0') * (*rit2 - '0');
				tmp += next;
				if (tmp >= 9)						//�����λͬ�ϴεĽ�λ��Ӻ�Խ�磬��λ
				{
					next = tmp / 10;
					tmp %= 10;
				}
				else
				{
					next = 0;						//���û������λ���򽫽�λֵ��0
				}
				ret1 += to_string(tmp);				//��ÿ��ѭ����˵Ľ���洢Ϊ�ַ���
				//ret1.insert(0, to_string(tmp));
			}
			if (next > 0)							//�����λ���������λ��������ѭ����ʣ���һ����λ��ȫ
			{
				ret1 += to_string(next);
				next = 0;
				//ret1.insert(0, to_string(next));
			}
			reverse(ret1.begin(), ret1.end());		//��Ϊ��������ӵ͵���λ������ģ����Զ�+=������ַ�����Ҫ������
			for (int j = 0; j < i; j++)
			{
				ret1 += '0';
			}
			i++;
			ret = addStrings(ret, ret1);			//��ÿ�εõ����ַ����Ȳ���0�������ַ������
			ret1.clear();
		}
		return ret;
	}
};

//�������
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

//ɾ������������ظ���
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

//�����г��ִ�������һ�������
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

//ֻ����һ�ε����� II
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