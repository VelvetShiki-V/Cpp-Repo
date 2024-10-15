#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>

//面试题：交换两个变量（不创建临时变量）
int main()
{
	int a = 0, b = 0;
	scanf("%d %d", &a, &b);
	//方法一：加减法交换							//弊端为数字不能太大，防止补码溢出
	a = a + b;
	b = a - b;
	a = a - b;
	printf("交换后：a = %d, b = %d\n", a, b);
	//方法二：异或
	a = a ^ b;
	b = a ^ b;										//一个数异或它自己为0
	a = a ^ b;										//再次异或相当于a^b^a^b
	printf("再次交换后：a = %d, b = %d\n", a, b);
}



//4. 牛客：写一个函数返回参数二进制中 1 的个数；比如： 15——0000 1111，其中有 4 个 1
//int countt(int a)
//{
//	int i = 0, count = 0;
//	for (i = 0; i < 32; i++)
//	{
//		if (a % 2 == 1 || a % 2 == -1)			//前者为数值位模2情况，后者%2 == -1是因为若a为负数，最高位%2为-1，也要算进去
//		{
//			count++;
//		}
//		a >>= 1;
//	}
//	return count;
//}
//int main()
//{
//	int a = 0, count = 0;
//	scanf("%d", &a);
//	count = countt(a);
//	printf("1的个数为：%d\n", count);
//	return 0;
//}



//3. 获取一个整数二进制序列中所有的偶数位和奇数位，分别打印出二进制序列
//void GetSingle(int a)
//{
//	int i = 0;
//	int arr[16] = { 0 };
//	for (i = 0; i < 16; i++)				//将奇数位置上的比特位输出
//	{
//		arr[i] = a % 2;
//		a >>= 2;
//	}
//	for (i = 15; i >= 0; i--)				//逆序打印颠倒的比特位
//	{
//		printf("%d", arr[i]);
//	}
//	printf("\n");
//}
//void GetEven(int a)
//{
//	int i = 0;
//	int arr[16] = { 0 };
//	for (i = 0; i < 16; i++)				//将偶数位置上的比特位输出
//	{
//		if (i == 0)
//		{
//			a >>= 1;
//		}
//		arr[i] = a % 2;
//		a >>= 2;
//	}
//	for (i = 15; i >= 0; i--)				//逆序打印颠倒的比特位
//	{
//		printf("%d", arr[i]);
//	}
//	printf("\n");
//}
//int main()
//{
//	int a = 0;
//	scanf("%d", &a);
//	GetEven(a);
//	GetSingle(a);
//	return 0;
//}



//牛客2：输入两个整数，求两个整数二进制格式有多少个位不同
//int BitDiff(int a, int b)
//{
//	int tmp = 0, i = 0, count = 0;
//	tmp = a ^ b;							//异或出n个1
//	for (i = 0; i < 32; i++)
//	{
//		if (tmp % 2 == 1)					//模2取最低比特位
//		{
//			count++;
//		}
//		tmp >>= 1;							//补码右移移位一位
//		
//	}
//	return count;
//}
//int main()
//{
//	int a = 0, b = 0;
//	scanf("%d %d", &a, &b);
//	int ret = BitDiff(a, b);
//	printf("有%d个比特位不同\n", ret);
//	return 0;
//}



//LeetCode1：消失的数字
// 数组nums包含从0到n的所有整数，但其中缺了一个，找出那个缺失的整数。在O(n)时间内完成。
//例如：：[9,6,4,2,3,5,7,0,1]，输出：8
// 
//int FindMissing(int* arr, int sz)				//异或方法
// {
//int i = 0, num = 0;
//while (i < sz)
//{
//	num ^= arr[i];
//	i++;
//}
//i = 0;
//while (i < sz + 1)
//{
//	num ^= i;
//	i++;
//}
//return num;
//}
////int FindMissing(int* arr, int sz)
////{
////	int i = 0, num = 0;
////	while (i <= sz - 1)
////	{
////		if (i == 0)
////		{
////			num = arr[i] ^ arr[i + 1];
////			i += 2;
////		}
////		else
////		{
////			num ^= arr[i];
////			i++;
////		}
////	}
////	i = 0;
////	while (i <= sz)
////	{
////		num ^= i;
////		i++;
////	}
////	return num;
////}
//
//int main()
//{
//	//int a[] = { 9,6,4,2,3,5,7,0,1 };			//多组输入测试
//	//int a[] = { 3,0,1 };
//	//int a[] = { 9,6,4,2,3,5,7,0,1 };
//	//int a[] = { 0,1,2,4,5 };
//	//int a[] = { 9,6,4,2,3,5,7,8,1 };
//	//int a[] = { 1,2,3 };
//	int a[] = { 1,2,5,4,3,8,7,6 };
//	int sz = sizeof(a) / sizeof(a[0]);
//	int ret = FindMissing(a, sz);
//	printf("消失的数字为：%d\n", ret);
//	return 0;
//}