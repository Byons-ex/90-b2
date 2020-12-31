#include "cmd_console_tools.h"
#include "mine_sweeper.h"
#include <memory.h>
#include <string.h>

void paintMode_1(MineField* field)
{
	int w, h;
	FieldSize(field, w, h);

	cct_cls();

	cct_showstr(0, 0, "内部数组:");

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
			char grid = internalGrid(field, x, y);
			if(grid != '0')
				cct_showch(col, 3 + y, grid);
			else
				cct_showch(col, 3 + y, ' ');
			cct_showch(col + 1, 3 + y, ' ');
			col += 2;
		}
	}

	cct_showstr(0, h + 5, "按回车键继续...");
}

void paintFieldWithStr(MineField* field, const char *head[], int headCount, const char* rear[], int rearCount)
{
	int w, h;
	FieldSize(field, w, h);

	cct_cls();
	
	if (headCount > 0)
	{
		for (int y = 0; y < headCount; ++y)
			cct_showstr(0, y, head[y]);
	}

	int offsetY = headCount + 1;

	// 显示列编号
	cct_showstr(0, offsetY, "  |");
	char colCh = '1';
	int col = 3;
	for (int x = 0; x < w; ++x)
	{
		cct_showch(col, offsetY, colCh);
		cct_showch(col + 1, offsetY, ' ');
		col += 2;
		++colCh;
		if (colCh == ':')
			colCh = 'a';
	}

	++offsetY;

	// 分割线
	cct_showstr(0, offsetY, "--+");
	for (int x = 0; x < (w + 1) * 2; ++x)
	{
		cct_showstr(x + 3, offsetY, "-");
	}

	++offsetY;

	char rowCh = 'A';
	for (int y = 0; y < h; ++y)
	{
		// 行编号
		cct_showch(0, offsetY + y, rowCh++);
		cct_showstr(1, offsetY + y, " |");

		col = 3;
		for (int x = 0; x < w; ++x)
		{
			char ch = grid(field, x, y);
			switch (ch)
			{
			case '0':
				cct_showch(col, offsetY + y, ' ', COLOR_HYELLOW, ch - '0');
				cct_showch(col + 1, offsetY + y, ' ', COLOR_HYELLOW, COLOR_HYELLOW);
				break;

			case '*':
				cct_showch(col, offsetY + y, ch, COLOR_HYELLOW, COLOR_BLACK);
				cct_showch(col + 1, offsetY + y, ' ', COLOR_HYELLOW, COLOR_HYELLOW);
				break;

			case '?':
				cct_showch(col, offsetY + y, '?', COLOR_HYELLOW, COLOR_BLACK);
				cct_showch(col + 1, offsetY + y, ' ', COLOR_HYELLOW, COLOR_HYELLOW);
				break;

			case '!':
				cct_showch(col, offsetY + y, 'X', COLOR_RED, COLOR_BLACK);
				cct_showch(col + 1, offsetY + y, ' ', COLOR_RED, COLOR_RED);
				break;

			case ' ':
				cct_showch(col, offsetY + y, 'X');
				cct_showch(col + 1, offsetY + y, ' ');
				break;

			default:
				cct_showch(col, offsetY + y, ch, COLOR_HYELLOW, ch - '0');
				cct_showch(col + 1, offsetY + y, ' ', COLOR_HYELLOW, COLOR_HYELLOW);
				break;
			}

			col += 2;
		}
	}

	if (rearCount > 0)
	{
		offsetY += h + 2;
		for (int y = 0; y < rearCount; ++y)
		{
			cct_showstr(0, y + offsetY, rear[y]);
		}
	}
}


void InitGraph(MineField* field)
{
	int w, h;
	FieldSize(field, w, h);
	cct_setconsoleborder(6 * w + 6, 3 * h + 7);

	// 画行标题
	int y = 0;
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
		cct_showch(x, 1, title);
		++title;

		if (title == ':')
			title = 'a';
	}

	// 画═
	x = y = 2;
	for (int i = 0; i < w * 3 + 1; ++i)
	{
		y = 2;
		for (int j = 0; j < h + 1; ++j)
		{
			cct_showstr(x, y, "═", COLOR_HWHITE, COLOR_BLACK);
			y += 3;
		}
		x += 2;
	}

	// 画║
	x = y = 2;
	for (int i = 0; i < w + 1; ++i)
	{
		y = 2;
		for (int j = 0; j < h * 3 + 1; ++j)
		{
			cct_showstr(x, y, "║", COLOR_HWHITE, COLOR_BLACK);
			y += 1;
		}
		x += 6;
	}

	// 画四个角
	cct_showstr(2, 2, "╔", COLOR_HWHITE, COLOR_BLACK);
	cct_showstr(2, 2 + 3 * h, "╚", COLOR_HWHITE, COLOR_BLACK);
	cct_showstr(2 + w * 6, 2, "╗", COLOR_HWHITE, COLOR_BLACK);
	cct_showstr(2 + w * 6, 2 + 3 * h, "╝", COLOR_HWHITE, COLOR_BLACK);

	// 画╠.╣
	y = 2;
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
		cct_showstr(x, 2, "╦", COLOR_HWHITE, COLOR_BLACK);
		cct_showstr(x, 2 + h * 3, "╩", COLOR_HWHITE, COLOR_BLACK);
	}

	// 画╬
	x = y = 2;
	for (int i = 0; i < w - 1; ++i)
	{
		x += 6;
		y = 2;
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
			updateGraphGrid(field, x, y, ' ');
		}
	}

	cct_gotoxy(6 * w + 5, 3 * h + 6);
}

void updateGraphGrid(MineField* field, int x, int y, char stuff)
{
	int w, h;
	FieldSize(field, w, h);

	x = 4 + (x * 6);
	y = 3 + (y * 3);

	switch (stuff)
	{
	case '*':
		cct_showstr(x, y, "    ", COLOR_WHITE, COLOR_WHITE);
		cct_showstr(x, y + 1, "    ", COLOR_WHITE, COLOR_WHITE);
		cct_showch(x + 1, y + 1, stuff, COLOR_WHITE, COLOR_BLACK);
		break;

	case '!':
		cct_showstr(x, y, "    ", COLOR_YELLOW, COLOR_YELLOW);
		cct_showstr(x, y + 1, "    ", COLOR_YELLOW, COLOR_YELLOW);
		cct_showch(x + 1, y + 1, stuff, COLOR_YELLOW, COLOR_RED);
		break;

	case '?':
		cct_showstr(x, y, "    ", COLOR_YELLOW, COLOR_YELLOW);
		cct_showstr(x, y + 1, "    ", COLOR_YELLOW, COLOR_YELLOW);
		cct_showch(x + 1, y + 1, stuff, COLOR_YELLOW, COLOR_BLACK);
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

	cct_gotoxy(6 * w + 5, 3 * h + 6);
}

void showMsgWitGraph(MineField* field, const char* str)
{
	int w, h;
	FieldSize(field, w, h);
	cct_showstr(0, 3 * h + 6, str);
	cct_gotoxy(6 * w + 5, 3 * h + 6);
}


void showMosePosWithGraph(MineField* field, const char* str)
{
	int w, h;
	FieldSize(field, w, h);

	char* spaceFill = new char[6 * w + 6];
	memset(spaceFill, ' ', (6 * w + 6) * sizeof(char));
	spaceFill[6 * w + 5] = 0;
	memcpy(spaceFill, str, strlen(str));
	cct_showstr(0, 3 * h + 3, spaceFill);

	delete[] spaceFill;

	cct_gotoxy(6 * w + 5, 3 * h + 6);
}