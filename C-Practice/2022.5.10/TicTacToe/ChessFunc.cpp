#define _CRT_SECURE_NO_WARNINGS 1
#include"Func.h"
int WelcomeUI()											//��ӭ����
{
	char title[] = "��ӭ����������";
	int ret = 0;
	printf("%20s\n", title);
	int i = 0;
	while (i < 9)
	{
		printf("  *");
		i++;
	}
	printf("\n	1. ��ʼ��Ϸ\n");
	printf("	2. �˳���Ϸ\n");
	i = 0;
	while (i < 9)
	{
		printf("  *");
		i++;
	}
	printf("\n");
	printf("������1�Խ�����Ϸ������2�˳���");
	scanf("%d", &ret);
	return ret;
}

int WhoFirst(int ret)										//����˳����
{
	printf("����������˳��0ΪAI���ߣ�1Ϊ������ߣ�");
	scanf("%d", &ret);
	while (ret != 0 && ret != 1)
	{
		printf("���������룺");
		scanf("%d", &ret);
	}
	return ret;
}

void Sample(char samp[3][3])								//�������չʾ
{
	int k = 1;
	printf("\n��Ϸ��������������ʾ���������볬��AI��ս��\n");
	for (int i = 0; i < 3; i++)
	{
		printf("+---------+---------+---------+\n");
		printf("|");
		for (int j = 0; j < 3; j++)
		{
			printf("    %d    |", k);
			k++;
		}
		printf("\n");
	}
	printf("+---------+---------+---------+\n\n");
}

void ChessInit(char parr[3][3])								//���̳�ʼ��
{
	extern int count;
	int i = 0, j = 0;
	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			parr[i][j] = ' ';
		}
	}
}

void Print(char parr[3][3])									//��ӡ����
{
	for (int i = 0; i < 3; i++)
	{
		printf("+---------+---------+---------+\n");
		printf("|");
		for (int j = 0; j < 3; j++)
		{
			printf("%5c    |", parr[i][j]);
		}
		printf("\n");
	}
	printf("+---------+---------+---------+\n\n");
}

int PlayerCheck(int x, int y, char parr[3][3])
{
	if (parr[x][y] == 'O' || parr[x][y] == 'X')
	{
		printf("�ظ����ӣ�");
		return 1;
	}
	return 0;
}

int PlayerRound(char parr[3][3])							//������ӣ�����1-9����
{	
	int x = 0, ret = -1, i = 0, j = 0;
	extern int count;
	do
	{
		printf("\n����������λ�ã�");
		scanf("%d", &x);
		while (x < 1 || x > 9)
		{
			printf("����������������룺");
			scanf("%d", &x);
		}
		i = ((x % 3 == 0) ? x / 3 - 1 : x / 3);				
		j = ((x % 3 - 1 == -1) ? 2 : x % 3 - 1);
		ret = PlayerCheck(i, j, parr);
	} while (ret == 1);
	printf("������һ����\n");
	parr[i][j] = 'O';
	return ++count;
}

void PosCheck(int x, int y, char parr[3][3])				//��������λ�ü��
{
	while (parr[x][y] != ' ')
	{
		x = rand() % 3;
		y = rand() % 3;
	}
	parr[x][y] = 'X';
}

int PCRound(char parr[3][3])								//��������
{
	extern int count;
	if (count == 9)
	{
		return 0;
	}
	int x = rand() % 3;
	int y = rand() % 3;
	PosCheck(x, y, parr);
	printf("AI�غϣ�\n");
	return ++count;
}

int Judge(char parr[3][3])									//�ж���Ӯ
{
	extern int count;
	int i = 0, j = 0, k = 0;
	char tmp[3];
	char PWIN[] = "OOO";
	char PLOS[] = "XXX";
	char GET[4];

	while (i < 3)											//�ж��Ƿ�������ͬ����Ӯ���
	{
		for (j = 0; j < 3; j++)
		{
			tmp[j] = parr[i][j];
		}
		snprintf(GET, 4, "%s", tmp);
		if (strcmp(GET, PWIN) == 0)
		{
			printf("��һ�ʤ��\n");
			return 2;
		}
		if (strcmp(GET, PLOS) == 0)
		{
			printf("AI��ʤ��\n");
			return 2;
		}
		i++;
	}

	k = 0, j = 0;
	while (j < 3)											//�ж��Ƿ�������ͬ����Ӯ���
	{
		for (i = 0; i < 3; i++)
		{
			tmp[k] = parr[k][j];
			k++;
		}
		snprintf(GET, 4, "%s", tmp);
		if (strcmp(GET, PWIN) == 0)
		{
			printf("��һ�ʤ��\n");
			return 2;
		}
		if (strcmp(GET, PLOS) == 0)
		{
			printf("AI��ʤ��\n");
			return 2;
		}
		k = 0;
		j++;
	}

	j = 0;
	for (i = 0; i < 3; i++)									//�ж��Ƿ��жԽ�ͬ����Ӯ���
	{														//��Խ�
		tmp[j] = parr[j][j];
		j++;
	}
	snprintf(GET, 4, "%s", tmp);
	if (strcmp(GET, PWIN) == 0)
	{
		printf("��һ�ʤ��\n");
		return 2;
	}
	if (strcmp(GET, PLOS) == 0)
	{
		printf("AI��ʤ��\n");
		return 2;
	}
	j = 0;
	for (i = 2; i >= 0; i--)								//�ҶԽ�
	{
		tmp[j] = parr[j][i];
		j++;
	}
	snprintf(GET, 4, "%s", tmp);
	if (strcmp(GET, PWIN) == 0)
	{
		printf("��һ�ʤ��\n");
		return 2;
	}
	if (strcmp(GET, PLOS) == 0)
	{
		printf("AI��ʤ��\n");
		return 2;
	}
	if (count == 9)
	{
		printf("���壡\n");
		return 2;
	}
	return 1;
}

int Retry()
{
	char r = '0';
	printf("�ٴ�һ�֣�����Y��Nȷ�����˳���\n");
	do
	{
		while ((r = getchar()) == '\n')
		{
			;
		}
		scanf("%*[^\n]"); scanf("%*c");
		if (r == 'N')
		{
			exit(-1);
		}
		else if (r != 'Y')
		{
			printf("������ Y or N\n");
		}
	} while (r != 'Y');
	system("cls");
	return 1;
}