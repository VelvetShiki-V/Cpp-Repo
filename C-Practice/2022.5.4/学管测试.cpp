#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<windows.h>
#include<string.h>

int ID[5] = { 10001,10002,10003,10004 };
char NAME[5][10] = { "张三", "李四", "王老五", "赵六" };
char PASSWORD[5][16] = { "aaaaa","bbbbb","ccccc","ddddd" };
int Num = 4;

int NameSearch(int a)
{
	//int b;
	int tmp = a;
	tmp %= 10;
	if (tmp < 1 || tmp > 4)
	{
		return NULL;
	}
	//else
	//{
	//	if (a > 1)
	//	{
	//		printf("输入-1查姓1查名：");
	//		scanf("%d", &b);
	//	}
	printf("学号%d名字为：%s\n",/* NAME[a - 1][b + 1], NAME[a - 1][b + 2], */a, NAME[tmp - 1]);	/*%c%c */
	return a;
}

char* PWSearch(int b)
{
	b %= 10;
	if (b < 1 || b > 4)
	{
		return NULL;
	}
	else
	{
		//printf("%s\n", PASSWORD[b - 1]);
		return PASSWORD[b - 1];
	}
}

int Login(int a)
{
	int x;
	char y[10];
	char* pw;
	printf("请再次输入ID验证：");
	scanf("%d", &x);
	if (x == NameSearch(a))
	{
		printf("请输入密码验证：");
	here:
		scanf("%s", y);
		pw = PWSearch(a);
		if(!(strcmp(pw, y)) != 0 )
		{
			x %= 10;
			printf("登录成功,你的身份为%s，正在进入首页\n", NAME[x - 1]);
			return 0;
		}
		else
		{
			printf("密码错误，请重新输入：");
			goto here;
		}
	}
	else
	{
		printf("账号不存在，正在进入注册页面...\n");
		Sleep(2000);
		system("cls");
		return 1;
	}
	return 0;
}

int main()
{
	while (1)
	{
		int a, n;
		printf("请输入ID：");
		scanf("%d", &a);
		printf("请输入要执行的功能编号：\n1. 学号对应名字查询功能\n2. 学号对应密码查询功能\n3. 登录功能\n");
		scanf("%d", &n);
		switch (n)
		{
		case 1: NameSearch(a);
			continue;
		case 2: PWSearch(a);
			continue;
		case 3: Login(a);
			continue;
		default:
			break;
		}
		return 0;
	}
}