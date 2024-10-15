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
	printf("1. %5d\n", i);	//最小宽度输出：数据占5列，且靠右输出
	printf("2. %-5d\n", i);   //数据占5列，且靠左输出
	printf("3. %+d\n", i);    //数据输出带符号
	printf("4. %+u\n", j);	  //对无符号数没用
	printf("5. 整型十进制：%d, 八进制：%o ，十六进制：%x\n", i, i, i);
	printf("5. %2s\n", k);    //指定字符串输出长度
	printf("6. %f\n", l);  //实数部分全部输出，小数保留6位
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
//	printf("布尔占用：%d字节，整型占用%d字节\n", j, l);
//	bool FALSE = false;
//	bool x = 3;
//	bool y = -1;
//	printf("分别给布尔赋值2,0,3，-1得到值：%hhd %hhd %hhd %hhd\n", TRUE, FALSE, x, y);
//	getchar();
//	return 0;
//}