#define _CRT_SECURE_NO_WARNINGS 1
#include"HeapFunc.h"

void Test_1()
{
	HP heap;
	HPInit(&heap);
	HP* hp = &heap;
	HPEtype a[] = { 3,20,8,6,1,4,62,43,23,12,10,77,30 };
	int sz = sizeof(a) / sizeof(a[0]);
	for (int i = 0; i < sz; i++)
	{
		SmHPPush(hp, a[i]);
	}
	printf("观察小堆的物理结构（顺序表）:");
	for (int i = 0; i < sz; i++)
	{
		printf("%d ", hp->arr[i]);
	}
	printf("\n遍历堆（小堆遍历等同于升序打印并清空：）");		//算法时间复杂度O(N^2)，因为每次取顶去顶后，要重新排堆
	SmPrint(hp);
	HPDestroy(hp);
}

void Test_2()
{
	HP heap;
	HPInit(&heap);
	HP* hp = &heap;
	HPEtype a[] = { 3,20,8,6,1,4,62,43,23,12,10,77,30 };
	int sz = sizeof(a) / sizeof(a[0]);
	printf("观察大根堆物理结构（顺序表）：");
	for (int i = 0; i < sz; i++)
	{
		BigHPPush(hp, a[i]);
	}
	for (int i = 0; i < sz; i++)
	{
		printf("%d ", hp->arr[i]);
	}
	printf("\n遍历堆（大堆遍历等同于升序打印并清空：）");		//算法时间复杂度O(N^2)，因为每次取顶去顶后，要重新排堆
	BigPrint(hp);
	printf("此时堆的元素个数：%d\n", HPSize(hp));
	printf("此时的堆顶元素：%d\n", HPTop(hp));
	HPDestroy(hp);
}

void Test_3()
{
	HP heap;
	HPInit(&heap);
	HP* hp = &heap;
	HPEtype a[] = { 83, 49,72,0,5,2,98,37,10,8,5,2,1,7,3,5,0,2 };
	int sz = sizeof(a) / sizeof(a[0]);
	printf("升序建大堆\n");
	for (int i = 0; i < sz; i++)
	{
		BigHPPush(hp, a[i]);
	}
	printf("大堆建成后的结构：");
	for (int i = 0; i < sz; i++)
	{
		printf("%d ", hp->arr[i]);
	}
	printf("\n观察堆升序算法后数组：");
	HPSortAscend(hp);
	for (int i = 0; i < sz; i++)
	{
		printf("%d ", hp->arr[i]);
	}

	//printf("观察堆降序算法后数组：");
	//HPSortDescend(hp);						//降序
	//for (int i = 0; i < sz; i++)
	//{
	//	printf("%d ", hp->arr[i]);
	//}
}

int main()
{
	//Test_1();			//小堆存储和遍历打印
	//Test_2();			//大堆存储和遍历打印
	Test_3();			//堆升序
	//Test_4();			//堆降序
	return 0;
}