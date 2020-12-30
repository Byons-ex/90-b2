#pragma once
#include <stdlib.h>
#include <inttypes.h>

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

MineField* initMineField(unsigned w, unsigned h, unsigned mineCount);
void uninitMineField(MineField* field);
void FieldSize(MineField* field, unsigned& w, unsigned& h);
unsigned char grid(MineField* field, unsigned x, unsigned y);
unsigned char internalGrid(MineField* field, unsigned x, unsigned y);
int clear(MineField* field, unsigned x, unsigned y);
void setStatus(MineField* field, unsigned x, unsigned y, GRID_STATUS status);

void launchMode_1(unsigned w, unsigned h, unsigned mineCount);
void paintMode_1(MineField* field);

void paintFieldWithStr(MineField* field, const char* head[], int headCount, const char* rear[], int rearCount);

void launchMode_2(unsigned w, unsigned h, unsigned mineCount);
void launchMode_3(unsigned w, unsigned h, unsigned mineCount);
void launchMode_4(unsigned w, unsigned h, unsigned mineCount);
void launchMode_5(unsigned w, unsigned h, unsigned mineCount);

void InitGraph(MineField *field);
void setGraphGrid(MineField *field, unsigned x, unsigned y, char stuff);

int waitKeyDown(unsigned w, unsigned h, GRID_STATUS &flag, unsigned& x, unsigned& y);

void waitPressEnter();

char* timeToSecString(uint64_t ms);