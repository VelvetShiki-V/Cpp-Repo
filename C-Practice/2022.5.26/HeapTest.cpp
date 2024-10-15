#define _CRT_SECURE_NO_WARNINGS 1
#include"HeapFunc.h"

//堆通用函数
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
	printf("堆为空\n");
	return -1;
}

void Swap(HPEtype* a, HPEtype* b)
{
	assert(a && b);
	*a ^= *b;
	*b ^= *a;
	*a ^= *b;
}

int HPSize(HP* hp)								//堆的元素个数
{
	assert(hp);
	if (!HPEmpty(hp))
	{
		return hp->size;
	}
	printf("堆为空\n");
	return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
//小堆插入
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

//小堆删除
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

//小堆插入的向上元素调整
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

//小堆删除的向下元素调整
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

//小堆遍历清空打印——升序输出
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
//大堆插入
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
	//建堆，两种方式，上调和下调
	BigMoveUpward(hp, (hp->size - 2) / 2);			//上调——插入一般用上调函数，因为只需一次就可以了
	//int end = (hp->size - 2) / 2;					//下调——但是下调有前提，左右子树必须是堆，所以要从末结点的双亲结点开始调
	//while (end >= 0)
	//{
	//	BigMoveDownward(hp, end);
	//	end--;
	//}
}

//大堆删除
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

//大堆插入的向上元素调整
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

//大堆向下元素调整
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

//大堆遍历清空打印——升序输出
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
//升序函数
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
