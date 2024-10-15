#define _CRT_SECURE_NO_WARNINGS 1
#include"Stack.h"

void StackInit(ST* Bot)									//栈结构的初始化
{
	Bot->a = NULL;
	Bot->capacity = Bot->top = 0;
}

void StackPush(ST* Bot, StackEtype x)					//压栈，只能在栈顶插入数据
{
	assert(Bot);
	if (Bot->capacity == Bot->top)
	{
		int expand = Bot->capacity == 0 ? 4 : Bot->capacity * 2;
		StackEtype* tmp = (StackEtype*)realloc(Bot->a, sizeof(StackEtype)* expand);				//必须使用realloc函数调整实参栈空间（原地或异地扩容）
		assert(tmp);
		Bot->a = tmp;
		Bot->capacity = expand;
	}
	Bot->a[Bot->top] = x;
	Bot->top++;
}

void StackPop(ST* Bot)									//出栈，只能从栈顶删除数据
{
	assert(Bot);
	//assert(Bot->top > 0);
	assert(!StackEmpty(Bot));
	Bot->top--;
}

bool StackEmpty(ST* Bot)								//判断栈是否为空
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
	return Bot->top == 0;								//直接用返回布尔值判断，不用if-else判断
}

void StackDestroy(ST* Bot)								//栈结构的销毁
{
	assert(Bot);
	free(Bot->a);
	Bot->a = NULL;
	Bot->capacity = Bot->top = 0;
}

StackEtype StackTop(ST* Bot)							//取出栈顶元素
{
	assert(Bot);
	assert(!StackEmpty(Bot));
	return Bot->a[Bot->top - 1];
}

int StackSize(ST* Bot)									//计算压栈元素个数
{
	assert(Bot);
	return Bot->top;
}
