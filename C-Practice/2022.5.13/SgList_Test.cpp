#define _CRT_SECURE_NO_WARNINGS 1
#include"SgList.h"
void SingleList_Test1_Define_Print()
{
	SgLNode* n1 = (SgLNode*)malloc(sizeof(SGLElemType));		//ÿ�����Ľṹ��ռ俪��
	assert(n1);
	SgLNode* n2 = (SgLNode*)malloc(sizeof(SGLElemType));
	assert(n2);
	SgLNode* n3 = (SgLNode*)malloc(sizeof(SGLElemType));
	assert(n3);
	SgLNode* n4 = (SgLNode*)malloc(sizeof(SGLElemType));
	assert(n4);

	n1->next = n2;												//�ṹ���е�ָ������ָ�����һ���ṹ���ַ��ֵ									
	n2->next = n3;
	n3->next = n4;
	n4->next = NULL;

	n1->data = 1;												//ÿ��������ֵ��ֵ
	n2->data = 2;
	n3->data = 3;
	n4->data = 4;

	printf("Test1��");
	SGLPrint(n1);												//���׽ڵ㵽β��������ӡ��ֵ���ֵ
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
	printf("Test2.0��");
	SGLPrint(n1);												//��ӡ������ֵ

	SgLNode* n3 = NULL;											//Ҫ�ı��׽ڵ��ַ����Ҫ����ָ������ĵ�ַ�������β�ָ���޷��ı�ʵ�ε�ַ
	SGLPushBack(&n3, 1);
	SGLPushBack(&n3, 2);
	printf("Test2.1��");
	SGLPrint(n3);												//��ӡ������ֵ
}

void SingleList_Test3_PUSHFRONT()
{
	SgLNode* n1 = BuyListNode(1);
	SgLNode* n2 = BuyListNode(2);
	n1->next = n2;
	printf("Test3.0��");
	SGLPrint(n1);

	SgLNode* n3 = NULL;
	SGLPushFront(&n3, 1);
	SGLPushFront(&n3, 0);
	SGLPushFront(&n3, -2);
	SGLPushFront(&n3, -3);
	SGLPushFront(&n3, -4);
	SGLPushFront(&n3, -5);


	printf("Test3.1��");
	SGLPrint(n3);

	printf("������ǰ����ֵͷɾ��");
	SGLPopFront(&n3);
	SGLPopFront(&n3);
	SGLPopFront(&n3);
	SGLPrint(n3);

	printf("����������ֵͷɾ��");
	SGLPopFront(&n3);
	SGLPopFront(&n3);
	SGLPopFront(&n3);
	//SGLPopFront(&n3);					//ͷɾ���ܶ�ɾ����Ϊ������Ϊ�գ��޷�ͨ��ԭͷ���ָ��������������ַ���������˿յ�ַ��assert����
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
	printf("ԭ����ṹ��");
	SGLPrint(n1);
	SGLPopBack(&n1);						//βɾβ���n4
	SGLPopBack(&n1);						//βɾβ���n3
	SGLPopBack(&n1);						//βɾβ���n2
	SGLPopBack(&n1);						//βɾβ���n1����Ϊ������
	//SGLPopBack(&n1);						//βɾ����������
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
	printf("ԭ����ṹ��");
	SGLPrint(n1);

	//����һ��ֵ
	SgLNode* ret = SGLFind(n1, 5);					//��Ҫ���Һ��޸ĵ�ֵΪ5
	if (ret == NULL)
	{
		printf("��ֵ�����ڡ�\n");
	}
	else
	{
		printf("��ֵΪ��%d\n", ret->data);
		printf("��ֵ��һ�γ��ֵ��ڴ��ַΪ��%p\n", ret);
	}

	//���ݲ��ҵ���ֵ�޸ĸ�ֵ
	SGLElemType x = 50;
	if (ret == NULL)
	{
		printf("��ֵ�����ڡ�\n");
	}
	else
	{
		ret->data = x;
		printf("��ֵ�ѱ��޸ģ�������ֵΪ��");
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
	printf("ԭ����ṹ��");
	SGLPrint(n1);

	//ĳ��λ��ǰ����һ��ֵ
	SGLInsert(&n1, n3, 8);					//n3���ǰ����һ����㣬�����½ڵ�������Ϊ8
	printf("n3ǰ��һ��8��");
	SGLPrint(n1);
	SGLInsert(&n1, n5, 10);					//n5���ǰ����һ����㣬�����½ڵ�������Ϊ10
	printf("n5ǰ��һ��10��");
	SGLPrint(n1);

	SGLInsert(&n1, n1, 0);					//ͷ���ǰ����ֵ
	printf("ͷ���ǰ��һ��0��");
	SGLPrint(n1);
	SGLInsert(&n1, n1, 77);					//ͷ���ǰ�ٲ���ֵ
	printf("ͷ���ǰ��һ��77��");
	SGLPrint(n1);

	//SGLInsert(&n1, NULL, 999);			//β�������ֵ����Ȼ���ԣ����ǲ����ϱ�׼���÷���β��Ӧ��β�庯��PushBack����������NULLλ���Ͻ��½ڵ�
	//printf("β�������ֵ999��");
	//SGLPrint(n1);

	//����һ�����
	SGLErase(&n1, n5);
	//n4->next->next = NULL;				//��Ҫע��β����ͷź󣬸ı��β�pos��ֵ�ÿգ���Ч�����������ڶ��������ָ��ָ���ֵ�ÿգ���Ч��
	printf("����β��㣺");
	SGLPrint(n1);
	SGLErase(&n1, n3);
	printf("����n3��㣺");
	SGLPrint(n1);
	SGLErase(&n1, n1);
	printf("����ͷ��㣺");
	SGLPrint(n1);
	SGLErase(&n1, n1);
	printf("�ٴβ���ͷ��㣺");
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
	printf("ԭ����ṹ��");
	SGLPrint(n4);

	//ĳλ�ú󷽲���
	printf("��3���һ��10��");
	SGLInsertAfter(n2, 10);
	SGLPrint(n4);

	printf("��β���5���һ��20��");
	SGLInsertAfter(n1, 20);
	SGLPrint(n4);

	//��ĳλ�ú󷽲���
	printf("��4�󷽲���Ԫ�أ�");
	SGLEraseAfter(n5);
	SGLPrint(n4);

	printf("��β���20�����Ԫ�أ�");
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