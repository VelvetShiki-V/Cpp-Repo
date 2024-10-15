#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<string.h>
int main()          //转义字符
{
    int i;
    char j[6];
    for (i = 0; i < 5; i++)
    {
        scanf("%d", &j[i]);
    }
    j[i] = '\0';
    printf("%s", j);
    return 0;
    //int arr[10] = { 1,2,3,4,5 };
//printf("%d", arr);
//char arr[5] = { 'a','b','c',0};
////char arr[] = "\0123";
//printf("%s", arr);
}


//int main()          //字符容量常量
//{
//    const int a = 5;
//    int arr1[a] = { 1 };
//    int j = sizeof(arr1) / sizeof(int);
//    printf("%d", j);
//    printf("okk??)");
//    getchar();
//    //int n = 5, arr[n] = { 0 };    //错误写法，变量不能作为数组容量值
//    //int arr1[5] = { 0 };
//    return 0;
//}


//int main()          //转义字符
//{
//    printf("八进制转义为ASCII字符：\061\n十六进制转义为ASCII字符：\x68\n");
//    printf("%d\n", strlen("c:\test\628\test.c\n"));     //输出15
//    printf("使用八进制转义空格' '：\40，使用十六进制转义回车：\xA");       //空格的ASC是32，转换为16进制是x20，使用转义字符为 \x20
//    printf("%d\n", strlen("c:\test\121"));      //转义字符占一个字节，\t和\121共占2个字节，分别代表跳格tab和八进制转义ascii
//    return 0;
//}


//int main()    //计算表达式(-8+22)×a-10+c÷2，其中，a = 40，c = 212
//{
//	int a = 40, c = 212;
//	printf("%d", (-8 + 22) * a - 10 + c / 2);
//	return 0;
//}


//int main()   // 输入整数被除数和除数，输出整数商和余数
//{
//	int a, b;
//	scanf("%d %d", &a, &b);
//	printf("%d %d", a / b, a % b);
//	return 0;
//}


//int main()    //输出要求的格式字符串
//{
//    //printf("%-8s%-7s%-6s\n", "Name", "Age", "Gender");      //格式化输出写法
//    //printf("---------------------\n");
//    //printf("%-8s%-7s%-6s\n", "Jack", "18", "man");
//    //return 0;
//
//    printf("Name    Age    Gender\n");      //写法二
//    printf("---------------------\n");
//    printf("Jack    18     man");
//}


//int main()      //你是天才吗
//{
//    int a;
//    scanf("%d", &a);
//    if (a >= 140)
//    {
//        printf("Genius");
//    }
//    return 0;
//}


//int main()       //输入两个数比较大小，输出较大数
//{
//	int a[2] = {0};
//	int i;
//	for (i = 0; i < 2; i++)
//	{
//		scanf("%d", &a[i]);
//	}
//	if (a[0] > a[1])
//	{
//		printf("%d", a[0]);
//	}
//	else
//	{
//		printf("%d", a[1]);
//	}
//	return 0;
//}


//int main()      //输入正数，输出-1；输入0，输出0；输入负数，输出1
//{
//    int x, y;
//    scanf("%d", &x);
//    setbuf(stdin, NULL);
//    if (x > 0)
//    {
//        y = -1;
//        printf("%d", y);
//    }
//    else if (x == 0)
//    {
//        y = 0;
//        printf("%d", y);
//    }
//    else
//    {
//        y = 1;
//        printf("%d", y);
//    }
//    return 0;
//}