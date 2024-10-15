#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

typedef int HPEtype;
typedef struct Heap
{
	HPEtype* arr;
	int size;
	int capacity;
}HP;

void HeapInit(HP* hp);							//堆初始化
void HeapDestroy(HP* hp);						//堆销毁
void HPPush(HP* hp, HPEtype x);					//堆的数据插入
void AdjustUp(HP* hp, int child);				//向上调整
void Swap(HPEtype* a, HPEtype* b);				//交换两个节点数据
//void HPPop(HP* hp);								//堆的数据删除
//HPEtype HPTop(HP* hp);							//取出堆顶根节点元素
//bool HPEmpty(HP* hp);							//判空
//int HPSize(HP* hp);								//堆数据个数