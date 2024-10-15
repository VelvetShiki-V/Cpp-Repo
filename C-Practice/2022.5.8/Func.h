#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<easyx.h>
#include<conio.h>
#include<mmsystem.h>
#pragma comment (lib, "winmm.lib")
#define MAX 50
#define WIN_Width 820			//������
#define WIN_Height 720			//����߶�
#define Length 3				//�߳�ʼ���ȣ���󲻳���5(Recommended)
#define Scale 10				//��ÿ�ڴ�С
#define FoodSize 10				//ʳ���С
struct snake					//�߽ṹ����
{
	int length;
	int direction;
	int speed;
	POINT coord[MAX];			//��������MAX������ṹ��POINT
};

struct Food						//ʳ�ﶨ��
{
	int x;
	int y;
	int r;
	DWORD color;				//DWORDΪ�޷���long
	time_t t;
	bool flag;
};

enum direction					//�������ҷ���ö�ٶ���
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};

//��������
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