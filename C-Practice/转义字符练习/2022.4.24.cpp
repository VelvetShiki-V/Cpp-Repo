#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<string.h>
int main()          //ת���ַ�
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


//int main()          //�ַ���������
//{
//    const int a = 5;
//    int arr1[a] = { 1 };
//    int j = sizeof(arr1) / sizeof(int);
//    printf("%d", j);
//    printf("okk??)");
//    getchar();
//    //int n = 5, arr[n] = { 0 };    //����д��������������Ϊ��������ֵ
//    //int arr1[5] = { 0 };
//    return 0;
//}


//int main()          //ת���ַ�
//{
//    printf("�˽���ת��ΪASCII�ַ���\061\nʮ������ת��ΪASCII�ַ���\x68\n");
//    printf("%d\n", strlen("c:\test\628\test.c\n"));     //���15
//    printf("ʹ�ð˽���ת��ո�' '��\40��ʹ��ʮ������ת��س���\xA");       //�ո��ASC��32��ת��Ϊ16������x20��ʹ��ת���ַ�Ϊ \x20
//    printf("%d\n", strlen("c:\test\121"));      //ת���ַ�ռһ���ֽڣ�\t��\121��ռ2���ֽڣ��ֱ��������tab�Ͱ˽���ת��ascii
//    return 0;
//}


//int main()    //������ʽ(-8+22)��a-10+c��2�����У�a = 40��c = 212
//{
//	int a = 40, c = 212;
//	printf("%d", (-8 + 22) * a - 10 + c / 2);
//	return 0;
//}


//int main()   // ���������������ͳ�������������̺�����
//{
//	int a, b;
//	scanf("%d %d", &a, &b);
//	printf("%d %d", a / b, a % b);
//	return 0;
//}


//int main()    //���Ҫ��ĸ�ʽ�ַ���
//{
//    //printf("%-8s%-7s%-6s\n", "Name", "Age", "Gender");      //��ʽ�����д��
//    //printf("---------------------\n");
//    //printf("%-8s%-7s%-6s\n", "Jack", "18", "man");
//    //return 0;
//
//    printf("Name    Age    Gender\n");      //д����
//    printf("---------------------\n");
//    printf("Jack    18     man");
//}


//int main()      //���������
//{
//    int a;
//    scanf("%d", &a);
//    if (a >= 140)
//    {
//        printf("Genius");
//    }
//    return 0;
//}


//int main()       //�����������Ƚϴ�С������ϴ���
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


//int main()      //�������������-1������0�����0�����븺�������1
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