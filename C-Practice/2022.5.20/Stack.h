#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

typedef int StackEtype;								//栈中元素的数据类型（本质为数组/链表中存储数据）
typedef struct Stack
{
	StackEtype* a;									//指向栈底地址或为栈开辟空间/扩容
	int top;										//标识栈顶位置
	int capacity;									//标识栈容量
}ST;

void StackInit(ST* Bot);							//栈结构的初始化
void StackDestroy(ST* Bot);							//栈结构的销毁
void StackPush(ST* Bot, StackEtype x);				//压栈，只能在栈顶插入数据
void StackPop(ST* Bot);								//出栈，只能从栈顶删除数据
bool StackEmpty(ST* Bot);							//判断栈是否为空
StackEtype StackTop(ST* Bot);						//取出栈顶元素
int StackSize(ST* Bot);								//计算压栈元素个数
