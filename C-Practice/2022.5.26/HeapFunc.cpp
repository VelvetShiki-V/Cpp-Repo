#define _CRT_SECURE_NO_WARNINGS 1
#include"HeapFunc.h"

void Test_1()
{
	HP heap;
	HPInit(&heap);
	HP* hp = &heap;
	HPEtype a[] = { 3,20,8,6,1,4,62,43,23,12,10,77,30 };
	int sz = sizeof(a) / sizeof(a[0]);
	for (int i = 0; i < sz; i++)
	{
		SmHPPush(hp, a[i]);
	}
	printf("�۲�С�ѵ�����ṹ��˳���:");
	for (int i = 0; i < sz; i++)
	{
		printf("%d ", hp->arr[i]);
	}
	printf("\n�����ѣ�С�ѱ�����ͬ�������ӡ����գ���");		//�㷨ʱ�临�Ӷ�O(N^2)����Ϊÿ��ȡ��ȥ����Ҫ�����Ŷ�
	SmPrint(hp);
	HPDestroy(hp);
}

void Test_2()
{
	HP heap;
	HPInit(&heap);
	HP* hp = &heap;
	HPEtype a[] = { 3,20,8,6,1,4,62,43,23,12,10,77,30 };
	int sz = sizeof(a) / sizeof(a[0]);
	printf("�۲���������ṹ��˳�����");
	for (int i = 0; i < sz; i++)
	{
		BigHPPush(hp, a[i]);
	}
	for (int i = 0; i < sz; i++)
	{
		printf("%d ", hp->arr[i]);
	}
	printf("\n�����ѣ���ѱ�����ͬ�������ӡ����գ���");		//�㷨ʱ�临�Ӷ�O(N^2)����Ϊÿ��ȡ��ȥ����Ҫ�����Ŷ�
	BigPrint(hp);
	printf("��ʱ�ѵ�Ԫ�ظ�����%d\n", HPSize(hp));
	printf("��ʱ�ĶѶ�Ԫ�أ�%d\n", HPTop(hp));
	HPDestroy(hp);
}

void Test_3()
{
	HP heap;
	HPInit(&heap);
	HP* hp = &heap;
	HPEtype a[] = { 83, 49,72,0,5,2,98,37,10,8,5,2,1,7,3,5,0,2 };
	int sz = sizeof(a) / sizeof(a[0]);
	printf("���򽨴��\n");
	for (int i = 0; i < sz; i++)
	{
		BigHPPush(hp, a[i]);
	}
	printf("��ѽ��ɺ�Ľṹ��");
	for (int i = 0; i < sz; i++)
	{
		printf("%d ", hp->arr[i]);
	}
	printf("\n�۲�������㷨�����飺");
	HPSortAscend(hp);
	for (int i = 0; i < sz; i++)
	{
		printf("%d ", hp->arr[i]);
	}

	//printf("�۲�ѽ����㷨�����飺");
	//HPSortDescend(hp);						//����
	//for (int i = 0; i < sz; i++)
	//{
	//	printf("%d ", hp->arr[i]);
	//}
}

int main()
{
	//Test_1();			//С�Ѵ洢�ͱ�����ӡ
	//Test_2();			//��Ѵ洢�ͱ�����ӡ
	Test_3();			//������
	//Test_4();			//�ѽ���
	return 0;
}