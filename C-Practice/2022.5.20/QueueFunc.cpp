#define _CRT_SECURE_NO_WARNINGS 1
#include"Queue.h"

void Print(QP* Qptr)
{
	assert(Qptr);
	if (QueueEmpty(Qptr))
	{
		printf("队列为空\n");
	}
	else
	{
		QNode* cur = Qptr->Head;
		printf("Head->");
		while (cur)
		{
			printf("%d->", cur->data);
			cur = cur->next;
		}
		printf("Null\n");
	}
}

void QueueInit(QP* Qptr)								//队列指针初始化
{
	assert(Qptr);
	Qptr->Head = Qptr->Tail = NULL;
}

void QPushBack(QP* Qptr, QueEType x)					//队列尾插
{
	assert(Qptr);
	QNode* NewNode = (QNode*)malloc(sizeof(QNode));		//新建带尾插的结点
	assert(NewNode);
	NewNode->next = NULL;
	NewNode->data = x;
	if (Qptr->Head == Qptr->Tail && Qptr->Head == NULL)	//若当前队列链表为空，则将该新节点被头指针和尾指针所指向
	{
		Qptr->Head = Qptr->Tail = NewNode;
	}
	else												//否则仅挪动尾指针指向该结点进行标记
	{
		Qptr->Tail->next = NewNode;
		Qptr->Tail = NewNode;
	}
}

void QPopFront(QP* Qptr)								//队列头删
{
	assert(Qptr);										//防空指针
	assert(!QueueEmpty(Qptr));								//防空链表
	QNode* Next = Qptr->Head->next;						//备份头结点的后继结点地址
	if (Next == NULL)									//若头结点后继地址为空，则释放当前头和尾所在结点并全部置空
	{
		free(Qptr->Head);
		Qptr->Head = Qptr->Tail = NULL;
	}
	else												//否则将头指针所在结点释放并向后移动一个结点
	{
		free(Qptr->Head);
		Qptr->Head = Next;
	}
}

bool QueueEmpty(QP* Qptr)									//队列判空
{
	assert(Qptr);
	return Qptr->Head == Qptr->Tail && Qptr->Head == NULL;
}

void QueueDestroy(QP* Qptr)									//队列消除
{
	assert(Qptr);
	while (!QueueEmpty(Qptr))								//如果队列内仍有结点元素，循环头删直至队列链表为空
	{
		QPopFront(Qptr);
	}
}

QueEType GetQHead(QP* Qptr)									//取队列头值
{
	assert(Qptr);
	assert(!QueueEmpty(Qptr));
	return Qptr->Head->data;
}

QueEType GetQTail(QP* Qptr)									//取队列尾值
{
	assert(Qptr);
	assert(!QueueEmpty(Qptr));
	return Qptr->Tail->data;
}

int QueueSize(QP* Qptr)									//队列大小，也可以在Queueptr中加入size，每次尾插时++，每次头删时--，该函数直接返回size即可，效率更高
{
	assert(Qptr);
	int count = 0;
	if (QueueEmpty(Qptr))
	{
		printf("队列内无任何元素\n");
	}
	else
	{
		QNode* cur = Qptr->Head;
		while (cur)
		{
			count++;
			cur = cur->next;
		}
	}
	return count;
}
