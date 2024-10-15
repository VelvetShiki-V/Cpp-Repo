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
	//移除算法——法1：跳过结点链接
	assert(Head);											//当传入空链表时出错，做题勿用，因为测试案例有传入空链表
	SgL* Cur = Head;
	SgL* tmp4 = Head;
	while (Cur)
	{
		if (Cur->data == value && Head->data == value)				//判断头结点是否为value值
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
				Head = tmp1;										//改变头结点地址
				Cur = Head;
			}
		}
		else if (Cur->data == value)								//判断当前结点是否为value值
		{
			SgL* tmp2 = Cur->next;
			free(Cur);
			Cur = tmp2;
			tmp4->next = Cur;
		}
		else if (Cur->next == NULL)									//判断下个结点是否为空
		{
			return Head;
		}
		else if (Cur->next->data != value)							//若下个节点不为空，则判断下个结点是否为value
		{
			Cur = Cur->next;
		}
		else
		{
			if(Cur->next->data == value)							//判断下一节点是否为value值
			{
				if (Cur->next->next == NULL)						//判断下下结点是否为空值
				{
					free(Cur->next);
					Cur->next = NULL;
					return Head;
				}
				else											    //满足则转移指向
				{
					SgL* tmp = Cur->next->next;
					free(Cur->next);
					Cur->next = tmp;
					tmp4 = Cur;
				}
			}
			if (Cur->next->next == NULL)							//若满足cur的下个结点不为空，判断下下结点是否为空值
			{
				if (Cur->next->data != value)						//若下下结点为空且下结点不为value
				{
					return Head;
				}
				else												//若下结点为value则直接释放下个结点并指向置空
				{
					free(Cur->next);
					Cur->next = NULL;
					return Head;
				}
			}
			Cur = Cur->next;										//将结点指针后移一次
		}
	}
	return Head;													//因为有返回头结点地址，所以不需要二级指针
}