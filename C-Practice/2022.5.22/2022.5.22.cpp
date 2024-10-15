#define _CRT_SECURE_NO_WARNINGS 1
#include"Stack_Queue.h"
//1. LeetCode����ջʵ�ֶ���
//������ʹ������ջʵ�������ȳ����С�����Ӧ��֧��һ�����֧�ֵ����в�����push��pop��peek��empty����
//ʵ�� MyQueue �ࣺ
//void push(int x) ��Ԫ�� x �Ƶ����е�ĩβ
//int pop() �Ӷ��еĿ�ͷ�Ƴ�������Ԫ��
//int peek() ���ض��п�ͷ��Ԫ��
//boolean empty() �������Ϊ�գ����� true �����򣬷��� false
void StackToQueue()
{
	MQ* obj = StructInit();
	//�Ȱ���ѹ��1234
	Push(obj, 1);
	Push(obj, 2);
	Push(obj, 3);
	Push(obj, 4);
	printf("��ͷԪ��Ϊ��%d\n", Peek(obj));
	printf("������ͷ������Ԫ��Ϊ��%d\n", Pop(obj));

	//��ѹ��567��ֻ��popջΪ��ʱ�Ž����ݵ���ȥ
	Push(obj, 5);
	Push(obj, 6);
	Push(obj, 7);
	printf("��ͷԪ��Ϊ��%d\n", Peek(obj));
	printf("������ͷ������Ԫ��Ϊ��%d\n", Pop(obj));
	if (Empty(obj))
	{
		puts("����Ϊ��");
	}
	else
	{
		puts("���в�Ϊ��");
	}

	//��������
	PrintQueue(obj);								
	if (Empty(obj))
	{
		puts("���������Ϊ��");
	}
	else
	{
		puts("��������в�Ϊ��");
	}
	Free(obj);
}

//2. ����ʵ��ջ
//��������ʹ����������ʵ��һ�������ȳ���LIFO����ջ����֧����ͨջ��ȫ�����ֲ�����push��top��pop �� empty����
//ʵ�� MyStack �ࣺ
//void push(int x) ��Ԫ�� x ѹ��ջ����
//int pop() �Ƴ�������ջ��Ԫ�ء�
//int top() ����ջ��Ԫ�ء�
//boolean empty() ���ջ�ǿյģ����� true �����򣬷��� false ��
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
	printf("��ȡ��ʱջ��Ԫ��Ϊ��%d\n", StackTop(obj));
	printf("��ջ��ȡ��ջ��Ԫ��Ϊ��%d\n", StackPop(obj));
	printf("��ջ��ȡ��ջ��Ԫ��Ϊ��%d\n", StackPop(obj));
	if (EmptyQ(obj))
	{
		printf("��ʱջΪ��\n");
	}
	else
	{
		printf("��ʱջ��Ϊ��\n");
	}
	PrintQ(obj);
	PushQ(obj, 8);
	PushQ(obj, 9);
	PushQ(obj, 10);
	PushQ(obj, 11);
	PushQ(obj, 12);
	printf("��ջ��ȡ��ջ��Ԫ��Ϊ��%d\n", StackPop(obj));
	printf("��ȡ��ʱջ��Ԫ��Ϊ��%d\n", StackTop(obj));
	printf("��ջ��ȡ��ջ��Ԫ��Ϊ��%d\n", StackPop(obj));
	PrintQ(obj);
	if (EmptyQ(obj))
	{
		printf("��ʱջΪ��\n");
	}
	else
	{
		printf("��ʱջ��Ϊ��\n");
	}
	FreeQ(obj);
}

int main()
{
	//StackToQueue();
	QueueToStack();
	return 0;
}