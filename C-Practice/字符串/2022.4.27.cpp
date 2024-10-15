#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdbool.h>
#include<string.h>
int main()
{
	int i = -1;
	float l = 123.456;
	double m = 2222222.3333333;
	char k[] = "abcdef";
	//unsigned j = 10;
	//printf("1. %5d\n", i);	//最小宽度输出：数据占5列，且靠右输出
	//printf("2. %-5d\n", i);   //数据占5列，且靠左输出
	//printf("3. %+d\n", i);    //数据输出带符号
	//printf("4. %+u\n", j);	  //对无符号数没用
	//printf("5. 整型十进制：%d, 八进制：%o ，十六进制：%x\n", i, i, i);


	////m为字符串占用最小宽度，指定字符串输出长度
	//printf("6. %10s\n", k);    
	//printf("7. %-8s\n", k);//%后加-是左对齐
	//printf("8. %5.3s\n", k);//%m.ns中n为限制输出字符串中的n个字符,若n>原字符串长度则全部输出


	//整数部分全部输出，小数保留6位（即使该实数小数点不够6位，也会补齐6位小数）
	//printf("9. %f\n", l);  
	//printf("10. %-8f\n", l); //最小宽度m包括小数，小数点和整数之和，m<实际宽度则全部输出
	//printf("11. %.2f\n", l); //n限制输出小数位数,可与例10组合使用
	//printf("12. %lf\n", m);   //双精度有效位数16位，但只输出6位小数
	//指数输出
	//printf("13. %e\n",l);//无需指定最小宽度和输出限制，由系统自动指定
	//				  对于实数123.456输出1.234560+02，该2代表2次方
	//printf("14. %g %g\n", l, m);  //系统自动选择输出模式%f或%e，根据输出占用宽度较小来选择，且不输出无意义的0


	////十六进制输出和变量地址的十六进制输出
	//printf("14. %X\n", i);  //注意，输出的是无符号十六进制数
	////对-1而言，其原码为1000...0001,转换为补码为1111...1111
	////因为%x将该数视为无符号数，且无符号数同正数，原反补码相同
	////所以十六进制输出其原码（同补码）FFFFFFFF
	//printf("15. 0x%p\n", &i); //前缀0x可写可不写，将i地址以十六进制输出
	////注意变量的地址每次运行都随机分配，所以每次值都不相同
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