#define _CRT_SECURE_NO_WARNINGS 1
#include"SqListPrac.h"

int main()
{
	int input = 0, ret = 0;
	SL arr;
	SLInit(&arr);
	printf("�����빦��ѡ��\n1. β��ֵ 2. ͷ��ֵ 3. βɾֵ \n4. ͷɾֵ 5. �м����ֵ 6. ����ֵ 7. ����ֵ 8. ��ӡ��");
	scanf("%d", &input);
	switch (input)
	{
	case 1:
	{
		printf("1. β������ֵ���س��ֿ���������-1�������룺");
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
