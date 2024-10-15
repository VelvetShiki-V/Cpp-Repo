#define _CRT_SECURE_NO_WARNINGS 1
#include"Queue.h"

void Print(QP* Qptr)
{
	assert(Qptr);
	if (QueueEmpty(Qptr))
	{
		printf("����Ϊ��\n");
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

void QueueInit(QP* Qptr)								//����ָ���ʼ��
{
	assert(Qptr);
	Qptr->Head = Qptr->Tail = NULL;
}

void QPushBack(QP* Qptr, QueEType x)					//����β��
{
	assert(Qptr);
	QNode* NewNode = (QNode*)malloc(sizeof(QNode));		//�½���β��Ľ��
	assert(NewNode);
	NewNode->next = NULL;
	NewNode->data = x;
	if (Qptr->Head == Qptr->Tail && Qptr->Head == NULL)	//����ǰ��������Ϊ�գ��򽫸��½ڵ㱻ͷָ���βָ����ָ��
	{
		Qptr->Head = Qptr->Tail = NewNode;
	}
	else												//�����Ų��βָ��ָ��ý����б��
	{
		Qptr->Tail->next = NewNode;
		Qptr->Tail = NewNode;
	}
}

void QPopFront(QP* Qptr)								//����ͷɾ
{
	assert(Qptr);										//����ָ��
	assert(!QueueEmpty(Qptr));								//��������
	QNode* Next = Qptr->Head->next;						//����ͷ���ĺ�̽���ַ
	if (Next == NULL)									//��ͷ����̵�ַΪ�գ����ͷŵ�ǰͷ��β���ڽ�㲢ȫ���ÿ�
	{
		free(Qptr->Head);
		Qptr->Head = Qptr->Tail = NULL;
	}
	else												//����ͷָ�����ڽ���ͷŲ�����ƶ�һ�����
	{
		free(Qptr->Head);
		Qptr->Head = Next;
	}
}

bool QueueEmpty(QP* Qptr)									//�����п�
{
	assert(Qptr);
	return Qptr->Head == Qptr->Tail && Qptr->Head == NULL;
}

void QueueDestroy(QP* Qptr)									//��������
{
	assert(Qptr);
	while (!QueueEmpty(Qptr))								//������������н��Ԫ�أ�ѭ��ͷɾֱ����������Ϊ��
	{
		QPopFront(Qptr);
	}
}

QueEType GetQHead(QP* Qptr)									//ȡ����ͷֵ
{
	assert(Qptr);
	assert(!QueueEmpty(Qptr));
	return Qptr->Head->data;
}

QueEType GetQTail(QP* Qptr)									//ȡ����βֵ
{
	assert(Qptr);
	assert(!QueueEmpty(Qptr));
	return Qptr->Tail->data;
}

int QueueSize(QP* Qptr)									//���д�С��Ҳ������Queueptr�м���size��ÿ��β��ʱ++��ÿ��ͷɾʱ--���ú���ֱ�ӷ���size���ɣ�Ч�ʸ���
{
	assert(Qptr);
	int count = 0;
	if (QueueEmpty(Qptr))
	{
		printf("���������κ�Ԫ��\n");
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
