#define _CRT_SECURE_NO_WARNINGS 1
#include"SGL.h"

//5. 链表中倒数第k个结点
//描述：输入一个链表，输出该链表中倒数第k个结点
//例：输入1， 【1, 2, 3, 4, 5】	输出5			输入3， 【1, 2, 3, 4, 5】		输出3
int main()
{
	SgL* n1 = BuyListNode(1);
	SgL* n2 = BuyListNode(2);
	SgL* n3 = BuyListNode(3);
	SgL* n4 = BuyListNode(4);
	SgL* n5 = BuyListNode(5);
	SgL* n6 = BuyListNode(6);
	SgL* n7 = BuyListNode(7);

	//SgL* n1 = BuyListNode(7);
	//SgL* n2 = BuyListNode(7);
	//SgL* n3 = BuyListNode(7);
	//SgL* n4 = BuyListNode(1);

	//SgL* n1 = BuyListNode(10);

	n1->next = n2;
	n2->next = n3;
	n3->next = n4;
	n4->next = n5;
	n5->next = n6;
	n6->next = n7;
	printf("原链表结构为：");
	Print(n1);
	int k = 3;
	printf("查找到的倒数第k个结点数值为：%d\n", LastKVal(n1, k));
}



//4. 查找中间结点——描述：给一个头结点为head的非空单链表，返回中间结点的data值
//比如：输入结点为1, 2, 3, 4, 5	输出为3
//int main()
//{
//	SgL* n1 = BuyListNode(1);
//	SgL* n2 = BuyListNode(2);
//	SgL* n3 = BuyListNode(3);
//	SgL* n4 = BuyListNode(4);
//	SgL* n5 = BuyListNode(5);
//	SgL* n6 = BuyListNode(6);
//	//SgL* n7 = BuyListNode(7);
//
//	n1->next = n2;
//	n2->next = n3;
//	n3->next = n4;
//	n4->next = n5;
//	n5->next = n6;
//	//n6->next = n7;
//	printf("原链表结构为：");
//	Print(n1);
//	printf("查找到的中间结点数值为：%d\n", FindMid(n1));
//}


//3. 逆序单链表——算法2：改变链表指向
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
//	printf("逆序后链表结构：");
//	SgL* NewHead = ReverseSL2(n1);
//	Print(NewHead);
//}



//2. 反转/逆置单链表，描述：给一个头结点head，反转该链表
//例如：即head = 1,2,3,4,5，反转后head = 5, 4, 3, 2, 1
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
//	//SgL* n4 = BuyListNode(7);
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
//	SgL* NewHead = ReverseSL(n1);
//	Print(NewHead);
//}



//1. LeetCode链表移除算法——法2：新链表尾插法
//int main()
//{
//	SgL* n1 = BuyListNode(1);
//	SgL* n2 = BuyListNode(2);
//	SgL* n3 = BuyListNode(1);
//	SgL* n4 = BuyListNode(3);
//	SgL* n5 = BuyListNode(4);
//	SgL* n6 = BuyListNode(1);
//	SgL* n7 = BuyListNode(1);
//
//	//SgL* n1 = BuyListNode(7);
//	//SgL* n2 = BuyListNode(7);
//	//SgL* n3 = BuyListNode(7);
//	//SgL* n4 = BuyListNode(7);
//
//	n1->next = n2;
//	n2->next = n3;
//	n3->next = n4;
//	n4->next = n5;
//	n5->next = n6;
//	n6->next = n7;
//
//	printf("原链表结构为：");
//	Print(n1);
//	Etype value = 1;
//	SgL* NewHead = PBackDelete(n1, value);
//	printf("\n移除后链表结构为：");
//	Print(NewHead);
//	return 0;
//}