#define _CRT_SECURE_NO_WARNINGS 1
#include"Queue.h"

void QueueTest_1()							//队列性质为先进先出，所以无论中途出多少数据，所有数据的相对顺序都不变
{
	QP QueuePtr;
	QueueInit(&QueuePtr);
	QPushBack(&QueuePtr, 1);
	QPushBack(&QueuePtr, 2);
	QPushBack(&QueuePtr, 3);
	QPushBack(&QueuePtr, 4);
	QPushBack(&QueuePtr, 5);
	//QueueDestroy(&QueuePtr);				//提前销毁队列，则后续访问会出错（打印不会，取值会）
	QPopFront(&QueuePtr);
	QPopFront(&QueuePtr);
	QPopFront(&QueuePtr);
	//QPopFront(&QueuePtr);
	//QPopFront(&QueuePtr);					//队列元素全部头删完，此时队列为空
	Print(&QueuePtr);						//打印只是为了方便观察，但队列性质规定其遍历元素只能通过头删直到队列尾，每个数据才真正能够取到
	printf("队头元素为：%d\n", GetQHead(&QueuePtr));
	printf("队尾元素为：%d\n", GetQTail(&QueuePtr));
	printf("队列大小为：%d\n", QueueSize(&QueuePtr));
	QueueDestroy(&QueuePtr);
}

int main()
{
	QueueTest_1();
	return 0;
}