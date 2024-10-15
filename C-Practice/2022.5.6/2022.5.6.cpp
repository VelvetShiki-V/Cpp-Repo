#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>

//6. 递归逆算法2
//int my_strlen(char* str)			//循环模拟strlen
//{
//	int count = 0;
//	while (*str != '\0')
//	{
//		count++;
//		str++;
//	}
//	return count;
//}
//void reverse_string(char* str)		//逆序字符串
//{
//	int len = my_strlen(str);
//	char temp = *str;				//解引用左首字符并暂存temp
//	*str = str[len - 1];			
//	str[len - 1] = '\0';			
//	if (my_strlen(str + 1) >= 2)
//	{
//		reverse_string(str + 1);
//	}
//	str[len - 1] = temp;
//}
//int main()
//{
//	char arr[10] = "abcdef";
//	reverse_string(arr);
//	printf("%s\n", arr);
//	return 0;
//}

//5. 找\0结束符的strlen函数可以在其他函数中使用，而sizeof不行
//int strlen_recur(char* a)			
//{
//	int count = 0;
//	while(*a != '\0')
//	{
//		count++;
//		a++;
//	}
//	return count;
//}
//void test(char a[])
//{
//	printf("%d\n", strlen_recur(a));
//}
//int main()
//{
//	char a[] = "abcdefghij";
//	test(a);
//	return 0;
//}

//4. 字符串逆序（递归实现）:输入abcde，输出edcba
int strlen_recur(char* a)								//不创建临时变量的递归实现my_strlen写法
{
	if (*a == '\0')
	{
		return 0;
	}
	return 1 + strlen_recur(++a);
}
char* StrRevr(char a[], char* right)					//字符串的两种传参方式char* a或char a[]
{
	if (a < right)
	{
		char tmp;
		tmp = *a;
		*a = *right;
		*right = tmp;
	}
	else
	{
		return 0;
	}
	StrRevr(++a, --right);
	return a; 
}
int main()
{
	char arr[30] = { -1 };
	int n;
	while (1)
	{
		printf("请输入一个字符串：");
		scanf("%s", arr);
		n = strlen_recur(arr);
		char* p = &arr[--n];
		StrRevr(arr, p);
		printf("%s\n", arr);
	}
	return 0;
}


//3. 递归和非递归分别实现strlen
//int strlen_recur(char* a)					//不创建临时变量的递归实现my_strlen写法
//{
//	if (*a == '\0')
//	{
//		return 0;
//	}
//	return 1 + strlen_recur(++a);
//}
//void strlen_while(char arr[])
//{
//	char* ptr = arr;
//	int count = 0;
//	while (*ptr != '\0')
//	{
//		count++;
//		ptr++;
//	}
//	printf("非递归循环计算结果：%d\n", count);
//}
//int main()
//{
//	int n;
//	char arr[30] = { -1 };
//	while (1)
//	{
//		printf("请输入一个字符串：");
//		scanf("%s", arr);
//		printf("递归计算结果：%d\n", n = strlen_recur(arr));
//		strlen_while(arr);
//	}
//	return 0;
//}


//2. 递归和非递归分别实现求n的阶乘（不考虑溢出的问题）
//int FacRecur(int x)
//{
//	if (x != 0)
//	{
//		x *= FacRecur(x - 1);
//	}
//	else
//	{
//		return 1;
//	}
//	return x;
//}
//int FacNormal(int y)
//{
//	int k = y - 1;
//	while (k != 0)
//	{
//		y *= k;
//		k--;
//	}
//	return y;
//}
//int main()
//{
//	int a, i, j;
//	while (1)
//	{
//		printf("请输入一个整数：");
//		scanf("%d", &a);
//		printf("递归阶乘结果：%d\n", i = FacRecur(a));
//		printf("普通循环阶乘结果：%d\n", j = FacNormal(a));
//	}
//	return 0;
//}


//1.递归方式实现打印一个整数的每一位
//void print(int a)
//{
//	printf("%d ", a % 10);
//	if (a / 10 != 0)
//	{
//		print(a / 10);
//	}
//	printf("\n");
//}
//int main()
//{
//	int a;
//	while (1)
//	{
//		printf("请输入一个整数：");
//		scanf("%d", &a);
//		print(a);
//	}
//	return 0;
//}