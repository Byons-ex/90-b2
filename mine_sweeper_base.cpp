#include "cmd_console_tools.h"
#include "mine_sweeper.h"
#include <stdlib.h>
#include <time.h>
#include <memory.h>

typedef struct MineField_
{
	char *field;
	char *status;
	int w, h;
	int mineCount;
	int safeZone;
	bool inited;
}MineField;

void RandMines(MineField* field, int reservedX, int reservedY)
{
	srand((unsigned int)time(NULL));
	for (int i = 0; i < field->mineCount; ++i)
	{
		int pos = rand() % (field->w * field->h - field->mineCount - 9) + field->mineCount + 9;
		field->field[i] = field->field[pos];
		field->field[pos] = '*';
	}

	int reservedSection = field->mineCount;
	for (int x = -1; x <= 1; ++x)
	{
		for (int y = -1; y <= 1; ++y)
		{
			if (reservedX + x >= 0 && reservedX + x < field->w &&
				reservedY + y >= 0 && reservedY + y < field->h)
			{
				field->field[reservedSection] = *(field->field + (reservedY + y) * field->w + (reservedX + x));
				*(field->field + (reservedY + y) * field->w + (reservedX + x)) = '0';
				++reservedSection;
			}
		}
	}
}

void markMineAround(MineField* field, int w, int h)
{
	for (int x = 0; x < w; ++x)
	{
		for (int y = 0; y < h; ++y)
		{
			if (*(field->field + y * w + x) != '*')
				continue;

			for (int offX = -1; offX <= 1; ++offX)
			{
				for (int offY = -1; offY <= 1; ++offY)
				{
					if (offX == 0 && offY == 0)
						continue;

					if (x + offX >= 0 && x + offX < field->w && y + offY >= 0 && y + offY < field->h)
						if (*(field->field + (y + offY) * w + (x + offX)) != '*')
							++(*(field->field + (y + offY) * w + (x + offX)));
				}
			}
		}
	}
}

MineField* initMineField(int w, int h, int mineCount)
{
	MineField* field = new MineField;
	field->field = new char[w * h];
	memset(field->field, '0', w * h * sizeof(char));

	field->status = new char[w * h]();

	field->w = w;
	field->h = h;
	field->mineCount = mineCount;
	field->inited = false;
	field->safeZone = w * h - mineCount;

	return field;
}

void FieldSize(MineField* field, int& w, int& h)
{
	w = field->w;
	h = field->h;
}

char grid(MineField* field, int x, int y)
{
	return (*(field->status + y * field->w + x)) == 0 ? 
		*(field->field + y * field->w + x) : (*(field->status + y * field->w + x));
}

char internalGrid(MineField* field, int x, int y)
{
	return *(field->field + y * field->w + x);
}

int clear(MineField* field, int x, int y)
{
	if (field->inited == false)
	{
		RandMines(field, x, y);
		markMineAround(field, field->w, field->h);
		field->inited = true;
	}

	if (*(field->field + y * field->w + x) == '*')
	{
		*(field->status + y * field->w + x) = ' ';
		return -1;
	}

	if (*(field->field + y * field->w + x) > '0' && *(field->status + y * field->w + x) != ' ')
	{
		*(field->status + y * field->w + x) = ' ';
		--field->safeZone;
		if (field->safeZone == 0)
			return 1;
		return 0;
	}

	if (*(field->status + y * field->w + x) == ' ')
		return 0;

	*(field->status + y * field->w + x) = ' ';
	--field->safeZone;
	if (field->safeZone == 0)
		return 1;

	for (int offX = -1; offX <= 1; ++offX)
	{
		for (int offY = -1; offY <= 1; ++offY)
		{
			if (x + offX >= 0 && x + offX < field->w &&
				y + offY >= 0 && y + offY < field->h)
			{
				if (clear(field, x + offX, y + offY) == 1)
					return 1;
			}
		}
	}

	return 0;
}

int clear(MineField* field, int x, int y, CLEAR_CALLBACK callback)
{
	if (field->inited == false)
	{
		RandMines(field, x, y);
		markMineAround(field, field->w, field->h);
		field->inited = true;
	}

	if (*(field->field + y * field->w + x) == '*')
	{
		*(field->status + y * field->w + x) = 0;
		callback(field, x, y, *(field->field + y * field->w + x));
		return -1;
	}

	if (*(field->field + y * field->w + x) > '0' && *(field->status + y * field->w + x) != ' ')
	{
		*(field->status + y * field->w + x) = 0;
		callback(field, x, y, *(field->field + y * field->w + x));
		--field->safeZone;
		if (field->safeZone == 0)
			return 1;
		return 0;
	}

	if (*(field->status + y * field->w + x) == ' ')
		return 0;

	*(field->status + y * field->w + x) = 0;
	callback(field, x, y, *(field->field + y * field->w + x));
	--field->safeZone;
	if (field->safeZone == 0)
		return 1;

	for (int offX = -1; offX <= 1; ++offX)
	{
		for (int offY = -1; offY <= 1; ++offY)
		{
			if (x + offX >= 0 && x + offX < field->w &&
				y + offY >= 0 && y + offY < field->h)
			{
				if (clear(field, x + offX, y + offY) == 1)
					return 1;
			}
		}
	}

	return 0;
}

void setStatus(MineField* field, int x, int y, char status)
{
	if ((*(field->status + y * field->w + x)) != ' ' && status != ' ')
		(*(field->status + y * field->w + x)) = status;
}

void uninitMineField(MineField* field)
{
	delete[] field->field;
	delete[] field->status;
	delete field;
}
