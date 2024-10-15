#define _CRT_SECURE_NO_WARNINGS 1
#include"Stack.h"

void Test_1()
{
	ST StackBot;
	StackInit(&StackBot);
	StackPush(&StackBot, 5);			//ѹջ
	StackPush(&StackBot, 4);
	StackPush(&StackBot, 3);
	StackPush(&StackBot, 2);
	StackPush(&StackBot, 1);

	StackPop(&StackBot);				//��ջ
	StackPop(&StackBot);
	//StackDestroy(&StackBot);			//����ջ������
	StackPop(&StackBot);
	//StackPop(&StackBot);
	//StackPop(&StackBot);				//��ѹջԪ����գ���ʱtopΪ0
	//StackPop(&StackBot);				//��ɾһ�Σ���Ϊջ�Ѿ�Ϊ�գ����Ա���
	printf("ջ��Ԫ��Ϊ��%d\n��ʱջ�ڻ�����%d��Ԫ��\n", StackTop(&StackBot), StackSize(&StackBot));
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
	//����ջ������Ϊջֻ�ܴ�ջ����ջ�׷��ʣ����Ա�������ζ�����ջ
	while (StackBot.top)				//ѭ���ж�����Ҳ�������пպ���������while(!StackEmpty(&StackBot));
	{
		//printf("%d ", StackBot.a[StackBot.top - 1]);		//����ȡջ��ֵ��ʽ
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