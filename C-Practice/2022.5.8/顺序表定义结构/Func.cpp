#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include"FuncDeclare.h"

//顺序表的结构体变量初始化
void SLInit(SL* ps)
{
	//s.arr = NULL;						//形参传值写法，不会改变在Main里定义传来的实参数组值
	//s.size = s.capacity = 0;
	assert(ps);							//预防式编程，防止传入空\野指针但不报错问题
	ps->arr = NULL;						//将数组地址置空
	ps->size = ps->capacity = 0;		//有效数值个数和容量置0
}

//检查顺序表结构内数组是否为空或溢出，并动态扩容
void SLCapacityCheck(SL* ps)
{
	assert(ps != NULL);
	if (ps->capacity == ps->size)														//如果数组中有效数值个数等于容量，则顺序表满
	{
		int Expand = ps->capacity == 0 ? 4 : ps->capacity * 2;							//判断容量清空，为空则新开辟空间，不为空则使原容量扩充1倍
		SLElemType* tmp = (SLElemType*)realloc(ps->arr, Expand * sizeof(SLElemType));	//使用realloc或malloc函数动态开辟
		if (tmp == NULL)																//防止开辟失败
		{
			printf("%s\n", strerror(errno));
			exit(-1);
		}
		else
		{
			ps->arr = tmp;																//将新开辟的内存地址传给原数组（原地扩容或异地扩容）
			ps->capacity = Expand;														//并使顺序表容量增大
		}
	}
}

//尾插函数
void PushBack(SL* ps, SLElemType x)
{
	assert(ps);
	SLCapacityCheck(ps);			//检查顺序表容量是否溢出或为空，并动态开辟容量
	ps->arr[ps->size] = x;		//将尾插值插入size值对应的数组下标
	++ps->size;					//并使size + 1，表示新插入了一个值
}

//头插函数
void PushFront(SL* ps, SLElemType x)
{
	assert(ps != NULL);
	SLCapacityCheck(ps);
	int end = ps->size - 1;
	while (end >= 0)
	{
		ps->arr[end + 1] = ps->arr[end];
		--end;
	}
	ps->arr[0] = x;
	++ps->size;
}

//尾删函数
void PopBack(SL* ps)
{
	//if (ps->size != 0)			//也可以使用assert(ps->size > 0);暴力检查，或printf打印提示
	//{
	//	--ps->size;
	//}
	//else
	//{
	//	printf("The Sequence List is already empty.\n");
	//}
	assert(ps);
	assert(ps->size > 0);			//size只有大于0才能进行删除操作，否则size可能会变为负数
	ps->size--;
}

//头删函数
void PopFront(SL* ps)
{
	assert(ps != NULL);
	assert(ps->size > 0);			//size只有大于0才能进行删除操作，否则size可能会变为负数
	int begin = 1;
	while (begin < ps->size)
	{
		ps->arr[begin - 1] = ps->arr[begin];
		begin++;
	}
	ps->size--;
}

//释放内存
void SLDestroy(SL* ps)
{
	assert(ps);
	free(ps->arr);					//只有free才会检查数组是否越界，而越界时的开辟realloc或size访问不会报错
	ps->arr = NULL;
	ps->size = ps->capacity = 0;
}

//中间插入函数(不能尾插，可以头插)
void SLInsert(SL* ps, int pos, SLElemType x)
{
	assert(ps);
	assert(pos >= 0 && pos <= ps->size);
	SLCapacityCheck(ps);
	int end = ps->size - 1;
	while (end >= pos)
	{
		ps->arr[end + 1] = ps->arr[end];
		--end;
	}
	ps->arr[pos] = x;
	ps->size++;
}

void SLErase(SL* ps, int pos)
{
	assert(ps);
	assert(pos >= 0 && pos < ps->size);
	int begin = pos;
	while (begin <= ps->size - 1)		//size-1是为了防止begin挪动越界访问，将越界的随机值赋值给size下标元素情况
	{
		ps->arr[begin] = ps->arr[begin + 1];
		++begin;
	}
	--ps->size;
}

int SLFind(SL* ps, SLElemType x)
{
	assert(ps);
	for (int i = 0; i < ps->size; i++)
	{
		if (x == ps->arr[i])
		{
			return i;
		}
	}
	return -1;						//找不到，返回下标-1，说明查找失败	
}

int SLModify(SL* ps, int pos, SLElemType x)
{
	assert(ps);
	assert(pos >= 0 && pos < ps->size);
	for (int i = 0; i < ps->size; i++)
	{
		if (pos == i)
		{
			ps->arr[i] = x;
			return i;
		}
	}
	return 0;
}