#define _CRT_SECURE_NO_WARNINGS 1
#include"SGL.h"

//5. �����е�����k�����
//����������һ����������������е�����k�����
//��������1�� ��1, 2, 3, 4, 5��	���5			����3�� ��1, 2, 3, 4, 5��		���3
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
	printf("ԭ����ṹΪ��");
	Print(n1);
	int k = 3;
	printf("���ҵ��ĵ�����k�������ֵΪ��%d\n", LastKVal(n1, k));
}



//4. �����м��㡪����������һ��ͷ���Ϊhead�ķǿյ����������м����dataֵ
//���磺������Ϊ1, 2, 3, 4, 5	���Ϊ3
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
//	printf("ԭ����ṹΪ��");
//	Print(n1);
//	printf("���ҵ����м�����ֵΪ��%d\n", FindMid(n1));
//}


//3. �����������㷨2���ı�����ָ��
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
//	printf("ԭ����ṹΪ��");
//	Print(n1);
//	printf("���������ṹ��");
//	SgL* NewHead = ReverseSL2(n1);
//	Print(NewHead);
//}



//2. ��ת/���õ�������������һ��ͷ���head����ת������
//���磺��head = 1,2,3,4,5����ת��head = 5, 4, 3, 2, 1
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
//	printf("ԭ����ṹΪ��");
//	Print(n1);
//	SgL* NewHead = ReverseSL(n1);
//	Print(NewHead);
//}



//1. LeetCode�����Ƴ��㷨������2��������β�巨
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
//	printf("ԭ����ṹΪ��");
//	Print(n1);
//	Etype value = 1;
//	SgL* NewHead = PBackDelete(n1, value);
//	printf("\n�Ƴ�������ṹΪ��");
//	Print(NewHead);
//	return 0;
//}