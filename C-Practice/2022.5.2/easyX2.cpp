#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<easyx.h>
#include<string.h>

//IMAGE为easyX的C++提供的类，可以获取到图片的高和宽
//获取文件中图片函数：loadimage();  参数为IMAGE* 指针变量，文件相对/绝对路径，图片的宽和高
//例：loadimage(&img, "./1.jpg", 600, 350);  表示使用路径下的.jpg文件给图片指针变量赋值并设置其宽和高
// 
//将图片放置于绘图窗口函数：putimage();  参数为需要放置的x，y坐标，图片IMAGE* 指针变量
//如果putimage的x,y参数设置成0,0，则从左上角原点开始绘制
//例：putimage(0, 0, &img);   表示将图片指针指向的.jpg图片（左上角起）放置于原点处

//按钮定义函数
void button(int x, int y, int w, int h, const char* text)
{
	setbkmode(0);										 //等价于TRANSPARENT
	setfillcolor(RGB(103, 71, 72));						 //设置按钮填充颜色
	fillroundrect(x, y, x + w, y + h, 10, 10);			 //设置按钮区域左上，右下坐标和圆角矩形弧度
	settextstyle(30, 0, "楷体");						 //设置“按钮”文字高度，宽度和字体样式
	char sample[10] = "button";							 //接收传进来的按钮显示文本“按钮”
	strcpy(sample, text);
	int width = x + (w - textwidth(text)) / 2;			 //将文本宽和高相对于按钮区域居中对齐
	int height = y + (h - textheight(text)) / 2;
	outtextxy(width, height, text);						 //按钮区域居中显示文本
}

//图片相对绘布背景居中函数
void picenter(int x, int y, int x1, int y1, IMAGE img)
{
	int width, height;                                         //计算图片相对于绘布的居中区域，以使图片保持居中
	width = (x - x1) / 2;
	height = (y - y1) / 2;
	putimage(width, height, &img);
}

int main()
{
	int x, y, a, b;
	IMAGE img;
	printf("请输入绘图宽和高：");
	scanf("%d %d", &x, &y);
	initgraph(x, y, EW_SHOWCONSOLE);
	printf("请输入待插图宽和高：");
	scanf("%d %d", &a, &b);
	loadimage(&img, "./1.jpg", a, b);						  //图片相对于源文件cpp的相对路径
	//loadimage(&img, "E:\\MATLAB/2.jpg", a, b);			  //图片的绝对路径
	picenter(x, y, a, b, img);								  //图片相对于绘布居中对齐函数，参数为绘布宽高，待插图宽高，和图片指针
	button(x/2, y/2, x/10, y/10, "按钮");                     //按钮左上x, y与宽高信息，设置为居中，传参显示文字为“按钮”

	//鼠标点击函数
	ExMessage msg;											  //ExMessage鼠标点击功能结构体类型,msg为结构体变量
	while (true)											  //实现循环点击
	{
		if (peekmessage(&msg, EM_MOUSE))					  //EM_MOUSE是宏，单击左键或右键时返回1
		{													  //peekmessage为接收鼠标或键盘输入函数，由EM_MOUSE行为为结构体指针msg赋值
			switch (msg.message)
			{
			case WM_LBUTTONDOWN:							  //分支语句，按下鼠标左键行为时执行
				if (msg.x >= x / 2 && msg.x <= x / 2 + x / 10 && msg.y >= y / 2 && msg.y <= y / 2 + y / 10)
				{											  //当点击鼠标左键，且点击区域在按钮x, y范围内时执行判断为真，执行操作
					printf("点击成功\n");
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
















////文字/图片相对外层图片居中函数
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
////鼠标点击
////
//void button(int x, int y)
//{
//	//设置按钮颜色样式和字体样式
//	setbkmode(0);  //等价于transparent
//	setfillcolor(RGB(0, 108, 190));
//	setlinecolor(RED);
//	settextstyle(25, 15, "宋体");
//	settextcolor(RGB(255, 60, 60));
//
//	//设置按钮形状
//	butcenter(1265, 691, x, y);							//圆角矩形参数void fillroundrect (int left, int top, int right, int bottom, int ellipsewidth, int ellipseheight);		// 画填充圆角矩形(有边框)
//	char text[] = "按钮";
//	//textcenter();
//}
//
//int main()
//{
//	//放置图片
//	IMAGE img, img1;
//
//	initgraph(1265, 691 ,EW_SHOWCONSOLE);
//	loadimage(&img, "./1.jpg", 600, 350);       //图片相对路径，./表示当前目录，../表示上一级目录
///*	loadimage(&img1, "E:\\MATLAB/2.jpg", 600, 350);   */ //图片绝对路径，注意正斜杆需要两个（因为需要转义），反斜杆只需要一个
//	//putimage(650, 300, &img1);
//	//
//	//居中放置图片
//	picenter(1265, 691, 600, 350, img);    //图片居中函数，参数为参照物右下角x,y坐标，待居中图片宽和高，插入的图片IMAGE指针
//
//	//创建按钮区域 
//	button(50, 30);
//
//	getchar();
//	closegraph();
//	return 0;
//}