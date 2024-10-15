#define _CRT_SECURE_NO_WARNINGS 1
#include"SglinkFunc.h"
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

Etype LastKVal(SgL* Head, int k)							//���ҵ�����k��
{
	assert(Head);
	SgL* cur = Head;
	int count = 0;
	while (cur)												//����������kֵ��Χ
	{
		cur = cur->next;
		count++;
	}
	assert(k >= 0 && k <= count);							//����k��ֵ��Χ������0�������֮��
	if (k == 0)												//��������0��ʱ������ͷ���ֵ
	{
		return NULL;
	}
	else
	{
		SgL* fast = Head;
		SgL* slow = Head;
		while (k--)											//�ÿ�ָ��������������k��
		{
			fast = fast->next;
		}
		while (fast)										//����ָ���ߵ�NULL����ʱ��ָ��ָ����ֵ��������k�����ֵ
		{
			slow = slow->next;
			fast = fast->next;
		}
		return slow->data;									//���ظ�ֵ
	}
	return 0;
}


SgL* Merging2SL(SgL* Head1, SgL* Head2)							//�ϲ���������������
{
	assert(Head1 && Head2);
	SgL* Guard = BuyListNode(NULL);								//�����ڱ�ͷ���ȴ�β��
	SgL* cur1 = Head1, * cur2 = Head2, * cur3 = Guard;			//�������ָ��ֱ��������ԭ���飬����һ������β��������
	while (cur1 && cur2)
	{
		if (cur1->data <= cur2->data)							//����һ��������ֵС�ڵڶ���������ֵ
		{
			cur3->next = BuyListNode(cur1->data);				//���������¿��ٽ�㣬����ԭ������ֵ����
			cur3 = cur3->next;
			cur1 = cur1->next;
		}
		else													//����һ��������ֵ���ڵڶ���
		{
			cur3->next = BuyListNode(cur2->data);
			cur3 = cur3->next;
			cur2 = cur2->next;
		}
	}
	if (cur1 != NULL)											//������һ��ԭ�����ȵ���NULL���ж���һ�������Ƿ�β�����
	{
		while (cur1)
		{
			cur3->next = BuyListNode(cur1->data);				
			cur3 = cur3->next;
			cur1 = cur1->next;
		}
	}
	else if (cur2 != NULL)										//����һ������û�ﵽNULL����β�������ʣ��ȫ��ֵβ�嵽�������
	{
		while (cur2)
		{
			cur3->next = BuyListNode(cur2->data);
			cur3 = cur3->next;
			cur2 = cur2->next;
		}
	}
	SgL* tmp = Guard->next;
	free(Guard);
	return tmp;
}

SgL* SLSlicing(SgL* Head, int x)								//�ָ�������
{
	assert(Head);
	SgL* move = Head;											//һ������ԭ�����ָ��
	SgL* LessGuard = BuyListNode(NULL);							//һ��ָ���ž���xֵС������ָ��
	SgL* BiggerGuard = BuyListNode(NULL);						//һ��ָ���ž���xֵ�������ָ��
	SgL* less = LessGuard, * big = BiggerGuard;
	while (move)												//��������Ϊ��ԭ����ָ�������NULL
	{
		if (move->data < x)										//��ԭ����ǰ���ֵ��x�£�����С������
		{
			less->next = BuyListNode(move->data);
			less = less->next;
		}
		else
		{
			big->next = BuyListNode(move->data);				//��֮�����������
			big = big->next;
		}
		move = move->next;
	}
	less->next = BiggerGuard->next;								//��С������ָ���������ͷ�ڱ�����̵Ľ�㴮������
	SgL* tmp = LessGuard->next;
	free(LessGuard);											//�ͷŴ�С������ڱ�λ
	free(BiggerGuard);
	return tmp;													//���´����ķָ�����ͷ����ַ����
}

bool PalinDrome(SgL* Head)										//�ж�һ�������Ƿ�Ϊ����
{
	assert(Head);
	if (Head->next == NULL)										//���������һ����㣬������
	{
		return true;
	}
	SgL* fast = Head, * slow = Head;							//�������ָ�����м���
	while (fast && fast->next)
	{
		fast = fast->next->next;
		slow = slow->next;
	}
	SgL* Push = slow;											//����ͷ��ָ�룬������ָ����ͷ�嵽���������������
	SgL* Get = NULL;											//����һ��ֻ�����������׽�㣨���ڱ���һ����㣩��ַ��ָ��
	while (Push)
	{
		SgL* head = BuyListNode(Push->data);					//�����½ڵ���Ϊ������ͷ��
		head->next = Get;										//���½ڵ����ָ���ѱ��ݵĺ�һ�����ĵ�ַ
		Get = head;												//Get��Ϊ���ݵ�ǰͷ����ַ��ָ�������			
		Push = Push->next;
	}
	Push = Head;
	while (Push != slow)										//ԭ�����м���������������Ƚ�
	{
		if (Push->data != Get->data)							//ֻҪ������һ������ȣ��ͷ��ؼ�
		{
			return false;
		}
		Push = Push->next;
		Get = Get->next;
	}
	return true;												//����ȫ����ȣ�������
}

SgL* CrossOver(SgL* Head1, SgL* Head2)							//���������ཻ��㺯��
{
	assert(Head1);
	assert(Head2);
	if (Head1->next == NULL && Head2->next == NULL)				//����������Ϊ���ڵ㣬�������ཻ
	{
		return NULL;
	}
	SgL* cur1 = Head1;
	SgL* cur2 = Head2;
	int count1 = 0, count2 = 0;
	while (cur1)												//�������������󳤶�
	{
		cur1 = cur1->next;
		count1++;
	}
	while (cur2)
	{
		cur2 = cur2->next;
		count2++;
	}
	int k = count1 > count2 ? count1 - count2 : count2 - count1;//������Ȳ��
	if (k == count1 - count2)
	{
		cur1 = Head1;
		while (k--)												//�ø�������������k�����
		{
			cur1 = cur1->next;
		}
		cur2 = Head2;											//���ö�����ı���ָ�����û�ͷ��
	}
	else if(k == count2 - count1)
	{
		cur2 = Head2;
		while (k--)
		{
			cur2 = cur2->next;
		}
		cur1 = Head1;
	}
	while (cur1)												//��ʱ�����������
	{
		if (cur1 == cur2)										//���������Ա�ָ���ַ��������ҵ�����
		{
			return cur1;
		}
		cur1 = cur1->next;
		cur2 = cur2->next;
	}
	return NULL;												//���򷵻ؿ�ֵ
}

bool RoundSgL(SgL* Head)										//��������
{
	if (Head == NULL || Head->next == NULL)						//������Ϊ�ջ�ͷ�����Ϊ�գ����ؼ�
	{
		return false;
	}
	SgL* fast = Head->next;										//��ָ������һ����֮��ÿ��������
	SgL* slow = Head;											//��ָ���ͷ��㿪ʼ��֮��ÿ����һ��
	while (fast != slow)										//ͨ���ȽϿ�ָ��ָ��Ľ���ַ����ָ��ָ���ַ�Ƿ������Ϊ�л�����
	{
		if (fast->next == NULL || fast->next->next == NULL)		//�����ָ���̺ͺ��̵�ַΪ�գ�ֱ���ж�Ϊ�޻��������ؼ�
		{
			return false;
		}
		fast = fast->next->next;											
		slow = slow->next;
	}
	return true;												//����ѭ������������ָ���ַ������ָ���ַ��������
}
