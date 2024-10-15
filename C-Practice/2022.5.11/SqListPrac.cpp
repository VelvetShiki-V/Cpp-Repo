#define _CRT_SECURE_NO_WARNINGS 1
#include"SqListPrac.h"
void SLInit(SL* parr)
{
	assert(parr);
	parr->arr = NULL;
	parr->size = 0;
	parr->capacity = 0;
}

void SLCapCheck(SL* parr)
{
	assert(parr);
	if (parr->size == parr->capacity)
	{
		int Expand = parr->capacity == 0 ? 4 : parr->capacity *= 2;				//Expand为赋给capacity前的临时变量，因为可能考虑到扩容失败情况
		SLElemType* tmp = (SLElemType*)realloc(parr->arr, sizeof(SLElemType) * Expand);		//realloc首参数为需要原地/异地扩容的地址，realloc扩容以字节为单位
		if (tmp == NULL)
		{
			perror("扩容失败\n");
			exit(EOF);
		}
		parr->arr = tmp;
		parr->capacity = Expand;
	}
}

void SLPushBack(SL* parr, SLElemType x)
{
	assert(parr);
	SLCapCheck(parr);
	parr->arr[parr->size] = x;
	parr->size++;
}

void SLPopBack(SL* parr)
{
	assert(parr);
	if (parr->size > 0)			//确保size不为0，否则为空表
	{
		parr->size--;
	}
	else
	{
		printf("空表无法尾删\n");
	}
}

void SLPushFront(SL* parr, SLElemType x)
{
	assert(parr);
	SLCapCheck(parr);
	int pos = parr->size - 1;							//自减会修改实参size值，而-1不会
	while (pos >= 0)
	{
		parr->arr[pos + 1] = parr->arr[pos];
		pos--;
	}
	parr->arr[0] = x;
	parr->size++;
}

void SLPopFront(SL* parr)
{
	assert(parr);
	int pos = 0;
	if (parr->size > 0)
	{
		while (pos < parr->size)
		{
			parr->arr[pos] = parr->arr[pos + 1];
			pos++;
		}
		parr->size--;
	}
	else
	{
		printf("空表无法头删\n");
	}
}

void SLInsert(SL* parr, SLElemType x, int pos)
{
	assert(parr);
	assert(pos >= 0 && pos <= parr->size);
	SLCapCheck(parr);
	int end = parr->size - 1;
	while(pos <= end)
	{
		parr->arr[end + 1] = parr->arr[end];
		--end;
	}
	parr->arr[pos] = x;
	parr->size++;
}

int SLErase(SL* parr, SLElemType x)
{
	assert(parr);
	int pos = SLFind(parr, x);
	//while (parr->arr[pos] != x)
	//{
	//	pos++;
	//}
	if (pos == -1)
	{
		return pos;
	}
	else
	{
		while (pos < parr->size)
		{
			parr->arr[pos] = parr->arr[pos + 1];
			pos++;
		}
		printf("已擦除该值\n");
		parr->size--;
	}
	return 0;
}

int SLFind(SL* parr, SLElemType x)
{
	int pos = 0;
	assert(parr);
	while (parr->arr[pos] != x && pos < parr->size)
	{
		pos++;
	}
	if (pos == parr->size)
	{
		printf("顺序表中无对应值。\n");
		return -1;
	}
	printf("已找到该值在表中第一次出现的位置，下标为：%d\n", pos);
	return pos;
}

void SLDestroy(SL* parr)
{
	assert(parr);
	free(parr->arr);
	parr->arr = NULL;
}

void Print(SL* parr)
{
	assert(parr);
	int pos = 0, i = 0;
	while (pos < parr->size)
	{
		printf("%d ", parr->arr[i]);
		i++;
		pos++;
	}
}