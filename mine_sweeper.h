#pragma once

typedef struct MineField_ MineField;

enum GRID_STATUS
{
	UNKNOWN = 0,
	DOUBT,
	FLAG,
	CLEAN,
};


int showMainMenu();
void showLevelMenu(unsigned& w, unsigned &h, unsigned& mineCount);


MineField* allocMineField(unsigned w, unsigned h);
void initMineField(MineField* field, unsigned mineCount, unsigned reservedX, unsigned reservedY);
void freeMineField(MineField* field);
void FieldSize(MineField* field, unsigned& w, unsigned& h);
unsigned char grid(MineField* field, unsigned x, unsigned y);
unsigned char internalGrid(MineField* field, unsigned x, unsigned y);
int clear(MineField* field, unsigned x, unsigned y);
void markFlag(MineField* field, unsigned x, unsigned y);
void markDoubt(MineField* field, unsigned x, unsigned y);
void cleanStatus(MineField* field, unsigned x, unsigned y);

void launchMode_1(unsigned w, unsigned h, unsigned mineCount);
void paintMode_1(MineField* field);

void launchMode_2(unsigned w, unsigned h, unsigned mineCount);
void paintMode_2(MineField* field);

void launchMode_3(unsigned w, unsigned h, unsigned mineCount);

void getPosFromKey(unsigned w, unsigned h, unsigned& x, unsigned& y);