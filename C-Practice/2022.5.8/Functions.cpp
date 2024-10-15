#define _CRT_SECURE_NO_WARNINGS 1
#include"Func.h"
snake s;
direction d;
Food f;


void GameInit()
{
	initgraph(WIN_Width, WIN_Height, NULL);
	//IMAGE BGP;
	//loadimage(&BGP, "./cheems.jpg", WIN_Width, WIN_Height, false);
	//putimage(0, 0, &BGP, false);
	setbkcolor(GREEN);
	cleardevice();
	s.length = Length;											//初始化蛇的长度（有几节）
	s.direction = RIGHT;										//初始化蛇头方向
	s.speed = Scale * 2;										//初始化蛇移动速度
	for (int i = 0; i < s.length; i++)
	{
		s.coord[i].x = 100 - Scale * 2 * i;						//初始化蛇的位置和蛇头下标s[0]
		s.coord[i].y = Scale;
	}
	FoodInit();
}

void FoodInit()
{
	srand((unsigned)time(&f.t));
	f.x = rand() % WIN_Width - 10;
	f.y = rand() % WIN_Height - 10;
	f.r = FoodSize;
	f.color = (RED);
	f.flag = true;
}

void GameDraw()
{
	BeginBatchDraw();
	if (f.flag)													//绘制食物
	{
		setfillcolor(f.color);
		solidcircle(f.x, f.y, f.r);
	}			
	setfillcolor(WHITE);										//设置蛇的颜色
	for (int i = 0; i < s.length; i++)
	{
		solidcircle(s.coord[i].x, s.coord[i].y, Scale);			//绘制蛇头大小和坐标显示
	}
	FlushBatchDraw();
	cleardevice();
}

void Move()
{
	for (int i = s.length - 1; i > 0; i--)						//身体跟着头走
	{
		s.coord[i] = s.coord[i - 1];							//蛇头坐标传给身体
	}
	switch (s.direction)										//键入控制蛇头速度和方向
	{
	case UP:
		s.coord[0].y -= s.speed;								//蛇头每移动一次走多少像素点
		if (s.coord[0].y <= 0)
		{
			s.coord[0].y = WIN_Height;							//当移动到边界时返回到另一边界
		}
		break;
	case DOWN:
		s.coord[0].y += s.speed;
		if (s.coord[0].y >= WIN_Height)
		{
			s.coord[0].y = 0;
		}
		break;
	case LEFT:
		s.coord[0].x -= s.speed;
		if (s.coord[0].x <= 0)
		{
			s.coord[0].x = WIN_Width;
		}
		break;
	case RIGHT:
		s.coord[0].x += s.speed;
		if (s.coord[0].x >= WIN_Width)
		{
			s.coord[0].x = 0;
		}
		break;
	}
}

void Control()													//键盘控制蛇方向
{
	if (_kbhit())												//检测有无按键输入，防阻塞
	{
		switch (_getch())
		{
		case 'w':
		case 'W':
		case 72: 
			if (s.direction != DOWN)							//按上不按下
			{
				s.direction = UP;								
			}
			break;
		case 's':
		case 'S':
		case 80: 
			if (s.direction != UP)								//按下不按上
			{
				s.direction = DOWN;							
			}
			break;
		case 'a':
		case 'A':
		case 75: 
			if (s.direction != RIGHT)							//按左不按右
			{
				s.direction = LEFT;							
			}
			break;
		case 'd':
		case 'D':
		case 77: 
			if (s.direction != LEFT)							//按右不按左
			{
				s.direction = RIGHT;						
			}
			break;
		case ' ':
			while (_getch() == ' ')
			{
				break;
			}
		}
	}
	if (GetAsyncKeyState(VK_ESCAPE))						 //GetAsyncKeyState()需要传入一个键值，参数为退出：VK_ESCAPE
	{
		HWND _Exit = GetHWnd();
		int ascertain = MessageBox(_Exit, "确定要退出吗？", "提示", MB_OKCANCEL);
		if (ascertain == IDOK)
		{
			exit(-1);
		}
	}
}

void EatFood()
{
	if (s.coord[0].x <= f.x + f.r && s.coord[0].x >= f.x - f.r 
		&& s.coord[0].y <= f.y + f.r && s.coord[0].y >= f.y - f.r
		&& f.flag)
	{
		s.length++;
		f.flag = false;
	}
	if (!f.flag)
	{
		FoodInit();
	}
}

void Music()
{
	mciSendString("open ./DC.mp3 alias BGM", 0, 0, 0);
	mciSendString("play BGM repeat", 0, 0, 0);
}

void Message()
{
	HWND M = GetHWnd();
	int ascertain = MessageBox(M, "Welcome to play Gluttonous Snake!", "欢迎！", MB_OKCANCEL);
	{
		if (ascertain == IDCANCEL)
		{
			exit(-1);
		}
	}
}