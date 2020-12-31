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
		int w, h, mineCount;
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
			launchMode_6(w, h, mineCount);
			break;
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

void launchMode_1(int w, int h, int mineCount)
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

void launchMode_2(int w, int h, int mineCount)
{
	MineField* field = initMineField(w, h, mineCount);

	const char* head[] = {"�ڲ����飺"};
	const char* rear[] = {"����λ�õ��������꣨���к��У��ϸ����ִ�Сд������G1/Af����Q/q�˳�����",
						  "���س����˳�..." };
	paintFieldWithStr(field, head, 1, rear, 1);

	int x, y;
	char flag;
	if (waitKeyDown(w, h, flag, x, y) != -1)
	{
		clear(field, x, y);
		paintFieldWithStr(field, head, 1, rear + 1, 1);
	}
	waitPressEnter();

	uninitMineField(field);
}

void launchMode_3(int w, int h, int mineCount)
{
	MineField* field = initMineField(w, h, mineCount);

	const char* head[] = { "�ַ����棺" };
	const char* rear[] = { "����λ�õ��������꣨���к��У��ϸ����ִ�Сд������G1/Af����Q/q�˳�����",
						   "���س����˳�..."};

	paintFieldWithStr(field, head, 1, rear, 1);

	int x, y;
	auto ret = 0;
	char flag;
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
		rear[0] = "���ϧ��ʧ����";
		paintFieldWithStr(field, head, 1, rear, 2);
	}

	if (ret == 1)
	{
		rear[0] = "��ϲ�㣬ʤ����";
		paintFieldWithStr(field, head, 1, rear, 2);
	}

	waitPressEnter();
	uninitMineField(field);
}

void launchMode_4(int w, int h, int mineCount)
{
	const char* head[2] = {NULL, "�ַ����棺"};  // Ԥ��һ��Ԫ�أ���������ʾʱ��
	const char* rear[] = { "����λ�õ��������꣨���к��У��ϸ����ִ�Сд������G1/Af����Q/q�˳�������ʾ�������Ϸʱ�䰴�ո�",
						   "ǰ׺[?!]�Ա�־��λ�ã������������λ�ã����磺!G1 ?Af�������ǰ��־ʹ��[~],��~Af�� ",
						   "���س����˳�..." };

	int headCount = 1;

	MineField* field = initMineField(w, h, mineCount);
	paintFieldWithStr(field, head + 1, 1, rear, 2);
	auto startTime = GetTickCount64();
	auto ret = 0;
	while (true)
	{
		int x, y;
		char flag;
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
				delete[] head[0];
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
		rear[1] = "���ϧ��ʧ����";
		paintFieldWithStr(field, head, headCount, rear + 1, 2);
	}

	if (ret == 1)
	{
		rear[1] = "��ϲ�㣬ʤ����";
		paintFieldWithStr(field, head, headCount, rear + 1, 2);
	}

	waitPressEnter();
	uninitMineField(field);
}

void launchMode_5(int w, int h, int mineCount)
{
	MineField* field = initMineField(w, h, mineCount);

	InitGraph(field);
	
	clear(field, 0, 0);

	for (int x = 0; x < w; ++x)
	{
		for(int y = 0; y < h; ++y)
		{
			updateGraphGrid(field, x, y, internalGrid(field, x, y));
		}
	}

	showMsgWitGraph(field, "���س����˳�...");
	waitPressEnter();
	uninitMineField(field);
}

void launchMode_6(int w, int h, int mineCount)
{
	MineField* field = initMineField(w, h, mineCount);

	InitGraph(field);

	while (true)
	{
		int mx, my, ma, k1, k2;
		cct_read_keyboard_and_mouse(mx, my, ma, k1, k2);

		if (ma == MOUSE_LEFT_BUTTON_CLICK)
			break;

		int x, y;
		char * str = mousePosToFieldPos(mx, my, w, h, x, y);
		if (str == NULL)
		{
			showMosePosWithGraph(field, "�Ƿ�λ��");
		}
		else
		{
			showMosePosWithGraph(field, str);
			delete[] str;
		}
	}

	showMsgWitGraph(field, "���س����˳�...");
	waitPressEnter();
	uninitMineField(field);
}


void launchMode_7(int w, int h, int mineCount)
{
	MineField* field = initMineField(w, h, mineCount);

	InitGraph(field);

	while (true)
	{
		int mx, my, ma, k1, k2;
		cct_read_keyboard_and_mouse(mx, my, ma, k1, k2);

		int x, y;
		char* str = mousePosToFieldPos(mx, my, w, h, x, y);
		if (str == NULL)
		{
			showMosePosWithGraph(field, "�Ƿ�λ��");
			continue;
		}

		showMosePosWithGraph(field, str);
		delete[] str;

		if (ma == MOUSE_LEFT_BUTTON_CLICK)
		{

		}
	}

	showMsgWitGraph(field, "���س����˳�...");
	waitPressEnter();
	uninitMineField(field);
}