#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>

int main()   //消失的数字：异或法，时间复杂度O(N)
{
	int arr[10] = {0}, sample[11]{0,1,2,3,4,5,6,7,8,9,10}, i = 0, x = 0;
	for (i; i < 10; i++)
	{
		scanf("%d", &arr[i]);
	}
	for (i = 0; i < 10; i++)  //先与输入数异或
	{
		x ^= arr[i];
	}
	for (i = 0; i < 11; i++)  //再与范围内所有数字异或
	{
		x ^= sample[i];
	}
	printf("消失的数字为：%d\n", x);  
	return 0;
}



//int main()      //消失的数字——找-1法：时间复杂度为O(N)的解法，不用排序
//{
//	int arr[11] = { -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1 }, a, b, c, d, e, f, g, h, i, j, m = 0;
//	printf("在0和10之间输入10个数,：");
//	scanf("%d %d %d %d %d %d %d %d %d %d", &a, &b, &c, &d, &e, &f, &g, &h, &i, &j);
//	arr[a] = a;
//	arr[b] = b;
//	arr[c] = c;
//	arr[d] = d;
//	arr[e] = e;
//	arr[f] = f;
//	arr[g] = g;
//	arr[h] = h;
//	arr[i] = i;
//	arr[j] = j;
//	while (arr[m] != -1)
//	{
//		m++;
//	}
//	printf("消失的数字为:%d\n", m);
//	return 0;
//}


//int arrangement(int(*a)[4], int* b)      //暴力找数法
//{
//	int i, j, k, tmp = 0;
//	printf("%d\n", k = sizeof(*a) / sizeof(*a[0]));
//	k--;
//	for (i = 0; i < k; i++)
//	{
//		for (j = 0; j < k; j++)
//		{
//			if (b[j] > b[j + 1])
//			{
//				tmp = b[j];
//				b[j] = b[j + 1];
//				b[j + 1] = tmp;
//			}
//		}
//	}
//	printf("排序好的数组(形参)：%d %d %d %d\n", b[0], b[1], b[2], b[3]);
//	return k;
//}
//
//void find(int* a, int b)
//{
//	int i;
//	for (i = 0; i < b; i++)
//	{
//		if (a[i + 1] - a[i] == 1)
//		{
//			continue;
//		}
//		else
//		{
//			printf("消失的数字为%d\n", a[i] + 1);
//		}
//	}
//}
//
//int main()      //消失的数字：输入一串连续数（其中一个不存在），找出那个数
//{
//	int arr[4] = { 0 };
//	printf("请输入5个有序或无序数中的4个数：");
//	scanf("%d %d %d %d", &arr[0], &arr[1], &arr[2], &arr[3]);
//	int k = arrangement(&arr, arr);
//	printf("排序好的数组(main)：%d %d %d %d\n", arr[0], arr[1], arr[2], arr[3]);
//	find(arr, k);
//	return 0;
//}

//void fun(int** a)
//{
//	;
//}
//int main()      //数组指针
//{
//	int arr[4] = { 0 }, i = 0;
//	printf("请输入4个数：");
//	scanf("%d %d %d %d", &arr[0], &arr[1], &arr[2], &arr[3]);
//	printf("%d\n", i = sizeof(arr) / sizeof(arr[0]));
//	int(*a)[4] = &arr;
//	fun(&arr);
//	printf("%d\n", i = sizeof(*a) / sizeof(*a[0]));
//	return 0;
//}