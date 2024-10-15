#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

typedef int EType;
typedef struct ListNode
{
	EType data;
	ListNode* next;
	ListNode* prev;
}DGR;

DGR* DGRInit();												//˫���ͷѭ�������ʼ��
void PushBack(DGR* Head, EType x);							//β��
void Print(DGR* Head);										//��ӡ������
DGR* BuyListNode(EType x);									//�����½ڵ�
void PushFront(DGR* Head, EType x);							//ͷ��
void PopBack(DGR* Head);									//βɾ
void PopFront(DGR* Head);									//ͷɾ
void DGRInsert(DGR* pos, EType x);							//��posλ��֮ǰ�����㣬���Գ䵱ͷ��β�壨��Ҫ��
void DGRErase(DGR* pos);									//ɾ��pos���ڵ�ַ�Ľ�㣬���Գ䵱ͷɾβɾ����Ҫ��
