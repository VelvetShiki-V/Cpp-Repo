#pragma once

#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

typedef int STEtype;
typedef struct Stack
{
	STEtype* arr;
	int top;
	int capacity;
}ST;

//
ST* StackInit();
void StackPush(ST* Bot, STEtype x);
void StackPop(ST* Bot);
STEtype StackTop(ST* Bot);
bool StackEmpty(ST* Bot);
ST* StackDestroy(ST* Bot);
void PrintPop(ST* Bot);
int StackSize(ST* Bot);