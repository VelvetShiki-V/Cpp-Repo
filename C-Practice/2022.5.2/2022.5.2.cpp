#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>

//����С������������շת�������������С��������ʽa*b/m
int main()
{
	int a, b, d = 1, count = 0, tmp, tmp1;
	scanf("%d %d", &a, &b);     //����35��20��ֻ��Ҫ3�ξͿ����ҵ�
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
	printf("��С�������ǣ�%d\n����%d���ҵ�����\n", a * b / tmp1, count);
	return 0;
}


//���Լ������շת�����
//int main()
//{
//	int a, b, d = 1, count = 0;
//	scanf("%d %d", &a, &b);     //����35��20��ֻ��Ҫ3�ξͿ����ҵ�
//	while (d)
//	{
//		if ((d = a % b) != 0)
//		{
//			a = b;
//			b = d;
//		}
//		count++;
//	}
//	printf("���Լ��Ϊ��%d\n����%d���ҵ�����\n", b, count);
//	return 0;
//}



//���Լ��ѭ������󷨡���O(N)   
//int main()      
//{
//	int a, b, j, count = 0;
//	scanf("%d %d", &a, &b);   //����35��20����Ҫѭ��16���ҵ��������
//	j = a < b ? a : b;
//	while (1)
//	{
//		count++;
//		if (a % j == 0 && a % j == b % j)
//		{
//			
//			printf("���Լ��Ϊ��%d\n", j);
//			break;
//		}
//		j--;
//	}
//	printf("����%d���ҵ�����\n", count);
//	return 0;
//}