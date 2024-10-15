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

//2. 将数组A中的内容和数组B中的内容进行交换。（数组一样大）
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
//	printf("第一个数组为：");
//	for (int i = 0; i < 10; i++)
//	{
//		printf("%d ", a[i]);
//	}
//	printf("\n");
//	printf("第二个数组为：");
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


//1. 实现函数init() 初始化数组为全0,实现print()  打印数组的每个元素,实现reverse()  函数完成数组元素的逆置。
//void init(int* a)
//{
//	for (int i = 0; i < 10; i++)
//	{
//		a[i] = i;  //若改成0，则把i改为0即可
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