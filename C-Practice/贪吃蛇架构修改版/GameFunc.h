#include"Declaration.h"

//游戏功能函数
void GamePlay();										//开始游戏
void GameOver();										//游戏结束
void GamePass(int PassNum);								//游戏通关
void Victory();											//游戏胜利
void SnakeMove();										//蛇身蛇头移动函数
void GameDraw();										//贪吃蛇和食物图形的缓冲绘制
void FoodInit();										//食物的随机生成和出现位置函数
void SnakeInit();										//蛇出生点和状态的初始化
void BorderLine(int SnakeState);						//蛇与地狱边界碰撞检测函数
void EatSelf(int SnakeState);							//蛇与自身坐标碰撞检测函数
void EatFoot();											//食物被吃判断函数

//交互函数
int KeyBoardControl();				//通过键盘和Windows静态库函数实现WASD控制蛇移动