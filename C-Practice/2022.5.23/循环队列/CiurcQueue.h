#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

typedef int CRQueue;						//ѭ�����д�ŵ���ֵ����
typedef struct CirQueue						//ѭ�����нṹ��
{
	CRQueue* arr;							//ʹ�ÿ���������ʵ�ֶ��С���FIFO
	int k;									//��������
	int Head;								//��ͷ�±�
	int Tail;								//��β�±꣨Ϊ��βԪ�ص���һ��λ�ã�
}CRQ;

CRQ* Create(int k);							//��ʼ��ѭ�����У�����һ�����ѭ��������Ϣ���ڴ棬�ٿ���һ��ʵ�ʴ洢���ݵ���������
bool enQueue(CRQ* obj, CRQueue value);		//�������
bool deQueue(CRQ* obj);						//�������
CRQueue GetFront(CRQ* obj);					//ȡ��ͷ�±�����Ԫ��
CRQueue GetRear(CRQ* obj);					//ȡ��β�±��ǰһ���±�����Ԫ��
bool Empty(CRQ* obj);						//�пա�����β�Ͷ�ͷ�±����ʱ�ж�Ϊ�ն���
bool Full(CRQ* obj);						//����������β�±�+1��ģ����k+1,�������ڶ�ͷ�±꣬�������
void Free(CRQ* obj);						//�ͷ���������Ͷ�����Ϣ�ڴ�