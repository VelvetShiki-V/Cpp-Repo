#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

typedef int QueEType;
typedef struct Queue
{
	QueEType data;
	Queue* next;
}QNode;
typedef struct Queueptr
{
	QNode* Head;
	QNode* Tail;
}QP;

void QueueInit(QP* Qptr);								//队列指针初始化
void QueueDestroy(QP* Qptr);							//队列消除
void QPushBack(QP* Qptr, QueEType x);					//队列尾插
void QPopFront(QP* Qptr);								//队列头删
bool QueueEmpty(QP* Qptr);								//队列判空
QueEType GetQHead(QP* Qptr);							//取队列头值
QueEType GetQTail(QP* Qptr);							//取队列尾值
int QueueSize(QP* Qptr);								//队列大小
void Print(QP* Qptr);									//打印队列
