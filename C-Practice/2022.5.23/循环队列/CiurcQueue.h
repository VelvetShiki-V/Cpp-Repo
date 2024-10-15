#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

typedef int CRQueue;						//循环队列存放的数值类型
typedef struct CirQueue						//循环队列结构体
{
	CRQueue* arr;							//使用可扩容数组实现队列——FIFO
	int k;									//队列容量
	int Head;								//队头下标
	int Tail;								//队尾下标（为队尾元素的下一个位置）
}CRQ;

CRQ* Create(int k);							//初始化循环队列，开辟一个存放循环队列信息的内存，再开辟一个实际存储数据的扩容数组
bool enQueue(CRQ* obj, CRQueue value);		//数组入队
bool deQueue(CRQ* obj);						//数组出队
CRQueue GetFront(CRQ* obj);					//取队头下标所在元素
CRQueue GetRear(CRQ* obj);					//取队尾下标的前一个下标所在元素
bool Empty(CRQ* obj);						//判空——队尾和队头下标相等时判定为空队列
bool Full(CRQ* obj);						//判满——队尾下标+1再模容量k+1,，若等于队头下标，则队列满
void Free(CRQ* obj);						//释放扩容数组和队列信息内存