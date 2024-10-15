#include"func.h"
string stradd(const string& num1, const string& num2)
{
	string::const_reverse_iterator rit1 = num1.crbegin();
	string::const_reverse_iterator rit2 = num2.crbegin();
	string arr;
	int next = 0;
	while (rit1 != num1.crend() || rit2 != num2.crend())
	{
		char end1 = rit1 == num1.crend() ? '0' : *rit1;
		char end2 = rit2 == num2.crend() ? '0' : *rit2;
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
		if (rit1 != num1.crend())
			rit1++;
		if (rit2 != num2.crend())
			rit2++;
	}
	if (next == 1)
	{
		arr += '1';
	}
    reverse(arr.begin(), arr.end());
	return arr;
}
