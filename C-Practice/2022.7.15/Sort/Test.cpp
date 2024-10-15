#include"Func.h"

void test1()
{
	int arr[] = { 9,2,3,7,1,8,0,4,10,5, -1, -3, 50};
	int sz = sizeof(arr) / sizeof(arr[0]);
	InsertSort2(arr, sz, Descend);
	for (int i = 0; i < sz; i++)
	{
		printf("%d ", arr[i]);
	}
}

void test2()
{
	//int arr[] = { 9,2,3,7,1,8,0,4,10,5,6 };
	int arr[] = { 1,2,3,4,6,5,7,8};
	int sz = sizeof(arr) / sizeof(arr[0]);
	printf("原数组：");
	for (int i = 0; i < sz; i++)
	{
		printf("%d ", arr[i]);
	}
	printf("\n");
	//ShellSort(arr, sz, Ascend);
	//BubbleSort(arr, sz, Descend);
	BubbleSortRevised(arr, sz, Ascend);
	//HPCreateDown(arr, sz, Bigger);
	//HPSort(arr, sz, Bigger);
	for (int i = 0; i < sz; i++)
	{
		printf("%d ", arr[i]);
	}
}

void test3_time()
{
	srand(time(0));
	const int N = 1000000;
	//int* a1 = (int*)malloc(sizeof(int) * N);
	//int* a2 = (int*)malloc(sizeof(int) * N);
	int* a3 = (int*)malloc(sizeof(int) * N);
	int* a4 = (int*)malloc(sizeof(int) * N);
	//int* a5 = (int*)malloc(sizeof(int) * N);
	//int* a6 = (int*)malloc(sizeof(int) * N);
	int* a7 = (int*)malloc(sizeof(int) * N);
	int* a8 = (int*)malloc(sizeof(int) * N);
	int* a9 = (int*)malloc(sizeof(int) * N);

	for (int i = 0; i < N; ++i)
	{
		a3[i] = rand();
		//a2[i] = a1[i];
		a4[i] = a3[i];
		a7[i] = a3[i];
		a8[i] = a3[i];
		a9[i] = a3[i];
		//a5[i] = a1[i];
		//a6[i] = a1[i];
		//a7[i] = a1[i];
	}

	int begin1 = clock();
	//InsertSort(a1, N, Ascend);
	int end1 = clock();

	int begin2 = clock();
	//BubbleSort(a2, N, Ascend);
	int end2 = clock();

	int begin3 = clock();
	ShellSort(a3, N, Ascend);
	int end3 = clock();

	int begin4 = clock();
	HPCreateDown(a4, N, Bigger);
	HPSort(a4, N, Bigger);
	int end4 = clock();

	int begin5 = clock();
	//SelectSort(a5, N, Ascend);
	int end5 = clock();

	int begin6 = clock();
	//BubbleSortRevised(a6, N, Ascend);
	int end6 = clock();

	int begin7 = clock();
	QuickSort(a7, 0, N - 1);
	int end7 = clock();

	int begin8 = clock();
	QuickSortStack(a8, 0, N - 1);
	int end8 = clock();

	int begin9 = clock();
	MergeSort(a9, N);
	int end9 = clock();

	printf("InsertSort:%d\n", end1 - begin1);
	printf("BubbleSort:%d\n", end2 - begin2);
	printf("BubbleSortRevised:%d\n", end6 - begin6);
	printf("SelectSort:%d\n", end5 - begin5);
	printf("ShellSort:%d\n", end3 - begin3);
	printf("HeapSort:%d\n", end4 - begin4);
	printf("QuickSort:%d\n", end7 - begin7);
	printf("QuickSortStack:%d\n", end8 - begin8);
	printf("MergeSort:%d\n", end9 - begin9);

	//free(a1);
	//free(a2);
	free(a3);
	free(a4);
	//free(a5);
	//free(a6);
	free(a7);
	free(a8);
}

void test4()
{
	int arr[] = { 9,2,3,7,1,8,0,4,10,5,6 };
	//int arr[] = { 3,4,5,1};
	int sz = sizeof(arr) / sizeof(arr[0]);
	SelectSort(arr, sz, Descend);
	for (int i = 0; i < sz; i++)
	{
		printf("%d ", arr[i]);
	}
}

void test5()
{
	int arr[] = { 9,2,3,7,1,8,0,4,10,5,6 };
	//int arr[] = { 6,1,2,7,9,3,4,5,10,8 };
	int sz = sizeof(arr) / sizeof(arr[0]);
	QuickSort(arr, 0, sz - 1);
	for (int i = 0; i < sz; i++)
	{
		printf("%d ", arr[i]);
	}
	printf("\n共递归%d次\n", count);
}

void test6()
{
	//int arr[] = { 9,2,3,7,1,8,0,4,10,5,6 };
	//int arr[] = { 6,1,2,7,9,3,4,5,10,8 };
	int arr[] = { 7,41,50,35,27,11,46,33,21,8,21 };
	//int arr[] = { 8, 41, 7, 0};
	int sz = sizeof(arr) / sizeof(arr[0]);
	QuickSortStack(arr, 0, sz - 1);
	for (int i = 0; i < sz; i++)
	{
		printf("%d ", arr[i]);
	}
}

void test7()
{
	//int arr[] = { 9,2,3,7,1,8,0,4,10,5,6 };
	int arr[] = { 6,1,2,7,9,3,4,5,10,8 ,11, 0};
	//int arr[] = { 7,41,50,35,27,11,46,33,21,8,21 };
	//int arr[] = { 8, 41, 7, 0};
	//int arr[] = { 10,6,7,1,3,9,4,2,5};
	int sz = sizeof(arr) / sizeof(arr[0]);
	//MergeSort(arr, sz);
	NonRecurMergeSort(arr, sz);
	//MergeSortNonR(arr, sz);
	for (int i = 0; i < sz; i++)
	{
		printf("%d ", arr[i]);
	}
}

void test8()
{
	int arr[] = { 9,6,8,7,1,8,0,4,10,9,6 };
	//int arr[] = { 6,1,2,7,9,3,4,5,10,8 ,11, 0 };
	int sz = sizeof(arr) / sizeof(arr[0]);
	CountSort(arr, sz);
	for (int i = 0; i < sz; i++)
	{
		printf("%d ", arr[i]);
	}
}

int main()
{
	//test1()
	//test2();
	//test3_time();
	//test4();
	//test5();
	//test6();
	//test7();
	test8();
	return 0;
}