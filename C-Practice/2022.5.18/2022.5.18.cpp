#define _CRT_SECURE_NO_WARNINGS 1
#include"SglinkFunc.h"

//6. 环形链表
//描述：给一个头结点head，判断链表是否有环，带环返回true，否则返回false
//注意：带环链表不能遍历，因为可能会死循环
int main()
{
	SgL* n1 = BuyListNode(7);
	SgL* n2 = BuyListNode(7);
	SgL* n3 = BuyListNode(7);
	SgL* n4 = BuyListNode(7);
	SgL* n5 = BuyListNode(7);
	n1->next = n2;
	n2->next = n3;
	n3->next = n4;
	n4->next = n5;
	n5->next = n3;

	//SgL* n1 = BuyListNode(1);

	bool Judge = RoundSgL(n1);
	if (Judge)
	{
		printf("是环形链表\n");
	}
	else
	{
		printf("不是环形链表\n");
	}
	return 0;
}


//5. 相交链表
//描述：给两个单链表头结点a，b，找出并返回两链表相交(即两个链表从某一点开始
//汇集到一起)的起始节点c，若不存在相交节点则返回NULL
//例：[1, 2, 4, 7, 8, 9]和[3, 5, 7, 8, 9]
//返回节点7的地址
//int main()
//{
//	SgL* n1 = BuyListNode(3);
//	SgL* n2 = BuyListNode(5);
//	//SgL* n3 = BuyListNode(7);
//	//SgL* n4 = BuyListNode(8);
//	//SgL* n5 = BuyListNode(9);
//	n1->next = n2;
//	//n2->next = n3;
//	//n3->next = n4;
//	//n4->next = n5;
//
//	SgL* n6 = BuyListNode(1);
//	//SgL* n7 = BuyListNode(2);
//	//SgL* n8 = BuyListNode(4);
//	//SgL* n9 = BuyListNode(7);
//
//	//n6->next = n2;
//	//n7->next = n8;
//	//n8->next = n9;
//	//n9->next = n3;
//
//	printf("原两个链表的结构为：\n");
//	Print(n1);
//	Print(n6);
//	int get = 1;
//	if (CrossOver(n1, n6) != NULL)
//	{
//		get = CrossOver(n1, n6)->data;
//		printf("两链表的相交结点为：%d\n", get);
//	}
//	else
//	{
//		printf("无交点\n");
//	}
//	return 0;
//}

//4. 链表的回文结构
//描述：设计一个时度O(N)，空度O(1)的回文链表结构，给一个链表头指针A，需要返回一个布尔值，代表其是否为回文结构，
//且链表长度 <= 900
//用例：1 - 2 - 2 - 1
//返回：true
//int main()
//{
//	//SgL* n1 = BuyListNode(5);
//	//SgL* n2 = BuyListNode(3);
//	//SgL* n3 = BuyListNode(2);
//	//SgL* n4 = BuyListNode(8);
//	//SgL* n5 = BuyListNode(1);
//	//SgL* n6 = BuyListNode(6);
//
//	SgL* n1 = BuyListNode(1);
//	SgL* n2 = BuyListNode(2);
//	SgL* n3 = BuyListNode(1);
//	//SgL* n4 = BuyListNode(2);
//	//SgL* n5 = BuyListNode(1);
//	//SgL* n6 = BuyListNode(1);
//
//	n1->next = n2;
//	n2->next = n3;
//	//n3->next = n4;
//	//n4->next = n5;
//	//n5->next = n6;
//	printf("原链表的结构为：");
//	Print(n1);
//
//	bool Judge = PalinDrome(n1);
//	if (Judge)
//	{
//		printf("是回文链表\n");
//	}
//	else
//	{
//		printf("不是回文链表\n");
//	}
//	return 0;
//}


//3. 链表分割
//给一链表头指针和值x，将所有小于结点值x的结点排在其余结点前，且不能改变原来数值的相对顺序，返回重排序后头指针
//例：给定链表[5, 3, 2, 8, 1, 6]，x = 7
//输出[5, 3, 2, 1, 6, 8]
//例：给定链表[5, 3, 2, 8, 1, 6]，x = 4
//输出[3, 2, 1, 5, 8，6]
//int main()
//{
//	SgL* n1 = BuyListNode(5);
//	SgL* n2 = BuyListNode(3);
//	SgL* n3 = BuyListNode(2);
//	SgL* n4 = BuyListNode(8);
//	SgL* n5 = BuyListNode(1);
//	SgL* n6 = BuyListNode(6);
//
//	//SgL* n1 = BuyListNode(1);
//	//SgL* n2 = BuyListNode(4);
//	//SgL* n3 = BuyListNode(3);
//	//SgL* n4 = BuyListNode(2);
//	//SgL* n5 = BuyListNode(5);
//	//SgL* n6 = BuyListNode(2);
//
//	//SgL* n1 = BuyListNode(2);
//	//SgL* n2 = BuyListNode(1);
//
//	n1->next = n2;
//	n2->next = n3;
//	n3->next = n4;
//	n4->next = n5;
//	n5->next = n6;
//	printf("原链表的结构为：");
//	Print(n1);
//
//	int x = 7;
//	//int x = 2;
//	printf("分隔数值为%d，分割后的链表为：", x);
//	SgL* Division = SLSlicing(n1, x);
//	Print(Division);
//}



//2. 合并两个有序链表
//描述：将两个升序链表合并为一个新的升序链表并返回
//例：给[1, 2, 4]和[1, 3, 4]，返回[1, 1, 2, 3, 4, 4]
//int main()
//{
//	SgL* n1 = BuyListNode(1);
//	SgL* n2 = BuyListNode(7);
//	SgL* n3 = BuyListNode(10);
//
//	SgL* n4 = BuyListNode(-1);
//	SgL* n5 = BuyListNode(3);
//	SgL* n6 = BuyListNode(4);
//	SgL* n7 = BuyListNode(7);
//
//	//SgL* n1 = BuyListNode(7);
//	//SgL* n2 = BuyListNode(7);
//	//SgL* n3 = BuyListNode(7);
//	//SgL* n4 = BuyListNode(1);
//
//	//SgL* n1 = BuyListNode(10);
//
//	n1->next = n2;
//	n2->next = n3;
//
//	n4->next = n5;
//	n5->next = n6;
//	n6->next = n7;
//	printf("原两个链表的结构为：");
//	Print(n1);
//	Print(n4);
//	printf("合并的两个新有序链表为：");
//	SgL* Merge = Merging2SL(n1, n4);
//	Print(Merge);
//}



//1. 链表中倒数第k个结点
//描述：输入一个链表，输出该链表中倒数第k个结点
//例：输入1， 【1, 2, 3, 4, 5】	输出5			输入3， 【1, 2, 3, 4, 5】		输出3
//int main()
//{
//	SgL* n1 = BuyListNode(1);
//	SgL* n2 = BuyListNode(2);
//	SgL* n3 = BuyListNode(3);
//	SgL* n4 = BuyListNode(4);
//	SgL* n5 = BuyListNode(5);
//	SgL* n6 = BuyListNode(6);
//	SgL* n7 = BuyListNode(7);
//
//	//SgL* n1 = BuyListNode(7);
//	//SgL* n2 = BuyListNode(7);
//	//SgL* n3 = BuyListNode(7);
//	//SgL* n4 = BuyListNode(1);
//
//	//SgL* n1 = BuyListNode(10);
//
//	n1->next = n2;
//	n2->next = n3;
//	n3->next = n4;
//	n4->next = n5;
//	n5->next = n6;
//	n6->next = n7;
//	printf("原链表结构为：");
//	Print(n1);
//	int k = 3;
//	printf("查找到的倒数第%d个结点数值为：%d\n",k, LastKVal(n1, k));
//}