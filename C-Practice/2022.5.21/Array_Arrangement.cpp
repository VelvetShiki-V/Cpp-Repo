#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>

struct S
{
	int z = 1;
	int arr[];
}ps;

void exit()
{
	printf("\nThe application is terminated, click the cross on the top right to exit.\n");
}

void Array_Arrangement(int* arr, int a)
{
	int i, j, tmp;
	for (j = 0; j < a - 1; j++)
	{
		for (i = 0; i < a - 1; i++)
		{
			if (arr[i] > arr[i + 1])
			{
				tmp = arr[i];
				arr[i] = arr[i + 1];
				arr[i + 1] = tmp;
			}
		}
	}
}

int main()
{
	char r;
	int i, n;
	atexit(exit);

	do
	{
		printf("\nThis code is to arrange an array in order.\n");
		printf("\nPlease input amount of numbers wanted to be calculated: ");
		scanf("%d", &n);
		struct S* ps = (struct S*)malloc(sizeof(struct S) + n * sizeof(int));
		printf("\nPlease input integers:\n");
		for (i = 0; i < n; i++)
		{
			scanf("%d", &ps->arr[i]);
		}
		Array_Arrangement(ps->arr, n);
		for (i = 0; i < n; i++)
		{
			printf("%d  ", ps->arr[i]);
		}
		free(ps);
		ps = NULL;

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