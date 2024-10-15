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

//��ͨ�ú���
void HPInit(HP* hp);							//�ѳ�ʼ��
void HPDestroy(HP* hp);							//������
HPEtype HPTop(HP* hp);							//ȡ�Ѷ�Ԫ��
void Swap(HPEtype* a, HPEtype* b);				//����Ԫ��
bool HPEmpty(HP* hp);							//�п�
int HPSize(HP* hp);								//�ѵ�Ԫ�ظ���

//С���Ѻ���
void SmHPPush(HP* hp, HPEtype x);				//С���Ѳ���
void SmMoveUpward(HP* hp, int parent);			//�����ϵ�
void SmMoveDownward(HP* hp, int parent);		//�µ�
void SmHPPop(HP* hp);							//С����ȥ��
void SmPrint(HP* hp);							//С���ѱ�����ȡ��+Pop����ͬ�������ӡ��

//����Ѻ���
void BigHPPush(HP* hp, HPEtype x);				//����Ѳ���
void BigMoveUpward(HP* hp, int parent);			//�����ϵ�
void BigMoveDownward(HP* hp, int parent);		//�µ�
void BigHPPop(HP* hp);							//�����ȥ��
void BigPrint(HP* hp);							//����ѱ�����ȡ��+Pop����ͬ�ڽ����ӡ��

//������
void HPSortAscend(HP* hp);						//����
void HPSortDescend(HP* hp);						//����