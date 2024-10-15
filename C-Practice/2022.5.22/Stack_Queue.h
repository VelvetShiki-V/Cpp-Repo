#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
//栈定义
typedef int STEtype;
typedef struct Stack
{
	STEtype* arr;							//栈通过顺序表实现，定义可扩容数组，容量和顶部
	int top;
	int capacity;
}ST;

//指向两个栈指针的指针
typedef struct MyQueue						
{
	ST* Push;								//Push栈用于数据压入的临时存放
	ST* Pop;								//当需要出队时，将Push栈的数据取头倒入Pop栈，并逐个取头出队
}MQ;

//栈函数
void StackInit(ST* Stack);					//将数组指针置空和容量size置0
void PushTop(ST* Stack, STEtype x);			//压栈
void PopTop(ST* Stack);						//出栈
bool STEmpty(ST* Stack);					//判空
STEtype GetSTop(ST* Stack);					//取栈顶元素
void STDestroy(ST* Stack);					//栈销毁

//栈实现队列函数
MQ* StructInit();							//初始化栈指针
void Push(MQ* obj, STEtype x);				//将入栈元素推到队尾，没有实际意义
int Pop(MQ* obj);							//弹出队头并返回队头元素，实现方式为Pop栈的栈头弹出并返回
int Peek(MQ* obj);							//取队头元素，实现方式为Pop栈头元素
bool Empty(MQ* obj);						//判断队列是否为空
void Free(MQ* obj);							//销毁队列
void PrintQueue(MQ* obj);


//队列定义
typedef int QEtype;
typedef struct Queue						//队列的实现使用链表
{
	QEtype data;							//数值域
	Queue* next;							//结点指针域
}QNode;

//队头队尾指针
typedef struct QuePtr
{
	QNode* Head;							//队头指针
	QNode* Tail;							//队尾指针
}QP;

//指向两个队列指针的指针
typedef struct MyStack						
{
	QP* Q1;									//指向第一个队列
	QP* Q2;									//指向第二个队列
}MST;

//队列函数
void QueueInit(QP* Qptr);					//队头与队尾指针初始化（置空）				
void QueueDestroy(QP* Qptr);				//队列的销毁				
void QPushBack(QP* Qptr, QEtype x);			//队列尾插
void QPopFront(QP* Qptr);					//队列头删
bool QueueEmpty(QP* Qptr);					//判空
QEtype GetQHead(QP* Qptr);					//取队头元素并返回
int QueueSize(QP* Qptr);					//计算队列中结点个数并返回

//队列实现栈函数
MST* StackCreate();							//初始化指向队列指针和两个队列的空间开辟
void PushQ(MST* obj, QEtype x);				//压栈，实现方式为将数据推入非空队列
QEtype StackPop(MST* obj);					//出栈，实现方式为将非空队列数据非队尾数据倒入空队列，剩下的队尾结点出栈，释放并返回
QEtype StackTop(MST* obj);					//实现方式与出栈一致，返回非空队列尾结点值，再将该结点尾插到非空队列，将所在队列置为空队列
bool EmptyQ(MST* obj);						//判空栈（两个队列是否都为空）
void FreeQ(MST* obj);						//释放栈（两个队列的内存释放）
void PrintQ(MST* obj);						//遍历打印栈，实现方式为不断出栈和返回栈顶元素，因此遍历完毕后为空栈（两个空队列）
