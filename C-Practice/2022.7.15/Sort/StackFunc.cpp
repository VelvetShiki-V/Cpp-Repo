#include"StackFunc.h"

ST* StackInit()
{
	ST* NewStack = (ST*)malloc(sizeof(ST));
	assert(NewStack);
	NewStack->arr = NULL;
	NewStack->capacity = NewStack->top = 0;
	return NewStack;
}

void StackPush(ST* Bot, STEtype x)
{
	assert(Bot);
	if (Bot->top == Bot->capacity)
	{
		int expand = Bot->capacity == 0 ? 4 : Bot->capacity * 2;
		STEtype* NewSpace  = (STEtype*)realloc(Bot->arr, expand * sizeof(STEtype));
		assert(NewSpace);
		Bot->capacity = expand;
		Bot->arr = NewSpace;
	}
	Bot->arr[Bot->top] = x;
	Bot->top++;
}

bool StackEmpty(ST* Bot)
{
	assert(Bot);
	return Bot->top == 0;
}

void StackPop(ST* Bot)
{
	assert(Bot);
	if (StackEmpty(Bot))
	{
		printf("栈为空\n");
		return;
	}
	else
	{
		Bot->top--;
	}
}

STEtype StackTop(ST* Bot)
{
	assert(Bot);
	if (StackEmpty(Bot))
	{
		printf("\n栈为空\n");
		return -1;
	}
	else
	{
		return Bot->arr[Bot->top - 1];
	}
}

ST* StackDestroy(ST* Bot)
{
	assert(Bot);
	free(Bot->arr);
	Bot->arr = NULL;
	Bot->capacity = Bot->top = 0;
	free(Bot);
	Bot = NULL;
	return Bot;
}

void PrintPop(ST* Bot)
{
	assert(Bot);
	printf("Top-> ");
	while (!StackEmpty(Bot))
	{
		printf("%d ", StackTop(Bot));
		StackPop(Bot);
	}
	printf("<-Bot");
}

int StackSize(ST* Bot)									//计算压栈元素个数
{
	assert(Bot);
	return Bot->top;
}