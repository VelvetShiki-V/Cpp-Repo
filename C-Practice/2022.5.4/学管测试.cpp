#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<windows.h>
#include<string.h>

int ID[5] = { 10001,10002,10003,10004 };
char NAME[5][10] = { "����", "����", "������", "����" };
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
	//		printf("����-1����1������");
	//		scanf("%d", &b);
	//	}
	printf("ѧ��%d����Ϊ��%s\n",/* NAME[a - 1][b + 1], NAME[a - 1][b + 2], */a, NAME[tmp - 1]);	/*%c%c */
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
	printf("���ٴ�����ID��֤��");
	scanf("%d", &x);
	if (x == NameSearch(a))
	{
		printf("������������֤��");
	here:
		scanf("%s", y);
		pw = PWSearch(a);
		if(!(strcmp(pw, y)) != 0 )
		{
			x %= 10;
			printf("��¼�ɹ�,������Ϊ%s�����ڽ�����ҳ\n", NAME[x - 1]);
			return 0;
		}
		else
		{
			printf("����������������룺");
			goto here;
		}
	}
	else
	{
		printf("�˺Ų����ڣ����ڽ���ע��ҳ��...\n");
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
		printf("������ID��");
		scanf("%d", &a);
		printf("������Ҫִ�еĹ��ܱ�ţ�\n1. ѧ�Ŷ�Ӧ���ֲ�ѯ����\n2. ѧ�Ŷ�Ӧ�����ѯ����\n3. ��¼����\n");
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