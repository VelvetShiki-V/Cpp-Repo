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

SgL* BuyListNode(Etype Newnode);						//�����½ڵ㺯��
void Print(SgL* Head);									//��ӡ������
Etype LastKVal(SgL* Head, int k);						//������������k����㺯��
SgL* Merging2SL(SgL* Head1, SgL* Head2);				//�ϲ���������������
SgL* SLSlicing(SgL* Head, int x);						//�ָ�������
bool PalinDrome(SgL* Head);								//�ж�һ�������Ƿ�Ϊ����
SgL* CrossOver(SgL* Head1, SgL* Head2);					//���������ཻ��㺯��
bool RoundSgL(SgL* Head);								//�ж�һ�������Ƿ�Ϊ��������
