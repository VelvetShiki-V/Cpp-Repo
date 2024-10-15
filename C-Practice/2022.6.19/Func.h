#pragma once
#include<stdio.h>
#include<assert.h>
#include<stdlib.h>

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
SgLNode* SGLPushFront1(SgLNode* Head, SGLElemType x);
void SGLPopFront(SgLNode** Head);							//����ͷɾ
void SGLPopBack(SgLNode** Head);							//����βɾ
SgLNode* SGLFind(SgLNode* Head, SGLElemType x);				//�������ֵ�Ľ���ַ��������
void SGLInsert(SgLNode** Head, SgLNode* pos, SGLElemType x);//�����м���루ĳ���ǰ����
void SGLErase(SgLNode** Head, SgLNode* pos);				//�����������ע������***��
void SGLInsertAfter(SgLNode* pos, SGLElemType x);			//�����м���루ĳ���󷽣�
void SGLEraseAfter(SgLNode* pos);							//�����������ĳ���󷽣�
void Erase(SgLNode** Head, SgLNode* pos);





//typedef int SLEtype;
//typedef struct Sglist
//{
//	SLEtype data;
//	struct Sglist* next;
//}SGL;

////�����������
//SGL* BuyListNode(SLEtype x);
//void PushBack(SGL* Head, SLEtype x);
//void PopBack(SGL** Head);
//void PushFront(SGL** Head, SLEtype x);
//void PopFront(SGL** Head);
//void InsertPrev(SGL** Head, SGL* pos, SLEtype x);
//void InsertAfter(SGL** Head, SGL* pos, SLEtype x);
//SGL* Find(SGL* Head, SGL* pos);
//void Erase(SGL** Head, SGL* pos);
//bool Empty(SGL* Head);
//int Size(SGL* Head);
//void Print(SGL* Head);
//void Destroy(SGL** Head);
