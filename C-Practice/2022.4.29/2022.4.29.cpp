#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>

int main()   //
{
	int a, b, c[1000] = { 0 }, d[1000] = { 0 }, count = 0, count1 = 0, i, j;
	scanf("%d %d", &a, &b);    //���������ÿո�ֿ�����
	for (i = 1; i <= a; i++)  //��a��ȫ������
	{
		if (a % i == 0)
		{
			c[count] = i;
			count++;
		}
	}
	for (i = 1; i <= b; i++)  //b��ȫ������
	{
		if (b % i == 0)
		{
			d[count1] = i;
			count1++;
		}
	}
	int tmp = --count1;
	for (i = --count; i >= 0; i--)  //��a��b���������
	{
		for (j = tmp; j >= 0; j--)
		{
			if (c[i] == d[j])
			{
				printf("���Լ��Ϊ%d\n", c[i]);
				return 0;
			}
		}
	}
	getchar;
	return 0;
}

//int a, b;

//if(a%b)
//char y = 513;      //�����޷���char��0000 0000�±߽磬���ϱ߽����ѭ��
//printf("%d\n", y);

//int main()   // 100��3�ı��������
//{
//	for (int i = 3; i <= 100; i+=3)
//	{
//		printf("%d ", i);
//	}
//	return 0;
//}


//void arrange(int* a)  //ð������
//{
//	int temp, i;
//	for (i = 0; i < 2; i++)
//	{
//		for (int j = 0; j < 2; j++)
//		{
//			if (a[j] < a[j + 1])
//			{
//				temp = a[j];
//				a[j] = a[j + 1];
//				a[j + 1] = temp;
//			}
//			else
//			{
//				continue;
//			}
//		}
//	}
//	for (i = 0; i < 3; i++)
//	{
//		printf("%d ", a[i]);
//	}
//	
//
//}
//int main()   //�������Ӵ�С���
//{
//	int arr[3];
//	for (int i = 0; i < 3; i++)
//	{
//		scanf("%d", &arr[i]);
//	}
//	//int max = arr[0] > arr[1] ? arr[0] : arr[1];    // ͷ��д��
//	//int temp = arr[0] + arr[1] - max;
//	//int maxmax = max > arr[2] ? max : arr[2];
//	//int temp2 = max + arr[2] - maxmax;
//	//int mid = temp > temp2 ? temp : temp2;
//	//int min = temp + temp2 - mid;
//	//printf("%d %d %d", maxmax, mid, min);
//	//д��2
//	arrange(arr);
//	return 0;
//}