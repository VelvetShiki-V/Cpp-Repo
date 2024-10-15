#include"Func.h"

void test_Insert()
{
	int arr[] = { 3,1,8,9,0,4,7,2,5,10,6 };
	int arr1[] = { -3,9,-5,6,4,2,10,8,1};
	int sz = sizeof(arr) / sizeof(arr[0]);
	InsertSort(arr, sz);
	for (int i = 0; i < sz; i++)
	{
		printf("%d ", arr[i]);
	}
}

void test_Shell()
{
	int arr[] = { 3,1,8,9,0,4,7,2,5,10,6 };
	int arr1[] = { -3,9,-5,6,4,2,10,8,1 };
	int sz = sizeof(arr1) / sizeof(arr[0]);
	ShellSort(arr1, sz);
	for (int i = 0; i < sz; i++)
	{
		printf("%d ", arr1[i]);
	}
}

void test_Select()
{
	int arr[] = { 3,1,8,9,0,4,7,2,5,10,6 };
	int arr1[] = { -3,9,-5,6,4,2,10,8,1, 0 };
	int arr2[] = {6,4,2,1,0};
	int sz = sizeof(arr2) / sizeof(int);
	SelectSort(arr2, sz);
	for (int i = 0; i < sz; i++)
	{
		printf("%d ", arr2[i]);
	}
}

void test_Bubble()
{
	int arr[] = { 3,1,8,9,0,4,7,2,5,10,6 };
	int arr1[] = { -3,9,-5,6,4,2,10,8,1, 0 };
	int arr2[] = { 10,9,8,5,7,6,4,2,1,0, 3 };
	int arr3[] = { 10,9,8,7,5,6,4,3,2,1 };
	int sz = sizeof(arr3) / sizeof(int);
	BubbleSort(arr3, sz);
	for (int i = 0; i < sz; i++)
	{
		printf("%d ", arr3[i]);
	}
}

void test_Quick()
{
	int arr[] = { 3,1,8,9,0,4,7,2,5,10,6 };
	int arr3[] = { 10,9,8,7,5,6,4,3,2,1 };
	int sz = sizeof(arr) / sizeof(int);
	//QuickSort(arr3, 0, sz - 1);
	//for (int i = 0; i < sz; i++)
	//{
	//	printf("%d ", arr3[i]);
	//}
	QuickSortStack(arr, 0, sz - 1);
	for (int i = 0; i < sz; i++)
	{
		printf("%d ", arr[i]);
	}
}

void test_Merge()
{
	int arr[] = { 3,1,8, 10, 5};
	//int arr[] = { 3,1,8,9,0,4,7,2,5,10,6 };
	int arr1[] = { 10,9,8,7,5,6,4,3,2,1 };
	int sz = sizeof(arr) / sizeof(int);
	//MergeSort(arr, sz);
	NonRecurMergeSort(arr, sz);
	//for (int i = 0; i < sz; i++)
	//{
	//	printf("%d ", arr[i]);
	//}
}

void test_Count()
{
	int arr[] = { 6,1,8,10,5,4,7,6,5,10,6,0,0 };
	int arr1[] = { 1005, 1003, 1001, 1020, 1015, 1000 };
	int sz = sizeof(arr1) / sizeof(int);
	CountSort(arr1, sz);
	for (int i = 0; i < sz; i++)
	{
		printf("%d ", arr1[i]);
	}
}

void test_HPSort()
{
	int arr[] = { 6,1,8,10,5,4,7,6,5,10,6,0,0 };
	int arr1[] = { 1005, 1003, 1001, 1020, 1015, 1000 };
	int sz = sizeof(arr1) / sizeof(int);
	HPCreate(arr1, sz, Ascend);
	HPSort(arr1, sz, Ascend);
	for (int i = 0; i < sz; i++)
	{
		printf("%d ", arr1[i]);
	}
}

void test_time()
{
	srand(time(0));
	const int N = 10000000;
	int* a1 = (int*)malloc(sizeof(int) * N);
	int* a2 = (int*)malloc(sizeof(int) * N);
	int* a3 = (int*)malloc(sizeof(int) * N);
	int* a4 = (int*)malloc(sizeof(int) * N);
	int* a5 = (int*)malloc(sizeof(int) * N);
	int* a6 = (int*)malloc(sizeof(int) * N);
	int* a7 = (int*)malloc(sizeof(int) * N);
	int* a8 = (int*)malloc(sizeof(int) * N);

	for (int i = 0; i < N; ++i)
	{
		a1[i] = rand();
		a2[i] = a1[i];
		a3[i] = a2[i];
		a4[i] = a3[i];
		a5[i] = a4[i];
		a6[i] = a5[i];
		a7[i] = a6[i];
		a8[i] = a7[i];
	}

	int begin1 = clock();
	QuickSort(a1, 0, N - 1);
	int end1 = clock();

	int begin2 = clock();
	QuickSortStack(a2, 0, N - 1);
	int end2 = clock();

	int begin3 = clock();
	MergeSort(a3, N);
	int end3 = clock();

	int begin4 = clock();
	NonRecurMergeSort(a4, N);
	int end4 = clock();

	int begin5 = clock();
	ShellSort(a5, N);
	int end5 = clock();

	int begin6 = clock();
	HPCreate(a6, N, Ascend);
	HPSort(a6, N, Ascend);
	int end6 = clock();

	int begin7 = clock();
	//InsertSort(a7, N);
	int end7 = clock();

	int begin8 = clock();
	//BubbleSort(a8, N);
	int end8 = clock();

	printf("QuickSort:%d\n", end1 - begin1);
	printf("QuickSortStack:%d\n", end2 - begin2);
	printf("MergeSort:%d\n", end3 - begin3);
	printf("NonRecurMergeSort:%d\n", end4 - begin4);
	printf("ShellSort:%d\n", end5 - begin5);
	printf("HeapSort:%d\n", end6 - begin6);
	printf("InsertSort:%d\n", end7 - begin7);
	printf("BubbleSort:%d\n", end8 - begin8);

	free(a1);
	free(a2);
	free(a3);
	free(a4);
	free(a5);
	free(a6);
	free(a7);
	free(a8);
}

int main()
{
	//test_Insert();
	//test_Shell();
	//test_Select();
	//test_Bubble();
	//test_Quick();
	//test_Merge();
	//test_Count();
	//test_HPSort();
	test_time();
}