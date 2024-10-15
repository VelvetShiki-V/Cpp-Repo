#pragma once
#include<stdio.h>
#include<assert.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<time.h>
typedef bool(*COM)(int, int);

//ֱ�Ӳ�������
void InsertSort(int* arr, int sz);

//ϣ������
void ShellSort(int* arr, int sz);							//gap����Ĳ�������

//ѡ������
void SelectSort(int* arr, int sz);							//ѡ��ѡС������β

//ð������
void BubbleSort(int* arr, int sz);							//flag�ж��Ƿ����򲢲��ٱȽ�

//��������
void QuickSort(int* arr, int Head, int Tail);
int HoareSort(int* arr, int left, int right);				//hoare��
int PitSort(int* arr, int left, int right);					//�ڿӷ�
int PointerSort(int* arr, int left, int right);				//ǰ��ָ�뷨
int GetMid(int* arr, int left, int right);					//����ȡ��
void QuickSortStack(int* arr, int Head, int Tail);			//�ǵݹ�ջʵ��

//�鲢����
void MergeSort(int* arr, int sz);							//�鲢�ݹ�����
void Subsort(int* arr, int* tmp, int Head, int Tail);		//�鲢�ӵݹ麯��
void NonRecurMergeSort(int* arr, int sz);					//�鲢�ǵݹ�����

//������
void HPCreate(int* arr, int sz, COM rule);
void AdjustDownward(int* arr, int sz, int parent, COM rule);
void HPSort(int* arr, int sz, COM rule);
bool Ascend(int a, int b);
bool Descend(int a, int b);

//��������
void CountSort(int* arr, int sz);							//range��Χѡ�����С������

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