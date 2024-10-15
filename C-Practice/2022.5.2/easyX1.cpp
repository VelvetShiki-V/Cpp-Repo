#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<graphics.h>
#include<easyx.h>

int main()
{
	//圆：circle
	//椭圆ellipse
	//多边形：polygon
	//扇形pie
	//矩形：rectangle
	//圆角矩形roundrect
	//线：line
	//点：putpixel

	//形状样式——各形状的单词前缀
	//各种形状函数默认：无填充但有边框
	//有边框和填充fill
	//无边框有填充solid
	//例：默认有边框无填充圆circle, 有边框和填充圆fillcircle，无边框有填充圆solidcircle

	//填充颜色：setfillcolor();其中可以为RGB数据，或英文单词（必须大写）
	//边框颜色：setlinecolor();
	//设置背景色：setbkcolor();  一般与清空绘图设备指令cleardevice();连用才能生效
	
	//设置线条样式：setlinestyle(); 参数为高度，宽度，字体
	//例：setlinestyle(PS_SOLID, 5);  为实现边框，5号字体
	
	//设置字体颜色settextcolor();   大写英文字母或RGB数据
	//qq截图用光标选取颜色按c直接拷贝RGB数据
	// 
	//输出字符或字符串outtextxy();  参数为坐标x, y，以及输出的字符串
	//字符串需要用双引号括起来，若没有预先在项目->easyX属性->配置属性->高级属性->字符集->使用多字节字符集（该字符集下可直接用双引号）
	//则需要使用TEXT("字符串内容")或_T("字符串内容")的格式将字符串括起来，才能输出
	// 
	//设置字体样式settextstyle();   参数为高，宽，"字体样式"    注：若高度宽度设置为0，表示字体自适应窗口大小
	//例：settextstyle(50, 0, "宋体");
	//
	//设置字体背景setbkmode();  输出的文本其自身也有背景覆盖，其中参数可以设置字符背景为透明与否
	//例：setbkmode(TRANSPARENT | OPAQUE);

	//设置初始化绘图窗口样式：initgraph(width),参数自左向右为宽width, 高height，窗口样式（默认int flag = NULL）
	//窗口样式还可以为SHOWCONSOLE（显示控制台），NOCLOSE（无退出按钮），NOMINIMIZE（无最小化按钮）
	 
	
	//示范sample
	//初始化绘图窗口
	initgraph(720, 360, NULL);  
	setbkcolor(GREEN);
	cleardevice();
	
	//画图
	setfillcolor(BLUE);
	setlinecolor(RED);
	setlinestyle(PS_SOLID, 5);
	//1. 原点（0, 0）填充有边框圆
	fillcircle(0, 0, 100);
	//2. 顶边无填充有边框矩形（坐标与半径一致）
	setlinecolor(YELLOW);
	setlinestyle(PS_SOLID, 1);
	circle(100, 100, 100);		  //参数：void rectangle(int left, int top, int right, int bottom)
	//3. 屏幕中央无边框有填充圆
	setfillcolor(WHITE);
	solidcircle(360, 180, 100);

	//在中央圆上写字
	settextcolor(BLACK);  //设置字体颜色
	outtextxy(320, 180, TEXT("Hello World"));  //在绘图界面输出字符的三种形式
	settextcolor(YELLOW);
	settextstyle(40, 15, "华文行楷");
	outtextxy(420, 180, _T("Hello World"));
	setbkmode(TRANSPARENT);     //设置字符背景与否，默认为不透明为OPAQUE
	settextcolor(RGB(182, 68, 255));   
	settextstyle(30, 20, "宋体");
	outtextxy(320, 230, "Hello World");

	//画矩形
	setfillcolor(BLACK);
	setlinestyle(PS_DASH, 5);
	setlinecolor(RGB(255, 0, 0));
	fillrectangle(500, 50, 700, 150);     //参数为左上角坐标xy，右下角坐标xy

	//在矩形框居中输出字符串
	settextcolor(RGB(255, 255, 255));      //如果不加入该条字符样式，会沿用之前设置的样式
	settextstyle(20, 10, "楷体");
	char arr[] = "This is Hello World";
	int width = (700 - 500) / 2 - textwidth(arr) / 2;     //计算出需要居中对齐的距离宽度
	int height = (150 - 50) / 2 - textheight(arr) / 2;    //计算出需要居中对齐的距离高度
	outtextxy(width + 500, height + 50, arr);             //输出时还需要加上需要对应输出的位置

	getchar();
	closegraph();         //关闭绘图窗口
/*	cleardevice;   */       //清空绘图设备
	
	return 0;
}