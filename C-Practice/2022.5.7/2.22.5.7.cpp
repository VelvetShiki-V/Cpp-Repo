#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
#define NUM 5
//4. 旋转数据数组：将数组向右轮转k个位置
int Swap(int* a, int* b, int* c)
{
	if (*c == NUM - 1)
	{
		return *a;									//若count计数到NUM - 1，则直接返回备份的tmp值，防止右移越界的指针b赋值给tmp
	}
	else if(*c != NUM - 1)
	{
		int tmp = *b;								//将下一个将被覆盖轮转的值备份
		*b = *a;									//前一个值覆盖后一个值实现轮转
		(*c)++;										//不能写成*c++，因为存在操作优先级和结合性
		return Swap(&tmp, ++b, c);					//将备份值tmp返回给Reverse1函数
	}
	return -1;										//若轮转出错，返回-1
}
void Reverse1(int* p, int k)
{
	int i;
	for (i = 0; i < k; i++)							//循环控制轮转的次数
	{
		int count = 0;
		int tmp = Swap(&p[0], &p[1], &count);		//进入数组轮转函数递归轮换
		if (tmp == -1)
		{
			printf("轮转出错\n");
			exit(-1);
		}
		else
		{
			p[0] = tmp;								//将轮转函数没有处理的数组首元素赋值已备份的末元素
		}
	}
}
int main()
{
	int arr[NUM], i, k;
	printf("请输入5个数据：");
	for (i = 0; i < NUM; i++)
	{
		scanf("%d", &arr[i]);
	}
	printf("输入的数据数组为：");
	for (i = 0; i < NUM; i++)
	{
		printf("%d ", arr[i]);
	}
	while (1)
	{
		printf("\n请输入需要向右轮转的次数：");
		scanf("%d", &k);
		Reverse1(arr, k);
		printf("向右轮转k个位置的数组为：");
		for (i = 0; i < NUM; i++)
		{
			printf("%d ", arr[i]);
		}
	}
	return 0;
}


//3. 计算斐波那契数：递归和非递归分别实现求第n个斐波那契数
//int FibNormal(int n)						//普通循环算法
//{
//	int a = 1, b = 1, i = 0;
//	for (i; i < n - 2; i++)
//	{
//		a = a + b;								//后一个值为前两个值相加（如a = 2 + 3 = 5）
//		b = a - b;								//前一个值由后一个值减再前一个值而得（如b = 5 - 2 = 3）
//	}
//	return a;									//返回后一个值
//}
//int FibRecur(int n)							//递归算法
//{
//	if (n <= 0)
//	{
//		return 0;
//	}
//	else if (n == 1 || n == 2)					//让第一和第二个位置均为1
//	{
//		return 1;
//	}
//	else
//	{
//		n = FibRecur(n - 1) + FibRecur(n - 2);	//递归使后一个位置值为前两个位置值相加
//		return n;
//	}
//}
//
//int main()
//{
//	int a;
//	while (1)
//	{
//		printf("请输入一斐波那契数的第n个位置：");
//		scanf("%d", &a);
//		printf("非递归结果：%d\n递归循环结果：%d\n", FibNormal(a), FibRecur(a));
//	}
//	return 0;
//}


//2. 递归实现n的k次方
//void pow(int n, int k, int m)				//不带返回值的递归
//{
//	if (k != 0)
//	{
//		n *= m;
//		pow(n, --k, m);						//参数传参时，--k和k--区别很大
//	}
//	else
//	{
//		printf("结果为：%d\n", n);
//	}
//}
//int POW(int n, int k)						//带返回值的递归，此种方法较好
//{
//	if (k == 0)
//	{
//		return 1;
//	}
//	return n *= POW(n, --k);
//}
//int main()
//{
//	int n, k, m = 0;
//	while (1)
//	{
//		printf("请输入一个数和幂：");
//		scanf("%d %d", &n, &k);
//		//m = n;
//		//pow(n, k - 1, m);
//		printf("结果为：%d\n", POW(n, k));
//	}
//	return 0;
//}


//1. 计算一个数的每位之和（递归实现）
//int DigSum(int a)							//递归算法开始不要嵌套，计算出正确结果再进行整体优化
//{
//	if (a == 0)
//	{
//		return 0;
//	}
//	int sum = 0, n = 0;
//	n = a % 10;
//	return sum = n + DigSum(a /= 10);
//}
//
//int main()
//{
//	int a;
//	while (1)
//	{
//		printf("请输入一个数：");
//		scanf("%d", &a);
//		printf("结果为：%d\n", DigSum(a));
//	}
//	return 0;
//}