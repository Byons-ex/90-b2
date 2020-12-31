#pragma once
#include <stdlib.h>
#include <inttypes.h>

typedef struct MineField_ MineField;

/// <summary>
/// 显示主菜单并等待用户输入选择
/// </summary>
/// <returns>用户的选择</returns>
int showMainMenu();

/// <summary>
/// 显示难度选择菜单并等待用户选择
/// </summary>
/// <param name="w">用于接收用户选择的难度相关的雷区宽度</param>
/// <param name="h">用于接收用户选择的难度相关的雷区高度</param>
/// <param name="mineCount">用于接收用户选择的难度相关的地雷数量</param>
void showLevelMenu(int& w, int &h, int& mineCount);

/// <summary>
/// 初始化雷区
/// </summary>
/// <param name="w"></param>
/// <param name="h"></param>
/// <param name="mineCount"></param>
/// <returns>返回初始化成功的雷区</returns>
MineField* initMineField(int w, int h, int mineCount);

/// <summary>
/// 释放雷区所用的相关资源，调用该函数后将导致field指针
/// </summary>
/// <param name="field">要释放的雷区指针</param>
void uninitMineField(MineField* field);

/// <summary>
/// 获取雷区的大小
/// </summary>
/// <param name="field">要检查的雷区</param>
/// <param name="w">雷区的宽度</param>
/// <param name="h">雷区的高度</param>
void FieldSize(MineField* field, int& w, int& h);

/// <summary>
/// 获取某个位置上的状态，如果该位置没有被挖掘，则返回该位置上的用户标记，如果该位置已经被挖掘，则返回改位置周围的地雷数量，
/// </summary>
/// <param name="field">要检索的雷区</param>
/// <param name="x">列坐标</param>
/// <param name="y">行坐标</param>
/// <returns></returns>
char grid(MineField* field, int x, int y);

/// <summary>
/// 获取某个位置上的内部状态
/// </summary>
/// <param name="field"></param>
/// <param name="x"></param>
/// <param name="y"></param>
/// <returns></returns>
char internalGrid(MineField* field, int x, int y);

typedef void(*CLEAR_CALLBACK)(MineField*, int, int, char);

/// <summary>
/// 清理某个位置，该函数会自行清理该位置周围绝对安全的位置，
/// 对于雷区的第一次清理，该位置绝对不会是地雷
/// </summary>
/// <param name="field">要清理的雷区</param>
/// <param name="x"></param>
/// <param name="y"></param>
/// <param name="callback">clear每清理一个位置时，会将该位置的状态通知到回调函数</param>
/// <returns>如果清理到地雷，返回-1，该雷区已经完全安全清理完毕（胜利），返回1，正常清理完成返回0</returns>
int clear(MineField* field, int x, int y, CLEAR_CALLBACK callback);

/// <summary>
/// 设置用户标记，只对还未挖掘的位置有效，可能的标记['!', '?', ' ']
/// </summary>
/// <param name="field"></param>
/// <param name="x"></param>
/// <param name="y"></param>
/// <param name="status">要设置的标记</param>
void setFlag(MineField* field, int x, int y, char status);

//--------------------------------------------------------------------------------------
/// <summary>
/// 各模式的入口
/// </summary>
typedef void(*LAUNCH_MODE)(int, int , int);
void launchMode_1(int w, int h, int mineCount);
void launchMode_2(int w, int h, int mineCount);
void launchMode_3(int w, int h, int mineCount);
void launchMode_4(int w, int h, int mineCount);
void launchMode_5(int w, int h, int mineCount);
void launchMode_6(int w, int h, int mineCount);
void launchMode_7(int w, int h, int mineCount);
void launchMode_8(int w, int h, int mineCount);
void launchMode_9(int w, int h, int mineCount);

//--------------------------------------------------------------------------------------
//----伪图形界面相关函数

void initGraph(MineField *field);
void updateGraphGrid(MineField *field, int x, int y, char stuff);
void showEndMsgWithGraph(MineField *field, const char *str);
void showMosePosWithGraph(MineField *field, int x, int y);
void showEndTimeWithGraph(MineField* field, uint64_t endTime);
void showTipMsgWithGraph(MineField *field, const char *tipStr);
void showCurrTimeWithGraph(MineField *field, uint64_t msTime);
void showRemianMineWithGraph(MineField* field, int remainCount);
void showResultWithGraph(MineField* field, const char* resultStr);

//--------------------------------------------------------------------------------------
//----字符界面相关函数
void initStrView(MineField* field);
void updateStrViewGrid_1(MineField* field, int x, int y, char stuff);
void updateStrViewGrid_2(MineField* field, int x, int y, char stuff);
void showHeadMsgWithStrView(const char* str);
void showRearMsgWithStrView(MineField* field, int row, const char* str);


//--------------------------------------------------------------------------------------
//----输入处理相关函数
bool keycodeToControlKey(int key, char& colKey);
bool keycodeToFieldRow(int fh, int key, int& row);
bool keycodeToFieldCol(int fw, int key, int& col);

bool mousePosToFieldPos(int mx, int my, int fw, int fh, int& fx, int& fy);

void waitPressEnter();
