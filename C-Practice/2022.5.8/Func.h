#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<easyx.h>
#include<conio.h>
#include<mmsystem.h>
#pragma comment (lib, "winmm.lib")
#define MAX 50
#define WIN_Width 820			//界面宽度
#define WIN_Height 720			//界面高度
#define Length 3				//蛇初始长度，最大不超过5(Recommended)
#define Scale 10				//蛇每节大小
#define FoodSize 10				//食物大小
struct snake					//蛇结构定义
{
	int length;
	int direction;
	int speed;
	POINT coord[MAX];			//蛇最大节数MAX和坐标结构体POINT
};

struct Food						//食物定义
{
	int x;
	int y;
	int r;
	DWORD color;				//DWORD为无符号long
	time_t t;
	bool flag;
};

enum direction					//上下左右方向枚举定义
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};

//函数声明
void WelcomeUI();
void Button();
void GameInit();
void FoodInit();
void GameDraw();
void Move();
void Control();
void EatFood();
void Music();
void Message();
void ModeSelect();