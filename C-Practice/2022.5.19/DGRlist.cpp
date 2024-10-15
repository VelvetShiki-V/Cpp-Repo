#define _CRT_SECURE_NO_WARNINGS 1
#include"DGR.h"
//˫���ͷ���ڱ���ѭ����������������

void DGRTest_1()
{
	DGR* GuardHead = DGRInit();						//��ʼ���ڱ�ͷ���
	PushBack(GuardHead, 1);							//ͷ����β��
	PushBack(GuardHead, 2);
	PushBack(GuardHead, 3);
	PushBack(GuardHead, 4);
	printf("β���ԭ����ṹ��");
	Print(GuardHead);

	printf("ͷ�������ṹ��");
	PushFront(GuardHead, 0);						//ͷ����ͷ��
	PushFront(GuardHead, -1);
	PushFront(GuardHead, -2);
	PushFront(GuardHead, -3);
	Print(GuardHead);
}

void DGRTest_2()
{
	DGR* GuardHead = DGRInit();						//��ʼ���ڱ�ͷ���
	PushBack(GuardHead, 1);							//ͷ����β��
	PushBack(GuardHead, 2);
	PushBack(GuardHead, 3);
	PushBack(GuardHead, 4);
	PushFront(GuardHead, 1);						//ͷ����ͷ��
	PushFront(GuardHead, 2);						
	PushFront(GuardHead, 3);						
	PushFront(GuardHead, 4);						
	printf("β���ͷ���ԭ����ṹ��");
	Print(GuardHead);

	printf("3��βɾ������ṹ��");
	PopBack(GuardHead);
	PopBack(GuardHead);
	PopBack(GuardHead);
	Print(GuardHead);
	printf("��4��ͷɾ������ṹ��");
	PopFront(GuardHead);
	PopFront(GuardHead);
	PopFront(GuardHead);
	PopFront(GuardHead);
	PopFront(GuardHead);							//�����ڱ�λһ��ͷ���
	//PopFront(GuardHead);							//��ɾһ�Σ���û��������ڱ�ͷ���ɾ��������ָ���ΪҰָ��
	Print(GuardHead);
}

void DGRTest_3()
{
	DGR* GuardHead = DGRInit();						//��ʼ���ڱ�ͷ���
	PushBack(GuardHead, 3);							//ͷ����β��
	PushBack(GuardHead, 4);
	PushFront(GuardHead, 2);						//ͷ����ͷ��
	PushFront(GuardHead, 1);
	printf("β���ͷ���ԭ����ṹ��");
	Print(GuardHead);

	//�м����/ͷ��/β��
	printf("3���30��");
	DGRInsert(GuardHead->prev, 30);
	Print(GuardHead);
	printf("2ǰ��10��");
	DGRInsert(GuardHead->next->next, 10);
	Print(GuardHead);
	printf("ͷ��50��");
	DGRInsert(GuardHead->next, 50);
	Print(GuardHead);
	printf("β��90��");
	DGRInsert(GuardHead, 90);
	Print(GuardHead);

	//�м����/ͷɾ/βɾ
	printf("1���10��");
	DGRErase(GuardHead->next->next->next);
	Print(GuardHead);
	printf("ɾͷ��");
	DGRErase(GuardHead->next);
	Print(GuardHead);
	printf("ɾβ��");
	DGRErase(GuardHead->prev);
	Print(GuardHead);
	printf("ɾ��ֻ���ڱ�ͷ��㣺");
	DGRErase(GuardHead->next);
	DGRErase(GuardHead->next);
	DGRErase(GuardHead->next);
	DGRErase(GuardHead->next);
	DGRErase(GuardHead->next);
	Print(GuardHead);
	//printf("��ɾ��");
	//DGRErase(GuardHead->next);
	//Print(GuardHead);
}


int main()
{
	//DGRTest_1();
	//DGRTest_2();
	DGRTest_3();
	return 0;
}