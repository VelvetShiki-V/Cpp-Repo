#define _CRT_SECURE_NO_WARNINGS 1
#include"SglinkFunc.h"

//6. ��������
//��������һ��ͷ���head���ж������Ƿ��л�����������true�����򷵻�false
//ע�⣺���������ܱ�������Ϊ���ܻ���ѭ��
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
		printf("�ǻ�������\n");
	}
	else
	{
		printf("���ǻ�������\n");
	}
	return 0;
}


//5. �ཻ����
//������������������ͷ���a��b���ҳ��������������ཻ(�����������ĳһ�㿪ʼ
//�㼯��һ��)����ʼ�ڵ�c�����������ཻ�ڵ��򷵻�NULL
//����[1, 2, 4, 7, 8, 9]��[3, 5, 7, 8, 9]
//���ؽڵ�7�ĵ�ַ
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
//	printf("ԭ��������ĽṹΪ��\n");
//	Print(n1);
//	Print(n6);
//	int get = 1;
//	if (CrossOver(n1, n6) != NULL)
//	{
//		get = CrossOver(n1, n6)->data;
//		printf("��������ཻ���Ϊ��%d\n", get);
//	}
//	else
//	{
//		printf("�޽���\n");
//	}
//	return 0;
//}

//4. ����Ļ��Ľṹ
//���������һ��ʱ��O(N)���ն�O(1)�Ļ�������ṹ����һ������ͷָ��A����Ҫ����һ������ֵ���������Ƿ�Ϊ���Ľṹ��
//�������� <= 900
//������1 - 2 - 2 - 1
//���أ�true
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
//	printf("ԭ����ĽṹΪ��");
//	Print(n1);
//
//	bool Judge = PalinDrome(n1);
//	if (Judge)
//	{
//		printf("�ǻ�������\n");
//	}
//	else
//	{
//		printf("���ǻ�������\n");
//	}
//	return 0;
//}


//3. ����ָ�
//��һ����ͷָ���ֵx��������С�ڽ��ֵx�Ľ������������ǰ���Ҳ��ܸı�ԭ����ֵ�����˳�򣬷����������ͷָ��
//������������[5, 3, 2, 8, 1, 6]��x = 7
//���[5, 3, 2, 1, 6, 8]
//������������[5, 3, 2, 8, 1, 6]��x = 4
//���[3, 2, 1, 5, 8��6]
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
//	printf("ԭ����ĽṹΪ��");
//	Print(n1);
//
//	int x = 7;
//	//int x = 2;
//	printf("�ָ���ֵΪ%d���ָ�������Ϊ��", x);
//	SgL* Division = SLSlicing(n1, x);
//	Print(Division);
//}



//2. �ϲ�������������
//��������������������ϲ�Ϊһ���µ�������������
//������[1, 2, 4]��[1, 3, 4]������[1, 1, 2, 3, 4, 4]
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
//	printf("ԭ��������ĽṹΪ��");
//	Print(n1);
//	Print(n4);
//	printf("�ϲ�����������������Ϊ��");
//	SgL* Merge = Merging2SL(n1, n4);
//	Print(Merge);
//}



//1. �����е�����k�����
//����������һ����������������е�����k�����
//��������1�� ��1, 2, 3, 4, 5��	���5			����3�� ��1, 2, 3, 4, 5��		���3
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
//	int k = 3;
//	printf("���ҵ��ĵ�����%d�������ֵΪ��%d\n",k, LastKVal(n1, k));
//}