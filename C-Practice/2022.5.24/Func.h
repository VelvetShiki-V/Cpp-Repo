#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<string.h>
//ջ�ṹ����
typedef char SType;
typedef struct Stack
{
	SType* a;
	int top;
	int capacity;
}ST;
//����ƥ��
bool BracketMatch(char* arr, int sz);