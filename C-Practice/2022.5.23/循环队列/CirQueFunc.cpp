#define _CRT_SECURE_NO_WARNINGS 1
#include"CiurcQueue.h"

CRQ* Create(int capacity)
{
	CRQ* Newarr = (CRQ*)malloc(sizeof(CRQ));
	Newarr->arr = (CRQueue*)malloc(sizeof(CRQueue) * (capacity + 1));
	assert(Newarr);
	Newarr->Head = Newarr->Tail = 0;
	Newarr->k = capacity;
	return Newarr;
}

bool Empty(CRQ* obj)
{
	assert(obj);
	return obj->Head == obj->Tail;
}

bool Full(CRQ* obj)
{
	assert(obj);
	return ((obj->Tail + 1) % (obj->k + 1)) == obj->Head;
}

bool enQueue(CRQ* obj, CRQueue value)
{
	assert(obj);
	if (!Full(obj))
	{
		obj->arr[obj->Tail] = value;
		obj->Tail = (obj->Tail + 1) % (obj->k + 1);
		return true;
	}
	return false;
}

bool deQueue(CRQ* obj)
{
	assert(obj);
	if (!Empty(obj))
	{
		obj->Head = (obj->Head + 1) % (obj->k + 1);
		return true;
	}
	return false;
}	


CRQueue GetFront(CRQ* obj)
{
	assert(obj);
	if (Empty(obj))
	{
		return -1;
	}
	return obj->arr[obj->Head];
}

CRQueue GetRear(CRQ* obj)
{
	assert(obj);
	if (Empty(obj))
	{
		return -1;
	}
	return obj->arr[(obj->Tail + obj->k) % (obj->k + 1)];			//��β�±�+����k�Ľ������ģ������k+1�����ܵõ�β�±�ǰһ���±�
}																	//�˴�������(obj->Tail - 1) % (obj->k + 1)����Ϊ��C/C++����ģ�����������Ǹ�������
																	//����ģ��Ϊ��������Tail == 0,(0 - 1) % 4 == -1��������3��
void Free(CRQ* obj)
{
	assert(obj);
	free(obj->arr);
	free(obj);
}