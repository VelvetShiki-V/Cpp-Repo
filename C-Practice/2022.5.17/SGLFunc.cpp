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
		if (move->data != x && count == 1)					//��һ����val�����Ϊ�������׽ڵ�
		{
			NewHead = move;
			insert = NewHead;
			count--;
		}
		else if (move->data != x)							//������val�����Ϊ���׽ڵ�����Ĳ�����
		{
			insert->next = move;
			insert = insert->next;
		}
		move = move->next;									//������ѭ����Ĭ���ƶ�move���ָ��
	}
	if (NewHead == NULL)									//��û���κη�val��㣬�򷵻ؿ�����
	{
		return NULL;
	}
	insert->next = NULL;									//��������������insert�ĺ�������ÿ�
	return NewHead;
}

SgL* PushFront(SgL* Head, Etype x)							//ͷ�庯��
{
	assert(Head);
	SgL* NewHead = BuyListNode(x);
	NewHead->next = Head;
	return NewHead;
}

SgL* ReverseSL(SgL* Head)									//���������㷨
{
	SgL* move = Head;										//����һ�����ָ�����ԭ����
	move = move->next;										//��ʼʱĬ���ƶ���ԭ����ڶ�����㴦���ȴ�ͷ��
	SgL* insert = Head;										//����һ����������ָ�룬����ͷ��ָ��
	while (move)
	{
		insert = PushFront(insert, move->data);				//��moveָ����ͷ����insert���
		move = move->next;
	}
	Head->next = NULL;										//��ԭ����ͷ������ָ���ÿ�
	return insert;
}


SgL* ReverseSL2(SgL* Head)									//���������㷨2
{	
	assert(Head);											//��������
	SgL* pre = Head;
	SgL* cur = Head->next;
	if (Head->next == NULL)									//�ж��Ƿ�Ϊ���������
	{
		return Head;
	}
	if (Head->next->next == NULL)							//�ж��Ƿ�Ϊ˫�������
	{
		cur->next = pre;
		pre->next = NULL;
		return cur;
	}
	else
	{	
		SgL* Next = Head->next->next;						//����ָ��pre, cur, Next�ֱ�洢ǰ�к��㣬���ı�ָ��ѭ����Next == NULL
		int count = 1;
		while(Next)
		{
			cur->next = pre;
			if (count == 1)
			{
				pre->next = NULL;							//����β������ÿ�
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


Etype FindMid(SgL* Head)									//�����м����㷨
{
	assert(Head);
	SgL* Fast = Head;										//�����ָ�룬һ�����������
	SgL* Slow = Head;										//������ָ�룬һ����һ�����
	if (Head->next == NULL)									//�ж������Ƿ�Ϊһ�����ṹ
	{
		return Head->data;
	}
	if (Head->next->next == NULL)							//�ж������Ƿ�Ϊ�������ṹ
	{
		return Head->next->data;
	}
	while (Fast->next != NULL && Fast->next->next != NULL)	//����ָ����¸����Ϊ�ջ����¸����Ϊ��ʱֹͣѭ��
	{
		Fast = Fast->next->next;
		Slow = Slow->next;
	}
	if (Fast->next == NULL)									//��ָ���¸����Ϊ��ʱ������ָ��ָ��Ľ����ֵ
	{
		return Slow->data;
	}
	else if (Fast->next->next == NULL)						//��ָ�����¸����Ϊ��ʱ������ָ��ĺ��ָ��ָ��Ľ����ֵ
	{
		return Slow->next->data;
	}
}

Etype LastKVal(SgL* Head, int k)							//���ҵ�����k��
{
	SgL* 
}