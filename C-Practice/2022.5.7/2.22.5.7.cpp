#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
#define NUM 5
//4. ��ת�������飺������������תk��λ��
int Swap(int* a, int* b, int* c)
{
	if (*c == NUM - 1)
	{
		return *a;									//��count������NUM - 1����ֱ�ӷ��ر��ݵ�tmpֵ����ֹ����Խ���ָ��b��ֵ��tmp
	}
	else if(*c != NUM - 1)
	{
		int tmp = *b;								//����һ������������ת��ֵ����
		*b = *a;									//ǰһ��ֵ���Ǻ�һ��ֵʵ����ת
		(*c)++;										//����д��*c++����Ϊ���ڲ������ȼ��ͽ����
		return Swap(&tmp, ++b, c);					//������ֵtmp���ظ�Reverse1����
	}
	return -1;										//����ת��������-1
}
void Reverse1(int* p, int k)
{
	int i;
	for (i = 0; i < k; i++)							//ѭ��������ת�Ĵ���
	{
		int count = 0;
		int tmp = Swap(&p[0], &p[1], &count);		//����������ת�����ݹ��ֻ�
		if (tmp == -1)
		{
			printf("��ת����\n");
			exit(-1);
		}
		else
		{
			p[0] = tmp;								//����ת����û�д����������Ԫ�ظ�ֵ�ѱ��ݵ�ĩԪ��
		}
	}
}
int main()
{
	int arr[NUM], i, k;
	printf("������5�����ݣ�");
	for (i = 0; i < NUM; i++)
	{
		scanf("%d", &arr[i]);
	}
	printf("�������������Ϊ��");
	for (i = 0; i < NUM; i++)
	{
		printf("%d ", arr[i]);
	}
	while (1)
	{
		printf("\n��������Ҫ������ת�Ĵ�����");
		scanf("%d", &k);
		Reverse1(arr, k);
		printf("������תk��λ�õ�����Ϊ��");
		for (i = 0; i < NUM; i++)
		{
			printf("%d ", arr[i]);
		}
	}
	return 0;
}


//3. ����쳲����������ݹ�ͷǵݹ�ֱ�ʵ�����n��쳲�������
//int FibNormal(int n)						//��ͨѭ���㷨
//{
//	int a = 1, b = 1, i = 0;
//	for (i; i < n - 2; i++)
//	{
//		a = a + b;								//��һ��ֵΪǰ����ֵ��ӣ���a = 2 + 3 = 5��
//		b = a - b;								//ǰһ��ֵ�ɺ�һ��ֵ����ǰһ��ֵ���ã���b = 5 - 2 = 3��
//	}
//	return a;									//���غ�һ��ֵ
//}
//int FibRecur(int n)							//�ݹ��㷨
//{
//	if (n <= 0)
//	{
//		return 0;
//	}
//	else if (n == 1 || n == 2)					//�õ�һ�͵ڶ���λ�þ�Ϊ1
//	{
//		return 1;
//	}
//	else
//	{
//		n = FibRecur(n - 1) + FibRecur(n - 2);	//�ݹ�ʹ��һ��λ��ֵΪǰ����λ��ֵ���
//		return n;
//	}
//}
//
//int main()
//{
//	int a;
//	while (1)
//	{
//		printf("������һ쳲��������ĵ�n��λ�ã�");
//		scanf("%d", &a);
//		printf("�ǵݹ�����%d\n�ݹ�ѭ�������%d\n", FibNormal(a), FibRecur(a));
//	}
//	return 0;
//}


//2. �ݹ�ʵ��n��k�η�
//void pow(int n, int k, int m)				//��������ֵ�ĵݹ�
//{
//	if (k != 0)
//	{
//		n *= m;
//		pow(n, --k, m);						//��������ʱ��--k��k--����ܴ�
//	}
//	else
//	{
//		printf("���Ϊ��%d\n", n);
//	}
//}
//int POW(int n, int k)						//������ֵ�ĵݹ飬���ַ����Ϻ�
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
//		printf("������һ�������ݣ�");
//		scanf("%d %d", &n, &k);
//		//m = n;
//		//pow(n, k - 1, m);
//		printf("���Ϊ��%d\n", POW(n, k));
//	}
//	return 0;
//}


//1. ����һ������ÿλ֮�ͣ��ݹ�ʵ�֣�
//int DigSum(int a)							//�ݹ��㷨��ʼ��ҪǶ�ף��������ȷ����ٽ��������Ż�
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
//		printf("������һ������");
//		scanf("%d", &a);
//		printf("���Ϊ��%d\n", DigSum(a));
//	}
//	return 0;
//}