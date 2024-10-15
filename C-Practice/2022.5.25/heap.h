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

void HeapInit(HP* hp);							//�ѳ�ʼ��
void HeapDestroy(HP* hp);						//������
void HPPush(HP* hp, HPEtype x);					//�ѵ����ݲ���
void AdjustUp(HP* hp, int child);				//���ϵ���
void Swap(HPEtype* a, HPEtype* b);				//���������ڵ�����
//void HPPop(HP* hp);								//�ѵ�����ɾ��
//HPEtype HPTop(HP* hp);							//ȡ���Ѷ����ڵ�Ԫ��
//bool HPEmpty(HP* hp);							//�п�
//int HPSize(HP* hp);								//�����ݸ���