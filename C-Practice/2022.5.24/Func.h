#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<string.h>
//栈结构定义
typedef char SType;
typedef struct Stack
{
	SType* a;
	int top;
	int capacity;
}ST;
//括号匹配
bool BracketMatch(char* arr, int sz);