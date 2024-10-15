#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
typedef int Etype;
typedef struct Singly_linked_list
{
	Etype data;
	Singly_linked_list* next;
}SgL;

SgL* BuyListNode(Etype Newnode);						//�����½ڵ�
void Print(SgL* Head);									//��ӡ����
SgL* PBackDelete(SgL * Head, Etype x);					//�Ƴ����β���㷨
SgL* ReverseSL(SgL* Head);								//���������㷨
SgL* PushFront(SgL* Head, Etype x);						//ͷ�庯��
SgL* ReverseSL2(SgL* Head);								//����������ָ���㷨
Etype FindMid(SgL* Head);								//�����м����㷨
Etype LastKVal(SgL* Head, int k);						//���ҵ�����k��

