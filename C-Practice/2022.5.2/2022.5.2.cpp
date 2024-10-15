#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>

//求最小公倍数——由辗转相除延伸来，最小公倍数公式a*b/m
int main()
{
	int a, b, d = 1, count = 0, tmp, tmp1;
	scanf("%d %d", &a, &b);     //输入35和20，只需要3次就可以找到
	tmp = a, tmp1 = b;
	while (d)
	{
		if ((d = tmp % tmp1) != 0)
		{
			tmp = tmp1;
			tmp1 = d;
		}
		count++;
	}
	printf("最小公倍数是：%d\n共计%d次找到该数\n", a * b / tmp1, count);
	return 0;
}


//最大公约数——辗转相除法
//int main()
//{
//	int a, b, d = 1, count = 0;
//	scanf("%d %d", &a, &b);     //输入35和20，只需要3次就可以找到
//	while (d)
//	{
//		if ((d = a % b) != 0)
//		{
//			a = b;
//			b = d;
//		}
//		count++;
//	}
//	printf("最大公约数为：%d\n共计%d次找到该数\n", b, count);
//	return 0;
//}



//最大公约数循环相减求法——O(N)   
//int main()      
//{
//	int a, b, j, count = 0;
//	scanf("%d %d", &a, &b);   //输入35和20，需要循环16次找到最大公因数
//	j = a < b ? a : b;
//	while (1)
//	{
//		count++;
//		if (a % j == 0 && a % j == b % j)
//		{
//			
//			printf("最大公约数为：%d\n", j);
//			break;
//		}
//		j--;
//	}
//	printf("共计%d次找到该数\n", count);
//	return 0;
//}