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

Etype LastKVal(SgL* Head, int k)							//查找倒数第k个
{
	assert(Head);
	SgL* cur = Head;
	int count = 0;
	while (cur)												//遍历链表找k值范围
	{
		cur = cur->next;
		count++;
	}
	assert(k >= 0 && k <= count);							//断言k的值范围必须在0到结点数之间
	if (k == 0)												//当倒数第0个时，返回头结点值
	{
		return NULL;
	}
	else
	{
		SgL* fast = Head;
		SgL* slow = Head;
		while (k--)											//让快指针先在链表中走k步
		{
			fast = fast->next;
		}
		while (fast)										//当快指针走到NULL，此时慢指针指向结点值即倒数第k个结点值
		{
			slow = slow->next;
			fast = fast->next;
		}
		return slow->data;									//返回该值
	}
	return 0;
}


SgL* Merging2SL(SgL* Head1, SgL* Head2)							//合并两个有序链表函数
{
	assert(Head1 && Head2);
	SgL* Guard = BuyListNode(NULL);								//创建哨兵头结点等待尾插
	SgL* cur1 = Head1, * cur2 = Head2, * cur3 = Guard;			//三个结点指针分别遍历两个原数组，还有一个负责尾插新链表
	while (cur1 && cur2)
	{
		if (cur1->data <= cur2->data)							//当第一个链表结点值小于第二个链表结点值
		{
			cur3->next = BuyListNode(cur1->data);				//在新链表新开辟结点，并将原链表结点值放入
			cur3 = cur3->next;
			cur1 = cur1->next;
		}
		else													//当第一个链表结点值大于第二个
		{
			cur3->next = BuyListNode(cur2->data);
			cur3 = cur3->next;
			cur2 = cur2->next;
		}
	}
	if (cur1 != NULL)											//当其中一个原链表先到达NULL，判断另一个链表是否尾插完毕
	{
		while (cur1)
		{
			cur3->next = BuyListNode(cur1->data);				
			cur3 = cur3->next;
			cur1 = cur1->next;
		}
	}
	else if (cur2 != NULL)										//若另一个链表没达到NULL，则尾插该链表剩余全部值尾插到新链表后
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

SgL* SLSlicing(SgL* Head, int x)								//分割链表函数
{
	assert(Head);
	SgL* move = Head;											//一个遍历原链表的指针
	SgL* LessGuard = BuyListNode(NULL);							//一个指向存放均比x值小的链表指针
	SgL* BiggerGuard = BuyListNode(NULL);						//一个指向存放均比x值大的链表指针
	SgL* less = LessGuard, * big = BiggerGuard;
	while (move)												//结束条件为当原链表指针遍历到NULL
	{
		if (move->data < x)										//若原链表当前结点值比x下，存入小链表中
		{
			less->next = BuyListNode(move->data);
			less = less->next;
		}
		else
		{
			big->next = BuyListNode(move->data);				//反之存入大链表中
			big = big->next;
		}
		move = move->next;
	}
	less->next = BiggerGuard->next;								//将小链表后继指针与大链表头哨兵结点后继的结点串联起来
	SgL* tmp = LessGuard->next;
	free(LessGuard);											//释放大小链表的哨兵位
	free(BiggerGuard);
	return tmp;													//将新串联的分割链表头结点地址返回
}

bool PalinDrome(SgL* Head)										//判断一个链表是否为回文
{
	assert(Head);
	if (Head->next == NULL)										//若链表仅有一个结点，返回真
	{
		return true;
	}
	SgL* fast = Head, * slow = Head;							//定义快慢指针找中间结点
	while (fast && fast->next)
	{
		fast = fast->next->next;
		slow = slow->next;
	}
	SgL* Push = slow;											//定义头插指针，将其所指向结点头插到新链表中完成逆序
	SgL* Get = NULL;											//定义一个只备份新链表首结点（即哨兵下一个结点）地址的指针
	while (Push)
	{
		SgL* head = BuyListNode(Push->data);					//开辟新节点作为新链表头部
		head->next = Get;										//让新节点可以指向已备份的后一个结点的地址
		Get = head;												//Get作为备份当前头部地址的指针而存在			
		Push = Push->next;
	}
	Push = Head;
	while (Push != slow)										//原链表到中间结点与新链表遍历比较
	{
		if (Push->data != Get->data)							//只要有其中一个不相等，就返回假
		{
			return false;
		}
		Push = Push->next;
		Get = Get->next;
	}
	return true;												//否则全部相等，返回真
}

SgL* CrossOver(SgL* Head1, SgL* Head2)							//找两链表相交结点函数
{
	assert(Head1);
	assert(Head2);
	if (Head1->next == NULL && Head2->next == NULL)				//若两个链表都为单节点，不可能相交
	{
		return NULL;
	}
	SgL* cur1 = Head1;
	SgL* cur2 = Head2;
	int count1 = 0, count2 = 0;
	while (cur1)												//遍历两个链表求长度
	{
		cur1 = cur1->next;
		count1++;
	}
	while (cur2)
	{
		cur2 = cur2->next;
		count2++;
	}
	int k = count1 > count2 ? count1 - count2 : count2 - count1;//算出长度差距
	if (k == count1 - count2)
	{
		cur1 = Head1;
		while (k--)												//让更长的链表先走k个结点
		{
			cur1 = cur1->next;
		}
		cur2 = Head2;											//并让短链表的遍历指针重置回头部
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
	while (cur1)												//此时两链表长度相等
	{
		if (cur1 == cur2)										//遍历链表并对比指针地址，相等则找到交点
		{
			return cur1;
		}
		cur1 = cur1->next;
		cur2 = cur2->next;
	}
	return NULL;												//否则返回空值
}

bool RoundSgL(SgL* Head)										//环形链表
{
	if (Head == NULL || Head->next == NULL)						//若链表为空或头结点后继为空，返回假
	{
		return false;
	}
	SgL* fast = Head->next;										//快指针先走一步，之后每次走两步
	SgL* slow = Head;											//慢指针从头结点开始，之后每次走一步
	while (fast != slow)										//通过比较快指针指向的结点地址与慢指针指向地址是否相等作为有环依据
	{
		if (fast->next == NULL || fast->next->next == NULL)		//如果快指针后继和后后继地址为空，直接判断为无环链表，返回假
		{
			return false;
		}
		fast = fast->next->next;											
		slow = slow->next;
	}
	return true;												//若从循环出来，即快指针地址等于慢指针地址，返回真
}
