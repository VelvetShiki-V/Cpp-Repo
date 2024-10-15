#pragma once
#include<stdio.h>
#include<assert.h>
#include<stdlib.h>
typedef int SLElemType;

typedef struct SeqList
{
	SLElemType* arr;
	int size;
	int capacity;
}SL;

//顺序表基本功能
void SLInit(SL* parr);
void SLCapCheck(SL* parr);
void SLPushBack(SL* parr, SLElemType x);
void SLPopBack(SL* parr);
void SLPushFront(SL* parr, SLElemType x);
void SLPopFront(SL* parr);
void SLInsert(SL* parr, SLElemType x, int pos);
int SLErase(SL* parr, SLElemType x);
int SLFind(SL* parr, SLElemType x);
void SLDestroy(SL* parr);
void Print(SL* parr);
