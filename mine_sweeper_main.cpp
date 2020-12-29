#include "cmd_console_tools.h"
#include "mine_sweeper.h"
#include <stdlib.h>

#include <iostream>


int main(void)
{
	cct_setfontsize("Terminal", 20, 10);
	cct_disable_mouse();
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


		case 5:


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
	MineField* mineField = allocMineField(w, h);
	initMineField(mineField, mineCount, 0, 0);
	paintMode_1(mineField);

	while (true)
	{
		int mx, my, ma, k1, k2;
		cct_read_keyboard_and_mouse(mx, my, ma, k1, k2);
		if (k1 == 0x0D)
			break;
	}

	freeMineField(mineField);
}

void launchMode_2(unsigned w, unsigned h, unsigned mineCount)
{
	MineField* field = allocMineField(w, h);

	paintMode_2(field);
	
	int mx, my;
	cct_getxy(mx, my);
	cct_showstr(0, my + 2, "�������λ�õ��������꣨���к��У��ϸ����ִ�Сд������G1/Af����Q/q�˳�����");

	unsigned x, y;
	getPosFromKey(w, h, x, y);

	initMineField(field, mineCount, x, y);
	clear(field, x, y);

	paintMode_2(field);
	cct_getxy(mx, my);
	cct_showstr(0, my + 2, "���س�������...");

	while (true)
	{
		int mx, my, ma, k1, k2;
		cct_read_keyboard_and_mouse(mx, my, ma, k1, k2);
		if (k1 == 0x0D)
			break;
	}

	freeMineField(field);
}

void launchMode_3(unsigned w, unsigned h, unsigned mineCount)
{
	MineField* field = allocMineField(w, h);

	paintMode_2(field);
	int mx, my;
	cct_getxy(mx, my);
	cct_showstr(0, my + 2, "�������λ�õ��������꣨���к��У��ϸ����ִ�Сд������G1/Af����Q/q�˳�����");

	unsigned kx, ky;
	getPosFromKey(w, h, kx, ky);

	initMineField(field, mineCount, kx, ky);
	auto ret = clear(field, kx, ky);

	while (ret == 0)
	{
		paintMode_2(field);
		int mx, my;
		cct_getxy(mx, my);
		cct_showstr(0, my + 2, "�������λ�õ��������꣨���к��У��ϸ����ִ�Сд������G1/Af����Q/q�˳�����");

		unsigned kx, ky;
		getPosFromKey(w, h, kx, ky);
		ret = clear(field, kx, ky);
	}

	if (ret == -1)
	{
		paintMode_2(field);
		int mx, my;
		cct_getxy(mx, my);
		cct_showstr(0, my + 2, "���ϧ��ʧ����");
	}

	if (ret == 1)
	{
		paintMode_2(field);
		int mx, my;
		cct_getxy(mx, my);
		cct_showstr(0, my + 2, "��ϲ����ʤ����");
	}

	cct_showstr(0, my + 3, "���س����˳�...");

	while (true)
	{
		int mx, my, ma, k1, k2;
		cct_read_keyboard_and_mouse(mx, my, ma, k1, k2);
		if (k1 == 0x0D)
			break;
	}
}