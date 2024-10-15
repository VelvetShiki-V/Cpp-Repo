#define _CRT_SECURE_NO_WARNINGS 1
#include"Stack.h"

void StackInit(ST* Bot)									//ջ�ṹ�ĳ�ʼ��
{
	Bot->a = NULL;
	Bot->capacity = Bot->top = 0;
}

void StackPush(ST* Bot, StackEtype x)					//ѹջ��ֻ����ջ����������
{
	assert(Bot);
	if (Bot->capacity == Bot->top)
	{
		int expand = Bot->capacity == 0 ? 4 : Bot->capacity * 2;
		StackEtype* tmp = (StackEtype*)realloc(Bot->a, sizeof(StackEtype)* expand);				//����ʹ��realloc��������ʵ��ջ�ռ䣨ԭ�ػ�������ݣ�
		assert(tmp);
		Bot->a = tmp;
		Bot->capacity = expand;
	}
	Bot->a[Bot->top] = x;
	Bot->top++;
}

void StackPop(ST* Bot)									//��ջ��ֻ�ܴ�ջ��ɾ������
{
	assert(Bot);
	//assert(Bot->top > 0);
	assert(!StackEmpty(Bot));
	Bot->top--;
}

bool StackEmpty(ST* Bot)								//�ж�ջ�Ƿ�Ϊ��
{
	assert(Bot);
	//if (Bot->top == 0)
	//{
	//	return true;
	//}
	//else
	//{
	//	return false;
	//}
	return Bot->top == 0;								//ֱ���÷��ز���ֵ�жϣ�����if-else�ж�
}

void StackDestroy(ST* Bot)								//ջ�ṹ������
{
	assert(Bot);
	free(Bot->a);
	Bot->a = NULL;
	Bot->capacity = Bot->top = 0;
}

StackEtype StackTop(ST* Bot)							//ȡ��ջ��Ԫ��
{
	assert(Bot);
	assert(!StackEmpty(Bot));
	return Bot->a[Bot->top - 1];
}

int StackSize(ST* Bot)									//����ѹջԪ�ظ���
{
	assert(Bot);
	return Bot->top;
}
