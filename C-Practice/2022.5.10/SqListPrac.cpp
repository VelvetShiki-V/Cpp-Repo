#define _CRT_SECURE_NO_WARNINGS 1
#include"SqListPrac.h"
void SLInit(SL* parr)
{
	parr = NULL;
	parr->size = 0;
	parr->capacity = 0;
}

void SLCapCheck(SL* parr)
{
	assert(parr);
	if (parr->size == parr->capacity)
	{
		parr->capacity == 0 ? 4 : parr->capacity *= 2;
		SL* tmp = (SL*)realloc(parr->arr, sizeof(int) * parr->capacity);
		parr = tmp;
	}
}

void SLPushBack(SL* parr, int x)
{
	assert(parr);
	SLCapCheck(parr);
	parr->arr[parr->size] = x;
	parr->arr++;
}

void SLPopBack(SL* parr)
{
	assert(parr);
	parr->size--;
}

void SLPushFront(SL* parr, int x)
{
	int pos = --parr->size;
	assert(parr);
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
	int pos = 0;
	assert(parr);
	SLCapCheck(parr);
	while (pos < parr->size)
	{
		parr->arr[pos + 1] = parr->arr[pos];
		pos++;
	}
	parr->size--;
}

void SLInsert(SL* parr, int x, int pos)
{
	assert(parr);
	assert(pos >= 0 && pos <= parr->size);
	SLCapCheck(parr);
	int end = --parr->size;
	while(pos <= end)
	{
		parr[end + 1] = parr[end];
		--end;
	}
	parr->arr[pos] = x;
	parr->size++;

}

void SLErase(SL* parr, int x)
{
	int pos = 0;
	assert(parr);
	while (parr->arr[pos] != x)
	{
		pos++;
	}
	while (pos < parr->size)
	{
		parr->arr[pos] = parr->arr[pos + 1];
		pos++;
	}
	parr->size--;
}

int SLFind(SL* parr, int x)
{
	int pos = 0;
	assert(parr);
	while (parr->arr[pos] != x && pos < parr->size)
	{
		pos++;
	}
	if (pos == parr->size)
	{
		printf("Can't find such number.\n");
		return -1;
	}
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
	}
}