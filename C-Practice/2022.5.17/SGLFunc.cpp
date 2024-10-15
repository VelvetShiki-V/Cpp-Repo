#define _CRT_SECURE_NO_WARNINGS 1
#include"SGL.h"
SgL* BuyListNode(Etype x)
{
	SgL* Newnode = (SgL*)malloc(sizeof(SgL));
	assert(Newnode);
	Newnode->data = x;
	Newnode->next = NULL;
	return Newnode;
}

void Print(SgL* Head)
{
	SgL* Cur = Head;
	while (Cur)
	{
		printf("%d->", Cur->data);
		Cur = Cur->next;
	}
	printf("NULL\n");
}

SgL* PBackDelete(SgL* Head, Etype x)
{
	assert(Head);
	SgL* NewHead = NULL;
	SgL* move = Head;
	SgL* insert = NULL;
	int count = 1;
	while (move)
	{
		if (move->data != x && count == 1)					//第一个非val结点作为新链表首节点
		{
			NewHead = move;
			insert = NewHead;
			count--;
		}
		else if (move->data != x)							//后续非val结点作为新首节点后续的插入结点
		{
			insert->next = move;
			insert = insert->next;
		}
		move = move->next;									//若进入循环，默认移动move结点指针
	}
	if (NewHead == NULL)									//若没有任何非val结点，则返回空链表
	{
		return NULL;
	}
	insert->next = NULL;									//若存在新链表，将insert的后续结点置空
	return NewHead;
}

SgL* PushFront(SgL* Head, Etype x)							//头插函数
{
	assert(Head);
	SgL* NewHead = BuyListNode(x);
	NewHead->next = Head;
	return NewHead;
}

SgL* ReverseSL(SgL* Head)									//逆置链表算法
{
	SgL* move = Head;										//定义一个结点指针遍历原链表
	move = move->next;										//初始时默认移动到原链表第二个结点处，等待头插
	SgL* insert = Head;										//定义一个新链表结点指针，用于头插指向
	while (move)
	{
		insert = PushFront(insert, move->data);				//将move指向结点头插入insert结点
		move = move->next;
	}
	Head->next = NULL;										//将原来的头结点后续指针置空
	return insert;
}


SgL* ReverseSL2(SgL* Head)									//逆置链表算法2
{	
	assert(Head);											//防空链表
	SgL* pre = Head;
	SgL* cur = Head->next;
	if (Head->next == NULL)									//判断是否为单结点链表
	{
		return Head;
	}
	if (Head->next->next == NULL)							//判断是否为双结点链表
	{
		cur->next = pre;
		pre->next = NULL;
		return cur;
	}
	else
	{	
		SgL* Next = Head->next->next;						//三个指针pre, cur, Next分别存储前中后结点，并改变指向循环到Next == NULL
		int count = 1;
		while(Next)
		{
			cur->next = pre;
			if (count == 1)
			{
				pre->next = NULL;							//将新尾结点后继置空
				count--;
			}
			pre = cur;
			cur = Next;
			Next = Next->next;
		}
	}
	cur->next = pre;
	return cur;
}


Etype FindMid(SgL* Head)									//查找中间结点算法
{
	assert(Head);
	SgL* Fast = Head;										//定义快指针，一次走两个结点
	SgL* Slow = Head;										//定义慢指针，一次走一个结点
	if (Head->next == NULL)									//判断链表是否为一个结点结构
	{
		return Head->data;
	}
	if (Head->next->next == NULL)							//判断链表是否为两个结点结构
	{
		return Head->next->data;
	}
	while (Fast->next != NULL && Fast->next->next != NULL)	//当快指针的下个结点为空或下下个结点为空时停止循环
	{
		Fast = Fast->next->next;
		Slow = Slow->next;
	}
	if (Fast->next == NULL)									//快指针下个结点为空时返回慢指针指向的结点数值
	{
		return Slow->data;
	}
	else if (Fast->next->next == NULL)						//快指针下下个结点为空时返回慢指针的后继指针指向的结点数值
	{
		return Slow->next->data;
	}
}

Etype LastKVal(SgL* Head, int k)							//查找倒数第k个
{
	SgL* 
}