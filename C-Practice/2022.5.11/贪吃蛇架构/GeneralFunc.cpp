#define _CRT_SECURE_NO_WARNINGS 1
#include"Declaration.h"

void button(int shape)									//按钮函数，参数为（形状）,RGB(0~255)
{
	if (shape == 1)
	{
		//rectangle();
														//相关参数查阅https://docs.easyx.cn/zh-cn/
	}
	else if (shape == 2)
	{
		//solidcircle();
	}
}

void Text(int x, int y, char* text)						//文本输出函数，参数为（待输出字符串数组地址）
{
	//ParaCenter(x, y);
	//outtextxy();
}

void ParaCenter(int* x, int* y)							//水平居中函数，参数为（图片或文本左上像素点横纵坐标的地址int*）
{
	//*x = WIN_Width / 2;
	//*y = WIN_Height / 2;
}

void Music(int MusicNum)								//音乐播放函数，参数为（歌曲编号，播放或停止）
{
	if (MusicNum == 1)
	{
		//mciSendString("open Route", 0, 0, 0);
		//mciSendString("play Route", 0, 0, 0);
	}
	else if (MusicNum == 2)
	{
		//mciSendString("open Route alias bgm", 0, 0, 0);		//alias为歌曲路径取别名
		//mciSendString("play Route", 0, 0, 0);
	}
	else
	{
		//mciSendString("close bgm", 0, 0, 0);
	}
}

void Message(LPCSTR* title, LPCSTR* content)						//弹窗函数，参数为（弹窗标题，弹窗内容）
{
	/*const char* a[] = { "abc" };
	LPCSTR* TEXT = a;*/
	//HWND Message = GetHWnd();										//获取当前窗口句柄，即该窗口的唯一进程识别
	//char TEXT[100];												//https://blog.csdn.net/lcxhjg/article/details/86214043
	//SetWindowText(title, "TEXT");
	//int tmp = MessageBox(NULL, *TEXT, *content, MB_OKCANCEL);
	//if (tmp == IDOK)
	//{
	//	printf("您已进入程序\n");
	//}
	//else
	//{
	//	exit(0);
	//}
}

void TurnTo(int PageNum)									//界面跳转函数，参数为（需要跳转的界面编号，如主页PageNum = 1,模式页面PageNum = 2等等）
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