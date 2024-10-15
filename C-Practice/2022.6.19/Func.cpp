#include"Func.h"

void SGLPrint(SgLNode* Head)									//�����ͷ��㵽β����ӡ����������Ҫ���ԣ�������ֱ�Ӵ�ӡNULL����ʾ����Ϊ�գ�
{
	SgLNode* Cur = Head;										//��ʱ�ṹ��ָ����������ڶ�����ı���
	while (Cur != NULL)											//����ǰ����ַΪ��ʱ������ѭ����ӡ
	{
		printf("%d->", Cur->data);								//��ӡ��ǰ������ֵ��ֵ
		Cur = Cur->next;										//ʹ��ǰ���ָ�����һ���Ľṹ���ַ���ǵ�ǰ����ַ
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
	//assert(Head);
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
	assert(Head);
	SgLNode* NewNode = BuyListNode(x);
	NewNode->next = *Head;										//ԭ���ľ�ͷ����ַ���½��ĺ����ṹ��ָ����ָ��
	*Head = NewNode;											//����ͷ����ַ����ԭ���ṹ��ָ��ָ���ͷ���ʵ�ε�ֵַ����Ϊ�µ�ͷ���
}

SgLNode* SGLPushFront1(SgLNode* Head, SGLElemType x)	//����ͷ�壬��һ��ָ��Ĵ�����ֵ����
{
	SgLNode* NewNode = BuyListNode(x);
	NewNode->next = Head;						//ԭ���ľ�ͷ����ַ���½��ĺ����ṹ��ָ����ָ��
	Head = NewNode;								//����ͷ����ַ����ԭ���ṹ��ָ��ָ���ͷ���ʵ�ε�ֵַ����Ϊ�µ�ͷ���
	return Head;
}

void SGLPopFront(SgLNode** Head)
{
	assert(Head);
	if ((*Head) != NULL)
	{
		SgLNode* Next = (*Head)->next;							//��ָ��ԭͷ����ַ��ָ������ò��ҵ���ָ��ĺ������Ľṹ���ַ�����丳ֵ���µĽṹ��ָ��ָ��
		free(*Head);											//��ԭ��ָ��ͷ����ַ��ָ��������õ�ͷ���ʵ�ε�ַ�����ͷ���malloc�ڶѵĿռ�
		*Head = Next;											//��Ϊfreeǰ�Ѿ���ԭ������ָ�����ַ��ֵ��ָ��Next�ˣ�����ֱ�ӽ��õ�ַ���Ǹ�ָ���ָ���*Head�����ͷ����ת��
																//���ͷŽ�㣬�ٽ����ݺõĺ�������ֵַ���ǽ��ָ��ָ��������˳���෴���޷��ͷ�ͷ����ڴ�
	}
	
}

void SGLPopBack(SgLNode** Head)									//����βɾ
{
	assert(Head);
	if ((*Head) != NULL)											//�������Ϊ�ղſ�βɾ
	{
		if ((*Head)->next == NULL)
		{
			free(*Head);										//��ͨ��ָ��ý��Ľṹ��ָ���ͷŸý��Ŀռ�
			*Head = NULL;
			//���ǽ�ָ�����ָ���ÿ�ǰ���������ͷŸý��malloc���ڴ�ռ䣬�����޷�ͨ����ָ���ҵ���Ӧ�ռ��ͷ��ڴ�
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
}

SgLNode* SGLFind(SgLNode* Head, SGLElemType x)					//�������
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

void SGLInsert(SgLNode** Head, SgLNode* pos, SGLElemType x)		//�����м����
{
	assert(Head);												//����ָ�������������ֹ������Ч
	if (*Head == NULL && pos == *Head)							//�������Ϊ���Լ�����λ��ҲΪ�գ�ִ��ͷ��
	{
		SGLPushFront(Head, x);
	}
	else if (*Head == NULL && pos != *Head)						//�������Ϊ�յ�����λ�ò�Ϊ�գ�����
	{
		printf("������λ�ò��Ϸ�\n");
		return;
	}
	else														//�������Ϊ��
	{
		SgLNode* Prepos = *Head;							//�����ҳ���������ǰһ������ʱָ�룬��ͷ����ַ��ֵ
		SgLNode* InsertNode = BuyListNode(x);				//��������ֵ�ŵ����ٵ��½ڵ���ֵ����
		if (*Head == pos)									//���ǰ������Ľ��Ϊͷ��㣬��ִ��ͷ�庯��
		{
			SGLPushFront(Head, x);
		}
		else
		{
			while (Prepos->next != pos)						//�������ͷ��㣬��ѭ���ҵ��������ǰһ�����
			{
				Prepos = Prepos->next;
			}
			Prepos->next = InsertNode;						//��ǰһ����������½�㲢��������
			InsertNode->next = pos;
		}
	}
}

void SGLErase(SgLNode** Head, SgLNode* pos)						//���������
{
	assert(*Head);
	assert(pos);
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
		Prepos->next = NULL;									//����Prepos->next == pos�ĺ��ָ�룬���������ÿ�ȴ����							
		//free(pos);											//��free(Prepos->next)������ͬ�����ͷ���β���
		//pos = NULL;											//����䲻�����ã���Ϊ��ʹβ��㱾���ÿ��ˣ�û��ʵ�ʸı�Prepose��ָ�����к��ָ���ָ����Ϊpos��ջ�������ˣ�����Prepos->next��ָ���ѱ�free�ռ�����ֵ
		//														//��ҪдΪ����д����pos = NULL���Բ���Ҫд�������ʵ��β�����ָ���ָ��ɵ��ⲿ�����ı���ָ��
		//Prepos->next = pos;									//ʵ���ϸı��˽��ָ��Խ��ṹ���еĺ��ָ��ָ����Prepos->next = NULL;ʵ������ͬ
	}
	else														//������������β��㣬������ͨ���
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

void SGLInsertAfter(SgLNode* pos, SGLElemType x)				//�����м���루ĳ���󷽣�
{
	assert(pos);												//�ж�pos����Ƿ����
	SgLNode* NewNode = BuyListNode(x);							//�ȴ���pos֮�������½��
	NewNode->next = pos->next;									//ԭpos��̸�Ϊ�½����
	pos->next = NewNode;										//pos���ֱ��ָ���½�㣬�������
}

void SGLEraseAfter(SgLNode* pos)								//�����������ĳ���󷽣�
{
	assert(pos);
	if (pos->next != NULL)
	{
		SgLNode* tmp = pos->next->next;
		free(pos->next);
		pos->next = tmp;
	}
	else
	{
		printf("��ֵ�����޸���Ԫ����Ҫɾ���������Ϊ��");
		return;
	}
}

void Erase(SgLNode** Head, SgLNode* pos)
{
	assert(Head);
	if (*Head != NULL)
	{
		if (pos == *Head)
		{
			*Head = pos->next;
			free(pos);
			return;
		}
		SgLNode* Prepos = *Head;
		while (Prepos->next != pos && Prepos->next)
		{
			Prepos = Prepos->next;
		}
		if (Prepos->next == NULL)
		{
			printf("û�д˽��\n");
		}
		else
		{
			SgLNode* tmp = pos->next;
			free(pos);
			Prepos->next = tmp;
		}
	}
}


//#include"Func.h"

//SGL* BuyListNode(SLEtype x)
//{
//	SGL* tmp = (SGL*)malloc(sizeof(SGL));
//	assert(tmp);
//	tmp->data = x;
//	tmp->next = NULL;
//	return tmp;
//}
//
//void PushBack(SGL* Head, SLEtype x)
//{
//	assert(Head);
//	SGL* cur = Head;
//	while (cur)
//	{
//		cur = cur->next;
//	}
//	cur = BuyListNode(x);
//}
//
//void PopBack(SGL** Head)
//{
//	assert(Head && *Head);
//	if (Empty(*Head))
//	{
//		if ((*Head)->next == NULL)
//		{
//			free(*Head);
//			*Head = NULL;
//		}
//		else
//		{
//			SGL* Tail = *Head;
//			while (Tail->next->next)
//			{
//				Tail = Tail->next;
//			}
//			free(Tail->next);
//			Tail->next = NULL;
//		}
//	}
//}
//
//void PushFront(SGL** Head, SLEtype x)
//{
//	assert(Head && *Head);
//	if (Empty(*Head))
//	{
//		SGL* head = (*Head);
//		(*Head) = BuyListNode(x);
//		(*Head)->next = head;
//	}
//	else
//	{
//		PushBack(*Head, x);
//	}
//}
//
//void PopFront(SGL** Head)
//{
//	assert(Head && *Head);
//	if (Empty(*Head))
//	{
//		SGL* NewHead = (*Head)->next;
//		free(*Head);
//		(*Head) = NewHead;
//	}
//}
//
//void InsertPrev(SGL** Head, SGL* pos, SLEtype x)
//{
//	assert(Head && *Head && pos);
//	if (*Head == pos)
//	{
//		PushFront(Head, x);
//	}
//	else
//	{
//		SGL* Prevpos = *Head;
//		while (Prevpos->next != pos && Prevpos->next)
//		{
//			Prevpos = Prevpos->next;
//		}
//		SGL* InsertNode = BuyListNode(x);
//		Prevpos->next = InsertNode;
//		InsertNode->next = pos;
//	}
//}
//
//void InsertAfter(SGL** Head, SGL* pos, SLEtype x)
//{
//	assert(Head && *Head && pos);
//	SGL* InsertNode = BuyListNode(x);
//	if (pos->next != NULL)
//	{
//		InsertNode->next = pos->next;
//		pos->next = InsertNode;
//	}
//	else
//	{
//		pos->next = InsertNode;
//	}
//}
//
//SGL* Find(SGL* Head, SGL* pos)
//{
//	assert(Head && pos);
//	SGL* cur = Head;
//	while (cur != pos && cur)
//	{
//		cur = cur->next;
//	}
//	if (cur == NULL)
//	{
//		printf("�Ҳ���\n");
//		return NULL;
//	}
//	return cur;
//}
//
//void Erase(SGL** Head, SGL* pos)
//{
//	assert(Head && *Head && pos);
//	if (Empty(*Head))
//	{
//		if (pos == *Head)
//		{
//			SGL* EraseNode = (*Head)->next;
//			free(*Head);
//			*Head = EraseNode;
//		}
//		else
//		{
//			SGL* Prevpos = *Head;
//			while (Prevpos->next != pos && Prevpos->next)
//			{
//				Prevpos = Prevpos->next;
//			}
//			SGL* tmp = pos->next;
//			free(pos);
//			Prevpos->next = tmp;
//		}
//	}
//}
//
//int Size(SGL* Head)
//{
//	assert(Head);
//	SGL* cur = Head;
//	int count = 0;
//	while (cur)
//	{
//		cur = cur->next;
//		count++;
//	}
//	return count;
//}
//
//bool Empty(SGL* Head)
//{
//	assert(Head);
//	return Size(Head);
//}
//
//void Print(SGL* Head)
//{
//	assert(Head);
//	if (Empty(Head))
//	{
//		SGL* cur = Head;
//		printf("Head->");
//		while (cur)
//		{
//			printf("%d->", cur->data);
//			cur = cur->next;
//		}
//		printf("NULL\n");
//	}
//	else
//	{
//		printf("������\n");
//	}
//}
//
//void Destroy(SGL** Head)
//{
//	assert(Head);
//	if (Empty(*Head))
//	{
//		while (Empty(*Head))
//		{
//			PopBack(Head);
//		}
//	}
//}