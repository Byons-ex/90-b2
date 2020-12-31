#pragma once
#include <stdlib.h>
#include <inttypes.h>

typedef struct MineField_ MineField;

int showMainMenu();
void showLevelMenu(int& w, int &h, int& mineCount);

MineField* initMineField(int w, int h, int mineCount);
void uninitMineField(MineField* field);
void FieldSize(MineField* field, int& w, int& h);
char grid(MineField* field, int x, int y);
char internalGrid(MineField* field, int x, int y);
int clear(MineField* field, int x, int y);
typedef void(*CLEAR_CALLBACK)(MineField*, int, int, char);
int clear(MineField* field, int x, int y, CLEAR_CALLBACK callback);
void setStatus(MineField* field, int x, int y, char status);

void launchMode_1(int w, int h, int mineCount);
void paintMode_1(MineField* field);

void paintFieldWithStr(MineField* field, const char* head[], int headCount, const char* rear[], int rearCount);

void launchMode_2(int w, int h, int mineCount);
void launchMode_3(int w, int h, int mineCount);
void launchMode_4(int w, int h, int mineCount);
void launchMode_5(int w, int h, int mineCount);
void launchMode_6(int w, int h, int mineCount);
void launchMode_7(int w, int h, int mineCount);

void InitGraph(MineField *field);
void updateGraphGrid(MineField *field, int x, int y, char stuff);
void showMsgWitGraph(MineField* field, const char *str);
void showMosePosWithGraph(MineField *field, const char *str);

int waitKeyDown(int w, int h, char&flag, int& x, int& y);
char* mousePosToFieldPos(int mx, int my, int fw, int fh, int& fx, int& fy);

void waitPressEnter();

char* timeToSecString(uint64_t ms);