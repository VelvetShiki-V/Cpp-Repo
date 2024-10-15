#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

typedef int QueEType;
typedef struct Queue
{
	QueEType data;
	Queue* next;
}QNode;
typedef struct Queueptr
{
	QNode* Head;
	QNode* Tail;
}QP;

void QueueInit(QP* Qptr);								//����ָ���ʼ��
void QueueDestroy(QP* Qptr);							//��������
void QPushBack(QP* Qptr, QueEType x);					//����β��
void QPopFront(QP* Qptr);								//����ͷɾ
bool QueueEmpty(QP* Qptr);								//�����п�
QueEType GetQHead(QP* Qptr);							//ȡ����ͷֵ
QueEType GetQTail(QP* Qptr);							//ȡ����βֵ
int QueueSize(QP* Qptr);								//���д�С
void Print(QP* Qptr);									//��ӡ����
