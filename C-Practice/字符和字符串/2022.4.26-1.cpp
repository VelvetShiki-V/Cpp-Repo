#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdbool.h>
#include<string.h>
int main()
{
	//int arr[] = { 1,2,3,4,5 };
	int i = -1;
	unsigned j = 10;
	char k[] = "abcdef";
	float l = 123.444444444;
	double m = 22.333333333;
	printf("1. %5d\n", i);	//��С������������ռ5�У��ҿ������
	printf("2. %-5d\n", i);   //����ռ5�У��ҿ������
	printf("3. %+d\n", i);    //�������������
	printf("4. %+u\n", j);	  //���޷�����û��
	printf("5. ����ʮ���ƣ�%d, �˽��ƣ�%o ��ʮ�����ƣ�%x\n", i, i, i);
	printf("5. %2s\n", k);    //ָ���ַ����������
	printf("6. %f\n", l);  //ʵ������ȫ�������С������6λ
	printf("7. %5.1f\n", l);
	printf("8. %lf\n", m);   //
	getchar();
	return 0;
}


//int main()
//{
//	int a = 1;
//	int* i = &a;
//	printf("%p\n", &a);
//	printf("0x%X\n", &a);
//	getchar();
//	return 0;
//}


//int main()
//{
//	bool x = true;
//	int y = 2;
//	printf("x = %hhd, y = %d", x, y);
//	getchar();
//	return 0;
//}


//int main()
//{
//	bool TRUE = true;
//	int j = sizeof(TRUE);
//	int k = 1;
//	int l = sizeof(k);
//	printf("����ռ�ã�%d�ֽڣ�����ռ��%d�ֽ�\n", j, l);
//	bool FALSE = false;
//	bool x = 3;
//	bool y = -1;
//	printf("�ֱ��������ֵ2,0,3��-1�õ�ֵ��%hhd %hhd %hhd %hhd\n", TRUE, FALSE, x, y);
//	getchar();
//	return 0;
//}