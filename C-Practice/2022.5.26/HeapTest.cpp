#define _CRT_SECURE_NO_WARNINGS 1
#include"HeapFunc.h"

//��ͨ�ú���
void HPInit(HP* hp)
{
	assert(hp);
	hp->arr = NULL;
	hp->capacity = hp->size = 0;
}

void HPDestroy(HP* hp)
{
	assert(hp);
	free(hp->arr);
	hp->arr = NULL;
	hp->capacity = hp->size = 0;
}

bool HPEmpty(HP* hp)
{
	assert(hp);
	return hp->size == 0;
}

HPEtype HPTop(HP* hp)
{
	assert(hp);
	if (!HPEmpty(hp))
	{
		return hp->arr[0];
	}
	printf("��Ϊ��\n");
	return -1;
}

void Swap(HPEtype* a, HPEtype* b)
{
	assert(a && b);
	*a ^= *b;
	*b ^= *a;
	*a ^= *b;
}

int HPSize(HP* hp)								//�ѵ�Ԫ�ظ���
{
	assert(hp);
	if (!HPEmpty(hp))
	{
		return hp->size;
	}
	printf("��Ϊ��\n");
	return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
//С�Ѳ���
void SmHPPush(HP* hp, HPEtype x)
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
	hp->size++;
	if (hp->arr[hp->size - 1] < hp->arr[(hp->size - 2) / 2])
	{
		SmMoveUpward(hp, (hp->size - 2) / 2);
	}
}

//С��ɾ��
void SmHPPop(HP* hp)
{
	assert(hp);
	if (!HPEmpty(hp))
	{
		Swap(&hp->arr[0], &hp->arr[hp->size - 1]);
		hp->size--;
		if (hp->arr[0] > hp->arr[1] || hp->arr[0] > hp->arr[2])
		{
			SmMoveDownward(hp, 0);
		}
	}
}

//С�Ѳ��������Ԫ�ص���
void SmMoveUpward(HP* hp, int parent)
{
	assert(hp);
	int child = hp->size - 1;
	while (child > 0)
	{
		if (hp->arr[child] < hp->arr[parent])
		{
			Swap(&hp->arr[child], &hp->arr[parent]);
			child = parent;
			parent = (child - 1) / 2;
		}
		else
		{
			break;
		}
	}
}

//С��ɾ��������Ԫ�ص���
void SmMoveDownward(HP* hp, int parent)
{
	assert(hp);
	int child = parent * 2 + 1;
	while (child < hp->size)
	{
		if (child + 1 < hp->size && hp->arr[child] > hp->arr[child + 1])
		{
			child += 1;
		}
		if (hp->arr[parent] > hp->arr[child])
		{
			Swap(&hp->arr[parent], &hp->arr[child]);
			parent = child;
			child = parent * 2 + 1;
		}
		else
		{
			break;
		}
	}
}

//С�ѱ�����մ�ӡ�����������
void SmPrint(HP* hp)
{
	assert(hp);
	while (!HPEmpty(hp))
	{
		printf("%d ", HPTop(hp));
		SmHPPop(hp);
	}
	printf("\n");
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//��Ѳ���
void BigHPPush(HP* hp, HPEtype x)
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
	hp->size++;
	//���ѣ����ַ�ʽ���ϵ����µ�
	BigMoveUpward(hp, (hp->size - 2) / 2);			//�ϵ���������һ�����ϵ���������Ϊֻ��һ�ξͿ�����
	//int end = (hp->size - 2) / 2;					//�µ����������µ���ǰ�ᣬ�������������Ƕѣ�����Ҫ��ĩ����˫�׽�㿪ʼ��
	//while (end >= 0)
	//{
	//	BigMoveDownward(hp, end);
	//	end--;
	//}
}

//���ɾ��
void BigHPPop(HP* hp)
{
	assert(hp);
	if (!HPEmpty(hp))
	{
		Swap(&hp->arr[0], &hp->arr[hp->size - 1]);
		hp->size--;
		if (hp->arr[0] < hp->arr[1] || hp->arr[0] < hp->arr[2])
		{
			BigMoveDownward(hp, 0);
		}
	}
}

//��Ѳ��������Ԫ�ص���
void BigMoveUpward(HP* hp, int parent)
{
	assert(hp);
	int child = hp->size - 1;
	while (child > 0)
	{
		if (hp->arr[child] > hp->arr[parent])
		{
			Swap(&hp->arr[child], &hp->arr[parent]);
			child = parent;
			parent = (child - 1) / 2;
		}
		else
		{
			break;
		}
	}
}

//�������Ԫ�ص���
void BigMoveDownward(HP* hp, int parent)
{
	assert(hp);
	int child = parent * 2 + 1;
	while (child < hp->size)
	{
		if (child + 1 < hp->size && hp->arr[child] < hp->arr[child + 1])
		{
			child++;
		}
		if (hp->arr[parent] < hp->arr[child])
		{
			Swap(&hp->arr[parent], &hp->arr[child]);
			parent = child;
			child = parent * 2 + 1;
		}
		else
		{
			break;
		}
	}
}

//��ѱ�����մ�ӡ�����������
void BigPrint(HP* hp)
{
	assert(hp);
	while (!HPEmpty(hp))
	{
		printf("%d ", HPTop(hp));
		BigHPPop(hp);
	}
	printf("\n");
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
//������
void HPSortAscend(HP* hp)
{
	assert(hp);
	if (!HPEmpty(hp))
	{
		int end = hp->size - 1;
		while (end > 0)
		{
			Swap(&hp->arr[0], &hp->arr[end]);
			BigMoveDownward(hp, 0);
			end--;
		}
	}
}
