#include"Declaration.h"

//菜单函数
//1，开始游戏(先初始化游戏数据Init_date再进入Game函数)
//2，排行榜
//3，设置
//4，开发者名单
//5，退出游戏

//界面菜单和页面函数
void MainMenu();					//开始界面菜单
void ModeSelectMenu();				//模式选择界面菜单
void SettingsMenu();				//设置界面菜单
void MusicMenu();					//音乐选择界面菜单
void ControlPanelShow();			//按键说明界面菜单
void DevelopersShow();				//制作组信息页面

//进入游戏界面函数
void NormalPage();					//普通模式界面设计
void InfinityPage();				//无尽模式界面设计
void PracticePage();				//练习模式界面设计
void PausePage(int get);			//暂停界面设计