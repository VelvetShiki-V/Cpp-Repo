#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<time.h>
#include<stdlib.h>


//5.
int main()
{
	int a = 0;
	time_t t;  //time_t����long long��64λ������
/*	srand((unsigned)time(&t));  */ //ʹ��time������ֵ
	t = rand();
	t %= 100;
	while (a != t)
	{
		printf("\n������һ������");
		scanf("%d", &a);
		if (a > t)
		{
			printf("����\n");
		}
		else if (a < t)
		{
			printf("С��\n");
		}
		else
		{
			printf("����\n");
		}
	}
}



//4.
//int main()   //��ģ
//{
//	int a = 0, b = 0;
//	for (a = 1, b = 1; a <= 100; a++)
//	{
//		if (b >= 20) break;
//		if (b % 3 == 1)
//		{
//			b = b + 3;
//			continue;
//		}
//		b = b - 5;
//	}
//	printf("%d\n", a);
//	return 0;
//}



//3.
//int main()   //��Сдת��
//{
//    char a;
//    while ((a = getchar()) != EOF)
//    {
//        if (a >= 'A' && a <= 'Z')
//        {
//            printf("%c\n", a + 32);
//        }
//        else if (a >= 'a' && a <= 'z')
//        {
//            printf("%c\n", a - 32);
//        }
//    }
//    return 0;
//}



//2.
//int main()  //С����ѧУ��ѧ¥�ĵ���ǰ���˺ܶ��ˣ�����ǰ����n�����ڵȵ��ݡ�����ÿ�ο��Գ���12��
//                //ÿ��������Ҫ��ʱ��Ϊ4���ӣ�����Ҫ2���ӣ�����Ҫ2���ӣ���
//                 //����Ҫ���ٷ��Ӳ��ܳ˵��ݵ���¥�ϡ����������������1�㣩
//{
//    int n, time = 2, a;
//    scanf("%d", &n);
//    if (n < 12 && n >= 0)
//    {
//        printf("%d", time);
//    }
//    else if (n >= 12)
//    {
//        a = n / 12;
//        a *= 4;
//        printf("%d", a + time);
//    }
//    return 0;
//}



//1.
//int main()   //��ֵ��ASCII���ַ����
//{
//    printf("%c%c%c%c%c%c%c%c%c%c%c%c ", 73, 32, 99, 97, 110, 32, 100, 111, 32, 105, 116, 33);
//    return 0;
//}