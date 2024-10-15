#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include"FuncDeclare.h"

void Delete(SL* ps)
{
	PopBack(ps);
}

void print(SL ps)
{
	int i = 0;
	for (i = 0; i < ps.size; i++)
	{
		printf("%d ", ps.arr[i]);
	}
	printf("\n");
}

void Push1(SL ps1)
{
	PushBack(&ps1, 1);						//若顺序表仅初始化，而尾插函数中没有开辟capacity，则越界
	PushBack(&ps1, 3);
	PushBack(&ps1, 2);
	PushBack(&ps1, 4);
	PushBack(&ps1, 7);
	PushBack(&ps1, 6);
	//尾删操作
	Delete(&ps1);
	Delete(&ps1);
	//Delete(&ps1);							//测试尾删使size访问越界效果
	//Delete(&ps1);
	//Delete(&ps1);
	//Delete(&ps1);
	//Delete(&ps1);
	//Delete(&ps1);
	//Delete(&ps1);
	PushBack(&ps1, 1);
	PushBack(&ps1, 1);
	PushBack(&ps1, 1);
	print(ps1);
	//动态开辟的顺序表释放销毁
	SLDestroy(&ps1);
}

void Push2(SL ps2)
{
	PushFront(&ps2, 5);
	PushFront(&ps2, 4);
	PushFront(&ps2, 3);
	PushFront(&ps2, 2);
	PushFront(&ps2, 1);
	PushFront(&ps2, 0);
	//尾删操作
	Delete(&ps2);
	print(ps2);
	SLDestroy(&ps2);
}

void DeleteFront(SL ps3)
{
	PushBack(&ps3, 8);
	PushBack(&ps3, 9);
	PushBack(&ps3, 10);
	PushFront(&ps3, 6);
	PushFront(&ps3, 5);
	PushFront(&ps3, 4);
	PopFront(&ps3);
	PopFront(&ps3);
	PopFront(&ps3);
	PopFront(&ps3);
	PopFront(&ps3);
	PopFront(&ps3);
	//PopFront(&ps3);
	PushFront(&ps3, 1);
	print(ps3);
	SLDestroy(&ps3);
}

int main()
{
	//结构体变量定义和初始化
	SL s1, s2, s3;							
	//SLInit(s1);							//传值写法，不会改变在Main里定义传来的实参数组值
	SLInit(&s1);							//传址写法，可以通过初始化函数解引用改变实参s1的数组容量，size和capacity值
	SLInit(&s2);
	SLInit(&s3);

	//尾插操作
	Push1(s1);

	//头插操作
	Push2(s2);

	//头删操作
	DeleteFront(s3);

	return 0;
}