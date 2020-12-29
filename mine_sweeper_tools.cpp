#include "cmd_console_tools.h"
#include "mine_sweeper.h"

void getPosFromKey(unsigned w, unsigned h, unsigned& x, unsigned& y)
{
	int mx, my, ma, k1 = 0x7FFFFFFF, k2;
	int yPos;

	while (k1 < 'A' || k1 >= 'A' + h) 
	{
		cct_read_keyboard_and_mouse(mx, my, ma, k1, k2);
	}
	
	y = k1 - 'A';

	cct_getxy(mx, my);
	cct_showch(mx, my, k1);

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
				return;
			}
			else if (k1 <= 'a' + w - 9 && k1 >= 'a')
			{
				x = k1 - 'a' + 9;
				cct_getxy(mx, my);
				cct_showch(mx, my, k1);
				return;
			}
		}
		else
		{
			if (k1 >= '1' && k1 <= '9')
			{
				x = k1 - '1';
				cct_getxy(mx, my);
				cct_showch(mx, my, k1);
				return;
			}
		}
	}

	x = y = 0;
}