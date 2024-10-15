#define _CRT_SECURE_NO_WARNINGS 1
#include"SgList.h"

void SGLPrint(SgLNode* Head)						//������ͷ��㵽β����ӡ����
{
	SgLNode* Cur = Head;							//��ʱ�ṹ��ָ����������ڶ������ı���
	while (Cur != NULL)							//����ǰ����ַΪ��ʱ������ѭ����ӡ
	{
		printf("%d->", Cur->data);				//��ӡ��ǰ������ֵ��ֵ
		Cur = Cur->next;						//ʹ��ǰ���ָ�����һ���Ľṹ���ַ���ǵ�ǰ����ַ
	}
	printf("NULL\n");
}

SgLNode* BuyListNode(SGLElemType x)								//�����½��ṹ�庯��
{
	SgLNode* NewNode = (SgLNode*)malloc(sizeof(SgLNode));		//�����½ڵ�ṹ���ַ
	assert(NewNode);
	NewNode->data = x;											//�½ڵ���ֵ�����ⲿ�ֶ������x��ֵ
	NewNode->next = NULL;										//Ĭ���½ڵ�ָ�����һ����ַ�ÿ�
	return NewNode;												//���½ڵ�Ľṹ���ַ����
}

void SGLPushBack(SgLNode** Head, SGLElemType x)
{
	SgLNode* NewNode = BuyListNode(x);
	if (*Head == NULL)											//�������׽ڵ�ʵ�ε�ַΪ�գ���Ϊ������ʱ
	{
		*Head = NewNode;										//β���൱��ͷ����ʼ�������׽ڵ��ַ
	}
	else														//���׽ڵ㲻Ϊ�գ������ǿ��������
																//Ѱ��β��㣬����β���ָ�����һ��ַΪ�½ڵ�ṹ���ַ
	{
		SgLNode* Tail = *Head;									//��β���ṹ��ָ��������壬��ʼ��Ϊͷ����ַ	
		while (Tail->next != NULL)								//��β���ָ�����һ�ṹ���ַΪ��ʱ���ҵ�β���
		{
			Tail = Tail->next;									//ʹ��ǰ���ָ�����һ���Ľṹ���ַ���ǵ�ǰ����ַ
		}
		Tail->next = NewNode;									//�þɵ�β���ָ����һ�����ĵ�ַ��ֵΪβ����½ڵ��ַ
	}
}

void SGLPushFront(SgLNode** Head, SGLElemType x)				//����ͷ�壬���׽ڵ�Ľṹ���ַ���ö���ָ�����
{
	SgLNode* NewNode = BuyListNode(x);
	NewNode->next = *Head;										//ԭ���ľ�ͷ����ַ���½��ĺ����ṹ��ָ����ָ��
	*Head = NewNode;											//����ͷ����ַ����ԭ���ṹ��ָ��ָ���ͷ���ʵ�ε�ֵַ����Ϊ�µ�ͷ���
}

void SGLPopFront(SgLNode** Head)
{
	assert(*Head);
	SgLNode* Next = (*Head)->next;							//��ָ��ԭͷ����ַ��ָ������ò��ҵ���ָ��ĺ������Ľṹ���ַ�����丳ֵ���µĽṹ��ָ��ָ��
	free(*Head);											//��ԭ��ָ��ͷ����ַ��ָ��������õ�ͷ���ʵ�ε�ַ�����ͷ���malloc�ڶѵĿռ�
	*Head = Next;											//��Ϊfreeǰ�Ѿ���ԭ������ָ�����ַ��ֵ��ָ��Next�ˣ�����ֱ�ӽ��õ�ַ���Ǹ�ָ���ָ���*Head�����ͷ����ת��
															//���ͷŽ�㣬�ٽ����ݺõĺ�������ֵַ���ǽ��ָ��ָ��������˳���෴���޷��ͷ�ͷ����ڴ�
}

void SGLPopBack(SgLNode** Head)								//����βɾ
{
	assert(*Head);
	if ((*Head)->next == NULL)
	{
		free(*Head);										//��ͨ��ָ��ý��Ľṹ��ָ���ͷŸý��Ŀռ�
		*Head = NULL;										//���ǽ�ָ�����ָ���ÿ�ǰ���������ͷŸý��malloc���ڴ�ռ䣬�����޷�ͨ����ָ���ҵ���Ӧ�ռ��ͷ��ڴ�
															//����βɾ��㣬���ͷţ����ÿ�
	}
	else
	{
		SgLNode* Tail = *Head;
		while (Tail->next->next != NULL)					//�ҵ����ڶ������Tail
		{
			Tail = Tail->next;
		}
		free(Tail->next);									//�ͷ�β���
		Tail->next = NULL;									//��ʹ�����ڶ������ĺ���ָ���ÿ�
	}
}

SgLNode* SGLFind(SgLNode* Head, SGLElemType x)								//��������
{
	assert(Head);
	SgLNode* Cur = Head;
	while (Cur)
	{
		if (Cur->data == x)
		{
			return Cur;
		}
		Cur = Cur->next;
	}
	return NULL;
}

void SGLInsert(SgLNode** Head, SgLNode* pos, SGLElemType x)						//�����м����
{
	assert(Head);
	SgLNode* Prepos = *Head;
	SgLNode* InsertNode = BuyListNode(0);
	if (*Head == pos)
	{
		SGLPushFront(Head, x);
	}
	else
	{
		while (Prepos->next != pos)
		{
			Prepos = Prepos->next;
		}
		Prepos->next = InsertNode;
		InsertNode->data = x;
		InsertNode->next = pos;
	}
}

void SGLErase(SgLNode** Head, SgLNode* pos)						//����������
{
	assert(*Head);
	SgLNode* Prepos = *Head;									//ָ��ͷ������ʱָ�룬�����Ҵ���������ǰһ�����
	SgLNode* tmp = BuyListNode(0);								//�����ݵ��¿սڵ�
	if (pos == *Head)											//���������Ϊͷ���
	{
		tmp = (*Head)->next;									//����ͷ����̽���ַ
		free(*Head);											//ͨ�����ָ���ͷ�ͷ���
		*Head = tmp;											//����̽���ַ��ֵ���½���Ϊ��ͷ���
	}
	else if (pos->next == NULL)									//���������Ϊβ���
	{
		while (Prepos->next != pos)
		{
			Prepos = Prepos->next;
		}
		free(Prepos->next);
		Prepos->next = NULL;
	}
	else
	{
																//������������β��㣬������ͨ���
	}
	{
		while (Prepos->next != pos)
		{
			Prepos = Prepos->next;
		}
		tmp = pos->next;
		free(Prepos->next);
		Prepos->next = tmp;
	}
}

