#define _CRT_SECURE_NO_WARNINGS 1
#include"SgL.h"

//��������һ�������ͷ�ڵ� head ��һ������ val ������ɾ���������������� Node.val == val �Ľڵ㣬������ �µ�ͷ�ڵ� ��
//���磺���룺head = [1,2,6,3,4,5,6], val = 6
//�����[1, 2, 3, 4, 5]


int main()
{
	//SgL* n1 = BuyListNode(1);
	//SgL* n2 = BuyListNode(2);
	//SgL* n3 = BuyListNode(3);
	//SgL* n4 = BuyListNode(3);
	//SgL* n5 = BuyListNode(4);
	//SgL* n6 = BuyListNode(5);
	//SgL* n7 = BuyListNode(5);
	//n1->next = n2;
	//n2->next = n3;
	//n3->next = n4;
	//n4->next = n5;
	//n5->next = n6;
	//n6->next = n7;

	//SgL* n1 = BuyListNode(7);
	//SgL* n2 = BuyListNode(7);
	//SgL* n3 = BuyListNode(7);
	//SgL* n4 = BuyListNode(7);
	//n1->next = n2;
	//n2->next = n3;
	//n3->next = n4;

	SgL* n1 = BuyListNode(1);
	SgL* n2 = BuyListNode(2);
	SgL* n3 = BuyListNode(1);
	n1->next = n2;
	n2->next = n3;
	printf("ԭ����ṹΪ��");
	Print(n1);

	////�Ƴ��㷨������1�������������
	int value = 2;
	SgL* NewHead = Remove(n1, value);
	printf("�Ƴ��������ṹΪ��");
	Print(NewHead);
	return 0;
}
