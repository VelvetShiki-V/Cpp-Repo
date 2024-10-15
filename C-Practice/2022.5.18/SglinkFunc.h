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

SgL* BuyListNode(Etype Newnode);						//开辟新节点函数
void Print(SgL* Head);									//打印链表函数
Etype LastKVal(SgL* Head, int k);						//查找链表倒数第k个结点函数
SgL* Merging2SL(SgL* Head1, SgL* Head2);				//合并两个有序链表函数
SgL* SLSlicing(SgL* Head, int x);						//分割链表函数
bool PalinDrome(SgL* Head);								//判断一个链表是否为回文
SgL* CrossOver(SgL* Head1, SgL* Head2);					//找两链表相交结点函数
bool RoundSgL(SgL* Head);								//判断一个链表是否为环形链表
