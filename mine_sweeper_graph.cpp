#include "cmd_console_tools.h"
#include "mine_sweeper.h"
#include <memory.h>
#include <string.h>
#include <stdio.h>

void graph_init(MineField* field)
{
	int w, h;
	FieldSize(field, w, h);
	cct_setconsoleborder(6 * w + 6, 3 * h + 8);

	// 画行标题
	int y = 1;
	char title = 'A';
	for (int i = 0; i < h; ++i)
	{
		y += 3;
		cct_showch(0, y, title);
		++title;
	}

	// 画列标题
	int x = 0;
	title = '1';
	for (int i = 0; i < w; ++i)
	{
		x += 6;
		cct_showch(x, 2, title);
		++title;

		if (title == ':')
			title = 'a';
	}

	// 画═
	x = 2;
	y = 3;
	for (int i = 0; i < w * 3 + 1; ++i)
	{
		y = 3;
		for (int j = 0; j < h + 1; ++j)
		{
			cct_showstr(x, y, "═", COLOR_HWHITE, COLOR_BLACK);
			y += 3;
		}
		x += 2;
	}

	// 画║
	x = 2;
	y = 3;
	for (int i = 0; i < w + 1; ++i)
	{
		y = 3;
		for (int j = 0; j < h * 3 + 1; ++j)
		{
			cct_showstr(x, y, "║", COLOR_HWHITE, COLOR_BLACK);
			y += 1;
		}
		x += 6;
	}

	// 画四个角
	cct_showstr(2, 3, "╔", COLOR_HWHITE, COLOR_BLACK);
	cct_showstr(2, 3 + 3 * h, "╚", COLOR_HWHITE, COLOR_BLACK);
	cct_showstr(2 + w * 6, 3, "╗", COLOR_HWHITE, COLOR_BLACK);
	cct_showstr(2 + w * 6, 3 + 3 * h, "╝", COLOR_HWHITE, COLOR_BLACK);

	// 画╠.╣
	y = 3;
	for (int i = 0; i < h - 1; ++i)
	{
		y += 3;
		cct_showstr(2, y, "╠", COLOR_HWHITE, COLOR_BLACK);
		cct_showstr(2 + w * 6, y, "╣", COLOR_HWHITE, COLOR_BLACK);
	}

	// 画╦.╩
	x = 2;
	for (int i = 0; i < w - 1; ++i)
	{
		x += 6;
		cct_showstr(x, 3, "╦", COLOR_HWHITE, COLOR_BLACK);
		cct_showstr(x, 3 + h * 3, "╩", COLOR_HWHITE, COLOR_BLACK);
	}

	// 画╬
	x = 2;
	y = 3;
	for (int i = 0; i < w - 1; ++i)
	{
		x += 6;
		y = 3;
		for (int j = 0; j < h - 1; ++j)
		{
			y += 3;
			cct_showstr(x, y, "╬", COLOR_HWHITE, COLOR_BLACK);
		}
	}

	for (x = 0; x < w; ++x)
	{
		for (y = 0; y < h; ++y)
		{
			graph_updateGrid(field, x, y, ' ');
		}
	}
}

void graph_updateGrid(MineField* field, int x, int y, char stuff)
{
	int w, h;
	FieldSize(field, w, h);

	x = 4 + (x * 6);
	y = 4 + (y * 3);

	switch (stuff)
	{
	case '*':
		cct_showstr(x, y, "    ", COLOR_WHITE, COLOR_WHITE);
		cct_showstr(x, y + 1, "    ", COLOR_WHITE, COLOR_WHITE);
		cct_showch(x + 1, y + 1, stuff, COLOR_WHITE, COLOR_BLACK);
		break;

	case '!':
		cct_showstr(x, y, "    ", COLOR_HRED, COLOR_HRED);
		cct_showstr(x, y + 1, "    ", COLOR_HRED, COLOR_HRED);
		cct_showch(x + 1, y + 1, stuff, COLOR_HRED, COLOR_BLACK);
		break;

	case '?':
		cct_showstr(x, y, "    ", COLOR_HYELLOW, COLOR_HYELLOW);
		cct_showstr(x, y + 1, "    ", COLOR_HYELLOW, COLOR_HYELLOW);
		cct_showch(x + 1, y + 1, stuff, COLOR_HYELLOW, COLOR_BLACK);
		break;

	case ' ':
		cct_showstr(x, y, "    ", COLOR_YELLOW, COLOR_YELLOW);
		cct_showstr(x, y + 1, "    ", COLOR_YELLOW, COLOR_YELLOW);
		break;

	case '0':
		cct_showstr(x, y, "    ", COLOR_WHITE, COLOR_WHITE);
		cct_showstr(x, y + 1, "    ", COLOR_WHITE, COLOR_WHITE);
		break;

	default:
		cct_showstr(x, y, "    ", COLOR_WHITE, COLOR_WHITE);
		cct_showstr(x, y + 1, "    ", COLOR_WHITE, COLOR_WHITE);
		cct_showch(x + 1, y + 1, stuff, COLOR_WHITE, stuff - '0');
		break;
	}
}

void graph_endMsg(MineField* field, const char* str)
{
	int w, h;
	FieldSize(field, w, h);
	cct_showstr(0, 3 * h + 7, str);
	cct_gotoxy(6 * w + 5, 3 * h + 7);
}


void graph_mousePos(MineField* field, int x, int y)
{
	int w, h;
	FieldSize(field, w, h);

	char str[32];

	if (x == -1 || y == -1) 
	{
		strcpy_s(str, 32, "【非法位置】");
	}
	else
	{
		char sx = x < 9 ? x + '1' : x - 9 + 'a';
		char sy = y + 'A';
		sprintf_s(str, 32, "【光标位置】：%c行 %c列", sy, sx);
	}

	char* spaceFill = new char[(6 * w + 6) / 2];
	memset(spaceFill, ' ', (6 * w + 6) / 2 * sizeof(char));
	spaceFill[(6 * w + 6) / 2 - 1] = 0;
	memcpy(spaceFill, str, strlen(str));
	cct_showstr(0, 3 * h + 4, spaceFill);

	delete[] spaceFill;
}

void graph_endTime(MineField* field, uint64_t endTime)
{
	int w, h;
	FieldSize(field, w, h);

	char timeStr[32];
	sprintf_s(timeStr, 32, "本次用时：%.3f秒", (int)endTime / 1000.0f);

	cct_showstr(0, 3 * h + 5, timeStr);

	cct_gotoxy(6 * w + 5, 3 * h + 7);
}

void graph_tipMsg(MineField* field, const char *tipStr)
{
	int w, h;
	FieldSize(field, w, h);

	cct_showstr(6 * w + 5 - strlen(tipStr), 3 * h + 5, tipStr);
}

void graph_currentTime(MineField* field, uint64_t msTime)
{
	int w, h;
	FieldSize(field, w, h);
	
	char timeStr[32];
	sprintf_s(timeStr, 32, "当前时间：%.3f秒", (int)msTime / 1000.0f);

	char* spaceFill = new char[(6 * w + 6) / 2 - 1];
	memset(spaceFill, ' ', (6 * w + 6) / 2 * sizeof(char) - 1);
	spaceFill[(6 * w + 6) / 2 - 2] = 0;
	memcpy(spaceFill, timeStr, strlen(timeStr));
	cct_showstr(6 * w + 5 - strlen(timeStr), 0, spaceFill);

	delete[] spaceFill;
}

void graph_remainMines(MineField* field, int remainCount)
{
	int w, h;
	FieldSize(field, w, h);

	char remainMineStr[32];
	sprintf_s(remainMineStr, 32, "剩余地雷：%d", remainCount);

	char* spaceFill = new char[(6 * w + 6) / 2];
	memset(spaceFill, ' ', (6 * w + 6) / 2 * sizeof(char));
	spaceFill[(6 * w + 6) / 2 - 1] = 0;
	memcpy(spaceFill, remainMineStr, strlen(remainMineStr));
	cct_showstr(0, 0, spaceFill, 0, COLOR_HYELLOW);

	delete[] spaceFill;
}

void graph_result(MineField* field, const char* resultStr)
{
	int w, h;
	FieldSize(field, w, h);

	char* spaceFill = new char[(6 * w + 6) / 2];
	memset(spaceFill, ' ', (6 * w + 6) / 2 * sizeof(char));
	spaceFill[(6 * w + 6) / 2 - 1] = 0;
	memcpy(spaceFill, resultStr, strlen(resultStr));
	cct_showstr(0, 3 * h + 4, spaceFill);
}

void strView_init(MineField* field)
{
	int w, h;
	FieldSize(field, w, h);

	cct_cls();

	// 显示列编号
	cct_showstr(0, 1, "  |");
	char colCh = '1';
	int col = 3;
	for (int x = 0; x < w; ++x)
	{
		cct_showch(col, 1, colCh);
		cct_showch(col + 1, 1, ' ');
		col += 2;
		++colCh;
		if (colCh == ':')
			colCh = 'a';
	}

	// 分割线
	cct_showstr(0, 2, "--+");
	for (int x = 0; x < (w + 1) * 2; ++x)
	{
		cct_showstr(x + 3, 2, "-");
	}

	char rowCh = 'A';
	for (int y = 0; y < h; ++y)
	{
		// 行编号
		cct_showch(0, 3 + y, rowCh++);
		cct_showstr(1, 3 + y, " |");

		col = 3;
		for (int x = 0; x < w; ++x)
		{
			cct_showch(col, 3 + y, 'X');
			cct_showch(col + 1, 3 + y, ' ');
			col += 2;
		}
	}
}

void strView_updateGrid_1(MineField* field, int x, int y, char stuff)
{
	x = 3 + x * 2;
	y = 3 + y;

	int curX, curY;
	cct_getxy(curX, curY);

	cct_showch(x, y, stuff);

	cct_gotoxy(curX, curY);
}

void strView_updateGrid_2(MineField* field, int x, int y, char stuff)
{
	x = 3 + x * 2;
	y = 3 + y;

	int curX, curY;
	cct_getxy(curX, curY);

	switch (stuff)
	{
	case '*':
		cct_showch(x, y, '*', COLOR_HYELLOW, COLOR_BLACK);
		break;

	case '!':
		cct_showch(x, y, '!', COLOR_HRED, COLOR_BLACK);
		break;

	case '?':
		cct_showch(x, y, '?');
		break;

	case ' ':
		cct_showch(x, y, 'X');
		break;

	case '0':
		cct_showch(x, y, '0', COLOR_HYELLOW, COLOR_BLACK);
		break;

	default:
		cct_showch(x, y, stuff, COLOR_HYELLOW, stuff - '0');
		break;
	}

	cct_gotoxy(curX, curY);
}
