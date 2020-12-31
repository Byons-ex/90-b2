#include "cmd_console_tools.h"
#include "mine_sweeper.h"
#include <string.h>
#include <stdio.h>
#include <Windows.h>

int waitKeyDown(int w, int h, char& flag, int& x, int& y)
{
	int mx, my, ma, k1 = 0x7FFFFFFF, k2;
	bool isQuit = false;
	int ret = 0;
	y = 0x7FFFFFFF;

	while (!isQuit)
	{
		cct_read_keyboard_and_mouse(mx, my, ma, k1, k2);
		switch (k1)
		{
		case '!':
			flag = '!';
			isQuit = true;
			break;

		case '?':
			flag = '?';
			isQuit = true;
			break;

		case '~':
			flag = ' ';
			isQuit = true;
			break;

		case 'Q':
		case 'q':
			return -1;

		case ' ':
			return 1;

		default:
			if (k1 >= 'A' && k1 < 'A' + (int)h)
			{
				cct_getxy(mx, my);
				cct_showch(mx, my, k1);
				y = k1 - 'A';
				isQuit = true;
			}
			continue;
		}

		cct_getxy(mx, my);
		cct_showch(mx, my, k1);
	}

	if (y == 0x7FFFFFFF)
	{
		while (k1 < 'A' || k1 >= 'A' + (int)h)
			cct_read_keyboard_and_mouse(mx, my, ma, k1, k2);

		cct_getxy(mx, my);
		cct_showch(mx, my, k1);
		y = k1 - 'A';
		ret = 2;
	}

	k1 = 0x7FFFFFFF;
	while (true)
	{
		cct_read_keyboard_and_mouse(mx, my, ma, k1, k2);
		if (w > 9)
		{
			if (k1 >= '1' && k1 <= '9')
			{
				x = k1 - '1';
				cct_getxy(mx, my);
				cct_showch(mx, my, k1);
				return ret;
			}
			else if (k1 <= 'a' + (int)w - 9 && k1 >= 'a')
			{
				x = k1 - 'a' + 9;
				cct_getxy(mx, my);
				cct_showch(mx, my, k1);
				return ret;
			}
		}
		else
		{
			if (k1 >= '1' && k1 <= '9')
			{
				x = k1 - '1';
				cct_getxy(mx, my);
				cct_showch(mx, my, k1);
				return ret;
			}
		}
	}

	x = y = 0;
	return ret;
}

char* mousePosToFieldPos(int mx, int my, int fw, int fh, int& fx, int& fy)
{
	mx -= 2;
	my -= 2;

	if (mx / 6 >= fw || mx % 6 < 2 || my / 3 >= fh || my % 3 < 1)
		return NULL;

	fx = mx / 6;
	fy = my / 3;

	char *str = new char[32];
	char sx = fx < 9 ? fx + '1' : fx - 9 + 'a';
	char sy = fy + 'A';
	sprintf_s(str, 32, "当前位置：%c, %c", sy, sx);
	return str;
}

void waitPressEnter()
{
	while (true)
	{
		int mx, my, ma, k1, k2;
		cct_read_keyboard_and_mouse(mx, my, ma, k1, k2);
		if (k1 == 0x0D)
			break;
	}
}

char* timeToSecString(uint64_t ms)
{
	char* str = new char[32];
	sprintf_s(str, 32, "当前时间%.3f秒", (int)ms / 1000.0f);
	return str;
}