#pragma once
#include<stdio.h>
#include<assert.h>
#include<stdlib.h>

typedef struct SeqList
{
	int* arr;
	int size;
	int capacity;
}SL;

//顺序表基本功能
void SLInit(SL* parr);
void SLCapCheck(SL* parr);
void SLPushBack(SL* parr, int x);
void SLPopBack(SL* parr);
void SLPushFront(SL* parr, int x);
void SLPopFront(SL* parr);
void SLInsert(SL* parr, int x, int pos);
void SLErase(SL* parr);
int SLFind(SL* parr, int x);
void SLDestroy(SL* parr);
void Print(SL* parr);
