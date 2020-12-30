#include "cmd_console_tools.h"
#include "mine_sweeper.h"
#include <stdlib.h>
#include <Windows.h>


int main(void)
{
	cct_setfontsize("Terminal", 16, 8);
	//cct_disable_mouse();
	int model = showMainMenu();

	while (model != 0)
	{
		unsigned w, h, mineCount;
		showLevelMenu(w, h, mineCount);

		switch (model)
		{
		case 1:
			launchMode_1(w, h, mineCount);
			break;
		case 2:
			launchMode_2(w, h, mineCount);
			break;
		case 3:
			launchMode_3(w, h, mineCount);
			break;
		case 4:
			launchMode_4(w, h, mineCount);
			break;
		case 5:
			launchMode_5(w, h, mineCount);
			break;
		case 6:


		case 7:


		case 8:


		case 9:


		default:
			break;
		}

		model = showMainMenu();
	}

	return 0;
}

void launchMode_1(unsigned w, unsigned h, unsigned mineCount)
{
	MineField* mineField = initMineField(w, h, mineCount);
	clear(mineField, 0, 0);
	paintMode_1(mineField);

	while (true)
	{
		int mx, my, ma, k1, k2;
		cct_read_keyboard_and_mouse(mx, my, ma, k1, k2);
		if (k1 == 0x0D)
			break;
	}

	uninitMineField(mineField);
}

void launchMode_2(unsigned w, unsigned h, unsigned mineCount)
{
	MineField* field = initMineField(w, h, mineCount);

	const char* head[] = {"内部数组："};
	const char* rear[] = {"输入位置的行列坐标（先行后列，严格区分大小写，例：G1/Af，按Q/q退出）：",
						  "按回车键退出..." };
	paintFieldWithStr(field, head, 1, rear, 1);

	unsigned x, y;
	GRID_STATUS flag;
	if (waitKeyDown(w, h, flag, x, y) != -1)
	{
		clear(field, x, y);
		paintFieldWithStr(field, head, 1, rear + 1, 1);
	}
	waitPressEnter();

	uninitMineField(field);
}

void launchMode_3(unsigned w, unsigned h, unsigned mineCount)
{
	MineField* field = initMineField(w, h, mineCount);

	const char* head[] = { "字符界面：" };
	const char* rear[] = { "输入位置的行列坐标（先行后列，严格区分大小写，例：G1/Af，按Q/q退出）：",
						   "按回车键退出..."};

	paintFieldWithStr(field, head, 1, rear, 1);

	unsigned x, y;
	auto ret = 0;
	GRID_STATUS	flag;
	while (true)
	{
		ret = waitKeyDown(w, h, flag, x, y);
		if (ret == -1)
		{
			ret = -2;
			break;
		}

		if (ret != 0)
		{
			paintFieldWithStr(field, head, 1, rear, 1);
			continue;
		}

		ret = clear(field, x, y);
		if (ret == -1)
			break;

		paintFieldWithStr(field, head, 1, rear, 1);
	}

	if (ret == -2)
	{
		paintFieldWithStr(field, head, 1, rear + 1, 1);
	}

	if (ret == -1)
	{
		rear[0] = "真可惜，失败了";
		paintFieldWithStr(field, head, 1, rear, 2);
	}

	if (ret == 1)
	{
		rear[0] = "恭喜你，胜利了";
		paintFieldWithStr(field, head, 1, rear, 2);
	}

	waitPressEnter();
	uninitMineField(field);
}

void launchMode_4(unsigned w, unsigned h, unsigned mineCount)
{
	const char* head[2] = {NULL, "字符界面："};  // 预留一个元素，待会能显示时间
	const char* rear[] = { "输入位置的行列坐标（先行后列，严格区分大小写，例：G1/Af，按Q/q退出），显示或更新游戏时间按空格。",
						   "前缀[?!]以标志该位置，而不是清理该位置，例如：!G1 ?Af，清除当前标志使用[~],如~Af： ",
						   "按回车键退出..." };

	int headCount = 1;

	MineField* field = initMineField(w, h, mineCount);
	paintFieldWithStr(field, head + 1, 1, rear, 2);
	auto startTime = GetTickCount64();
	auto ret = 0;
	while (true)
	{
		unsigned x, y;
		GRID_STATUS flag;
		ret = waitKeyDown(w, h, flag, x, y);
		if (ret == -1)
		{
			paintFieldWithStr(field, head, headCount, rear + 2, 1);
			waitPressEnter();
			uninitMineField(field);
			return;
		}

		if (ret == 1)
		{
			if (head[0] != NULL)
				delete head[0];
			head[0] = timeToSecString(GetTickCount64() - startTime);
			headCount = 2;
			paintFieldWithStr(field, head, headCount, rear, 2);
			continue;
		}
		
		if (ret == 2)
		{
			setStatus(field, x, y, flag);
			paintFieldWithStr(field, head, headCount, rear, 2);
			continue;
		}

		ret = clear(field, x, y);
		if (ret != 0)
			break;

		paintFieldWithStr(field, head, headCount, rear, 2);
	}

	if (ret == -1)
	{
		rear[1] = "真可惜，失败了";
		paintFieldWithStr(field, head, headCount, rear + 1, 2);
	}

	if (ret == 1)
	{
		rear[1] = "恭喜你，胜利了";
		paintFieldWithStr(field, head, headCount, rear + 1, 2);
	}

	waitPressEnter();
	uninitMineField(field);
}

void launchMode_5(unsigned w, unsigned h, unsigned mineCount)
{
	MineField* field = initMineField(w, h, mineCount);

	InitGraph(field);
	

	waitPressEnter();
	uninitMineField(field);
}