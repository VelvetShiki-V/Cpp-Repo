#define _CRT_SECURE_NO_WARNINGS 1
#include"Func.h"

int main()
{
	Message();
	//WelcomeUI();
	GameInit();
	Music();
	//ModeSelect();
	while (1)
	{
		GameDraw();
		Move();
		Control();
		EatFood();
		Sleep(50);
	}
	closegraph();
	return 0;
}