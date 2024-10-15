#pragma once
#include<stdio.h>
#include<string.h>
#include<time.h>
#include<stdlib.h>
void WelcomeUI();											//欢迎界面
void ChessInit(char parr[3][3]);							//棋盘初始化
void Print(char parr[3][3]);								//打印棋盘
int PlayerRound(char parr[3][3]);							//玩家落子，输入1-9定子
int PCRound(char parr[3][3]);								//电脑落子
int Judge(char parr[3][3]);									//判断输赢
void PosCheck(int x, int y, char parr[3][3]);				//电脑落子检查
int PlayerCheck(int x, int y, char parr[3][3]);				//玩家落子检查
void Sample(char samp[3][3]);								//输入规则展示
int Retry();												//重新游玩或退出
