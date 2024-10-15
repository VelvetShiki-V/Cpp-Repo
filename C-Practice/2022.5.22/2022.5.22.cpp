#define _CRT_SECURE_NO_WARNINGS 1
#include"Stack_Queue.h"
//1. LeetCode——栈实现队列
//描述仅使用两个栈实现先入先出队列。队列应当支持一般队列支持的所有操作（push、pop、peek、empty）：
//实现 MyQueue 类：
//void push(int x) 将元素 x 推到队列的末尾
//int pop() 从队列的开头移除并返回元素
//int peek() 返回队列开头的元素
//boolean empty() 如果队列为空，返回 true ；否则，返回 false
void StackToQueue()
{
	MQ* obj = StructInit();
	//先按序压入1234
	Push(obj, 1);
	Push(obj, 2);
	Push(obj, 3);
	Push(obj, 4);
	printf("队头元素为：%d\n", Peek(obj));
	printf("弹出队头并返回元素为：%d\n", Pop(obj));

	//再压入567，只有pop栈为空时才将数据倒过去
	Push(obj, 5);
	Push(obj, 6);
	Push(obj, 7);
	printf("队头元素为：%d\n", Peek(obj));
	printf("弹出队头并返回元素为：%d\n", Pop(obj));
	if (Empty(obj))
	{
		puts("队列为空");
	}
	else
	{
		puts("队列不为空");
	}

	//遍历队列
	PrintQueue(obj);								
	if (Empty(obj))
	{
		puts("遍历后队列为空");
	}
	else
	{
		puts("遍历后队列不为空");
	}
	Free(obj);
}

//2. 队列实现栈
//描述：仅使用两个队列实现一个后入先出（LIFO）的栈，并支持普通栈的全部四种操作（push、top、pop 和 empty）。
//实现 MyStack 类：
//void push(int x) 将元素 x 压入栈顶。
//int pop() 移除并返回栈顶元素。
//int top() 返回栈顶元素。
//boolean empty() 如果栈是空的，返回 true ；否则，返回 false 。
void QueueToStack()
{
	MST* obj = StackCreate();
	PushQ(obj, 1);
	PushQ(obj, 2);
	PushQ(obj, 3);
	PushQ(obj, 4);
	PushQ(obj, 5);
	PushQ(obj, 6);
	PushQ(obj, 7);
	printf("读取此时栈顶元素为：%d\n", StackTop(obj));
	printf("弹栈并取出栈顶元素为：%d\n", StackPop(obj));
	printf("弹栈并取出栈顶元素为：%d\n", StackPop(obj));
	if (EmptyQ(obj))
	{
		printf("此时栈为空\n");
	}
	else
	{
		printf("此时栈不为空\n");
	}
	PrintQ(obj);
	PushQ(obj, 8);
	PushQ(obj, 9);
	PushQ(obj, 10);
	PushQ(obj, 11);
	PushQ(obj, 12);
	printf("弹栈并取出栈顶元素为：%d\n", StackPop(obj));
	printf("读取此时栈顶元素为：%d\n", StackTop(obj));
	printf("弹栈并取出栈顶元素为：%d\n", StackPop(obj));
	PrintQ(obj);
	if (EmptyQ(obj))
	{
		printf("此时栈为空\n");
	}
	else
	{
		printf("此时栈不为空\n");
	}
	FreeQ(obj);
}

int main()
{
	//StackToQueue();
	QueueToStack();
	return 0;
}