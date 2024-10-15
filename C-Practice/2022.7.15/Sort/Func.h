#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"HeapFunc.h"
#include"StackFunc.h"

extern int count;

//��������
typedef bool (*COM)(int, int);
bool Descend(int a, int b);
bool Ascend(int a, int b);

//ֱ�Ӳ�������
void InsertSort(int* arr, int sz, COM rule);			//ǰ�󽻻�˼·
void InsertSort2(int* arr, int sz, COM rule);			//����˼·

//ϣ������
void ShellSort(int* arr, int sz, COM rule);				//gap����Ĳ�������

//ѡ������
void SelectSort(int* arr, int sz, COM rule);			//ѡ��ѡС������β

//ð������
void BubbleSortRevised(int* arr, int sz, COM rule);		//flag�ж��Ƿ����򲢲��ٱȽ�

//��������
void QuickSort(int* arr, int Head, int Tail);
int HoareSort(int* arr, int left, int right);			//hoare��
int PitSort(int* arr, int left, int right);				//�ڿӷ�
int PointerSort(int* arr, int left, int right);			//ǰ��ָ�뷨
int GetMid(int* arr, int left, int right);				//����ȡ��
void QuickSortStack(int* arr, int Head, int Tail);		//�ǵݹ�ջʵ��

//�鲢����
void MergeSort(int* arr, int sz);						//�鲢�ݹ�����
void Subsort(int* arr, int* tmp, int Head, int Tail);	//�鲢�ӵݹ麯��
void NonRecurMergeSort(int* arr, int sz);				//�鲢�ǵݹ�����

//��������
void CountSort(int* arr, int sz);						//range��Χѡ�����С������