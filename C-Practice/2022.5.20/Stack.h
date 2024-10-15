#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

typedef int StackEtype;								//ջ��Ԫ�ص��������ͣ�����Ϊ����/�����д洢���ݣ�
typedef struct Stack
{
	StackEtype* a;									//ָ��ջ�׵�ַ��Ϊջ���ٿռ�/����
	int top;										//��ʶջ��λ��
	int capacity;									//��ʶջ����
}ST;

void StackInit(ST* Bot);							//ջ�ṹ�ĳ�ʼ��
void StackDestroy(ST* Bot);							//ջ�ṹ������
void StackPush(ST* Bot, StackEtype x);				//ѹջ��ֻ����ջ����������
void StackPop(ST* Bot);								//��ջ��ֻ�ܴ�ջ��ɾ������
bool StackEmpty(ST* Bot);							//�ж�ջ�Ƿ�Ϊ��
StackEtype StackTop(ST* Bot);						//ȡ��ջ��Ԫ��
int StackSize(ST* Bot);								//����ѹջԪ�ظ���
