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
	MergeSort(arr, sz);
	//for (int i = 0; i < sz; i++)
	//{
	//	printf("%d ", arr[i]);
	//}
}

int main()
{
	//test_Insert();
	//test_Shell();
	//test_Select();
	//test_Bubble();
	//test_Quick();
	test_Merge();
}