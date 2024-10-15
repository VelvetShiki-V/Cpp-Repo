#include"Declaration.h"

int MouseClick(ExMessage* click, int BUT_Width, int BUT_Height);	//通过鼠标点击操作界面函数，参数为（ExMessage*鼠标功能结构体地址）可以实现左键或右键与界面的交互
																	//以及传入鼠标点击区域的按钮宽高
void Button(int shape, int x, int y);								//按钮样式设计函数，参数为（形状）
void TurnTo(int PageNum);											//界面跳转函数，参数为（需要跳转的界面编号，如主页PageNum = 1,模式页面PageNum = 2等等）
void Text(char* text, int x, int y);								//文本输出函数
void Music(int MusicNum);											//音乐播放函数，参数为（歌曲编号，播放或停止）
void Message(LPCSTR* title, LPCSTR* content);						//弹窗函数，参数为（弹窗标题，弹窗内容，类型为常量字符指针LPCSTR*）
void PicInsert(IMAGE img, char* route, int width, int height, int change);		//插入图片或背景函数，参数为（图片指针，图片路径字符串，待插入图片宽高） // 相对路径： "./image.jpg"		绝对路径："D:\App\Adobe\Dw"
void ParaCenter(int* x, int* y);									//水平居中函数，参数为（图片或文本左上像素点横纵坐标的地址int*）
void Exit();														//退出
