#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<string.h>
int main()
{
	char x = '5', y = '6';
	printf("字符相加之和：%c %d\n", x + y, x + y);  //即ASCII码之和，分别字符输出和十进制整型输出
	x = 50; y = 'A';
	printf("十进制ASCII与字符相加之和：%c %d\n", x + y, x + y);  //实质也是ASCII加法运算，同上
	x = 'a'; y = 'b';
	int z = x + y;
	printf("字符相加之和：%c %d\n", x + y, x + y);  //ASCII运算，但超出可打印范围，输出%d进行了整型提升
	printf("字符相加之和：%c %d\n", z, z);  //ASCII运算，之前已经进行过了整型提升
	getchar();
	return 0;
}


//int main()
//{
//	//int x = 'b';
//	//printf("%c %d\n", x, x); //字符赋值整型变量，字符输出与十进制ASCII整型输出
//	//x = 48;
//	//printf("%c %d\n", x, x); //整数直接以ASCII对应字符%c输出
//	//char x = 'ab';
//	//printf("%c\n", x);  //字符输出被截断的b
//	//x = '34';
//	//printf("%d\n", x); //十进制输出被截断的'4'对应ASCII码
//	getchar();
//	return 0;
//}


//int main()
//{
//	char x = 127;  //有符号char的0 111 1111正边界
//	printf("1. %d\n", x);
//	x = -128;     //有符号char的1 000 0000负边界
//	printf("2. %d\n", x);
//	x = 128;     //有符号char超过正边界，溢出从负边界向0循环:
//				//进位得1 000 0000，向1 111 1111（十进制）循环
//	printf("3. %d\n", x);
//	x = 150;     //正边界溢出，溢出多少就相当于用负边界加几次二进制补码0000 0001
//				//128 - 150 = -22，溢出22，所以-128 + 22个二进制1得到-106
//	printf("4. %d\n", x);
//	unsigned char y = 255;   //无符号整数上边界
//	printf("5. %d\n", y);
//	y = 256;     //超过无符号char的1111 1111上边界，向下边界溢出，从0开始累加补码1循环，原理同上
//	printf("6. %d\n", y);
//	y = -1;      //超过无符号char的0000 0000下边界，向上边界溢出循环
//	printf("7. %d\n", y);
//	getchar();
//	return 0;
//}


//int main()
//{
//	//char是字符类型变量，用于接收字符或数字，也可以接收整型
//	char x = 'a';       //不能不加单引号写作a，否则注明标识符a未定义
//	printf("1. %c %d\n", x, x); //字符输出字符，整型输出ASCII码
//	x = '5';
//	printf("2. %c %d\n", x, x);//输出字符5，整型输出ASCII码
//	x = 5;
//	printf("3. %c %d\n", x, x);//字符以ASCII = 5输出但无法打印（控制字符），整型输出5
//	x = '32';                 //可打印字符ASCII范围十进制：32~126（从空格到波浪号）
//	printf("4. %c %d\n", x, x);//输出字符'2'，因为单引号内只能读取一个字符，整型同理，
//							  //读到字符'2'，对应ASCII输出50
//	x = 32;
//	printf("5. %c %d\n", x, x);//字符以ASCII = 32（空格）输出，整型输出32
//	getchar();
//	return 0;
//}



//int main()       
//{
//    //char a;
//    //a = 'A';
//    //char b = 65;
//    //printf("%d %d\n", a, b);
//    //int a[] = {'A', '\0'};
//    //printf("%s", a);
//    //char i[] = "";
//    //printf("%d", sizeof(i) / sizeof(char));
//    //
//    //int i, num;
//    //char j[6] = {65,65 ,65 ,65 ,'\0'}; //√
///*    printf("%c %d", j[1], j[1]);  */     //格式化输出字符串%s或字符%c时，自动为数组内每个下标对应数值加上单引号''，以ASCII码输出
//
//    //for (i = 0; i < 5; i++)
//    //{
//    //    scanf("%d", &num);
//    //    j[i] = (char)num;
//    //    setbuf(stdin, NULL);
//    //    //printf("%c", j[i]);
//    //}
//    //j[i] = '\0';
//    getchar();
//    return 0;

//int arr[10] = { 1,2,3,4,5 };
//printf("%d", arr);
//char arr[5] = { 'a','b','c',0};
////char arr[] = "\0123";
//printf("%s", arr);



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