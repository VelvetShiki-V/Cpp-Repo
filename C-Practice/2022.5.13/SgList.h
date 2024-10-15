#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

typedef int SGLElemType;									//��������ֵ�����������������

typedef struct SingleList									//����Ľṹ�嶨�壬����������ΪSgLNode���ṹ������ΪSingleList
{
	SGLElemType data;										//������ֵ��
	struct SingleList* next;								//��������ָ��������ڴ�ռ�ĺ������ṹ���ַ
}SgLNode;

void SGLPrint(SgLNode* Head);								//��ӡ������ֵ		
SgLNode* BuyListNode(SGLElemType x);						//�½ڵ����뿪�ٺ���
void SGLPushBack(SgLNode** Head, SGLElemType x);			//����β�壬����ָ��������������׽ڵ��ַ�����Խ��յ���Ҫ�Կ�������׽ڵ��ַ�����޸ĵ����
void SGLPushFront(SgLNode** Head, SGLElemType x);			//����ͷ�壬���׽ڵ�Ľṹ���ַ���ö���ָ�����
void SGLPopFront(SgLNode** Head);							//����ͷɾ
void SGLPopBack(SgLNode** Head);							//����βɾ
SgLNode* SGLFind(SgLNode* Head, SGLElemType x);				//�������ֵ�Ľ���ַ��������
void SGLInsert(SgLNode** Head, SgLNode* pos, SGLElemType x);//�����м���루ĳ���ǰ����
void SGLErase(SgLNode** Head, SgLNode* pos);				//�����������ע������***��
void SGLInsertAfter(SgLNode* pos, SGLElemType x);			//�����м���루ĳ���󷽣�
void SGLEraseAfter(SgLNode* pos);							//�����������ĳ���󷽣�
