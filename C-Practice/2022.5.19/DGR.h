#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

typedef int EType;
typedef struct ListNode
{
	EType data;
	ListNode* next;
	ListNode* prev;
}DGR;

DGR* DGRInit();												//双向带头循环链表初始化
void PushBack(DGR* Head, EType x);							//尾插
void Print(DGR* Head);										//打印链表函数
DGR* BuyListNode(EType x);									//开辟新节点
void PushFront(DGR* Head, EType x);							//头插
void PopBack(DGR* Head);									//尾删
void PopFront(DGR* Head);									//头删
void DGRInsert(DGR* pos, EType x);							//在pos位置之前插入结点，可以充当头插尾插（重要）
void DGRErase(DGR* pos);									//删除pos所在地址的结点，可以充当头删尾删（重要）
