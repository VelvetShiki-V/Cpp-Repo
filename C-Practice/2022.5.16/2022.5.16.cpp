#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>

//�����⣺����������������������ʱ������
int main()
{
	int a = 0, b = 0;
	scanf("%d %d", &a, &b);
	//����һ���Ӽ�������							//�׶�Ϊ���ֲ���̫�󣬷�ֹ�������
	a = a + b;
	b = a - b;
	a = a - b;
	printf("������a = %d, b = %d\n", a, b);
	//�����������
	a = a ^ b;
	b = a ^ b;										//һ����������Լ�Ϊ0
	a = a ^ b;										//�ٴ�����൱��a^b^a^b
	printf("�ٴν�����a = %d, b = %d\n", a, b);
}



//4. ţ�ͣ�дһ���������ز����������� 1 �ĸ��������磺 15����0000 1111�������� 4 �� 1
//int countt(int a)
//{
//	int i = 0, count = 0;
//	for (i = 0; i < 32; i++)
//	{
//		if (a % 2 == 1 || a % 2 == -1)			//ǰ��Ϊ��ֵλģ2���������%2 == -1����Ϊ��aΪ���������λ%2Ϊ-1��ҲҪ���ȥ
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
//	printf("1�ĸ���Ϊ��%d\n", count);
//	return 0;
//}



//3. ��ȡһ���������������������е�ż��λ������λ���ֱ��ӡ������������
//void GetSingle(int a)
//{
//	int i = 0;
//	int arr[16] = { 0 };
//	for (i = 0; i < 16; i++)				//������λ���ϵı���λ���
//	{
//		arr[i] = a % 2;
//		a >>= 2;
//	}
//	for (i = 15; i >= 0; i--)				//�����ӡ�ߵ��ı���λ
//	{
//		printf("%d", arr[i]);
//	}
//	printf("\n");
//}
//void GetEven(int a)
//{
//	int i = 0;
//	int arr[16] = { 0 };
//	for (i = 0; i < 16; i++)				//��ż��λ���ϵı���λ���
//	{
//		if (i == 0)
//		{
//			a >>= 1;
//		}
//		arr[i] = a % 2;
//		a >>= 2;
//	}
//	for (i = 15; i >= 0; i--)				//�����ӡ�ߵ��ı���λ
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



//ţ��2�������������������������������Ƹ�ʽ�ж��ٸ�λ��ͬ
//int BitDiff(int a, int b)
//{
//	int tmp = 0, i = 0, count = 0;
//	tmp = a ^ b;							//����n��1
//	for (i = 0; i < 32; i++)
//	{
//		if (tmp % 2 == 1)					//ģ2ȡ��ͱ���λ
//		{
//			count++;
//		}
//		tmp >>= 1;							//����������λһλ
//		
//	}
//	return count;
//}
//int main()
//{
//	int a = 0, b = 0;
//	scanf("%d %d", &a, &b);
//	int ret = BitDiff(a, b);
//	printf("��%d������λ��ͬ\n", ret);
//	return 0;
//}



//LeetCode1����ʧ������
// ����nums������0��n������������������ȱ��һ�����ҳ��Ǹ�ȱʧ����������O(n)ʱ������ɡ�
//���磺��[9,6,4,2,3,5,7,0,1]�������8
// 
//int FindMissing(int* arr, int sz)				//��򷽷�
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
//	//int a[] = { 9,6,4,2,3,5,7,0,1 };			//�����������
//	//int a[] = { 3,0,1 };
//	//int a[] = { 9,6,4,2,3,5,7,0,1 };
//	//int a[] = { 0,1,2,4,5 };
//	//int a[] = { 9,6,4,2,3,5,7,8,1 };
//	//int a[] = { 1,2,3 };
//	int a[] = { 1,2,5,4,3,8,7,6 };
//	int sz = sizeof(a) / sizeof(a[0]);
//	int ret = FindMissing(a, sz);
//	printf("��ʧ������Ϊ��%d\n", ret);
//	return 0;
//}