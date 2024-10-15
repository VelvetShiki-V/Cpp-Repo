#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
//#define clear while(getchar()!='\n');
//
//void buffer_clear(char r)
//{
//	while ((r = getchar()) != EOF && r != '\n')
//	{
//		;
//	}
//}
int main()
{

	char arr[10];
	for (int i = 0; i < 10; i++)
	{
		arr[i] = getchar();
		printf("Êä³ö£º%c\n", arr[i]);
		scanf("%*[^\n]"); scanf("%*c");
		//setbuf(stdin, NULL);
		//clear;
		//while ((ch = getchar()) != EOF && ch != '\n')
		//{
		//	;
		//}
		//getchar();

		/*fflush(stdin);*/
	}
}

//int main()
//{
//	char x[10];
//	char y[10];
//	char z[10];
//	char i[10];
//	scanf("%s", x);
//	scanf("%s", y);
//	scanf("%s", z);
//	scanf("%s", i);
//	printf("%s\n", x);
//	printf("%s\n", y);
//	printf("%s\n", z);
//	printf("%s\n", i);
//	printf("×Ö·û£º%c\n", getchar());
//	printf("×Ö·û£º%c\n", getchar());
//	printf("×Ö·û£º%c\n", getchar());
//	printf("×Ö·û£º%c\n", getchar());
////
//// 
////	char x, y;
////	scanf("%c", &x);
////	scanf("%c", &y);
////	char z = getchar();
////	printf("x = %c, y = %c, z = %c", x, y, z);
////
////	int a, b;
////	scanf("%d", &a);
////	scanf("%d", &b);
////	printf("a = %d, b = %d", a, b);
////	return 0;
//}



//int main()
//{
//
//	char x[10];
//	char y;
//	char z;
//	scanf("%s", x);
//	scanf("%c", &y);
//	scanf("%c", &z);
//	printf("×Ö·û´®Êä³ö£º%s\n", x);
//	printf("×Ö·ûÊä³ö£º%c\n", y);
//	printf("×Ö·ûÊä³ö£º%c\n", z);
//	//char y[10];
//	//char z[10];
//	//char i[10];
//
//	//scanf("%s", y);
//	//scanf("%s", z);
//	//scanf("%s", i);
//
//	//printf("%s", y);
//	//printf("%s", z);
//	//printf("%s", i);
//
//// 
//	//char x, y;
//	//scanf("%c", &x);
//	//scanf("%c", &y);
//	//char z = getchar();
//	//printf("x = %c, y = %c, z = %c", x, y, z);
//
//	//int a, b;
//	//scanf("%d", &a);
//	//scanf("%d", &b);
//	//printf("a = %d, b = %d", a, b);
//	//return 0;
//}