#define _CRT_SECURE_NO_WARNINGS 1
#include"Declaration.h"

void button(int shape)									//��ť����������Ϊ����״��,RGB(0~255)
{
	if (shape == 1)
	{
		//rectangle();
														//��ز�������https://docs.easyx.cn/zh-cn/
	}
	else if (shape == 2)
	{
		//solidcircle();
	}
}

void Text(int x, int y, char* text)						//�ı��������������Ϊ��������ַ��������ַ��
{
	//ParaCenter(x, y);
	//outtextxy();
}

void ParaCenter(int* x, int* y)							//ˮƽ���к���������Ϊ��ͼƬ���ı��������ص��������ĵ�ַint*��
{
	//*x = WIN_Width / 2;
	//*y = WIN_Height / 2;
}

void Music(int MusicNum)								//���ֲ��ź���������Ϊ��������ţ����Ż�ֹͣ��
{
	if (MusicNum == 1)
	{
		//mciSendString("open Route", 0, 0, 0);
		//mciSendString("play Route", 0, 0, 0);
	}
	else if (MusicNum == 2)
	{
		//mciSendString("open Route alias bgm", 0, 0, 0);		//aliasΪ����·��ȡ����
		//mciSendString("play Route", 0, 0, 0);
	}
	else
	{
		//mciSendString("close bgm", 0, 0, 0);
	}
}

void Message(LPCSTR* title, LPCSTR* content)						//��������������Ϊ���������⣬�������ݣ�
{
	/*const char* a[] = { "abc" };
	LPCSTR* TEXT = a;*/
	//HWND Message = GetHWnd();										//��ȡ��ǰ���ھ�������ô��ڵ�Ψһ����ʶ��
	//char TEXT[100];												//https://blog.csdn.net/lcxhjg/article/details/86214043
	//SetWindowText(title, "TEXT");
	//int tmp = MessageBox(NULL, *TEXT, *content, MB_OKCANCEL);
	//if (tmp == IDOK)
	//{
	//	printf("���ѽ������\n");
	//}
	//else
	//{
	//	exit(0);
	//}
}

void TurnTo(int PageNum)									//������ת����������Ϊ����Ҫ��ת�Ľ����ţ�����ҳPageNum = 1,ģʽҳ��PageNum = 2�ȵȣ�
{
	//switch (PageNum)
	//{
	//case1:
	// 	system("cls");
	//case2:
	//	break;
	//case3:
	//	break;
	//default:
	//	break;
	//}

}

void PicInsert(IMAGE img, char* route, int width, int height)
{
	//loadimage();
	//putiamge();
	//ParaCenter(int* x, int* y);
}