#define _CRT_SECURE_NO_WARNINGS 1
#include"Stack.h"

void Test_1()
{
	ST StackBot;
	StackInit(&StackBot);
	StackPush(&StackBot, 5);			//压栈
	StackPush(&StackBot, 4);
	StackPush(&StackBot, 3);
	StackPush(&StackBot, 2);
	StackPush(&StackBot, 1);

	StackPop(&StackBot);				//出栈
	StackPop(&StackBot);
	//StackDestroy(&StackBot);			//假设栈销毁了
	StackPop(&StackBot);
	//StackPop(&StackBot);
	//StackPop(&StackBot);				//将压栈元素清空，此时top为0
	//StackPop(&StackBot);				//多删一次，因为栈已经为空，所以报错
	printf("栈顶元素为：%d\n此时栈内还存在%d个元素\n", StackTop(&StackBot), StackSize(&StackBot));
	StackDestroy(&StackBot);			
}

void Test_2()
{
	ST StackBot;
	StackInit(&StackBot);
	StackPush(&StackBot, 1);		
	StackPush(&StackBot, 2);
	StackPush(&StackBot, 3);
	StackPush(&StackBot, 4);
	StackPush(&StackBot, 5);
	//遍历栈，但因为栈只能从栈顶到栈底访问，所以遍历就意味着清空栈
	while (StackBot.top)				//循环判断条件也可以由判空函数来控制while(!StackEmpty(&StackBot));
	{
		//printf("%d ", StackBot.a[StackBot.top - 1]);		//两种取栈顶值方式
		printf("%d ", StackTop(&StackBot));
		StackPop(&StackBot);
	}
	StackDestroy(&StackBot);

}

//int main()
//{
//	//Test_1();
//	Test_2();
//	return 0;
//}