#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct S
{
	int len = 1;
	int arr[];
}*ps;

void Exit()
{
	printf("\nThe application is terminated, click the cross on the top right to exit.\n");
}

void Bisection_Method(int* array, int a, int b)
{
	int i, j;
	int left = 0;
	int right = b - 1;
	for (i = 0; i < b; i++)
	{
		j = (array[right] + array[left]) / 2;
		if (j < a)
		{
			array[left] = j;
		}
		else if(j > a)
		{
			array[right] = j;
		}
		else
		{
			printf("The number has been located at the position of %dth, which counts %d times to finish.", j, i + 1);
			break;
		}
	}
}

void Array_Ergotic_Method(int* arr, int d, int c)
{
	int i;
	for (i = 0; i < c; i++)
	{
		if (d == arr[i])
		{
			printf("\nThe integer is found also with Ergotic method, which counts %d times to finish\n", i + 1);
			break;
		}
	}
}

int main()
{
	char r = 0;
	int i, n, a;
	atexit(Exit);

	do
	{
		printf("\nThis code is to locate a number in an array.\n");
		printf("\nPlease input amount of numbers, range from 1 to 1000, in an array included: ");
		scanf("%d", &n);
		ps = (struct S*)malloc(sizeof(struct S) + n * sizeof(int));
		if (ps == NULL)
		{
			printf("%s\n", strerror(errno));  /*To prevent warning of C6011*/
		}
		else
		{
			printf("\nThe array is presented in the below:\n");
			for (i = 0; i < n; i++)
			{
				ps->arr[i] = i + 1;
				printf("%d ", ps->arr[i]);
			}
			printf("\nPlease input a number ranged from 0 to %d to be located in the array above: ", n);
			scanf("%d", &a);
			Bisection_Method(ps->arr, a, i);
			Array_Ergotic_Method(ps->arr, a, n);
			free(ps);
			ps = NULL;
		}
		printf("\nWanna try other numbers? Input Y or N to retry or exit: ");
		do
		{
			while ((r = getchar()) == '\n')
			{
				;
			}
			if (r == 'N')
			{
				return 0;
			}
			else if (r != 'Y')
			{
				printf("Please input Y or N\n");
			}
		} while (r != 'Y');
	} while (r == 'Y');
	return 0;
}


//#define _CRT_SECURE_NO_WARNINGS 
//#include<stdio.h>
//#include<stdlib.h>
//#include<string.h>
//#include<errno.h>
//struct S
//{
//	int len;
//	int arr[];
//};
//
//void Exit()
//{
//	printf("\nThe application is terminated, click the cross on the top right to exit.\n");
//}
//
//void Bisection_Method(int* arr, int a, int b)
//{
//	int i, j;
//	int left = 0;
//	int right = b - 1;
//	for (i = 0; i < b; i++)
//	{
//		j = (arr[right] + arr[left]) / 2;
//		if (j < a)
//		{
//			arr[left] = j;
//		}
//		else if (j > a)
//		{
//			arr[right] = j;
//		}
//		else
//		{
//			printf("The number has been located at the position of %dth, which counts %d times to finish.", j + 1, i + 1);
//			break;
//		}
//	}
//}

//int main()
//{
//	char r;
//	int i, n, a, sz;
//	struct S s1;
//	atexit(Exit);
//	do
//	{
//		printf("\nThis code is to locate a number in an array.\n");
//		printf("\nPlease input amount of numbers, range from 0 to 1000, in an array included: ");
//		scanf("%d", &s1.len);
//		n = s1.len;
//		struct S* ps = (struct S*)malloc(sizeof(struct S) + n * sizeof(int));
//		if (ps == NULL)
//		{
//			printf("%s\n", strerror(errno));  /*To prevent warning of C6011*/
//		}
//		else
//		{
//			printf("\nThe array is presented in the below:\n");
//			//for (i = 0; i <= n; i++)  //0到n是n+1个数
//			for (i = 0; i < n; i++)
//			{
//				ps->arr[i] = i;
//				printf("%d ", i);
//			}
//			sz = i;
//			printf("\nPlease input a number ranged from 0 to %d to be located in the array above: ", n);
//			scanf("%d", &a);
//			//Bisection_Method(ps->arr, a, sz);   
//			Bisection_Method(ps->arr, a, sz);   //数组 ，需要查找的数， 数组元素个数
//			free(ps);
//			ps = NULL;
//		}
//		printf("\nWanna try other numbers? Input Y or N to retry or exit: ");
//		do
//		{
//			while ((r = getchar()) == '\n')
//			{
//				;
//			}
//			if (r == 'N')
//			{
//				return 0;
//			}
//			else if (r != 'Y')
//			{
//				printf("Please input Y or N\n");
//			}
//		} while (r != 'Y');
//	} while (r == 'Y');
//	return 0;
//}
//
