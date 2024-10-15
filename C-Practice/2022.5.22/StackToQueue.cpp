#define _CRT_SECURE_NO_WARNINGS 1
#include"Stack_Queue.h"

//栈函数
void StackInit(ST* Stack)
{
	Stack->arr = NULL;
	Stack->capacity = Stack->top = 0;
}

bool STEmpty(ST* Stack)
{
	assert(Stack);
	return Stack->top == 0;
}

STEtype GetSTop(ST* Stack)
{
	assert(Stack);
	if (!STEmpty(Stack))
	{
		return Stack->arr[Stack->top - 1];
	}
	return NULL;
}

void STDestroy(ST* Stack)
{
	assert(Stack);
	while (!STEmpty(Stack))
	{
		PopTop(Stack);
	}
	free(Stack->arr);
	Stack->capacity = Stack->top = 0;
}


void PushTop(ST* Stack, STEtype x)
{
	assert(Stack);
	if (Stack->capacity == Stack->top)
	{
		int expand = Stack->capacity == 0 ? 4 : Stack->capacity * 2;
		STEtype* tmp = (STEtype*)realloc(Stack->arr, sizeof(STEtype)* expand);
		assert(tmp);
		Stack->arr = tmp;
		Stack->capacity = expand;
	}
	Stack->arr[Stack->top] = x;
	Stack->top++;
}

void PopTop(ST* Stack)
{
	assert(Stack);
	if (!STEmpty(Stack))
	{
		Stack->arr[--Stack->top];
	}
}

void Push(MQ* obj, STEtype x)
{
	assert(obj);
	PushTop(obj->Push, x);
}

int Pop(MQ* obj)
{
	assert(obj);
	if (STEmpty(obj->Pop))
	{
		while (!STEmpty(obj->Push))
		{
			PushTop(obj->Pop, GetSTop(obj->Push));
			PopTop(obj->Push);
		}
	}
	STEtype tmp = GetSTop(obj->Pop);
	PopTop(obj->Pop);
	return tmp;
}

int Peek(MQ* obj)								//取队头元素
{
	assert(obj);
	if (STEmpty(obj->Pop))
	{
		while (!STEmpty(obj->Push))
		{
			PushTop(obj->Pop, GetSTop(obj->Push));
			PopTop(obj->Push);
		}
	}
	return  GetSTop(obj->Pop);
}

bool Empty(MQ* obj)							//判断队列是否为空
{
	assert(obj);
	return STEmpty(obj->Push) && STEmpty(obj->Pop);
}

void Free(MQ* obj)								//销毁队列
{
	assert(obj);
	while (!STEmpty(obj->Push))
	{
		STDestroy(obj->Push);
	}
	while (!STEmpty(obj->Pop))
	{
		STDestroy(obj->Pop);
	}
	free(obj);
}

MQ* StructInit()									//初始化栈指针
{
	MQ* tmp = (MQ*)malloc(sizeof(MQ));
	tmp->Push = (ST*)malloc(sizeof(ST));
	tmp->Pop = (ST*)malloc(sizeof(ST));
	StackInit(tmp->Push);
	StackInit(tmp->Pop);
	return tmp;
}

void PrintQueue(MQ* obj)
{
	assert(obj);
	printf("Head->");
	while (!STEmpty(obj->Pop))
	{
		printf("%d->", Pop(obj));
	}
	if(!STEmpty(obj->Push))
	{
		Peek(obj);
		while (!STEmpty(obj->Pop))
		{
			printf("%d->", Pop(obj));
		}
	}
	printf("Tail\n");
}
