#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"HeapFunc.h"
#include"StackFunc.h"

extern int count;

//交换规则
typedef bool (*COM)(int, int);
bool Descend(int a, int b);
bool Ascend(int a, int b);

//直接插入排序
void InsertSort(int* arr, int sz, COM rule);			//前后交换思路
void InsertSort2(int* arr, int sz, COM rule);			//覆盖思路

//希尔排序
void ShellSort(int* arr, int sz, COM rule);				//gap分组的插入排序

//选择排序
void SelectSort(int* arr, int sz, COM rule);			//选大选小交换首尾

//冒泡排序
void BubbleSortRevised(int* arr, int sz, COM rule);		//flag判断是否有序并不再比较

//快速排序
void QuickSort(int* arr, int Head, int Tail);
int HoareSort(int* arr, int left, int right);			//hoare版
int PitSort(int* arr, int left, int right);				//挖坑法
int PointerSort(int* arr, int left, int right);			//前后指针法
int GetMid(int* arr, int left, int right);				//三数取中
void QuickSortStack(int* arr, int Head, int Tail);		//非递归栈实现

//归并排序
void MergeSort(int* arr, int sz);						//归并递归排序
void Subsort(int* arr, int* tmp, int Head, int Tail);	//归并子递归函数
void NonRecurMergeSort(int* arr, int sz);				//归并非递归排序

//计数排序
void CountSort(int* arr, int sz);						//range范围选最大最小并计数