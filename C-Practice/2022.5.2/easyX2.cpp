#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<easyx.h>
#include<string.h>

//IMAGEΪeasyX��C++�ṩ���࣬���Ի�ȡ��ͼƬ�ĸߺͿ�
//��ȡ�ļ���ͼƬ������loadimage();  ����ΪIMAGE* ָ��������ļ����/����·����ͼƬ�Ŀ�͸�
//����loadimage(&img, "./1.jpg", 600, 350);  ��ʾʹ��·���µ�.jpg�ļ���ͼƬָ�������ֵ���������͸�
// 
//��ͼƬ�����ڻ�ͼ���ں�����putimage();  ����Ϊ��Ҫ���õ�x��y���꣬ͼƬIMAGE* ָ�����
//���putimage��x,y�������ó�0,0��������Ͻ�ԭ�㿪ʼ����
//����putimage(0, 0, &img);   ��ʾ��ͼƬָ��ָ���.jpgͼƬ�����Ͻ��𣩷�����ԭ�㴦

//��ť���庯��
void button(int x, int y, int w, int h, const char* text)
{
	setbkmode(0);										 //�ȼ���TRANSPARENT
	setfillcolor(RGB(103, 71, 72));						 //���ð�ť�����ɫ
	fillroundrect(x, y, x + w, y + h, 10, 10);			 //���ð�ť�������ϣ����������Բ�Ǿ��λ���
	settextstyle(30, 0, "����");						 //���á���ť�����ָ߶ȣ���Ⱥ�������ʽ
	char sample[10] = "button";							 //���մ������İ�ť��ʾ�ı�����ť��
	strcpy(sample, text);
	int width = x + (w - textwidth(text)) / 2;			 //���ı���͸�����ڰ�ť������ж���
	int height = y + (h - textheight(text)) / 2;
	outtextxy(width, height, text);						 //��ť���������ʾ�ı�
}

//ͼƬ��Ի沼�������к���
void picenter(int x, int y, int x1, int y1, IMAGE img)
{
	int width, height;                                         //����ͼƬ����ڻ沼�ľ���������ʹͼƬ���־���
	width = (x - x1) / 2;
	height = (y - y1) / 2;
	putimage(width, height, &img);
}

int main()
{
	int x, y, a, b;
	IMAGE img;
	printf("�������ͼ��͸ߣ�");
	scanf("%d %d", &x, &y);
	initgraph(x, y, EW_SHOWCONSOLE);
	printf("���������ͼ��͸ߣ�");
	scanf("%d %d", &a, &b);
	loadimage(&img, "./1.jpg", a, b);						  //ͼƬ�����Դ�ļ�cpp�����·��
	//loadimage(&img, "E:\\MATLAB/2.jpg", a, b);			  //ͼƬ�ľ���·��
	picenter(x, y, a, b, img);								  //ͼƬ����ڻ沼���ж��뺯��������Ϊ�沼��ߣ�����ͼ��ߣ���ͼƬָ��
	button(x/2, y/2, x/10, y/10, "��ť");                     //��ť����x, y������Ϣ������Ϊ���У�������ʾ����Ϊ����ť��

	//���������
	ExMessage msg;											  //ExMessage��������ܽṹ������,msgΪ�ṹ�����
	while (true)											  //ʵ��ѭ�����
	{
		if (peekmessage(&msg, EM_MOUSE))					  //EM_MOUSE�Ǻ꣬����������Ҽ�ʱ����1
		{													  //peekmessageΪ��������������뺯������EM_MOUSE��ΪΪ�ṹ��ָ��msg��ֵ
			switch (msg.message)
			{
			case WM_LBUTTONDOWN:							  //��֧��䣬������������Ϊʱִ��
				if (msg.x >= x / 2 && msg.x <= x / 2 + x / 10 && msg.y >= y / 2 && msg.y <= y / 2 + y / 10)
				{											  //��������������ҵ�������ڰ�ťx, y��Χ��ʱִ���ж�Ϊ�棬ִ�в���
					printf("����ɹ�\n");
				}
				break;
			default:
				break;
			}
		}
	}
	getchar();
	return 0;
}
















////����/ͼƬ������ͼƬ���к���
//void picenter(int x, int y, int x1, int y1, IMAGE img)
//{
//	int width, height;
//	width = (x - x1) / 2;
//	height = (y - y1) / 2;
//	putimage(width, height, &img);
//}
//
//void butcenter(int x, int y, int x1, int y1)
//{
//	int width, height;
//	width = (x - x1) / 2;
//	height = (y - y1) / 2;
//	fillrectangle(width, height, x, y);
//}
//
////void textcenter(int x, int y, int x1, int y1)
////{
////	int width, height;
////	width = (x - x1) / 2;
////	height = (y - y1) / 2;
////	outtextxy(x + *T_width, y + *T_height, text);
////}
//
//
////�����
////
//void button(int x, int y)
//{
//	//���ð�ť��ɫ��ʽ��������ʽ
//	setbkmode(0);  //�ȼ���transparent
//	setfillcolor(RGB(0, 108, 190));
//	setlinecolor(RED);
//	settextstyle(25, 15, "����");
//	settextcolor(RGB(255, 60, 60));
//
//	//���ð�ť��״
//	butcenter(1265, 691, x, y);							//Բ�Ǿ��β���void fillroundrect (int left, int top, int right, int bottom, int ellipsewidth, int ellipseheight);		// �����Բ�Ǿ���(�б߿�)
//	char text[] = "��ť";
//	//textcenter();
//}
//
//int main()
//{
//	//����ͼƬ
//	IMAGE img, img1;
//
//	initgraph(1265, 691 ,EW_SHOWCONSOLE);
//	loadimage(&img, "./1.jpg", 600, 350);       //ͼƬ���·����./��ʾ��ǰĿ¼��../��ʾ��һ��Ŀ¼
///*	loadimage(&img1, "E:\\MATLAB/2.jpg", 600, 350);   */ //ͼƬ����·����ע����б����Ҫ��������Ϊ��Ҫת�壩����б��ֻ��Ҫһ��
//	//putimage(650, 300, &img1);
//	//
//	//���з���ͼƬ
//	picenter(1265, 691, 600, 350, img);    //ͼƬ���к���������Ϊ���������½�x,y���꣬������ͼƬ��͸ߣ������ͼƬIMAGEָ��
//
//	//������ť���� 
//	button(50, 30);
//
//	getchar();
//	closegraph();
//	return 0;
//}