#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<time.h>
#include<stdlib.h>


//5.
int main()
{
	int a = 0;
	time_t t;  //time_t就是long long，64位长整形
/*	srand((unsigned)time(&t));  */ //使用time函数赋值
	t = rand();
	t %= 100;
	while (a != t)
	{
		printf("\n请输入一个数：");
		scanf("%d", &a);
		if (a > t)
		{
			printf("大了\n");
		}
		else if (a < t)
		{
			printf("小了\n");
		}
		else
		{
			printf("对了\n");
		}
	}
}



//4.
//int main()   //求模
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
//int main()   //大小写转化
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
//int main()  //小乐乐学校教学楼的电梯前排了很多人，他的前面有n个人在等电梯。电梯每次可以乘坐12人
//                //每次上下需要的时间为4分钟（上需要2分钟，下需要2分钟）。
//                 //还需要多少分钟才能乘电梯到达楼上。（假设最初电梯在1层）
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
//int main()   //数值以ASCII码字符输出
//{
//    printf("%c%c%c%c%c%c%c%c%c%c%c%c ", 73, 32, 99, 97, 110, 32, 100, 111, 32, 105, 116, 33);
//    return 0;
//}