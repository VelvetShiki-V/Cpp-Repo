#define _CRT_SECURE_NO_WARNINGS 1
#include"DGR.h"

DGR* DGRInit()												//˫���ͷѭ�������ʼ��
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

void Print(DGR* Head)										//��ӡ������
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


void PushBack(DGR* Head, EType x)							//β��
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

void PushFront(DGR* Head, EType x)							//ͷ��
{
	assert(Head);
	DGR* Push = BuyListNode(x);
	Push->prev = Head;
	Push->next = Head->next;
	Head->next = Push;
	Push->next->prev = Push;
}

void PopBack(DGR* Head)										//βɾ
{
	assert(Head);
	assert(Head->next != Head);								//��ֹβɾ�ѳ�ʼ�����ڱ�ͷ����Լ�ɾ��
	Head->prev = Head->prev->prev;
	free(Head->prev->next);
	Head->prev->next = Head;
}

void PopFront(DGR* Head)									//ͷɾ
{
	assert(Head);
	assert(Head->next != Head);								//��ֹͷɾ�ѳ�ʼ�����ڱ�ͷ����Լ�ɾ��
	Head->next = Head->next->next;
	free(Head->next->prev);
	Head->next->prev = Head;
}

void DGRInsert(DGR* pos, EType x)							//��posλ��֮ǰ������
{
	assert(pos);
	DGR* InsertNode = BuyListNode(x);						
	pos->prev->next = InsertNode;							//��pos��ͷ����һ��������ͷ�壻��pos��ͷ��㣬����β��
	InsertNode->prev = pos->prev;
	InsertNode->next = pos;
	pos->prev = InsertNode;
}
void DGRErase(DGR* pos)										//ɾ��pos���ڵ�ַ�Ľ��
{
	assert(pos);
	assert(pos->next != pos);
	pos->prev->next = pos->next;
	pos->next->prev = pos->prev;
	free(pos);
}
