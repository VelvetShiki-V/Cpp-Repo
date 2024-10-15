#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
//ջ����
typedef int STEtype;
typedef struct Stack
{
	STEtype* arr;							//ջͨ��˳���ʵ�֣�������������飬�����Ͷ���
	int top;
	int capacity;
}ST;

//ָ������ջָ���ָ��
typedef struct MyQueue						
{
	ST* Push;								//Pushջ��������ѹ�����ʱ���
	ST* Pop;								//����Ҫ����ʱ����Pushջ������ȡͷ����Popջ�������ȡͷ����
}MQ;

//ջ����
void StackInit(ST* Stack);					//������ָ���ÿպ�����size��0
void PushTop(ST* Stack, STEtype x);			//ѹջ
void PopTop(ST* Stack);						//��ջ
bool STEmpty(ST* Stack);					//�п�
STEtype GetSTop(ST* Stack);					//ȡջ��Ԫ��
void STDestroy(ST* Stack);					//ջ����

//ջʵ�ֶ��к���
MQ* StructInit();							//��ʼ��ջָ��
void Push(MQ* obj, STEtype x);				//����ջԪ���Ƶ���β��û��ʵ������
int Pop(MQ* obj);							//������ͷ�����ض�ͷԪ�أ�ʵ�ַ�ʽΪPopջ��ջͷ����������
int Peek(MQ* obj);							//ȡ��ͷԪ�أ�ʵ�ַ�ʽΪPopջͷԪ��
bool Empty(MQ* obj);						//�ж϶����Ƿ�Ϊ��
void Free(MQ* obj);							//���ٶ���
void PrintQueue(MQ* obj);


//���ж���
typedef int QEtype;
typedef struct Queue						//���е�ʵ��ʹ������
{
	QEtype data;							//��ֵ��
	Queue* next;							//���ָ����
}QNode;

//��ͷ��βָ��
typedef struct QuePtr
{
	QNode* Head;							//��ͷָ��
	QNode* Tail;							//��βָ��
}QP;

//ָ����������ָ���ָ��
typedef struct MyStack						
{
	QP* Q1;									//ָ���һ������
	QP* Q2;									//ָ��ڶ�������
}MST;

//���к���
void QueueInit(QP* Qptr);					//��ͷ���βָ���ʼ�����ÿգ�				
void QueueDestroy(QP* Qptr);				//���е�����				
void QPushBack(QP* Qptr, QEtype x);			//����β��
void QPopFront(QP* Qptr);					//����ͷɾ
bool QueueEmpty(QP* Qptr);					//�п�
QEtype GetQHead(QP* Qptr);					//ȡ��ͷԪ�ز�����
int QueueSize(QP* Qptr);					//��������н�����������

//����ʵ��ջ����
MST* StackCreate();							//��ʼ��ָ�����ָ����������еĿռ俪��
void PushQ(MST* obj, QEtype x);				//ѹջ��ʵ�ַ�ʽΪ����������ǿն���
QEtype StackPop(MST* obj);					//��ջ��ʵ�ַ�ʽΪ���ǿն������ݷǶ�β���ݵ���ն��У�ʣ�µĶ�β����ջ���ͷŲ�����
QEtype StackTop(MST* obj);					//ʵ�ַ�ʽ���ջһ�£����طǿն���β���ֵ���ٽ��ý��β�嵽�ǿն��У������ڶ�����Ϊ�ն���
bool EmptyQ(MST* obj);						//�п�ջ�����������Ƿ�Ϊ�գ�
void FreeQ(MST* obj);						//�ͷ�ջ���������е��ڴ��ͷţ�
void PrintQ(MST* obj);						//������ӡջ��ʵ�ַ�ʽΪ���ϳ�ջ�ͷ���ջ��Ԫ�أ���˱�����Ϻ�Ϊ��ջ�������ն��У�
