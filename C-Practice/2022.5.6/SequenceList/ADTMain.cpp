#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include"FuncDeclare.h"

void Delete(SL* ps)
{
	PopBack(ps);
}

void print(SL ps)
{
	int i = 0;
	for (i = 0; i < ps.size; i++)
	{
		printf("%d ", ps.arr[i]);
	}
	printf("\n");
}

void Push1(SL ps1)
{
	PushBack(&ps1, 1);						//��˳������ʼ������β�庯����û�п���capacity����Խ��
	PushBack(&ps1, 3);
	PushBack(&ps1, 2);
	PushBack(&ps1, 4);
	PushBack(&ps1, 7);
	PushBack(&ps1, 6);
	//βɾ����
	Delete(&ps1);
	Delete(&ps1);
	//Delete(&ps1);							//����βɾʹsize����Խ��Ч��
	//Delete(&ps1);
	//Delete(&ps1);
	//Delete(&ps1);
	//Delete(&ps1);
	//Delete(&ps1);
	//Delete(&ps1);
	PushBack(&ps1, 1);
	PushBack(&ps1, 1);
	PushBack(&ps1, 1);
	print(ps1);
	//��̬���ٵ�˳����ͷ�����
	SLDestroy(&ps1);
}

void Push2(SL ps2)
{
	PushFront(&ps2, 5);
	PushFront(&ps2, 4);
	PushFront(&ps2, 3);
	PushFront(&ps2, 2);
	PushFront(&ps2, 1);
	PushFront(&ps2, 0);
	//βɾ����
	Delete(&ps2);
	print(ps2);
	SLDestroy(&ps2);
}

void DeleteFront(SL ps3)
{
	PushBack(&ps3, 8);
	PushBack(&ps3, 9);
	PushBack(&ps3, 10);
	PushFront(&ps3, 6);
	PushFront(&ps3, 5);
	PushFront(&ps3, 4);
	PopFront(&ps3);
	PopFront(&ps3);
	PopFront(&ps3);
	PopFront(&ps3);
	PopFront(&ps3);
	PopFront(&ps3);
	//PopFront(&ps3);
	PushFront(&ps3, 1);
	print(ps3);
	SLDestroy(&ps3);
}

int main()
{
	//�ṹ���������ͳ�ʼ��
	SL s1, s2, s3;							
	//SLInit(s1);							//��ֵд��������ı���Main�ﶨ�崫����ʵ������ֵ
	SLInit(&s1);							//��ַд��������ͨ����ʼ�����������øı�ʵ��s1������������size��capacityֵ
	SLInit(&s2);
	SLInit(&s3);

	//β�����
	Push1(s1);

	//ͷ�����
	Push2(s2);

	//ͷɾ����
	DeleteFront(s3);

	return 0;
}