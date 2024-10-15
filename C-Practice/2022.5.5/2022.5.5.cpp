#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<math.h>
//9. 打印乘法口诀表，口诀表的行数和列数自己指定
int main()
{
	int i, j, a;
	scanf("%d", &a);
	for (i = 1; i <= a; i++)
	{
		for (j = 1; j <= i; j++)
		{
			printf("%d x %d = %d  ", i, j, i * j);
			if (j == i)
			{
				printf("\n");
			}
		}
		printf("\n");
	}
	return 0;
}


//8. 实现函数判断year是不是润年
//int main()
//{
//	int i;
//	while (scanf("%d", &i) != EOF)
//	{
//		if ((i) % 4 == 0 && (i) % 100 != 0)
//		{
//			printf("%d是闰年\n", i);
//		}
//		else if ((i) % 400 == 0)
//		{
//			printf("%d是闰年\n", i);
//		}
//		else
//		{
//			printf("%d不是闰年\n", i);
//		}
//	}
//	return 0;
//}



//7. 打印100~200素数，并输入一个数判断其是否为素数
//void primeTest(int a)
//{
//	int j;
//	for (j = 2; j <= sqrt(a); j++)
//	{
//		if (a % j == 0)
//		{
//			break;
//		}
//	}
//	if (j > sqrt(a))
//	{
//		printf("%d是一个素数\n", a);
//	}
//	else
//	{
//		printf("%d不是一个素数\n", a);
//	}
//}
//int main()
//{
//	int num = 201, j;
//	for (int i = 100; i < num; i++)
//	{
//		for (j = 2; j <= sqrt(i); j++)
//		{
//			if (i % j == 0)
//			{
//				break;
//			}
//		}
//		if (j > sqrt(i))
//		{
//			printf("%d ",i);
//		}
//	}
//	here:
//	printf("\n请输入一个数作判断：");
//	scanf("%d", &num);
//	primeTest(num);
//	goto here;
//	return 0;
//}


//6. 在屏幕上输出9*9乘法口诀表
//int main()
//{
//	int i, j;
//	for (i = 1; i <= 9; i++)
//	{
//		for (j = 1; j <= i; j++)
//		{
//			printf("%d x %d = %d  ", i, j, i * j);
//			if (j == i)
//			{
//				printf("\n");
//			}
//		}
//		printf("\n");
//	}
//	return 0;
//}


//5. 求10个整数中最大值
//void arrangement(int* a, int b)
//{
//	int i, j, tmp;
//	for (i = 0; i < b - 1; i++)
//	{
//		for (j = 0; j < b - 1; j++)
//		{
//			if (a[j] > a[j + 1])
//			{
//				tmp = a[j];
//				a[j] = a[j + 1];
//				a[j + 1] = tmp;
//			}
//			else
//			{
//				continue;
//			}
//		}
//	}
//}
//int main()
//{
//	int i = 0, arr[10] = { 0 }, j;
//	int* k = &i;
//	printf("输入10个整数：\n");
//	while (i < 10)
//	{
//		scanf("%d", &arr[i]);
//		i++;
//	}
//	j = sizeof(arr) / sizeof(arr[0]);
//	arrangement(arr, j);
//	i = 0;
//	while (i < 10)
//	{
//		printf("%d ", arr[i]);
//		i++;
//	}
//	printf("其中最大值为：%d\n", arr[9]);
//	return 0;
//}


//4. 计算1/1-1/2+1/3-1/4+1/5 …… + 1/99 - 1/100 的值，打印出结果
//int main()
//{
//	int i;
//	float j = 0.0, sum = 0.0;
//	for (i = 1; i < 101; i++)
//	{
//		j = 1.0/i;
//		if (i % 2 == 0)
//		{
//			j = -j;
//		}
//		sum += j;
//		printf("%f  " , j);
//	}
//	printf("\n最终结果为%f\n", sum);
//	return 0;
//}



//3. 编写程序数一下 1到 100 的所有整数中出现多少个数字9
//int main()
//{
//	int range = 101, count = 0, tmp;
//	for (int i = 9; i < range; i++)
//	{
//		tmp = i;
//		if (i % 10 == 9)
//		{
//			count++;
//		}
//		tmp /= 10;
//		if (tmp % 10 == 9)
//		{
//			count++;
//		}
//	}
//	printf("出现了%d次9\n", count);
//	return 0;
//}


//2. 打印100~200素数
//int main()
//{
//	int num = 201, j;
//	for (int i = 100; i < num; i++)
//	{
//		for (j = 2; j <= sqrt(i); j++)
//		{
//			if (i % j == 0)
//			{
//				break;
//			}
//		}
//		if (j > sqrt(i))
//		{
//			printf("%d ",i);
//		}
//	}
//	return 0;
//}

//1. 打印1000~2000间的闰年
//int main()
//{
//	int Year = 1001, i;
//	for (i = 0; i < Year; i++)
//	{
//		if ((1000 + i) % 4 == 0 && (1000 + i) % 100 != 0)
//		{
//			printf("%d ", i + 1000);
//		}
//		else if ((1000 + i) % 400 == 0)
//		{
//			printf("%d ", i + 1000);
//		}
//	}
//	return 0;
//}