#define _CRT_SECURE_NO_WARNINGS 1
#include"heap.h"

void HeapInit(HP* hp)							//�ѳ�ʼ��
{
	assert(hp);
	hp->arr = NULL;
	hp->capacity = hp->size = 0;
}

void HeapDestroy(HP* hp)						//������
{
	assert(hp);
	free(hp->arr);
	hp->arr = NULL;
	hp->capacity = hp->size = 0;
}

void Swap(HPEtype* a, HPEtype* b)
{
	*a ^= *b;
	*b ^= *a;
	*a ^= *b;
}

void AdjustUp(HP* hp, int child)
{
	assert(hp);
	int parent = (child - 1) / 2;
	if (hp->arr[child] < hp->arr[parent])
	{
		while (child > 0)
		{
			Swap(&hp->arr[child], &hp->arr[parent]);
			child = parent;
			parent = (child - 1) / 2;
		}
	}
}

void HPPush(HP* hp, HPEtype x)					//�ѵ����ݲ���
{
	assert(hp);
	if (hp->capacity == hp->size)
	{
		int expand = hp->capacity == 0 ? 4 : hp->capacity * 2;
		HPEtype* NewCap = (HPEtype*)realloc(hp->arr, sizeof(HPEtype) * expand);
		assert(NewCap);
		hp->arr = NewCap;
		hp->capacity = expand;
	}
	hp->arr[hp->size] = x;
	HPEtype child = hp->arr[hp->size];
	AdjustUp(hp, hp->size);
	hp->size++;
}

//void HPPop(HP* hp)								//�ѵ�����ɾ��
//{
//	;
//}


