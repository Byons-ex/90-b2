#include "cmd_console_tools.h"
#include "mine_sweeper.h"

#include <memory.h>

int showMainMenu()
{
	int select = -1;
	int mX, mY, key2, mAction;

	cct_cls();
	cct_setcursor(CURSOR_INVISIBLE);
	cct_setconsoleborder(75, 28);

	/*
	* ��������һ����ֵ�BUG����BUG���µ�һ�ε���showMainMenuʱ������̨δ��ʾ�ַ����Ŀ�������ɻ�ɫ
	* ֻ�е�һ�ε���showMainMenuʱ�ᷢ��������һ�ε���showMainMenu����������ֱ������ֻ���ù���
	* 
	* ��mian�����У�
	*	cct_setfontsize("Terminal", 20, 10);
	* 
	* �ڱ��������У�
	*	cct_cls();
	*	cct_setcursor(CURSOR_INVISIBLE);
	*	cct_setconsoleborder(75, 28);
	* 
	* ��Ψһ�Ĳ²�ֻ����cmd.exe��ĳЩBUG
	* Ŀǰ��ֻ��ʹ������Ĵ��������������
	*/
	char fill[76];
	memset(fill, ' ', 76);
	fill[75] = '\0';
	for (int y = 0; y < 28; ++y)
		cct_showstr(0, y, fill);

	cct_showstr(0, 0, "---------------------------");
	cct_showstr(0, 1, "1.ѡ���ѶȲ���ʾ�ڲ�����");
	cct_showstr(0, 2, "2.�����ʼλ�ò���ʾ���򿪵ĳ�ʼ����");
	cct_showstr(0, 3, "3.�ڲ����������");
	cct_showstr(0, 4, "4.�ڲ����������棨��ǣ�����ʱ�䣩");
	cct_showstr(0, 5, "5.����αͼ�λ���ܲ���ʾ�ڲ�����");
	cct_showstr(0, 6, "6.������λ�úͺϷ��ԣ���������˳���");
	cct_showstr(0, 7, "7.���ѡ���ʼλ�ò���ʾ���򿪵ĳ�ʼ����");
	cct_showstr(0, 8, "8.αͼ�ν��������");
	cct_showstr(0, 9, "9.αͼ�ν���������");
	cct_showstr(0, 10, "0.�˳���Ϸ");
	cct_showstr(0, 11, "---------------------------");

	cct_showstr(0, 12, "[��ѡ��]: ");

	while (select > '9' || select < '0')
		cct_read_keyboard_and_mouse(mX, mY, mAction, select, key2);

	return select - '0';
}

void showLevelMenu(int& w, int& h, int& mineCount)
{
	int select = -1;
	int mX, mY, key2, mAction;

	cct_cls();
	cct_setcolor();

	cct_showstr(0, 0, "��ѡ���Ѷ�:");
	cct_showstr(2, 1, "1.������9*9   - 10���ף�");
	cct_showstr(2, 2, "2.������16*16 - 40���ף�");
	cct_showstr(2, 3, "3.������16*30 - 99���ף�");

	cct_showstr(0, 4, "������[1..3]:");

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
