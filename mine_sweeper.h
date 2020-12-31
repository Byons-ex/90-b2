#pragma once
#include <stdlib.h>
#include <inttypes.h>

typedef struct MineField_ MineField;

/// <summary>
/// ��ʾ���˵����ȴ��û�����ѡ��
/// </summary>
/// <returns>�û���ѡ��</returns>
int showMainMenu();

/// <summary>
/// ��ʾ�Ѷ�ѡ��˵����ȴ��û�ѡ��
/// </summary>
/// <param name="w">���ڽ����û�ѡ����Ѷ���ص��������</param>
/// <param name="h">���ڽ����û�ѡ����Ѷ���ص������߶�</param>
/// <param name="mineCount">���ڽ����û�ѡ����Ѷ���صĵ�������</param>
void showLevelMenu(int& w, int &h, int& mineCount);

/// <summary>
/// ��ʼ������
/// </summary>
/// <param name="w"></param>
/// <param name="h"></param>
/// <param name="mineCount"></param>
/// <returns>���س�ʼ���ɹ�������</returns>
MineField* initMineField(int w, int h, int mineCount);

/// <summary>
/// �ͷ��������õ������Դ�����øú����󽫵���fieldָ��
/// </summary>
/// <param name="field">Ҫ�ͷŵ�����ָ��</param>
void uninitMineField(MineField* field);

/// <summary>
/// ��ȡ�����Ĵ�С
/// </summary>
/// <param name="field">Ҫ��������</param>
/// <param name="w">�����Ŀ��</param>
/// <param name="h">�����ĸ߶�</param>
void FieldSize(MineField* field, int& w, int& h);

/// <summary>
/// ��ȡĳ��λ���ϵ�״̬�������λ��û�б��ھ��򷵻ظ�λ���ϵ��û���ǣ������λ���Ѿ����ھ��򷵻ظ�λ����Χ�ĵ���������
/// </summary>
/// <param name="field">Ҫ����������</param>
/// <param name="x">������</param>
/// <param name="y">������</param>
/// <returns></returns>
char grid(MineField* field, int x, int y);

/// <summary>
/// ��ȡĳ��λ���ϵ��ڲ�״̬
/// </summary>
/// <param name="field"></param>
/// <param name="x"></param>
/// <param name="y"></param>
/// <returns></returns>
char internalGrid(MineField* field, int x, int y);

typedef void(*CLEAR_CALLBACK)(MineField*, int, int, char);

/// <summary>
/// ����ĳ��λ�ã��ú��������������λ����Χ���԰�ȫ��λ�ã�
/// ���������ĵ�һ��������λ�þ��Բ����ǵ���
/// </summary>
/// <param name="field">Ҫ���������</param>
/// <param name="x"></param>
/// <param name="y"></param>
/// <param name="callback">clearÿ����һ��λ��ʱ���Ὣ��λ�õ�״̬֪ͨ���ص�����</param>
/// <returns>����������ף�����-1���������Ѿ���ȫ��ȫ������ϣ�ʤ����������1������������ɷ���0</returns>
int clear(MineField* field, int x, int y, CLEAR_CALLBACK callback);

/// <summary>
/// �����û���ǣ�ֻ�Ի�δ�ھ��λ����Ч�����ܵı��['!', '?', ' ']
/// </summary>
/// <param name="field"></param>
/// <param name="x"></param>
/// <param name="y"></param>
/// <param name="status">Ҫ���õı��</param>
void setFlag(MineField* field, int x, int y, char status);

//--------------------------------------------------------------------------------------
/// <summary>
/// ��ģʽ�����
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
//----αͼ�ν�����غ���

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
//----�ַ�������غ���
void initStrView(MineField* field);
void updateStrViewGrid_1(MineField* field, int x, int y, char stuff);
void updateStrViewGrid_2(MineField* field, int x, int y, char stuff);
void showHeadMsgWithStrView(const char* str);
void showRearMsgWithStrView(MineField* field, int row, const char* str);


//--------------------------------------------------------------------------------------
//----���봦����غ���
bool keycodeToControlKey(int key, char& colKey);
bool keycodeToFieldRow(int fh, int key, int& row);
bool keycodeToFieldCol(int fw, int key, int& col);

bool mousePosToFieldPos(int mx, int my, int fw, int fh, int& fx, int& fy);

void waitPressEnter();
