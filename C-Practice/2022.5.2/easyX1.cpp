#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<graphics.h>
#include<easyx.h>

int main()
{
	//Բ��circle
	//��Բellipse
	//����Σ�polygon
	//����pie
	//���Σ�rectangle
	//Բ�Ǿ���roundrect
	//�ߣ�line
	//�㣺putpixel

	//��״��ʽ��������״�ĵ���ǰ׺
	//������״����Ĭ�ϣ�����䵫�б߿�
	//�б߿�����fill
	//�ޱ߿������solid
	//����Ĭ���б߿������Բcircle, �б߿�����Բfillcircle���ޱ߿������Բsolidcircle

	//�����ɫ��setfillcolor();���п���ΪRGB���ݣ���Ӣ�ĵ��ʣ������д��
	//�߿���ɫ��setlinecolor();
	//���ñ���ɫ��setbkcolor();  һ������ջ�ͼ�豸ָ��cleardevice();���ò�����Ч
	
	//����������ʽ��setlinestyle(); ����Ϊ�߶ȣ���ȣ�����
	//����setlinestyle(PS_SOLID, 5);  Ϊʵ�ֱ߿�5������
	
	//����������ɫsettextcolor();   ��дӢ����ĸ��RGB����
	//qq��ͼ�ù��ѡȡ��ɫ��cֱ�ӿ���RGB����
	// 
	//����ַ����ַ���outtextxy();  ����Ϊ����x, y���Լ�������ַ���
	//�ַ�����Ҫ��˫��������������û��Ԥ������Ŀ->easyX����->��������->�߼�����->�ַ���->ʹ�ö��ֽ��ַ��������ַ����¿�ֱ����˫���ţ�
	//����Ҫʹ��TEXT("�ַ�������")��_T("�ַ�������")�ĸ�ʽ���ַ������������������
	// 
	//����������ʽsettextstyle();   ����Ϊ�ߣ���"������ʽ"    ע�����߶ȿ������Ϊ0����ʾ��������Ӧ���ڴ�С
	//����settextstyle(50, 0, "����");
	//
	//�������屳��setbkmode();  ������ı�������Ҳ�б������ǣ����в������������ַ�����Ϊ͸�����
	//����setbkmode(TRANSPARENT | OPAQUE);

	//���ó�ʼ����ͼ������ʽ��initgraph(width),������������Ϊ��width, ��height��������ʽ��Ĭ��int flag = NULL��
	//������ʽ������ΪSHOWCONSOLE����ʾ����̨����NOCLOSE�����˳���ť����NOMINIMIZE������С����ť��
	 
	
	//ʾ��sample
	//��ʼ����ͼ����
	initgraph(720, 360, NULL);  
	setbkcolor(GREEN);
	cleardevice();
	
	//��ͼ
	setfillcolor(BLUE);
	setlinecolor(RED);
	setlinestyle(PS_SOLID, 5);
	//1. ԭ�㣨0, 0������б߿�Բ
	fillcircle(0, 0, 100);
	//2. ����������б߿���Σ�������뾶һ�£�
	setlinecolor(YELLOW);
	setlinestyle(PS_SOLID, 1);
	circle(100, 100, 100);		  //������void rectangle(int left, int top, int right, int bottom)
	//3. ��Ļ�����ޱ߿������Բ
	setfillcolor(WHITE);
	solidcircle(360, 180, 100);

	//������Բ��д��
	settextcolor(BLACK);  //����������ɫ
	outtextxy(320, 180, TEXT("Hello World"));  //�ڻ�ͼ��������ַ���������ʽ
	settextcolor(YELLOW);
	settextstyle(40, 15, "�����п�");
	outtextxy(420, 180, _T("Hello World"));
	setbkmode(TRANSPARENT);     //�����ַ��������Ĭ��Ϊ��͸��ΪOPAQUE
	settextcolor(RGB(182, 68, 255));   
	settextstyle(30, 20, "����");
	outtextxy(320, 230, "Hello World");

	//������
	setfillcolor(BLACK);
	setlinestyle(PS_DASH, 5);
	setlinecolor(RGB(255, 0, 0));
	fillrectangle(500, 50, 700, 150);     //����Ϊ���Ͻ�����xy�����½�����xy

	//�ھ��ο��������ַ���
	settextcolor(RGB(255, 255, 255));      //�������������ַ���ʽ��������֮ǰ���õ���ʽ
	settextstyle(20, 10, "����");
	char arr[] = "This is Hello World";
	int width = (700 - 500) / 2 - textwidth(arr) / 2;     //�������Ҫ���ж���ľ�����
	int height = (150 - 50) / 2 - textheight(arr) / 2;    //�������Ҫ���ж���ľ���߶�
	outtextxy(width + 500, height + 50, arr);             //���ʱ����Ҫ������Ҫ��Ӧ�����λ��

	getchar();
	closegraph();         //�رջ�ͼ����
/*	cleardevice;   */       //��ջ�ͼ�豸
	
	return 0;
}