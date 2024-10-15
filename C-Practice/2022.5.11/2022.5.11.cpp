#define _CRT_SECURE_NO_WARNINGS 1
#include"SqListPrac.h"

int main()
{
	int input = 0, pos = 0;
	SLElemType ret = 0;
	SL arr;
	SLInit(&arr);
	while (1)
	{
		printf("请输入功能选择：\n1. 尾插值 2. 头插值 3. 尾删值 \n4. 头删值 5. 中间插入值 6. 擦除值\n 7. 查找值 8. 打印表 9. 释放顺序表\n请选择：");
		scanf("%d", &input);
		switch (input)
		{
		case 1:
		{
			printf("尾插连续值（回车分开），输入-1结束输入：\n");
			while (scanf("%d", &ret) != EOF)
			{
				if (ret == -1)
				{
					system("cls");
					break;
				}
				SLPushBack(&arr, ret);
			}
		}
		break;
		case 2:
		{
			printf("头插连续值（回车分开），输入-1结束输入：\n");
			while (scanf("%d", &ret))
			{
				if (ret == -1)
				{
					system("cls");
					break;
				}
				SLPushFront(&arr, ret);
			}
			break;
		}
		case 3:
		{
			printf("输入1以连续尾删值，输入-1结束尾删：\n");
			while (scanf("%d", &ret))
			{
				if (ret == -1)
				{
					system("cls");
					break;
				}
				if (ret == 1)
				{
					SLPopBack(&arr);
				}
			}
			break;
		}
		case 4:
		{
			printf("输入1以连续头删值，输入-1结束尾删\n");
			while (scanf("%d", &ret))
			{
				if (ret == -1)
				{
					system("cls");
					break;
				}
				SLPopFront(&arr);
			}
			break;
		}
		case 5:
		{
			printf("中间插入连续值（回车分开），输入-1结束输入：\n");
			while (scanf("%d", &ret))
			{
				if (ret == -1)
				{
					system("cls");
					break;
				}
				printf("请输入此次插入下标位置：");
				scanf("%d", &pos);
				SLInsert(&arr, ret, pos);
				printf("请继续输入待插入值：");
			}
			break;
		}
		case 6:
		{
			printf("输入1以单个擦除表中对应现有值\n输入2以擦除表中所有对应值\n输入-1结束输入：\n");
			while (scanf("%d", &ret))
			{
				if (ret == -1)
				{
					system("cls");
					break;
				}
				else if (ret == 1)
				{
					while (1)
					{
						printf("请输入待擦除值，输入-1结束单个擦除：");
						scanf("%d", &ret);
						if (ret == -1)
						{
							break;
						}
						SLErase(&arr, ret);
					}
				}
				else if (ret == 2)
				{
					printf("请输入待擦除值，输入-1结束连续擦除：");
					while (1)
					{
						scanf("%d", &ret);
						if (ret == -1)
						{
							break;
						}
						while (1)
						{
							int tmp = ret;
							tmp = SLErase(&arr, ret);
							if (tmp == -1)
							{
								break;
							}
						}
						printf("请输入待擦除值，输入-1结束连续擦除：");
					}
				}
				printf("输入1以单个擦除表中对应现有值\n输入2以擦除表中所有对应值\n输入-1结束输入：\n");
			}
			break;
		}
		case 7:
		{
			printf("查找值，返回该元素在顺序表中的下标，输入-1结束输入：");
			while (scanf("%d", &ret))
			{
				if (ret == -1)
				{
					system("cls");
					break;
				}
				SLFind(&arr, ret);
			}
			break;
		}
		case 8:
		{
			printf("当前顺序表为：");
			Print(&arr);
			printf("\n\n");
			break;
		}
		case 9:
		{
			SLDestroy(&arr);
			printf("顺序表已从内存中释放。\n");
			exit(EOF);
		}
		}
	}
	return 0;
}
