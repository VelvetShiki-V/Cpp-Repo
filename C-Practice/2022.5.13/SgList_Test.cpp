#define _CRT_SECURE_NO_WARNINGS 1
#include"SgList.h"
void SingleList_Test1_Define_Print()
{
	SgLNode* n1 = (SgLNode*)malloc(sizeof(SGLElemType));		//每个结点的结构体空间开辟
	assert(n1);
	SgLNode* n2 = (SgLNode*)malloc(sizeof(SGLElemType));
	assert(n2);
	SgLNode* n3 = (SgLNode*)malloc(sizeof(SGLElemType));
	assert(n3);
	SgLNode* n4 = (SgLNode*)malloc(sizeof(SGLElemType));
	assert(n4);

	n1->next = n2;												//结构体中的指针域由指向的下一结点结构体地址赋值									
	n2->next = n3;
	n3->next = n4;
	n4->next = NULL;

	n1->data = 1;												//每个结点的数值域赋值
	n2->data = 2;
	n3->data = 3;
	n4->data = 4;

	printf("Test1：");
	SGLPrint(n1);												//从首节点到尾结点遍历打印数值域的值
}

void SingleList_Test2_PUSHBACK()
{
	SgLNode* n1 = (SgLNode*)malloc(sizeof(SGLElemType));
	assert(n1);
	SgLNode* n2 = (SgLNode*)malloc(sizeof(SGLElemType));
	assert(n2);
	n1->next = n2;																				
	n2->next = NULL;
	n1->data = 1;												
	n2->data = 2;
	SGLPushBack(&n1, 3);									
	SGLPushBack(&n1, 4);
	printf("Test2.0：");
	SGLPrint(n1);												//打印链表数值

	SgLNode* n3 = NULL;											//要改变首节点地址，需要传该指针变量的地址，否则形参指针无法改变实参地址
	SGLPushBack(&n3, 1);
	SGLPushBack(&n3, 2);
	printf("Test2.1：");
	SGLPrint(n3);												//打印链表数值
}

void SingleList_Test3_PUSHFRONT()
{
	SgLNode* n1 = BuyListNode(1);
	SgLNode* n2 = BuyListNode(2);
	n1->next = n2;
	printf("Test3.0：");
	SGLPrint(n1);

	SgLNode* n3 = NULL;
	SGLPushFront(&n3, 1);
	SGLPushFront(&n3, 0);
	SGLPushFront(&n3, -2);
	SGLPushFront(&n3, -3);
	SGLPushFront(&n3, -4);
	SGLPushFront(&n3, -5);


	printf("Test3.1：");
	SGLPrint(n3);

	printf("将链表前三个值头删：");
	SGLPopFront(&n3);
	SGLPopFront(&n3);
	SGLPopFront(&n3);
	SGLPrint(n3);

	printf("将链表所有值头删：");
	SGLPopFront(&n3);
	SGLPopFront(&n3);
	SGLPopFront(&n3);
	//SGLPopFront(&n3);					//头删不能多删，因为若链表为空，无法通过原头结点指针访问其后续结点地址，即访问了空地址，assert报错
	SGLPrint(n3);
}

void SingleList_Test4_POPBACK()
{
	SgLNode* n1 = BuyListNode(1);
	SgLNode* n2 = BuyListNode(2);
	SgLNode* n3 = BuyListNode(3);
	SgLNode* n4 = BuyListNode(4);
	n1->next = n2;
	n2->next = n3;
	n3->next = n4;
	printf("原链表结构：");
	SGLPrint(n1);
	SGLPopBack(&n1);						//尾删尾结点n4
	SGLPopBack(&n1);						//尾删尾结点n3
	SGLPopBack(&n1);						//尾删尾结点n2
	SGLPopBack(&n1);						//尾删尾结点n1，成为空链表
	//SGLPopBack(&n1);						//尾删空链表，报错
	SGLPrint(n1);
}

void SingleList_Test5_FIND_MODIFY()
{
	SgLNode* n1 = BuyListNode(1);
	SgLNode* n2 = BuyListNode(2);
	SgLNode* n3 = BuyListNode(3);
	SgLNode* n4 = BuyListNode(4);
	SgLNode* n5 = BuyListNode(5);
	n1->next = n3;
	n3->next = n2;
	n2->next = n5;
	n5->next = n4;
	printf("原链表结构：");
	SGLPrint(n1);

	//查找一个值
	SgLNode* ret = SGLFind(n1, 5);					//需要查找和修改的值为5
	if (ret == NULL)
	{
		printf("该值不存在。\n");
	}
	else
	{
		printf("该值为：%d\n", ret->data);
		printf("该值第一次出现的内存地址为：%p\n", ret);
	}

	//根据查找到的值修改该值
	SGLElemType x = 50;
	if (ret == NULL)
	{
		printf("该值不存在。\n");
	}
	else
	{
		ret->data = x;
		printf("该值已被修改，新链表值为：");
		SGLPrint(n1);
	}
}

void SingleList_Test6_INSERT_ERASE()
{
	SgLNode* n1 = BuyListNode(1);
	SgLNode* n2 = BuyListNode(2);
	SgLNode* n3 = BuyListNode(3);
	SgLNode* n4 = BuyListNode(4);
	SgLNode* n5 = BuyListNode(5);
	n1->next = n2;
	n2->next = n3;
	n3->next = n4;
	n4->next = n5;
	printf("原链表结构：");
	SGLPrint(n1);

	//某个位置前插入一个值
	SGLInsert(&n1, n3, 8);					//n3结点前插入一个结点，其中新节点数据域为8
	printf("n3前插一个8：");
	SGLPrint(n1);
	SGLInsert(&n1, n5, 10);					//n5结点前插入一个结点，其中新节点数据域为10
	printf("n5前插一个10：");
	SGLPrint(n1);

	SGLInsert(&n1, n1, 0);					//头结点前插入值
	printf("头结点前插一个0：");
	SGLPrint(n1);
	SGLInsert(&n1, n1, 77);					//头结点前再插入值
	printf("头结点前插一个77：");
	SGLPrint(n1);

	//SGLInsert(&n1, NULL, 999);			//尾结点后插入值，虽然可以，但是不符合标准的用法，尾插应用尾插函数PushBack，而不是在NULL位置上建新节点
	//printf("尾结点后插入值999：");
	//SGLPrint(n1);

	//擦除一个结点
	SGLErase(&n1, n5);
	//n4->next->next = NULL;				//需要注意尾结点释放后，改变形参pos的值置空（无效），而倒数第二个结点后继指针指向的值置空（有效）
	printf("擦除尾结点：");
	SGLPrint(n1);
	SGLErase(&n1, n3);
	printf("擦除n3结点：");
	SGLPrint(n1);
	SGLErase(&n1, n1);
	printf("擦除头结点：");
	SGLPrint(n1);
	SGLErase(&n1, n1);
	printf("再次擦除头结点：");
	SGLPrint(n1);
}

void SingleList_Test7_Insert_Erase_After()
{
	SgLNode* n1 = BuyListNode(5);
	SgLNode* n2 = BuyListNode(3);
	SgLNode* n3 = BuyListNode(2);
	SgLNode* n4 = BuyListNode(1);
	SgLNode* n5 = BuyListNode(4);
	n4->next = n3;
	n3->next = n2;
	n2->next = n5;
	n5->next = n1;
	printf("原链表结构：");
	SGLPrint(n4);

	//某位置后方插入
	printf("在3后插一个10：");
	SGLInsertAfter(n2, 10);
	SGLPrint(n4);

	printf("在尾结点5后插一个20：");
	SGLInsertAfter(n1, 20);
	SGLPrint(n4);

	//在某位置后方擦除
	printf("在4后方擦除元素：");
	SGLEraseAfter(n5);
	SGLPrint(n4);

	printf("在尾结点20后擦除元素：");
	SGLEraseAfter(n5->next);
	SGLPrint(n4);
}


int main()
{
	//SingleList_Test1_Define_Print();
	//SingleList_Test2_PUSHBACK();
	//SingleList_Test3_PUSHFRONT();
	//SingleList_Test4_POPBACK();
	//SingleList_Test5_FIND_MODIFY();
	//SingleList_Test6_INSERT_ERASE();
	SingleList_Test7_Insert_Erase_After();
	return 0;
}