#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>

int main()   //
{
	int a, b, c[1000] = { 0 }, d[1000] = { 0 }, count = 0, count1 = 0, i, j;
	scanf("%d %d", &a, &b);    //两个整型用空格分开输入
	for (i = 1; i <= a; i++)  //找a的全部因子
	{
		if (a % i == 0)
		{
			c[count] = i;
			count++;
		}
	}
	for (i = 1; i <= b; i++)  //b的全部因子
	{
		if (b % i == 0)
		{
			d[count1] = i;
			count1++;
		}
	}
	int tmp = --count1;
	for (i = --count; i >= 0; i--)  //找a和b的最大公因子
	{
		for (j = tmp; j >= 0; j--)
		{
			if (c[i] == d[j])
			{
				printf("最大公约数为%d\n", c[i]);
				return 0;
			}
		}
	}
	getchar;
	return 0;
}

//int a, b;

//if(a%b)
//char y = 513;      //超过无符号char的0000 0000下边界，向上边界溢出循环
//printf("%d\n", y);

//int main()   // 100内3的倍数数输出
//{
//	for (int i = 3; i <= 100; i+=3)
//	{
//		printf("%d ", i);
//	}
//	return 0;
//}


//void arrange(int* a)  //冒泡排序
//{
//	int temp, i;
//	for (i = 0; i < 2; i++)
//	{
//		for (int j = 0; j < 2; j++)
//		{
//			if (a[j] < a[j + 1])
//			{
//				temp = a[j];
//				a[j] = a[j + 1];
//				a[j + 1] = temp;
//			}
//			else
//			{
//				continue;
//			}
//		}
//	}
//	for (i = 0; i < 3; i++)
//	{
//		printf("%d ", a[i]);
//	}
//	
//
//}
//int main()   //三整数从大到小输出
//{
//	int arr[3];
//	for (int i = 0; i < 3; i++)
//	{
//		scanf("%d", &arr[i]);
//	}
//	//int max = arr[0] > arr[1] ? arr[0] : arr[1];    // 头晕写法
//	//int temp = arr[0] + arr[1] - max;
//	//int maxmax = max > arr[2] ? max : arr[2];
//	//int temp2 = max + arr[2] - maxmax;
//	//int mid = temp > temp2 ? temp : temp2;
//	//int min = temp + temp2 - mid;
//	//printf("%d %d %d", maxmax, mid, min);
//	//写法2
//	arrange(arr);
//	return 0;
//}