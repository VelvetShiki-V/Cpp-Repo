#define _CRT_SECURE_NO_WARNINGS 1
#include"Func.h"
//括号匹配栈算法改进
//有效字符串需满足：
//左括号必须用相同类型的右括号闭合。
//左括号必须以正确的顺序闭合。
int main()
{
	//char arr[7] = "()[]{}";	//true
	//char arr[5] = "(]{}";		//false
	//char arr[5] = "({})";		//true
	//char arr[5] = "([)]";		//false
	//char arr[20] = "((([[{}]])))";	//true
	//char arr[20] = "((([[{}]]]";		//false
	char arr[20] = "()]]{}";			//false
	int size = sizeof(arr) / sizeof(arr[0]);
	if (BracketMatch(arr, size))
	{
		puts("true");
	}
	else
	{
		puts("false");
	}
	return 0;
}