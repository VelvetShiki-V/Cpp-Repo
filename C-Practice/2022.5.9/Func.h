#pragma once
#include<stdio.h>
#include<string.h>
#include<time.h>
#include<stdlib.h>
void WelcomeUI();											//��ӭ����
void ChessInit(char parr[3][3]);							//���̳�ʼ��
void Print(char parr[3][3]);								//��ӡ����
int PlayerRound(char parr[3][3]);							//������ӣ�����1-9����
int PCRound(char parr[3][3]);								//��������
int Judge(char parr[3][3]);									//�ж���Ӯ
void PosCheck(int x, int y, char parr[3][3]);				//�������Ӽ��
int PlayerCheck(int x, int y, char parr[3][3]);				//������Ӽ��
void Sample(char samp[3][3]);								//�������չʾ
int Retry();												//����������˳�
