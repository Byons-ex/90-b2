#include "cmd_console_tools.h"
#include "mine_sweeper.h"
#include <stdlib.h>
#include <time.h>
#include <memory.h>

typedef struct MineField_
{
	unsigned char *field;
	unsigned char *status;
	unsigned w, h;
	unsigned mineCount;
	unsigned safeZone;
}MineField;

void RandMines(MineField* field, unsigned reservedX, unsigned reservedY)
{
	srand((unsigned int)time(NULL));
	for (unsigned i = 0; i < field->mineCount; ++i)
	{
		int pos = rand() % (field->w * field->h - field->mineCount - 9) + field->mineCount + 9;
		field->field[i] = field->field[pos];
		field->field[pos] = '*';
	}

	unsigned reservedSection = field->mineCount;
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

void markMineAround(MineField* field, unsigned w, unsigned h)
{
	for (unsigned x = 0; x < w; ++x)
	{
		for (unsigned y = 0; y < h; ++y)
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

MineField* allocMineField(unsigned w, unsigned h)
{
	MineField* field = new MineField;
	field->field = new unsigned char[w * h];
	memset(field->field, '0', w * h * sizeof(unsigned char));

	field->status = new unsigned char[w * h]();

	field->w = w;
	field->h = h;
	field->mineCount = 0;

	return field;
}

void initMineField(MineField *field, unsigned mineCount, unsigned reservedX, unsigned reservedY)
{
	field->mineCount = mineCount;
	field->safeZone = field->w * field->h - mineCount;
	RandMines(field, reservedX, reservedY);
	markMineAround(field, field->w, field->h);
}

void FieldSize(MineField* field, unsigned& w, unsigned& h)
{
	w = field->w;
	h = field->h;
}

unsigned char grid(MineField* field, unsigned x, unsigned y)
{
	return (*(field->status + y * field->w + x)) == CLEAN ? 
		*(field->field + y * field->w + x) : (*(field->status + y * field->w + x));
}

unsigned char internalGrid(MineField* field, unsigned x, unsigned y)
{
	return *(field->field + y * field->w + x);
}

int clear(MineField* field, unsigned x, unsigned y)
{
	if (*(field->field + y * field->w + x) == '*')
	{
		*(field->status + y * field->w + x) = CLEAN;
		return -1;
	}

	if (*(field->field + y * field->w + x) > '0' && *(field->status + y * field->w + x) != CLEAN)
	{
		*(field->status + y * field->w + x) = CLEAN;
		--field->safeZone;
		if (field->safeZone == 0)
			return 1;
		return 0;
	}

	if (*(field->status + y * field->w + x) == CLEAN)
		return 0;

	*(field->status + y * field->w + x) = CLEAN;
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

void markFlag(MineField* field, unsigned x, unsigned y)
{
	if ((*(field->status + y * field->w + x)) != CLEAN)
		(*(field->status + y * field->w + x)) = FLAG;
}

void markDoubt(MineField* field, unsigned x, unsigned y)
{
	if ((*(field->status + y * field->w + x)) != CLEAN)
		(*(field->status + y * field->w + x)) = DOUBT;
}

void cleanStatus(MineField* field, unsigned x, unsigned y)
{
	if ((*(field->status + y * field->w + x)) != CLEAN)
		(*(field->status + y * field->w + x)) = UNKNOWN;
}

void freeMineField(MineField* field)
{
	delete[] field->field;
	delete[] field->status;
	delete field;
}
