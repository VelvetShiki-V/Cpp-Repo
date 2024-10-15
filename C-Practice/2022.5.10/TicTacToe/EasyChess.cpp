#define _CRT_SECURE_NO_WARNINGS 1
#include"Func.h"
int count = 0;
int main()
{
	char arr[3][3];
	char samp[3][3];
	int ret = 0;
	time_t t;
	srand((unsigned int)(&t));
	ret = WelcomeUI();
	if (ret != 1)
	{
		exit(-1);
	}
	do
	{
		Sample(samp);
		ChessInit(arr);
		ret = WhoFirst(ret);
		if (ret == 1)
		{
			goto Player;
		}
		if (ret == 0)
		{
			goto AI;
		}
		while (1)
		{
			Player:
			PlayerRound(arr);
			Print(arr);
			AI:
			ret = PCRound(arr);
			if (ret != 0)
			{
				Print(arr);
			}
			ret = Judge(arr);
			if (ret == 2)
			{
				break;
			}
		}
		count = 0;
		ret = Retry();
	} while (ret == 1);
	return 0;	
}