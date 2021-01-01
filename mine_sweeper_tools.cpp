#include "cmd_console_tools.h"
#include "mine_sweeper.h"
#include <string.h>
#include <Windows.h>

bool keycodeToControlKey(int key, char& colKey)
{
	switch (key)
	{
	case '&':
	case '!':
	case '#':
	case 'q':
		colKey = (char)key;
		return true;

	case 'Q':
		colKey = 'q';
		return true;

	default:
		break;
	}

	return false;
}

bool keycodeToFieldRow(int fh, int key, int& row)
{
	if (key >= 'A' && key < 'A' + fh)
	{
		row = key - 'A';
		return true;
	}

	return false;
}

bool keycodeToFieldCol(int fw, int key, int& col)
{
	if (key >= '1' && key < '1' + fw)
	{
		col = key - '1';
		return true;
	}

	if (key >= 'a' && key < fw - 9 + 'a')
	{
		col = key - 'a' + 9;
		return true;
	}

	return false;
}

bool mousePosToFieldPos(int mx, int my, int fw, int fh, int& fx, int& fy)
{
	mx -= 2;
	my -= 3;

	if (mx / 6 >= fw || mx % 6 < 2 || my / 3 >= fh || my % 3 < 1)
		return false;

	fx = mx / 6;
	fy = my / 3;

	return true;
}

void strView_headMsg(const char* str)
{
	cct_showstr(0, 0, str);
}

void strView_rearMsg(MineField* field, int row, const char* str)
{
	int w, h;
	FieldSize(field, w, h);

	int y = h + 3 + row;
	cct_showstr(0, y, str);
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