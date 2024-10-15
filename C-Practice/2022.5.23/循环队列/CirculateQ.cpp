#define _CRT_SECURE_NO_WARNINGS 1
#include"CiurcQueue.h"
//LeetCode 设计循环队列——遵循FIFO（先进先出）原则且队尾被连接在队首之后以形成一个循环，它也被称为“环形缓冲器”。
//循环队列的好处：可以利用这个队列之前用过的空间，一旦一个队列满了，能使用相同空间去存储新的值
//描述：MyCircularQueue(k): 构造器，设置队列长度为 k 。
//Front: 从队首获取元素。如果队列为空，返回 - 1 。
//Rear : 获取队尾元素。如果队列为空，返回 - 1 。
//enQueue(value) : 向循环队列插入一个元素。如果成功插入则返回真。
//deQueue() : 从循环队列中删除一个元素。如果成功删除则返回真。
//Empty() : 检查循环队列是否为空。
//Full() : 检查循环队列是否已满。

void Judge(bool x)					//判断入队或出队是否成功
{
	if (x)
	{
		puts("true");
	}
	else
	{
		puts("false");
	}
}

void CirQueue_Test1()
{
	CRQ* arr = Create(5);
	//入队
	printf("入队\n");
	Judge(enQueue(arr, 1));
	Judge(enQueue(arr, 2));
	Judge(enQueue(arr, 3));
	Judge(enQueue(arr, 4));
	Judge(enQueue(arr, 5));
	Judge(enQueue(arr, 6));
	//出队
	printf("出队\n");
	Judge(deQueue(arr));
	Judge(deQueue(arr));
	Judge(deQueue(arr));
	Judge(deQueue(arr));
	Judge(deQueue(arr));
	Judge(deQueue(arr));
	Free(arr);
}

void CirQueue_Test2()
{
	CRQ* arr = Create(3);
	printf("此时队头元素为：%d\n", GetFront(arr));
	printf("此时队尾元素为：%d\n", GetRear(arr));
	printf("入队\n");
	Judge(enQueue(arr, 1));
	Judge(enQueue(arr, 2));
	Judge(enQueue(arr, 3));
	Judge(enQueue(arr, 4));
	printf("此时队头元素为：%d\n", GetFront(arr));
	printf("此时队尾元素为：%d\n", GetRear(arr));
	Judge(deQueue(arr));
	Judge(deQueue(arr));
	Judge(deQueue(arr));
	//Judge(deQueue(arr));
	Judge(enQueue(arr, 4));
	//Judge(enQueue(arr, 5));
	//Judge(enQueue(arr, 5));
	//Judge(enQueue(arr, 5));
	printf("此时队头元素为：%d\n", GetFront(arr));
	printf("此时队尾元素为：%d\n", GetRear(arr));
	Free(arr);
}

int main()
{
	//CirQueue_Test1();
	CirQueue_Test2();
	return 0;
}

