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
		printf("�����빦��ѡ��\n1. β��ֵ 2. ͷ��ֵ 3. βɾֵ \n4. ͷɾֵ 5. �м����ֵ 6. ����ֵ\n 7. ����ֵ 8. ��ӡ�� 9. �ͷ�˳���\n��ѡ��");
		scanf("%d", &input);
		switch (input)
		{
		case 1:
		{
			printf("β������ֵ���س��ֿ���������-1�������룺\n");
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
			printf("ͷ������ֵ���س��ֿ���������-1�������룺\n");
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
			printf("����1������βɾֵ������-1����βɾ��\n");
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
			printf("����1������ͷɾֵ������-1����βɾ\n");
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
			printf("�м��������ֵ���س��ֿ���������-1�������룺\n");
			while (scanf("%d", &ret))
			{
				if (ret == -1)
				{
					system("cls");
					break;
				}
				printf("������˴β����±�λ�ã�");
				scanf("%d", &pos);
				SLInsert(&arr, ret, pos);
				printf("��������������ֵ��");
			}
			break;
		}
		case 6:
		{
			printf("����1�Ե����������ж�Ӧ����ֵ\n����2�Բ����������ж�Ӧֵ\n����-1�������룺\n");
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
						printf("�����������ֵ������-1��������������");
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
					printf("�����������ֵ������-1��������������");
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
						printf("�����������ֵ������-1��������������");
					}
				}
				printf("����1�Ե����������ж�Ӧ����ֵ\n����2�Բ����������ж�Ӧֵ\n����-1�������룺\n");
			}
			break;
		}
		case 7:
		{
			printf("����ֵ�����ظ�Ԫ����˳����е��±꣬����-1�������룺");
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
			printf("��ǰ˳���Ϊ��");
			Print(&arr);
			printf("\n\n");
			break;
		}
		case 9:
		{
			SLDestroy(&arr);
			printf("˳����Ѵ��ڴ����ͷš�\n");
			exit(EOF);
		}
		}
	}
	return 0;
}
