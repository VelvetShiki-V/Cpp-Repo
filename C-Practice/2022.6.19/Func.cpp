#include"Func.h"

void SGLPrint(SgLNode* Head)									//链表从头结点到尾结点打印函数（不需要断言，空链表直接打印NULL，表示链表为空）
{
	SgLNode* Cur = Head;										//临时结构体指针变量，用于对链表的遍历
	while (Cur != NULL)											//当当前结点地址为空时，结束循环打印
	{
		printf("%d->", Cur->data);								//打印当前结点的数值域值
		Cur = Cur->next;										//使当前结点指向的下一结点的结构体地址覆盖当前结点地址
	}
	printf("NULL\n");
}

SgLNode* BuyListNode(SGLElemType x)								//创建新结点结构体函数
{
	SgLNode* NewNode = (SgLNode*)malloc(sizeof(SgLNode));		//开辟新节点结构体地址
	assert(NewNode);
	NewNode->data = x;											//新节点数值域由外部手动传入的x赋值
	NewNode->next = NULL;										//默认新节点指向的下一结点地址置空
	return NewNode;												//将新节点的结构体地址返回
}

void SGLPushBack(SgLNode** Head, SGLElemType x)
{
	//assert(Head);
	SgLNode* NewNode = BuyListNode(x);
	if (*Head == NULL)											//当链表首节点实参地址为空，即为空链表时
	{
		*Head = NewNode;										//尾插相当于头插或初始化链表首节点地址
	}
	else														//当首节点不为空，即不是空链表情况
																//寻找尾结点，并让尾结点指向的下一地址为新节点结构体地址
	{
		SgLNode* Tail = *Head;									//旧尾结点结构体指针变量定义，初始化为头结点地址	
		while (Tail->next != NULL)								//当尾结点指向的下一结构体地址为空时，找到尾结点
		{
			Tail = Tail->next;									//使当前结点指向的下一结点的结构体地址覆盖当前结点地址
		}
		Tail->next = NewNode;									//让旧的尾结点指向下一个结点的地址赋值为尾插的新节点地址
	}
}

void SGLPushFront(SgLNode** Head, SGLElemType x)				//链表头插，传首节点的结构体地址，用二级指针接收
{
	assert(Head);
	SgLNode* NewNode = BuyListNode(x);
	NewNode->next = *Head;										//原来的旧头结点地址被新结点的后续结构体指针所指向
	*Head = NewNode;											//将新头结点地址覆盖原来结构体指针指向的头结点实参地址值，成为新的头结点
}

SgLNode* SGLPushFront1(SgLNode* Head, SGLElemType x)	//链表头插，传一级指针的带返回值方法
{
	SgLNode* NewNode = BuyListNode(x);
	NewNode->next = Head;						//原来的旧头结点地址被新结点的后续结构体指针所指向
	Head = NewNode;								//将新头结点地址覆盖原来结构体指针指向的头结点实参地址值，成为新的头结点
	return Head;
}

void SGLPopFront(SgLNode** Head)
{
	assert(Head);
	if ((*Head) != NULL)
	{
		SgLNode* Next = (*Head)->next;							//对指向原头结点地址的指针解引用并找到其指向的后续结点的结构体地址，将其赋值给新的结构体指针指向
		free(*Head);											//将原先指向头结点地址的指针解引用拿到头结点实参地址，并释放其malloc在堆的空间
		*Head = Next;											//因为free前已经将原结点后续指向结点地址赋值给指针Next了，所以直接将该地址覆盖给指向空指针的*Head即完成头结点的转移
																//先释放结点，再将备份好的后续结点地址值覆盖结点指针指向；若操作顺序相反则无法释放头结点内存
	}
	
}

void SGLPopBack(SgLNode** Head)									//链表尾删
{
	assert(Head);
	if ((*Head) != NULL)											//如果链表不为空才可尾删
	{
		if ((*Head)->next == NULL)
		{
			free(*Head);										//先通过指向该结点的结构体指针释放该结点的空间
			*Head = NULL;
			//谨记将指向结点的指针置空前，必须先释放该结点malloc的内存空间，否则无法通过该指针找到对应空间释放内存
																//对于尾删结点，先释放，再置空
		}
		else
		{
			SgLNode* Tail = *Head;
			while (Tail->next->next != NULL)					//找倒数第二个结点Tail
			{
				Tail = Tail->next;
			}
			free(Tail->next);									//释放尾结点
			Tail->next = NULL;									//并使倒数第二个结点的后续指针置空
		}
	}
}

SgLNode* SGLFind(SgLNode* Head, SGLElemType x)					//链表查找
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

void SGLInsert(SgLNode** Head, SgLNode* pos, SGLElemType x)		//链表中间插入
{
	assert(Head);												//二级指针断言声明，防止链表无效
	if (*Head == NULL && pos == *Head)							//如果链表为空以及插入位置也为空，执行头插
	{
		SGLPushFront(Head, x);
	}
	else if (*Head == NULL && pos != *Head)						//如果链表为空但插入位置不为空，报错
	{
		printf("结点插入位置不合法\n");
		return;
	}
	else														//如果链表不为空
	{
		SgLNode* Prepos = *Head;							//定义找出待插入结点前一结点的临时指针，以头结点地址赋值
		SgLNode* InsertNode = BuyListNode(x);				//将待插入值放到开辟的新节点数值域中
		if (*Head == pos)									//如果前方插入的结点为头结点，则执行头插函数
		{
			SGLPushFront(Head, x);
		}
		else
		{
			while (Prepos->next != pos)						//如果不是头结点，则循环找到插入结点的前一个结点
			{
				Prepos = Prepos->next;
			}
			Prepos->next = InsertNode;						//将前一个结点后插入新结点并连接起来
			InsertNode->next = pos;
		}
	}
}

void SGLErase(SgLNode** Head, SgLNode* pos)						//链表结点擦除
{
	assert(*Head);
	assert(pos);
	SgLNode* Prepos = *Head;									//指向头结点的临时指针，用于找待擦除结点的前一个结点
	SgLNode* tmp = BuyListNode(0);								//待备份的新空节点
	if (pos == *Head)											//当擦除结点为头结点
	{
		tmp = (*Head)->next;									//备份头结点后继结点地址
		free(*Head);											//通过结点指针释放头结点
		*Head = tmp;											//将后继结点地址赋值给新结点成为新头结点
	}
	else if (pos->next == NULL)									//当擦除结点为尾结点
	{
		while (Prepos->next != pos)
		{
			Prepos = Prepos->next;
		}
		free(Prepos->next);
		Prepos->next = NULL;									//但是Prepos->next == pos的后继指针，对它进行置空却可以							
		//free(pos);											//与free(Prepos->next)作用相同，都释放了尾结点
		//pos = NULL;											//该语句不起作用，因为即使尾结点本身置空了，没有实质改变Prepose所指向结点中后继指针的指向，因为pos出栈后被销毁了，所以Prepos->next仍指向已被free空间的随机值
		//														//若要写为此种写法，pos = NULL可以不需要写，而针对实参尾结点后继指针的指向可到外部函数改变其指向
		//Prepos->next = pos;									//实质上改变了结点指针对结点结构体中的后继指针指向，与Prepos->next = NULL;实质上相同
	}
	else														//当擦除结点非首尾结点，而是普通结点
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

void SGLInsertAfter(SgLNode* pos, SGLElemType x)				//链表中间插入（某结点后方）
{
	assert(pos);												//判断pos结点是否存在
	SgLNode* NewNode = BuyListNode(x);							//等待在pos之后插入的新结点
	NewNode->next = pos->next;									//原pos后继改为新结点后继
	pos->next = NewNode;										//pos后继直接指向新结点，完成链接
}

void SGLEraseAfter(SgLNode* pos)								//链表结点擦除（某结点后方）
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
		printf("该值后已无更多元素需要删除，结果仍为：");
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
			printf("没有此结点\n");
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
//		printf("找不到\n");
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
//		printf("空链表\n");
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