#define _CRT_SECURE_NO_WARNINGS 1
#include"Func.h"
SGL* BuyListNode(SEtype x)
{
	SGL* NewNode = (SGL*)malloc(sizeof(SGL));
	assert(NewNode);
	NewNode->data = x;
	NewNode->next = NULL;
	return NewNode;
}

bool Detect(SGL* Head)
{
	assert(Head);
	SGL* fast, * slow;
	fast = slow = Head;
	while(fast && fast->next)
	{
		fast = fast->next->next;
		slow = slow->next;
		if (fast == slow)
		{
			return true;
		}
	}
	return false;
}

SEtype Enter(SGL* Head)
{
	assert(Head);
	SGL* fast, * slow, * In;
	fast = slow = In = Head;
	while (fast && fast->next)					//����ָ����������
	{
		fast = fast->next->next;
		slow = slow->next;
		if (fast == slow)						//�ҵ������㣬��ֻ����ָ�룬����ͷ���ͬʱ��ʼ�ƶ��뻷����ָ��
		{
			printf("�����ص�Ϊ��%d\n", fast->data);
			while (In != slow)					//�����ָ������ָ������ʱ����ʱ�Ľ������뻷��
			{
				slow = slow->next;
				In = In->next;
			}
			return In->data;					//���뻷����ֵ���أ�����۲�
		}
	}
	return -1;
}

RD* BuyRandom(SEtype x)							//�������ָ����
{
	RD* NewNode = (RD*)malloc(sizeof(RD));
	assert(NewNode);
	NewNode->data = x;
	NewNode->next = NULL;
	NewNode->random = NULL;
	return NewNode;
}

RD* Copy(RD* Head)								//��ԭ�����������������׽���ַ��ʵ��
{
	assert(Head);
	RD* cur = Head;
	while (cur)									//��һ��ѭ�����ٴ�������㲢�м���뵽ԭ�����У�������������ֵ��ͷ������ָ�루next��
	{
		RD* copynode = BuyRandom(cur->data);
		copynode->next = cur->next;
		cur->next = copynode;
		cur = copynode->next;
	}
	cur = Head;
	while (cur)									//���������ָ�룬��ָ����һ��ԭ�����������ָ��ָ��Ľ�����һ�����(��ָ���ѿ����Ľ��)
	{
		if (cur->random == NULL)
		{
			cur->next->random = NULL;
		}
		else if (cur->random == cur)
		{
			cur->next->random = cur->next;
		}
		else
		{
			cur->next->random = cur->random->next;
		}
		cur = cur->next->next;
	}
	cur = Head;
	RD* copynode = cur->next;
	RD* copyhead = copynode;
	while (cur)									//�����������ӳ���������ԭ����ָ�
	{
		cur->next = copynode->next;
		cur = cur->next;
		if (cur == NULL)
		{
			copynode->next = NULL;
			break;
		}
		copynode->next = cur->next;
		copynode = copynode->next;
	}
	return copyhead;
}

ST* StackInit()
{
	ST* init = (ST*)malloc(sizeof(ST));
	assert(init);
	init->a = NULL;
	init->capacity = init->top = 0;
	return init;
}

void STPop(ST* Bot)
{
	assert(Bot);
	if (Bot->top != 0)
	{
		Bot->top--;
	}
}

SType STTop(ST* Bot)
{
	assert(Bot);
	if (Bot->top != 0)
	{
		return Bot->a[Bot->top - 1];
	}
	return NULL;
}

bool BracketMatch(char* arr, int sz)
{
	ST* match = StackInit();
	assert(match);
	if (match->capacity == match->top)
	{
		int expand = match->capacity == 0 ? sz : match->capacity * 2;
		SType* newcap = (SType*)realloc(match->a, sizeof(SType) * expand);
		assert(newcap);
		match->a = newcap;
		match->capacity = expand;
	}
	char* cur = arr;
	char tmp[3] = { '0'};
	while (*cur != '\0')
	{
		if (*cur == '(' || *cur == '[' || *cur == '{')
		{
			match->a[match->top] = *cur;
			cur++;
			match->top++;
			continue;
		}
		if (*cur == ')' || *cur == ']' || *cur == '}')
		{
			if (cur == arr)
			{
				return false;
			}
			match->a[match->top] = *cur;
			match->top++;
			tmp[1] = STTop(match);
			STPop(match);
			tmp[0] = STTop(match);
			STPop(match);
		}
		if (strcmp(tmp, "()") && strcmp(tmp, "[]") && strcmp(tmp, "{}"))
		{
			return false;
		}
		cur++;
	}
	return true;
}
