#define _CRT_SECURE_NO_WARNINGS 1
#include"Func.h"
//����ƥ��ջ�㷨�Ľ�
//��Ч�ַ��������㣺
//�����ű�������ͬ���͵������űպϡ�
//�����ű�������ȷ��˳��պϡ�
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