#define _CRT_SECURE_NO_WARNINGS 1
#include"SgL.h"

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

SgL* Remove(SgL* Head, int value)
{
	//�Ƴ��㷨������1�������������
	assert(Head);											//�����������ʱ�����������ã���Ϊ���԰����д��������
	SgL* Cur = Head;
	SgL* tmp4 = Head;
	while (Cur)
	{
		if (Cur->data == value && Head->data == value)				//�ж�ͷ����Ƿ�Ϊvalueֵ
		{
			if (Cur->next == NULL)
			{
				free(Cur);
				return NULL;
			}
			else
			{
				SgL* tmp1 = Cur->next;
				free(Cur);
				Head = tmp1;										//�ı�ͷ����ַ
				Cur = Head;
			}
		}
		else if (Cur->data == value)								//�жϵ�ǰ����Ƿ�Ϊvalueֵ
		{
			SgL* tmp2 = Cur->next;
			free(Cur);
			Cur = tmp2;
			tmp4->next = Cur;
		}
		else if (Cur->next == NULL)									//�ж��¸�����Ƿ�Ϊ��
		{
			return Head;
		}
		else if (Cur->next->data != value)							//���¸��ڵ㲻Ϊ�գ����ж��¸�����Ƿ�Ϊvalue
		{
			Cur = Cur->next;
		}
		else
		{
			if(Cur->next->data == value)							//�ж���һ�ڵ��Ƿ�Ϊvalueֵ
			{
				if (Cur->next->next == NULL)						//�ж����½���Ƿ�Ϊ��ֵ
				{
					free(Cur->next);
					Cur->next = NULL;
					return Head;
				}
				else											    //������ת��ָ��
				{
					SgL* tmp = Cur->next->next;
					free(Cur->next);
					Cur->next = tmp;
					tmp4 = Cur;
				}
			}
			if (Cur->next->next == NULL)							//������cur���¸���㲻Ϊ�գ��ж����½���Ƿ�Ϊ��ֵ
			{
				if (Cur->next->data != value)						//�����½��Ϊ�����½�㲻Ϊvalue
				{
					return Head;
				}
				else												//���½��Ϊvalue��ֱ���ͷ��¸���㲢ָ���ÿ�
				{
					free(Cur->next);
					Cur->next = NULL;
					return Head;
				}
			}
			Cur = Cur->next;										//�����ָ�����һ��
		}
	}
	return Head;													//��Ϊ�з���ͷ����ַ�����Բ���Ҫ����ָ��
}