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
	s.length = Length;											//��ʼ���ߵĳ��ȣ��м��ڣ�
	s.direction = RIGHT;										//��ʼ����ͷ����
	s.speed = Scale * 2;										//��ʼ�����ƶ��ٶ�
	for (int i = 0; i < s.length; i++)
	{
		s.coord[i].x = 100 - Scale * 2 * i;						//��ʼ���ߵ�λ�ú���ͷ�±�s[0]
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
	if (f.flag)													//����ʳ��
	{
		setfillcolor(f.color);
		solidcircle(f.x, f.y, f.r);
	}			
	setfillcolor(WHITE);										//�����ߵ���ɫ
	for (int i = 0; i < s.length; i++)
	{
		solidcircle(s.coord[i].x, s.coord[i].y, Scale);			//������ͷ��С��������ʾ
	}
	FlushBatchDraw();
	cleardevice();
}

void Move()
{
	for (int i = s.length - 1; i > 0; i--)						//�������ͷ��
	{
		s.coord[i] = s.coord[i - 1];							//��ͷ���괫������
	}
	switch (s.direction)										//���������ͷ�ٶȺͷ���
	{
	case UP:
		s.coord[0].y -= s.speed;								//��ͷÿ�ƶ�һ���߶������ص�
		if (s.coord[0].y <= 0)
		{
			s.coord[0].y = WIN_Height;							//���ƶ����߽�ʱ���ص���һ�߽�
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

void Control()													//���̿����߷���
{
	if (_kbhit())												//������ް������룬������
	{
		switch (_getch())
		{
		case 'w':
		case 'W':
		case 72: 
			if (s.direction != DOWN)							//���ϲ�����
			{
				s.direction = UP;								
			}
			break;
		case 's':
		case 'S':
		case 80: 
			if (s.direction != UP)								//���²�����
			{
				s.direction = DOWN;							
			}
			break;
		case 'a':
		case 'A':
		case 75: 
			if (s.direction != RIGHT)							//���󲻰���
			{
				s.direction = LEFT;							
			}
			break;
		case 'd':
		case 'D':
		case 77: 
			if (s.direction != LEFT)							//���Ҳ�����
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
	if (GetAsyncKeyState(VK_ESCAPE))						 //GetAsyncKeyState()��Ҫ����һ����ֵ������Ϊ�˳���VK_ESCAPE
	{
		HWND _Exit = GetHWnd();
		int ascertain = MessageBox(_Exit, "ȷ��Ҫ�˳���", "��ʾ", MB_OKCANCEL);
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
	int ascertain = MessageBox(M, "Welcome to play Gluttonous Snake!", "��ӭ��", MB_OKCANCEL);
	{
		if (ascertain == IDCANCEL)
		{
			exit(-1);
		}
	}
}