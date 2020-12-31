#include "cmd_console_tools.h"
#include "mine_sweeper.h"

#include <iostream>

using namespace std;

int showMainMenu()
{
	int select = -1;
	int mX, mY, key2, mAction;

	cct_cls();

	cct_showstr(0, 0, "---------------------------");
	cct_showstr(0, 1, "1.选择难度并显示内部数组");
	cct_showstr(0, 2, "2.输入初始位置并显示被打开的初始区域");
	cct_showstr(0, 3, "3.内部数组基础版");
	cct_showstr(0, 4, "4.内部数组完整版（标记，运行时间）");
	cct_showstr(0, 5, "5.画出伪图形化框架并显示内部数据");
	cct_showstr(0, 6, "6.检测鼠标位置和合法性（左键单机退出）");
	cct_showstr(0, 7, "7.鼠标选择初始位置并显示被打开的初始区域");
	cct_showstr(0, 8, "8.伪图形界面基础版");
	cct_showstr(0, 9, "9.伪图形界面完整版");
	cct_showstr(0, 10, "0.退出游戏");
	cct_showstr(0, 11, "---------------------------");

	cct_showstr(0, 12, "[请选择]: ");

	while (select > '9' || select < '0')
		cct_read_keyboard_and_mouse(mX, mY, mAction, select, key2);

	return select - '0';
}

void showLevelMenu(int& w, int& h, int& mineCount)
{
	int select = -1;
	int mX, mY, key2, mAction;

	cct_cls();

	cct_showstr(0, 0, "请选择难度:");
	cct_showstr(2, 1, "1.初级（9*9   - 10颗雷）");
	cct_showstr(2, 2, "2.初级（16*16 - 40颗雷）");
	cct_showstr(2, 3, "3.初级（16*30 - 99颗雷）");

	cct_showstr(0, 4, "请输入[1..3]:");

	while (select > '9' || select < '0')
		cct_read_keyboard_and_mouse(mX, mY, mAction, select, key2);

	switch (select - '0')
	{
	case 1:
		w = h = 9;
		mineCount = 10;
		return;
	case 2:
		w = h = 16;
		mineCount = 40;
		return;

	case 3:
		w = 30;
		h = 16;
		mineCount = 99;
		return;

	default:
		w = h = mineCount = 0;
		return;
	}
}
