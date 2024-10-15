#define _CRT_SECURE_NO_WARNINGS 1
#include"Declaration.h"

int GameOver()											//游戏结束，参数为空，返回值返回（重试1或退出0）
{
	;
}

void GamePass(int PassNum)								//游戏通关，参数为（普通通关到下一界面，或通关获胜，调用Victory）
{
	/*if ()
		GamePass(1)
		if ()
			GamePass(2)
			if ()
				Victory();*/
}

void Victory()  										//游戏胜利
{
	;
}

int KeyBoardControl()									//通过键盘和Windows静态库函数实现WASD控制蛇移动
{
	//if (_kbhit())
	//	{
	//		char direction = _getch();					 //键入值接收，阻塞输入函数，一般配合_kbhit使用
	//		printf("对应虚拟ASCII值：%d , 对应字符：%c\n", direction, direction);
	//		switch (direction)
	//	    {
	//		case 'w':
	//		case'W':
	//		case 72:
	//		break;
	//		...
	//		...
	//		...
	//		}
	//	}
	// 
	// 
	// 或
	// 
	//if(GetAsyncKeyState(VK_ESCAPE))					//GetAsyncKeyState()需要传入一个键值，参数为退出：VK_ESCAPE	
	//	{
	//		HWND _Exit = GetHWnd();
	//		Message();
	//		...
	//		...
	//		...
	//		break;
	//	}
}

void Infinity()
{
	;
}