#define _CRT_SECURE_NO_WARNINGS 1
#include"Func.h"
int count = 0;
int main()
{
	char arr[3][3];
	char samp[3][3];
	int ret = 0;
	WelcomeUI();
	scanf("%d", &ret);
	if (ret != 1)
	{
		exit(-1);
	}
	do
	{
		if (ret == 1)
		{
			Sample(samp);
		}
		ChessInit(arr);
		while (ret == 1)
		{
			PlayerRound(arr);
			Print(arr);
			PCRound(arr);
			Print(arr);
			ret = Judge(arr);
			if (ret == 0)
			{
				break;
			}
		}
		count = 0;
		ret = Retry();
	} while (ret == 1);
	return 0;	
}

//2. ������A�е����ݺ�����B�е����ݽ��н�����������һ����
//void init(int* a, int a1[])
//{
//	for (int i = 0; i < 10; i++)
//	{
//		a[i] = i;
//	}
//	for (int i = 0; i < 10; i++)
//	{
//		a1[i] = 10 - i;
//	}
//}
//void print(int a[], int a1[])
//{
//	printf("��һ������Ϊ��");
//	for (int i = 0; i < 10; i++)
//	{
//		printf("%d ", a[i]);
//	}
//	printf("\n");
//	printf("�ڶ�������Ϊ��");
//	for (int i = 0; i < 10; i++)
//	{
//		printf("%d ", a1[i]);
//	}
//	printf("\n\n");
//}
//void swap(int* a, int* b, int right)
//{
//	int left = 0, tmp = 0;
//	while (left < right)
//	{
//		tmp = a[left];
//		a[left] = b[left];
//		b[left] = tmp;
//		left++;
//	}
//}
//int main()
//{
//	int arr[10], arr1[10];
//	init(arr, arr1);
//	print(arr, arr1);
//	int end = sizeof(arr) / sizeof(arr[0]);
//	swap(arr, arr1, --end);
//	print(arr, arr1);
//	return 0;
//}


//1. ʵ�ֺ���init() ��ʼ������Ϊȫ0,ʵ��print()  ��ӡ�����ÿ��Ԫ��,ʵ��reverse()  �����������Ԫ�ص����á�
//void init(int* a)
//{
//	for (int i = 0; i < 10; i++)
//	{
//		a[i] = i;  //���ĳ�0�����i��Ϊ0����
//	}
//}
//void print(int a[])
//{
//	for (int i = 0; i < 10; i++)
//	{
//		printf("%d ", a[i]);
//	}
//	printf("\n");
//}
//void reverse(int a[], int right)
//{
//	int left = 0, tmp = 0;
//	while (left < right)
//	{
//		tmp = a[left];
//		a[left] = a[right];
//		a[right] = tmp;
//		left++;
//		right--;
//	}
//}
//int main()
//{
//	int arr[10];
//	init(arr);
//	print(arr);
//	int end = sizeof(arr) / sizeof(arr[0]);
//	reverse(arr, --end);
//	print(arr);
//	return 0;
//}