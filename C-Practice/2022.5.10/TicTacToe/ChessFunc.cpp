#define _CRT_SECURE_NO_WARNINGS 1
#include"Func.h"
int WelcomeUI()											//欢迎界面
{
	char title[] = "欢迎游玩三子棋";
	int ret = 0;
	printf("%20s\n", title);
	int i = 0;
	while (i < 9)
	{
		printf("  *");
		i++;
	}
	printf("\n	1. 开始游戏\n");
	printf("	2. 退出游戏\n");
	i = 0;
	while (i < 9)
	{
		printf("  *");
		i++;
	}
	printf("\n");
	printf("请输入1以进入游戏，输入2退出：");
	scanf("%d", &ret);
	return ret;
}

int WhoFirst(int ret)										//先手顺序函数
{
	printf("请输入先手顺序：0为AI先走，1为玩家先走：");
	scanf("%d", &ret);
	while (ret != 0 && ret != 1)
	{
		printf("请重新输入：");
		scanf("%d", &ret);
	}
	return ret;
}

void Sample(char samp[3][3])								//输入规则展示
{
	int k = 1;
	printf("\n游戏规则：输入如下所示数据落子与超级AI对战！\n");
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

void ChessInit(char parr[3][3])								//棋盘初始化
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

void Print(char parr[3][3])									//打印棋盘
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
		printf("重复落子！");
		return 1;
	}
	return 0;
}

int PlayerRound(char parr[3][3])							//玩家落子，输入1-9定子
{	
	int x = 0, ret = -1, i = 0, j = 0;
	extern int count;
	do
	{
		printf("\n请输入棋盘位置：");
		scanf("%d", &x);
		while (x < 1 || x > 9)
		{
			printf("输入错误，请重新输入：");
			scanf("%d", &x);
		}
		i = ((x % 3 == 0) ? x / 3 - 1 : x / 3);				
		j = ((x % 3 - 1 == -1) ? 2 : x % 3 - 1);
		ret = PlayerCheck(i, j, parr);
	} while (ret == 1);
	printf("您走了一步：\n");
	parr[i][j] = 'O';
	return ++count;
}

void PosCheck(int x, int y, char parr[3][3])				//电脑落子位置检查
{
	while (parr[x][y] != ' ')
	{
		x = rand() % 3;
		y = rand() % 3;
	}
	parr[x][y] = 'X';
}

int PCRound(char parr[3][3])								//电脑落子
{
	extern int count;
	if (count == 9)
	{
		return 0;
	}
	int x = rand() % 3;
	int y = rand() % 3;
	PosCheck(x, y, parr);
	printf("AI回合：\n");
	return ++count;
}

int Judge(char parr[3][3])									//判断输赢
{
	extern int count;
	int i = 0, j = 0, k = 0;
	char tmp[3];
	char PWIN[] = "OOO";
	char PLOS[] = "XXX";
	char GET[4];

	while (i < 3)											//判断是否有三子同行输赢情况
	{
		for (j = 0; j < 3; j++)
		{
			tmp[j] = parr[i][j];
		}
		snprintf(GET, 4, "%s", tmp);
		if (strcmp(GET, PWIN) == 0)
		{
			printf("玩家获胜！\n");
			return 2;
		}
		if (strcmp(GET, PLOS) == 0)
		{
			printf("AI获胜！\n");
			return 2;
		}
		i++;
	}

	k = 0, j = 0;
	while (j < 3)											//判断是否有三子同列输赢情况
	{
		for (i = 0; i < 3; i++)
		{
			tmp[k] = parr[k][j];
			k++;
		}
		snprintf(GET, 4, "%s", tmp);
		if (strcmp(GET, PWIN) == 0)
		{
			printf("玩家获胜！\n");
			return 2;
		}
		if (strcmp(GET, PLOS) == 0)
		{
			printf("AI获胜！\n");
			return 2;
		}
		k = 0;
		j++;
	}

	j = 0;
	for (i = 0; i < 3; i++)									//判断是否有对角同子输赢情况
	{														//左对角
		tmp[j] = parr[j][j];
		j++;
	}
	snprintf(GET, 4, "%s", tmp);
	if (strcmp(GET, PWIN) == 0)
	{
		printf("玩家获胜！\n");
		return 2;
	}
	if (strcmp(GET, PLOS) == 0)
	{
		printf("AI获胜！\n");
		return 2;
	}
	j = 0;
	for (i = 2; i >= 0; i--)								//右对角
	{
		tmp[j] = parr[j][i];
		j++;
	}
	snprintf(GET, 4, "%s", tmp);
	if (strcmp(GET, PWIN) == 0)
	{
		printf("玩家获胜！\n");
		return 2;
	}
	if (strcmp(GET, PLOS) == 0)
	{
		printf("AI获胜！\n");
		return 2;
	}
	if (count == 9)
	{
		printf("和棋！\n");
		return 2;
	}
	return 1;
}

int Retry()
{
	char r = '0';
	printf("再打一局？输入Y或N确定或退出：\n");
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
			printf("请输入 Y or N\n");
		}
	} while (r != 'Y');
	system("cls");
	return 1;
}