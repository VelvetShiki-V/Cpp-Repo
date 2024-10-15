#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

typedef int SGLElemType;									//将链表数值域的数据类型重命名

typedef struct SingleList									//链表的结构体定义，重命名类型为SgLNode，结构体名称为SingleList
{
	SGLElemType data;										//链表数值域
	struct SingleList* next;								//链表结点中指向非连续内存空间的后续结点结构体地址
}SgLNode;

void SGLPrint(SgLNode* Head);								//打印链表数值		
SgLNode* BuyListNode(SGLElemType x);						//新节点申请开辟函数
void SGLPushBack(SgLNode** Head, SGLElemType x);			//链表尾插，二级指针变量接收链表首节点地址，用以接收当需要对空链表的首节点地址进行修改的情况
void SGLPushFront(SgLNode** Head, SGLElemType x);			//链表头插，传首节点的结构体地址，用二级指针接收
void SGLPopFront(SgLNode** Head);							//链表头删
void SGLPopBack(SgLNode** Head);							//链表尾删
SgLNode* SGLFind(SgLNode* Head, SGLElemType x);				//链表查找值的结点地址，并返回
void SGLInsert(SgLNode** Head, SgLNode* pos, SGLElemType x);//链表中间插入（某结点前方）
void SGLErase(SgLNode** Head, SgLNode* pos);				//链表结点擦除（注意事项***）
void SGLInsertAfter(SgLNode* pos, SGLElemType x);			//链表中间插入（某结点后方）
void SGLEraseAfter(SgLNode* pos);							//链表结点擦除（某结点后方）
