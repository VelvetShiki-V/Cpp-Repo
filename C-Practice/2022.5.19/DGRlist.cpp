#define _CRT_SECURE_NO_WARNINGS 1
#include"DGR.h"
//双向带头（哨兵）循环链表——最优链表

void DGRTest_1()
{
	DGR* GuardHead = DGRInit();						//初始化哨兵头结点
	PushBack(GuardHead, 1);							//头结点后尾插
	PushBack(GuardHead, 2);
	PushBack(GuardHead, 3);
	PushBack(GuardHead, 4);
	printf("尾插后原链表结构：");
	Print(GuardHead);

	printf("头插后链表结构：");
	PushFront(GuardHead, 0);						//头结点后头插
	PushFront(GuardHead, -1);
	PushFront(GuardHead, -2);
	PushFront(GuardHead, -3);
	Print(GuardHead);
}

void DGRTest_2()
{
	DGR* GuardHead = DGRInit();						//初始化哨兵头结点
	PushBack(GuardHead, 1);							//头结点后尾插
	PushBack(GuardHead, 2);
	PushBack(GuardHead, 3);
	PushBack(GuardHead, 4);
	PushFront(GuardHead, 1);						//头结点后头插
	PushFront(GuardHead, 2);						
	PushFront(GuardHead, 3);						
	PushFront(GuardHead, 4);						
	printf("尾插和头插后原链表结构：");
	Print(GuardHead);

	printf("3次尾删后链表结构：");
	PopBack(GuardHead);
	PopBack(GuardHead);
	PopBack(GuardHead);
	Print(GuardHead);
	printf("再4次头删后链表结构：");
	PopFront(GuardHead);
	PopFront(GuardHead);
	PopFront(GuardHead);
	PopFront(GuardHead);
	PopFront(GuardHead);							//留下哨兵位一个头结点
	//PopFront(GuardHead);							//再删一次，若没断言则把哨兵头结点删除，后续指针成为野指针
	Print(GuardHead);
}

void DGRTest_3()
{
	DGR* GuardHead = DGRInit();						//初始化哨兵头结点
	PushBack(GuardHead, 3);							//头结点后尾插
	PushBack(GuardHead, 4);
	PushFront(GuardHead, 2);						//头结点后头插
	PushFront(GuardHead, 1);
	printf("尾插和头插后原链表结构：");
	Print(GuardHead);

	//中间插入/头插/尾插
	printf("3后插30：");
	DGRInsert(GuardHead->prev, 30);
	Print(GuardHead);
	printf("2前插10：");
	DGRInsert(GuardHead->next->next, 10);
	Print(GuardHead);
	printf("头插50：");
	DGRInsert(GuardHead->next, 50);
	Print(GuardHead);
	printf("尾插90：");
	DGRInsert(GuardHead, 90);
	Print(GuardHead);

	//中间擦除/头删/尾删
	printf("1后擦10：");
	DGRErase(GuardHead->next->next->next);
	Print(GuardHead);
	printf("删头：");
	DGRErase(GuardHead->next);
	Print(GuardHead);
	printf("删尾：");
	DGRErase(GuardHead->prev);
	Print(GuardHead);
	printf("删到只留哨兵头结点：");
	DGRErase(GuardHead->next);
	DGRErase(GuardHead->next);
	DGRErase(GuardHead->next);
	DGRErase(GuardHead->next);
	DGRErase(GuardHead->next);
	Print(GuardHead);
	//printf("再删：");
	//DGRErase(GuardHead->next);
	//Print(GuardHead);
}


int main()
{
	//DGRTest_1();
	//DGRTest_2();
	DGRTest_3();
	return 0;
}