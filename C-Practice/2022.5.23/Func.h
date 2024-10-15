#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<string.h>

//������ṹ����
typedef int SEtype;
typedef struct SingleList
{
	SEtype data;
	SingleList* next;
}SGL;
SGL* BuyListNode(SEtype x);			//���ٽ��

//�����ָ������ṹ����
typedef struct Random
{
	SEtype data;
	Random* next;
	Random* random;					//���ԭ������ṹ����һ��ָ���������ָ����
}RD;
RD* BuyRandom(SEtype x);			//�������ָ����

//ջ�ṹ����
typedef char SType;
typedef struct Stack
{
	SType* a;
	int top;
	int capacity;
}ST;

//��������
bool Detect(SGL* Head);				//�ж������Ƿ��л�
SEtype Enter(SGL* n1);				//�����뻷��ֵ��������۲죩

//���
RD* Copy(RD* Head);					//��ԭ�����������������׽���ַ��ʵ��

//����ƥ��
bool BracketMatch(char* arr, int sz);