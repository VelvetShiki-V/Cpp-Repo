#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>

//6. �ݹ����㷨2
//int my_strlen(char* str)			//ѭ��ģ��strlen
//{
//	int count = 0;
//	while (*str != '\0')
//	{
//		count++;
//		str++;
//	}
//	return count;
//}
//void reverse_string(char* str)		//�����ַ���
//{
//	int len = my_strlen(str);
//	char temp = *str;				//�����������ַ����ݴ�temp
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

//5. ��\0��������strlen��������������������ʹ�ã���sizeof����
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

//4. �ַ������򣨵ݹ�ʵ�֣�:����abcde�����edcba
int strlen_recur(char* a)								//��������ʱ�����ĵݹ�ʵ��my_strlenд��
{
	if (*a == '\0')
	{
		return 0;
	}
	return 1 + strlen_recur(++a);
}
char* StrRevr(char a[], char* right)					//�ַ��������ִ��η�ʽchar* a��char a[]
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
		printf("������һ���ַ�����");
		scanf("%s", arr);
		n = strlen_recur(arr);
		char* p = &arr[--n];
		StrRevr(arr, p);
		printf("%s\n", arr);
	}
	return 0;
}


//3. �ݹ�ͷǵݹ�ֱ�ʵ��strlen
//int strlen_recur(char* a)					//��������ʱ�����ĵݹ�ʵ��my_strlenд��
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
//	printf("�ǵݹ�ѭ����������%d\n", count);
//}
//int main()
//{
//	int n;
//	char arr[30] = { -1 };
//	while (1)
//	{
//		printf("������һ���ַ�����");
//		scanf("%s", arr);
//		printf("�ݹ��������%d\n", n = strlen_recur(arr));
//		strlen_while(arr);
//	}
//	return 0;
//}


//2. �ݹ�ͷǵݹ�ֱ�ʵ����n�Ľ׳ˣ���������������⣩
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
//		printf("������һ��������");
//		scanf("%d", &a);
//		printf("�ݹ�׳˽����%d\n", i = FacRecur(a));
//		printf("��ͨѭ���׳˽����%d\n", j = FacNormal(a));
//	}
//	return 0;
//}


//1.�ݹ鷽ʽʵ�ִ�ӡһ��������ÿһλ
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
//		printf("������һ��������");
//		scanf("%d", &a);
//		print(a);
//	}
//	return 0;
//}