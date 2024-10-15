#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<string.h>

//单链表结构定义
typedef int SEtype;
typedef struct SingleList
{
	SEtype data;
	SingleList* next;
}SGL;
SGL* BuyListNode(SEtype x);			//开辟结点

//带随机指针链表结构定义
typedef struct Random
{
	SEtype data;
	Random* next;
	Random* random;					//相比原单链表结构多了一个指向随机结点的指针域
}RD;
RD* BuyRandom(SEtype x);			//开辟随机指针结点

//栈结构定义
typedef char SType;
typedef struct Stack
{
	SType* a;
	int top;
	int capacity;
}ST;

//环形链表
bool Detect(SGL* Head);				//判断链表是否有环
SEtype Enter(SGL* n1);				//返回入环点值（更方便观察）

//深拷贝
RD* Copy(RD* Head);					//将原随机链表深拷贝并返回首结点地址至实参

//括号匹配
bool BracketMatch(char* arr, int sz);