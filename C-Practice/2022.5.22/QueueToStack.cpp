#define _CRT_SECURE_NO_WARNINGS 1
#include"Stack_Queue.h"

void QueueInit(QP* Qptr)
{
	Qptr->Head = Qptr->Tail = NULL;
}

void QPushBack(QP* Qptr, QEtype x)
{
	assert(Qptr);
	QNode* NewNode = (QNode*)malloc(sizeof(QNode));
	assert(NewNode);
	NewNode->data = x;
	NewNode->next = NULL;
	if (Qptr->Head == NULL)
	{
		Qptr->Head = Qptr->Tail = NewNode;
	}
	else
	{
		Qptr->Tail->next = NewNode;
		Qptr->Tail = NewNode;
	}
}

void QPopFront(QP* Qptr)
{
	assert(Qptr);
	if (Qptr->Head->next != NULL)
	{
		QNode* tmp = Qptr->Head->next;
		free(Qptr->Head);
		Qptr->Head = tmp;
	}
	else
	{
		free(Qptr->Head);
		Qptr->Head = Qptr->Tail = NULL;
	}
}

bool QueueEmpty(QP* Qptr)
{
	assert(Qptr);
	return QueueSize(Qptr) == 0;
}

int QueueSize(QP* Qptr)
{
	assert(Qptr);
	int count = 0;
	QNode* cur = Qptr->Head;
	while (cur)
	{
		cur = cur->next;
		count++;
	}
	return count;
}

QEtype GetQHead(QP* Qptr)
{
	assert(Qptr);
	assert(!QueueEmpty(Qptr));
	return Qptr->Head->data;
}

void QueueDestroy(QP* Qptr)
{
	while (!QueueEmpty(Qptr))
	{
		QPopFront(Qptr);
	}
}

MST* StackCreate()
{
	MST* tmp = (MST*)malloc(sizeof(MST));
	tmp->Q1 = (QP*)malloc(sizeof(QP));
	tmp->Q2 = (QP*)malloc(sizeof(QP));
	QueueInit(tmp->Q1);
	QueueInit(tmp->Q2);
	return tmp;
}

void PushQ(MST* obj, QEtype x)
{
	assert(obj);
	QP* EMPTY = obj->Q1;
	QP* NONEMPTY = obj->Q2;
	if (!QueueEmpty(EMPTY))
	{
		EMPTY = obj->Q2;
		NONEMPTY = obj->Q1;
	}
	QPushBack(NONEMPTY, x);
}

QEtype StackPop(MST* obj)
{
	assert(obj);
	QP* EMPTY = obj->Q1;
	QP* NONEMPTY = obj->Q2;
	if (!QueueEmpty(EMPTY))
	{
		EMPTY = obj->Q2;
		NONEMPTY = obj->Q1;
	}
	while (QueueSize(NONEMPTY) > 1)
	{
		QPushBack(EMPTY, GetQHead(NONEMPTY));
		QPopFront(NONEMPTY);
	}
	QEtype tmp = NONEMPTY->Head->data;
	QPopFront(NONEMPTY);
	return tmp;
}

QEtype StackTop(MST* obj)
{
	assert(obj);
	QP* EMPTY = obj->Q1;
	QP* NONEMPTY = obj->Q2;
	if (!QueueEmpty(EMPTY))
	{
		EMPTY = obj->Q2;
		NONEMPTY = obj->Q1;
	}
	while (QueueSize(NONEMPTY) > 1)
	{
		QPushBack(EMPTY, GetQHead(NONEMPTY));
		QPopFront(NONEMPTY);
	}
	QEtype tmp = NONEMPTY->Head->data;
	QPushBack(EMPTY, tmp);
	QPopFront(NONEMPTY);
	return tmp;
}

bool EmptyQ(MST* obj)
{
	assert(obj);
	if (QueueSize(obj->Q1) == 0 && QueueSize(obj->Q2) == 0)
	{
		return true;
	}
	return false;
}


void FreeQ(MST* obj)
{
	assert(obj);
	QueueDestroy(obj->Q1);
	QueueDestroy(obj->Q2);
	free(obj->Q1);
	free(obj->Q2);
	free(obj);
}

void PrintQ(MST* obj)
{
	assert(obj);
	printf("Top->");
	while (!EmptyQ(obj))
	{
		printf("%d->", StackTop(obj));
		StackPop(obj);
	}
	printf("Bottom\n");
}