#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<string.h>
int main()
{
	char x = '5', y = '6';
	printf("�ַ����֮�ͣ�%c %d\n", x + y, x + y);  //��ASCII��֮�ͣ��ֱ��ַ������ʮ�����������
	x = 50; y = 'A';
	printf("ʮ����ASCII���ַ����֮�ͣ�%c %d\n", x + y, x + y);  //ʵ��Ҳ��ASCII�ӷ����㣬ͬ��
	x = 'a'; y = 'b';
	int z = x + y;
	printf("�ַ����֮�ͣ�%c %d\n", x + y, x + y);  //ASCII���㣬�������ɴ�ӡ��Χ�����%d��������������
	printf("�ַ����֮�ͣ�%c %d\n", z, z);  //ASCII���㣬֮ǰ�Ѿ����й�����������
	getchar();
	return 0;
}


//int main()
//{
//	//int x = 'b';
//	//printf("%c %d\n", x, x); //�ַ���ֵ���ͱ������ַ������ʮ����ASCII�������
//	//x = 48;
//	//printf("%c %d\n", x, x); //����ֱ����ASCII��Ӧ�ַ�%c���
//	//char x = 'ab';
//	//printf("%c\n", x);  //�ַ�������ضϵ�b
//	//x = '34';
//	//printf("%d\n", x); //ʮ����������ضϵ�'4'��ӦASCII��
//	getchar();
//	return 0;
//}


//int main()
//{
//	char x = 127;  //�з���char��0 111 1111���߽�
//	printf("1. %d\n", x);
//	x = -128;     //�з���char��1 000 0000���߽�
//	printf("2. %d\n", x);
//	x = 128;     //�з���char�������߽磬����Ӹ��߽���0ѭ��:
//				//��λ��1 000 0000����1 111 1111��ʮ���ƣ�ѭ��
//	printf("3. %d\n", x);
//	x = 150;     //���߽������������پ��൱���ø��߽�Ӽ��ζ����Ʋ���0000 0001
//				//128 - 150 = -22�����22������-128 + 22��������1�õ�-106
//	printf("4. %d\n", x);
//	unsigned char y = 255;   //�޷��������ϱ߽�
//	printf("5. %d\n", y);
//	y = 256;     //�����޷���char��1111 1111�ϱ߽磬���±߽��������0��ʼ�ۼӲ���1ѭ����ԭ��ͬ��
//	printf("6. %d\n", y);
//	y = -1;      //�����޷���char��0000 0000�±߽磬���ϱ߽����ѭ��
//	printf("7. %d\n", y);
//	getchar();
//	return 0;
//}


//int main()
//{
//	//char���ַ����ͱ��������ڽ����ַ������֣�Ҳ���Խ�������
//	char x = 'a';       //���ܲ��ӵ�����д��a������ע����ʶ��aδ����
//	printf("1. %c %d\n", x, x); //�ַ�����ַ����������ASCII��
//	x = '5';
//	printf("2. %c %d\n", x, x);//����ַ�5���������ASCII��
//	x = 5;
//	printf("3. %c %d\n", x, x);//�ַ���ASCII = 5������޷���ӡ�������ַ������������5
//	x = '32';                 //�ɴ�ӡ�ַ�ASCII��Χʮ���ƣ�32~126���ӿո񵽲��˺ţ�
//	printf("4. %c %d\n", x, x);//����ַ�'2'����Ϊ��������ֻ�ܶ�ȡһ���ַ�������ͬ��
//							  //�����ַ�'2'����ӦASCII���50
//	x = 32;
//	printf("5. %c %d\n", x, x);//�ַ���ASCII = 32���ո�������������32
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
//    //char j[6] = {65,65 ,65 ,65 ,'\0'}; //��
///*    printf("%c %d", j[1], j[1]);  */     //��ʽ������ַ���%s���ַ�%cʱ���Զ�Ϊ������ÿ���±��Ӧ��ֵ���ϵ�����''����ASCII�����
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