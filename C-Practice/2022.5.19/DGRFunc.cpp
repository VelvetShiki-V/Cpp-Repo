#define _CRT_SECURE_NO_WARNINGS 1
#include"DGR.h"

DGR* DGRInit()												//双向带头循环链表初始化
{
	DGR* GuardNode = (DGR*)malloc(sizeof(DGR));
	assert(GuardNode);
	GuardNode->next = GuardNode;
	GuardNode->prev = GuardNode;
	return GuardNode;
}

DGR* BuyListNode(EType x)
{
	DGR* NewNode = (DGR*)malloc(sizeof(DGR));
	assert(NewNode);
	NewNode->next = NULL;
	NewNode->prev = NULL;
	NewNode->data = x;
	return NewNode;
}

void Print(DGR* Head)										//打印链表函数
{
	assert(Head);
	DGR* Begin = Head->next;
	printf("Head->");
	while (Begin != Head)
	{
		printf("%d->", Begin->data);
		Begin = Begin->next;
	}
	printf("Head\n");
}


void PushBack(DGR* Head, EType x)							//尾插
{
	assert(Head);
	DGR* NewNode = (DGR*)malloc(sizeof(DGR));
	DGR* Tail = Head->prev;
	Tail->next = NewNode;
	NewNode->next = Head;
	NewNode->prev = Tail;
	NewNode->data = x;
	Head->prev = NewNode;
}

void PushFront(DGR* Head, EType x)							//头插
{
	assert(Head);
	DGR* Push = BuyListNode(x);
	Push->prev = Head;
	Push->next = Head->next;
	Head->next = Push;
	Push->next->prev = Push;
}

void PopBack(DGR* Head)										//尾删
{
	assert(Head);
	assert(Head->next != Head);								//防止尾删把初始化的哨兵头结点自己删除
	Head->prev = Head->prev->prev;
	free(Head->prev->next);
	Head->prev->next = Head;
}

void PopFront(DGR* Head)									//头删
{
	assert(Head);
	assert(Head->next != Head);								//防止头删把初始化的哨兵头结点自己删除
	Head->next = Head->next->next;
	free(Head->next->prev);
	Head->next->prev = Head;
}

void DGRInsert(DGR* pos, EType x)							//在pos位置之前插入结点
{
	assert(pos);
	DGR* InsertNode = BuyListNode(x);						
	pos->prev->next = InsertNode;							//若pos在头结点后一个，则是头插；若pos在头结点，则是尾插
	InsertNode->prev = pos->prev;
	InsertNode->next = pos;
	pos->prev = InsertNode;
}
void DGRErase(DGR* pos)										//删除pos所在地址的结点
{
	assert(pos);
	assert(pos->next != pos);
	pos->prev->next = pos->next;
	pos->next->prev = pos->prev;
	free(pos);
}
