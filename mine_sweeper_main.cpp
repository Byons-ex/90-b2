#include "cmd_console_tools.h"
#include "mine_sweeper.h"
#include <stdlib.h>
#include <stdio.h>
#include <Windows.h>

int main(void)
{
	cct_setfontsize("Terminal", 16, 8);
	int model = showMainMenu();

	LAUNCH_MODE modes[] = { launchMode_1,
							launchMode_2,
							launchMode_3,
							launchMode_4,
							launchMode_5,
							launchMode_6,
							launchMode_7,
							launchMode_8,
							launchMode_9 };

	while (model != 0)
	{
		int w, h, mineCount;
		showLevelMenu(w, h, mineCount);

		modes[model - 1](w, h, mineCount);

		model = showMainMenu();
	}

	return 0;
}

void launchMode_1(int w, int h, int mineCount)
{
	cct_setcursor(CURSOR_VISIBLE_NORMAL);
	MineField* mineField = initMineField(w, h, mineCount);
	initStrView(mineField);
	clear(mineField, 0, 0, updateStrViewGrid_1);

	for (int x = 0; x < w; ++x)
	{
		for (int y = 0; y < h; ++y)
		{
			updateStrViewGrid_1(mineField, x, y, internalGrid(mineField, x, y));
		}
	}

	showHeadMsgWithStrView("�ڲ����飺");

	showRearMsgWithStrView(mineField, 2, "���س����˳�...");

	waitPressEnter();
	uninitMineField(mineField);
}

void launchMode_2(int w, int h, int mineCount)
{
	cct_setcursor(CURSOR_VISIBLE_NORMAL);
	MineField* field = initMineField(w, h, mineCount);

	initStrView(field);
	showHeadMsgWithStrView("�ַ����棺");
	showRearMsgWithStrView(field, 2, "����λ�õ��������꣨���к��У��ϸ����ִ�Сд������G1/Af����Q/q�˳�����");

	int x = -1, y = -1;
	while (true)
	{
		int mx, my, ma, k1, k2;
		cct_read_keyboard_and_mouse(mx, my, ma, k1, k2);
		
		char controlKey;
		if (keycodeToControlKey(k1, controlKey))
		{
			if (controlKey == 'q')
			{
				break;
			}
		}

		int row;
		if (keycodeToFieldRow(h, k1, row))
		{
			y = row;
			cct_getxy(mx, my);
			cct_showch(mx, my, k1);
			continue;
		}

		int col;
		if (keycodeToFieldCol(w, k1, col) && y != -1)
		{
			x = col;
			cct_getxy(mx, my);
			cct_showch(mx, my, k1);
			break;
		}
	}
	
	if(x != -1 && y != -1)
		clear(field, x, y, updateStrViewGrid_2);

	showRearMsgWithStrView(field, 3, "���س����˳�...");
	waitPressEnter();
	uninitMineField(field);
}

void launchMode_3(int w, int h, int mineCount)
{
	cct_setcursor(CURSOR_VISIBLE_NORMAL);
	MineField* field = initMineField(w, h, mineCount);

	initStrView(field);
	showHeadMsgWithStrView("�ַ����棺");
	showRearMsgWithStrView(field, 2, "����λ�õ��������꣨���к��У��ϸ����ִ�Сд������G1/Af����Q/q�˳�����");

	int x = -1, y = -1;
	int ret = 0;
	while (true)
	{
		int mx, my, ma, k1, k2;
		cct_read_keyboard_and_mouse(mx, my, ma, k1, k2);

		char controlKey;
		if (keycodeToControlKey(k1, controlKey))
		{
			if (controlKey == 'q' && y == -1)
			{
				ret = -2;
				break;
			}
		}

		int row;
		if (keycodeToFieldRow(h, k1, row))
		{
			y = row;
			cct_getxy(mx, my);
			cct_showch(mx, my, k1);
			continue;
		}

		int col;
		if (keycodeToFieldCol(w, k1, col) && y != -1)
		{
			x = col;
			cct_getxy(mx, my);
			cct_showstr(mx - 1, my, "   ");
			cct_gotoxy(mx - 1, my);

			ret = clear(field, x, y, updateStrViewGrid_2);
			if (ret != 0)
				break;

			x = y = -1;
		}
	}

	if (ret == -1)
	{
		showRearMsgWithStrView(field, 3, "���ϧ��ʧ����            ");
	}

	if (ret == 1)
	{
		showRearMsgWithStrView(field, 3, "��ϲ�㣬ʤ����            ");
	}

	showRearMsgWithStrView(field, 4, "���س����˳�...");
	waitPressEnter();
	uninitMineField(field);
}

void launchMode_4(int w, int h, int mineCount)
{
	cct_setcursor(CURSOR_VISIBLE_NORMAL);
	MineField* field = initMineField(w, h, mineCount);

	initStrView(field);
	showHeadMsgWithStrView("�ַ����棺");
	showRearMsgWithStrView(field, 3, "��������˵����& - ��Ϸ������ʱ��(���ַ����ɣ�����Ҫ������)");
	showRearMsgWithStrView(field, 4, "              ! - ��Ǹ�����Ϊ��(����!E3)");
	showRearMsgWithStrView(field, 5, "              # - ȡ�����      (����#E3)");
	showRearMsgWithStrView(field, 6, "�����루����������к��У��ϸ����ִ�Сд������G1/Af����Q/q�˳�����");

	uint64_t startTime = GetTickCount64();

	int x = -1, y = -1;
	char controlKey = -1;
	int ret = 0;
	while (true)
	{
		int mx, my, ma, k1, k2;
		cct_read_keyboard_and_mouse(mx, my, ma, k1, k2);

		char key;
		if (keycodeToControlKey(k1, key) && y == -1)
		{
			if (key == 'q')
			{
				ret = -2;
				break;
			}

			if (key == '&')
			{
				cct_getxy(mx, my);

				char* timeStr = new char[32];
				uint64_t currTime = GetTickCount64() - startTime;
				sprintf_s(timeStr, 32, "��ǰʱ�䣺 %.3f��", (int)currTime / 1000.0f);
				showRearMsgWithStrView(field, 2, timeStr);
				delete[] timeStr;

				cct_gotoxy(mx, my);
				continue;
			}

			cct_getxy(mx, my);
			cct_showch(mx, my, key);
			controlKey = key;
			continue;
		}

		int row;
		if (keycodeToFieldRow(h, k1, row) && y == -1)
		{
			y = row;
			cct_getxy(mx, my);
			cct_showch(mx, my, k1);
			continue;
		}

		int col;
		if (keycodeToFieldCol(w, k1, col) && y != -1)
		{
			x = col;

			showRearMsgWithStrView(field, 6, "�����루����������к��У��ϸ����ִ�Сд������G1/Af����Q/q�˳�����   ");
			cct_getxy(mx, my);
			cct_gotoxy(mx - 3, my);

			if (controlKey != -1)
			{
				if (controlKey == '!')
				{
					setFlag(field, x, y, '!');
					updateStrViewGrid_2(field, x, y, '!');
				}

				if (controlKey == '#')
				{
					setFlag(field, x, y, ' ');
					updateStrViewGrid_2(field, x, y, ' ');
				}

				controlKey = -1;
				x = y = -1;
				continue;
			}

			ret = clear(field, x, y, updateStrViewGrid_2);
			if (ret != 0)
				break;

			x = y = -1;
		}
	}

	if (ret == -1)
	{
		showRearMsgWithStrView(field, 7, "���ϧ��ʧ����            ");
	}

	if (ret == 1)
	{
		showRearMsgWithStrView(field, 7, "��ϲ�㣬ʤ����            ");
	}

	showRearMsgWithStrView(field, 8, "���س����˳�...");
	waitPressEnter();
	uninitMineField(field);
}

void launchMode_5(int w, int h, int mineCount)
{
	MineField* field = initMineField(w, h, mineCount);

	initGraph(field);
	
	clear(field, 0, 0, updateGraphGrid);

	for (int x = 0; x < w; ++x)
	{
		for(int y = 0; y < h; ++y)
		{
			updateGraphGrid(field, x, y, internalGrid(field, x, y));
		}
	}

	showEndMsgWithGraph(field, "���س����˳�...");
	waitPressEnter();
	uninitMineField(field);
}

void launchMode_6(int w, int h, int mineCount)
{
	MineField* field = initMineField(w, h, mineCount);

	initGraph(field);

	while (true)
	{
		int mx, my, ma, k1, k2;
		cct_read_keyboard_and_mouse(mx, my, ma, k1, k2);

		if (ma == MOUSE_LEFT_BUTTON_CLICK)
			break;

		int x, y;
		bool succeed = mousePosToFieldPos(mx, my, w, h, x, y);
		if (!succeed)
		{
			showMosePosWithGraph(field, -1, -1);
		}
		else
		{
			showMosePosWithGraph(field, x, y);
		}
	}

	showEndMsgWithGraph(field, "���س����˳�...");
	waitPressEnter();
	uninitMineField(field);
}

void launchMode_7(int w, int h, int mineCount)
{
	MineField* field = initMineField(w, h, mineCount);

	initGraph(field);

	while (true)
	{
		int mx, my, ma, k1, k2;
		cct_read_keyboard_and_mouse(mx, my, ma, k1, k2);

		int x, y;
		bool succeed = mousePosToFieldPos(mx, my, w, h, x, y);
		if (!succeed)
		{
			showMosePosWithGraph(field, -1, -1);
			continue;
		}

		showMosePosWithGraph(field, x, y);

		if (ma == MOUSE_LEFT_BUTTON_CLICK)
		{
			clear(field, x, y, updateGraphGrid);
			break;
		}
	}

	showEndMsgWithGraph(field, "���س����˳�...");
	waitPressEnter();
	uninitMineField(field);
}

void launchMode_8(int w, int h, int mineCount)
{
	MineField* field = initMineField(w, h, mineCount);

	initGraph(field);

	int ret = 0;

	while (true)
	{
		int mx, my, ma, k1, k2;
		cct_read_keyboard_and_mouse(mx, my, ma, k1, k2);

		if (k1 == VK_ESCAPE)
		{
			ret = -2;
			break;
		}

		int x, y;
		bool succeed = mousePosToFieldPos(mx, my, w, h, x, y);
		if (!succeed)
		{
			showMosePosWithGraph(field, -1, -1);
			continue;
		}

		showMosePosWithGraph(field, x, y);

		if (ma == MOUSE_LEFT_BUTTON_CLICK)
		{
			ret = clear(field, x, y, updateGraphGrid);
			if (ret != 0)
				break;
		}

		if (ma == MOUSE_RIGHT_BUTTON_CLICK)
		{
			auto flag = grid(field, x, y);
			switch (flag)
			{
			case '?':
				setFlag(field, x, y, '!');
				updateGraphGrid(field, x, y, '!');
				break;
			case '!':
				setFlag(field, x, y, ' ');
				updateGraphGrid(field, x, y, ' ');
				break;
			case ' ':
				setFlag(field, x, y, '?');
				updateGraphGrid(field, x, y, '?');
				break;
			default:
				break;
			}
		}
	}

	if (ret == -1)
	{
		showResultWithGraph(field, "�����ˣ� �´�Ŭ��...");
	}

	if (ret == 1)
	{
		showResultWithGraph(field, "��Ӯ��...");
	}

	showEndMsgWithGraph(field, "���س����˳�...");
	waitPressEnter();
	uninitMineField(field);
}

void launchMode_9(int w, int h, int mineCount)
{
	MineField* field = initMineField(w, h, mineCount);

	initGraph(field);

	uint64_t startTime = GetTickCount64();
	showCurrTimeWithGraph(field, 0);

	int ret = 0;

	int dangerFlagCount = 0;
	showRemianMineWithGraph(field, mineCount);

	showTipMsgWithGraph(field, "��ESC���������ո������Ϸʱ��");

	while (true)
	{
		int mx, my, ma, k1, k2;
		cct_read_keyboard_and_mouse(mx, my, ma, k1, k2);

		if (k1 == VK_ESCAPE)
		{
			ret = -2;
			break;
		}

		if (k1 == VK_SPACE)
		{
			showCurrTimeWithGraph(field, GetTickCount64() - startTime);
		}

		int x, y;
		bool succeed = mousePosToFieldPos(mx, my, w, h, x, y);
		if (!succeed)
		{
			showMosePosWithGraph(field, -1, -1);
			continue;
		}

		showMosePosWithGraph(field, x, y);

		if (ma == MOUSE_LEFT_BUTTON_CLICK)
		{
			ret = clear(field, x, y, updateGraphGrid);
			if (ret != 0)
				break;
		}

		if (ma == MOUSE_RIGHT_BUTTON_CLICK)
		{
			auto flag = grid(field, x, y);
			switch (flag)
			{
			case '?':
				setFlag(field, x, y, '!');
				updateGraphGrid(field, x, y, '!');
				++dangerFlagCount;
				showRemianMineWithGraph(field, mineCount - dangerFlagCount);
				break;

			case '!':
				setFlag(field, x, y, ' ');
				updateGraphGrid(field, x, y, ' ');
				--dangerFlagCount;
				showRemianMineWithGraph(field, mineCount - dangerFlagCount);
				break;

			case ' ':
				setFlag(field, x, y, '?');
				updateGraphGrid(field, x, y, '?');
				break;

			default:
				break;
			}
		}
	}

	if (ret == -1)
	{
		showResultWithGraph(field, "�����ˣ� �´�Ŭ��...");
	}

	if (ret == 1)
	{
		showRemianMineWithGraph(field, 0);
		showResultWithGraph(field, "��Ӯ��...");
	}
	
	showEndTimeWithGraph(field, GetTickCount64() - startTime);
	showEndMsgWithGraph(field, "���س����˳�...");
	waitPressEnter();
	uninitMineField(field);
}
