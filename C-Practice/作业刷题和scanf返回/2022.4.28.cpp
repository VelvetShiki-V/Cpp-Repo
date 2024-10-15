#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
//define不是关键字
//int define = 1;
//printf("%d", define);

int main()
{
    char a[5], c[3];
    int b;
    b = scanf("%s %s", a,c);
    printf("%d\n", b);
    //while (b<1)
    //{


    //    for (int i = 0; i < a; i++)
    //    {
    //        printf("*");
    //    }
    //    printf("\n");
    //    b++;
    //}
    return 0;
}
 

//int main()
//{
//    int a;
//    while (scanf("%d", &a) != EOF || a == 0)
//    {
///*        a = scanf("%d", &a);    *///该写法错误，scanf函数返回值为匹配成功的个数，而并非赋的值，所以永远为1
//        //scanf("%d", &a);
//        for (int i = 0; i < a; i++)
//        {
//            printf("*");
//        }
//        printf("\n");
//    }
//    return 0;
//}

//int main()  //计算平均升高
//{
//    float height[5];
//    scanf("%f %f %f %f %f ", &height[0], &height[1], &height[2], &height[3], &height[4]);
//    printf("%.2f", (height[0] + height[1] + height[2] + height[3] + height[4]) / 5);
//    return 0;
//}



//int main()
//{
//
//    二维数组存储5x5的浮点数
//    float a[5][5];
//    int i, j;
//    for (i = 0; i < 5; i++)
//    {
//        for (j = 0; j < 5; j++)
//        {
//            scanf("%f", &a[i][j]);
//            printf("%.1f ", a[i][j]);
//        }
//    }
//
//    法2
// /*   float a[5], b[5], c[5], d[5], e[5];
//    scanf("%f %f %f %f %f", &a[0], &a[1], &a[2], &a[3], &a[4]);
//    scanf("%f %f %f %f %f", &b[0], &b[1], &b[2], &b[3], &b[4]);
//    scanf("%f %f %f %f %f", &c[0], &c[1], &c[2], &c[3], &c[4]);
//    scanf("%f %f %f %f %f", &d[0], &d[1], &d[2], &d[3], &d[4]);
//    scanf("%f %f %f %f %f", &e[0], &e[1], &e[2], &e[3], &e[4]);
//    printf("%.1f %.1f %.1f %.1f %.1f %.1f\n", a[0], a[1], a[2], a[3], a[4], a[0] + a[1] + a[2] + a[3] + a[4]);
//    printf("%.1f %.1f %.1f %.1f %.1f %.1f\n", b[0], b[1], b[2], b[3], b[4], b[0] + b[1] + b[2] + b[3] + b[4]);
//    printf("%.1f %.1f %.1f %.1f %.1f %.1f\n", c[0], c[1], c[2], c[3], c[4], c[0] + c[1] + c[2] + c[3] + c[4]);
//    printf("%.1f %.1f %.1f %.1f %.1f %.1f\n", d[0], d[1], d[2], d[3], d[4], d[0] + d[1] + d[2] + d[3] + d[4]);
//    printf("%.1f %.1f %.1f %.1f %.1f %.1f\n", e[0], e[1], e[2], e[3], e[4], e[0] + e[1] + e[2] + e[3] + e[4]);
//    return 0;*/
//}


//int max3(int g, int h, int i)   //计算表达式并输出浮点数
//{
//    int max = g > h ? g : h;
//    max = max > i ? max : i;
//    return max;
//}
//
//int main()
//{
//    int a, b, c, d, e, f;
//    float k;
//    scanf("%d %d %d", &a, &b, &c);
//    d = max3(a + b, b, c);
//    e = max3(a, b + c, c);
//    f = max3(a, b, b + c);
//    printf("%.2f", k = (float)d / (float)(e + f));
//    return 0;
//}


//#include<stdio.h>
//int sum(int a)
//{
//    int c = 0;
//    static int b = 3;
//    c += 1;
//    b += 2;
//    return (a + b + c);
//}
//int main()
//{
//    int i;
//    int a = 2;
//    for (i = 0; i < 5; i++)
//    {
//        printf("%d,", sum(a));
//    }
//}


//int main()   //实现一个数的逆序
//{
//    int a;
//    scanf("%d", &a);
//    while (a)
//    {
//        printf("%d", a % 10);
//        a /= 10;
//    }
//    return 0;
//}


//int main()  //输出浮点数，平均值，总和
//{
//    float a, b, c, d, e;
//    scanf("%f %f %f", &a, &b, &c);
//    printf("%.2f %.2f", a + b + c, (a + b + c) / 3);
//    return 0;
//}


//int main()   //两个数比较大小
//{
//    int x, y, i;
//    while((scanf("%d %d", &x, &y)) != EOF)
//    {
//        if (x == y)
//        {
//            printf("%d=%d\n", x, y);
//        }
//        else if (x < y)
//        {
//            printf("%d<%d\n", x, y);
//        }
//        else
//        {
//            printf("%d>%d\n", x, y);
//        }
//    }
//    return 0;
//}

