#pragma once
#include<stdio.h>
#include<assert.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<time.h>
typedef bool(*COM)(int, int);

//直接插入排序
void InsertSort(int* arr, int sz);

//希尔排序
void ShellSort(int* arr, int sz);							//gap分组的插入排序

//选择排序
void SelectSort(int* arr, int sz);							//选大选小交换首尾

//冒泡排序
void BubbleSort(int* arr, int sz);							//flag判断是否有序并不再比较

//快速排序
void QuickSort(int* arr, int Head, int Tail);
int HoareSort(int* arr, int left, int right);				//hoare版
int PitSort(int* arr, int left, int right);					//挖坑法
int PointerSort(int* arr, int left, int right);				//前后指针法
int GetMid(int* arr, int left, int right);					//三数取中
void QuickSortStack(int* arr, int Head, int Tail);			//非递归栈实现

//归并排序
void MergeSort(int* arr, int sz);							//归并递归排序
void Subsort(int* arr, int* tmp, int Head, int Tail);		//归并子递归函数
void NonRecurMergeSort(int* arr, int sz);					//归并非递归排序

//堆排序
void HPCreate(int* arr, int sz, COM rule);
void AdjustDownward(int* arr, int sz, int parent, COM rule);
void HPSort(int* arr, int sz, COM rule);
bool Ascend(int a, int b);
bool Descend(int a, int b);

//计数排序
void CountSort(int* arr, int sz);							//range范围选最大最小并计数

///////////////////////////////////////////////////////////////////////////
typedef int STEtype;
typedef struct Stack
{
	STEtype* arr;
	int top;
	int capacity;
}ST;

ST* STInit();
void STPush(ST* Bot, STEtype x);
void STPop(ST* Bot);
STEtype STTop(ST* Bot);
void STDestroy(ST** Bot);
bool STEmpty(ST* Bot);