#pragma once
#include <stdlib.h>
#include <inttypes.h>

typedef struct MineField_ MineField;


//---------------------------------------------------------------------------------
//----菜单相关
//----定义实现于mine_sweeper_menu.cpp

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

//------------------------------------------------------------------------------------
//----游戏逻辑相关
//----定义实现于mine_sweeper_base.cpp

/// <summary>
/// 初始化雷区，如果不需要的了，请使用uninitMineField释放相关资源
/// </summary>
/// <param name="w"></param>
/// <param name="h"></param>
/// <param name="mineCount"></param>
/// <returns>返回初始化成功的雷区</returns>
MineField* initMineField(int w, int h, int mineCount);

/// <summary>
/// 释放雷区所用的相关资源，调用该函数后将导致field指针无效，你可以安全的将指针置NULL
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

/// <summary>
/// clear函数使用的回调原型
/// </summary>
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
//----各模式的入口
//----定义实现于mine_sweeper_main.cpp

/// <summary>
/// main函数存储启动模式的函数原型
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
//----以下函数都使用field参数用于定位输出位置
//----定义实现于mine_sweeper_graph.cpp

/// <summary>
/// 根据field参数初始化伪图形界面
/// </summary>
/// <param name="field"></param>
void graph_init(MineField *field);

/// <summary>
/// 更新某个位置上的状态
/// </summary>
/// <param name="field"></param>
/// <param name="x"></param>
/// <param name="y"></param>
/// <param name="stuff">该位置上的东西，可能的值：参见grid函数的返回值</param>
void graph_updateGrid(MineField *field, int x, int y, char stuff);

/// <summary>
/// 在界面尾部显示一个消息
/// </summary>
/// <param name="field"></param>
/// <param name="str"></param>
void graph_endMsg(MineField *field, const char *str);

/// <summary>
/// 将鼠标指针的xy位置显示到伪图形界面
/// </summary>
/// <param name="field"></param>
/// <param name="x"></param>
/// <param name="y"></param>
void graph_mousePos(MineField *field, int x, int y);

/// <summary>
/// 显示结束时间
/// </summary>
/// <param name="field"></param>
/// <param name="endTime">这应该是一个自graph_init至此的毫秒数</param>
void graph_endTime(MineField* field, uint64_t endTime);

/// <summary>
/// 显示提示信息
/// </summary>
/// <param name="field"></param>
/// <param name="tipStr"></param>
void graph_tipMsg(MineField *field, const char *tipStr);

/// <summary>
/// 显示当前时间
/// </summary>
/// <param name="field"></param>
/// <param name="msTime">这应该是一个自graph_init至此的毫秒数</param>
void graph_currentTime(MineField *field, uint64_t msTime);

/// <summary>
/// 显示剩余地雷数
/// </summary>
/// <param name="field"></param>
/// <param name="remainCount"></param>
void graph_remainMines(MineField* field, int remainCount);

/// <summary>
/// 显示游戏结果
/// </summary>
/// <param name="field"></param>
/// <param name="resultStr"></param>
void graph_result(MineField* field, const char* resultStr);

//--------------------------------------------------------------------------------------
//----字符界面相关函数
//----以下函数可能需要field参数用于定位输出位置
//----定义实现于mine_sweeper_graph.cpp

/// <summary>
/// 根据field参数初始化图形界面
/// </summary>
/// <param name="field"></param>
void strView_init(MineField* field);

/// <summary>
/// 更新某个位置上的状态，这个版本使用默认字体背景颜色和前景颜色
/// </summary>
/// <param name="field"></param>
/// <param name="x"></param>
/// <param name="y"></param>
/// <param name="stuff">该位置上的东西，可能的值：参见grid函数的返回值</param>
void strView_updateGrid_1(MineField* field, int x, int y, char stuff);

/// <summary>
/// 更新某个位置上的状态，这个版本可能会使用不同的字体背景颜色和前景颜色用于区分不用的状态
/// </summary>
/// <param name="field"></param>
/// <param name="x"></param>
/// <param name="y"></param>
/// <param name="stuff">该位置上的东西，可能的值：参见grid函数的返回值</param>
void strView_updateGrid_2(MineField* field, int x, int y, char stuff);

/// <summary>
/// 在字符界面的头部显示一个信息，该信息的长度不应该超过整个控制台窗口的长度，否则显示效果会很奇怪
/// </summary>
/// <param name="str"></param>
void strView_headMsg(const char* str);

/// <summary>
/// 在字符界面的尾部显示一个信息
/// </summary>
/// <param name="field"></param>
/// <param name="row">从字符界面尾部以0开始偏移的行数</param>
/// <param name="str"></param>
void strView_rearMsg(MineField* field, int row, const char* str);


//--------------------------------------------------------------------------------------
//----输入处理相关函数
//----定义实现于mine_sweeper_tools.cpp

/// <summary>
/// 将键盘按键转换成控制码，如果转换成功, colKey可能的值：'?', '!', '&', 'q';
/// </summary>
/// <param name="key">要转换的按键</param>
/// <param name="colKey">用于接收转换后的控制码</param>
/// <returns>转换成功返回true，否则false</returns>
bool keycodeToControlKey(int key, char& colKey);

/// <summary>
/// 将键盘按键转换成雷区的行坐标
/// </summary>
/// <param name="fh">雷区的高度</param>
/// <param name="key">要转换的按键</param>
/// <param name="row">用于接收转换后的雷区行坐标，如果失败，row的值将不会改变</param>
/// <returns>成功返回true，失败false</returns>
bool keycodeToFieldRow(int fh, int key, int& row);

/// <summary>
/// 将键盘按键转换成雷区的列坐标
/// </summary>
/// <param name="fw">雷区的宽度</param>
/// <param name="key">要转换的按键</param>
/// <param name="col">用于接收转换后的雷区列坐标，如果失败，col的值将不会改变</param>
/// <returns>成功返回true，失败false</returns>
bool keycodeToFieldCol(int fw, int key, int& col);

/// <summary>
/// 将鼠标位置转换伪雷区位置
/// </summary>
/// <param name="mx">鼠标的x位置</param>
/// <param name="my">鼠标的y位置</param>
/// <param name="fw">雷区的宽度</param>
/// <param name="fh">雷区的高度</param>
/// <param name="fx">用于接收转换成功后的雷区列坐标，否则保持原值</param>
/// <param name="fy">用于接收转换成功后的雷区行坐标，否则保持原值</param>
/// <returns>成功返回true，否则false</returns>
bool mousePosToFieldPos(int mx, int my, int fw, int fh, int& fx, int& fy);

/// <summary>
/// 等待用户按下Enter键，函数会一直阻塞至enter键按下才返回
/// </summary>
void waitPressEnter();
