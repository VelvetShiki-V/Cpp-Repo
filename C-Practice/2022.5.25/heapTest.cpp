#define _CRT_SECURE_NO_WARNINGS 1
#include"heap.h"

int main()
{
	int arr[] = { 1,5,2,8,6,3,9,10,25,47,37,56 };
	int i = 0;
	int sz = sizeof(arr) / sizeof(arr[0]);
	HP hp;
	HeapInit(&hp);
	HP* heap = &hp;
	for (i = 0; i < sz; i++)
	{
		HPPush(heap, arr[i]);
	}
	HeapDestroy(heap);
	return 0;
}