#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<time.h>

typedef int HPEtype;
typedef bool(*COM)(int, int);
typedef struct heap
{
	HPEtype* arr;
	int size;
	int capacity;
}HP;

//¶Ñº¯Êý½Ó¿Ú
HP* HPInit();
bool Bigger(HPEtype a, HPEtype b);
bool Smaller(HPEtype a, HPEtype b);
void HPPush(HP* root, HPEtype x, COM rule);
void HPPop(HP* root, COM rule);
bool HPEmpty(HP* root);
int HPSize(HP* root);
HPEtype HPTop(HP* root);
HP* HPDestroy(HP* root);
void AdjustUpward(HPEtype* arr, int child, COM rule);
void AdjustDownward(HPEtype* arr, int size, int parent, COM rule);
void HPPrint(HP* root, COM rule);
void Swap(HPEtype* a, HPEtype* b);
///////////////////////////////////////////////////
void HPCreateDown(int* arr, int size, COM rule);
void HPCreateUP(int* arr, int size, COM rule);
void HPSort(int* arr, int size, COM rule);
void BubbleSort(int* arr, int size, COM rule);
HPEtype* TopK(HPEtype* arr, int k, int size, COM rule);
void PrintTopK(HPEtype* Toparr, int k);
