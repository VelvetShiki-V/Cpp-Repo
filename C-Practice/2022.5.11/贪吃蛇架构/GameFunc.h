#include"Declaration.h"

//以下为游戏参数设置
#define MAX 100						//蛇身体的最大节数
#define Length 2					//蛇初始长度，最大不超过5(Recommended)
#define Scale 						//蛇每节大小
#define FoodSize 5					//食物大小

//以下为游戏相关模块的结构体模板
struct snake						//蛇结构定义
{
	int length;						//蛇的初始长度
	int direction;					//蛇的初始朝向
	int speed;						//蛇的速度
	POINT coord[MAX];				//蛇最大节数MAX和嵌套坐标结构体类型POINT，通过coord[].x或coord[].y访问蛇头横纵坐标实现蛇的移动
};

enum direction						//方向键上下左右方向枚举定义
{
	UP,								//0
	DOWN,							//1
	LEFT,							//2
	RIGHT							//3
};

struct Food							//食物定义
{
	int x;							//食物横坐标
	int y;							//食物纵坐标
	int r;							//食物大小半径
	DWORD color;					//unsigned long型变量，定义食物颜色RGB值
	time_t t;						//食物在游戏中随机生成变量
	bool flag;						//判断食物是否被吃掉的布尔变量（0被吃，1没被吃）
};

//游戏功能函数
int GameOver();						//游戏结束，参数为空，返回值返回（重试1或退出0）
void GamePass(int PassNum);			//游戏通关，参数为（普通通关到下一界面，或通关获胜，调用Victory）
void Victory();						//游戏胜利，参数为空
void Infinity();

//交互函数
int KeyBoardControl();				//通过键盘和Windows静态库函数实现WASD控制蛇移动