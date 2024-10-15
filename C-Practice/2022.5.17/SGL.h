#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
typedef int Etype;
typedef struct Singly_linked_list
{
	Etype data;
	Singly_linked_list* next;
}SgL;

SgL* BuyListNode(Etype Newnode);						//开辟新节点
void Print(SgL* Head);									//打印链表
SgL* PBackDelete(SgL * Head, Etype x);					//移除结点尾插算法
SgL* ReverseSL(SgL* Head);								//逆置链表算法
SgL* PushFront(SgL* Head, Etype x);						//头插函数
SgL* ReverseSL2(SgL* Head);								//逆置链表三指针算法
Etype FindMid(SgL* Head);								//查找中间结点算法
Etype LastKVal(SgL* Head, int k);						//查找倒数第k个

