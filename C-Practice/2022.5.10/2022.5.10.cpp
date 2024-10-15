#define _CRT_SECURE_NO_WARNINGS 1
#include"SqListPrac.h"

int main()
{
	int input = 0, ret = 0;
	SL arr;
	SLInit(&arr);
	printf("请输入功能选择：\n1. 尾插值 2. 头插值 3. 尾删值 \n4. 头删值 5. 中间插入值 6. 擦除值 7. 查找值 8. 打印表");
	scanf("%d", &input);
	switch (input)
	{
	case 1:
	{
		printf("1. 尾插连续值（回车分开），输入-1结束输入：");
		{
			while (scanf("%d", &ret) != -1)
			{
				SLPushBack(&arr, ret);
			}
		}
	}
	break;
	case 2:
	{

		return 0;
	}
	}
}
