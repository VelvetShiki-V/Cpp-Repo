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
	return obj->arr[(obj->Tail + obj->k) % (obj->k + 1)];			//用尾下标+容量k的结果，再模上容量k+1，就能得到尾下标前一个下标
}																	//此处不能用(obj->Tail - 1) % (obj->k + 1)，因为在C/C++中求模运算若对象是负数，则
																	//其求模仍为负数（如Tail == 0,(0 - 1) % 4 == -1，而不是3）
void Free(CRQ* obj)
{
	assert(obj);
	free(obj->arr);
	free(obj);
}