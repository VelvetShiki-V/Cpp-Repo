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

//堆通用函数
void HPInit(HP* hp);							//堆初始化
void HPDestroy(HP* hp);							//堆销毁
HPEtype HPTop(HP* hp);							//取堆顶元素
void Swap(HPEtype* a, HPEtype* b);				//交换元素
bool HPEmpty(HP* hp);							//判空
int HPSize(HP* hp);								//堆的元素个数

//小根堆函数
void SmHPPush(HP* hp, HPEtype x);				//小根堆插入
void SmMoveUpward(HP* hp, int parent);			//插入上调
void SmMoveDownward(HP* hp, int parent);		//下调
void SmHPPop(HP* hp);							//小根堆去顶
void SmPrint(HP* hp);							//小根堆遍历（取顶+Pop，等同于升序打印）

//大根堆函数
void BigHPPush(HP* hp, HPEtype x);				//大根堆插入
void BigMoveUpward(HP* hp, int parent);			//插入上调
void BigMoveDownward(HP* hp, int parent);		//下调
void BigHPPop(HP* hp);							//大根堆去顶
void BigPrint(HP* hp);							//大根堆遍历（取顶+Pop，等同于降序打印）

//堆排序
void HPSortAscend(HP* hp);						//升序
void HPSortDescend(HP* hp);						//降序