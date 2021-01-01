#pragma once
#include <stdlib.h>
#include <inttypes.h>

typedef struct MineField_ MineField;


//---------------------------------------------------------------------------------
//----�˵����
//----����ʵ����mine_sweeper_menu.cpp

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

//------------------------------------------------------------------------------------
//----��Ϸ�߼����
//----����ʵ����mine_sweeper_base.cpp

/// <summary>
/// ��ʼ���������������Ҫ���ˣ���ʹ��uninitMineField�ͷ������Դ
/// </summary>
/// <param name="w"></param>
/// <param name="h"></param>
/// <param name="mineCount"></param>
/// <returns>���س�ʼ���ɹ�������</returns>
MineField* initMineField(int w, int h, int mineCount);

/// <summary>
/// �ͷ��������õ������Դ�����øú����󽫵���fieldָ����Ч������԰�ȫ�Ľ�ָ����NULL
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

/// <summary>
/// clear����ʹ�õĻص�ԭ��
/// </summary>
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
//----��ģʽ�����
//----����ʵ����mine_sweeper_main.cpp

/// <summary>
/// main�����洢����ģʽ�ĺ���ԭ��
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
//----���º�����ʹ��field�������ڶ�λ���λ��
//----����ʵ����mine_sweeper_graph.cpp

/// <summary>
/// ����field������ʼ��αͼ�ν���
/// </summary>
/// <param name="field"></param>
void graph_init(MineField *field);

/// <summary>
/// ����ĳ��λ���ϵ�״̬
/// </summary>
/// <param name="field"></param>
/// <param name="x"></param>
/// <param name="y"></param>
/// <param name="stuff">��λ���ϵĶ��������ܵ�ֵ���μ�grid�����ķ���ֵ</param>
void graph_updateGrid(MineField *field, int x, int y, char stuff);

/// <summary>
/// �ڽ���β����ʾһ����Ϣ
/// </summary>
/// <param name="field"></param>
/// <param name="str"></param>
void graph_endMsg(MineField *field, const char *str);

/// <summary>
/// �����ָ���xyλ����ʾ��αͼ�ν���
/// </summary>
/// <param name="field"></param>
/// <param name="x"></param>
/// <param name="y"></param>
void graph_mousePos(MineField *field, int x, int y);

/// <summary>
/// ��ʾ����ʱ��
/// </summary>
/// <param name="field"></param>
/// <param name="endTime">��Ӧ����һ����graph_init���˵ĺ�����</param>
void graph_endTime(MineField* field, uint64_t endTime);

/// <summary>
/// ��ʾ��ʾ��Ϣ
/// </summary>
/// <param name="field"></param>
/// <param name="tipStr"></param>
void graph_tipMsg(MineField *field, const char *tipStr);

/// <summary>
/// ��ʾ��ǰʱ��
/// </summary>
/// <param name="field"></param>
/// <param name="msTime">��Ӧ����һ����graph_init���˵ĺ�����</param>
void graph_currentTime(MineField *field, uint64_t msTime);

/// <summary>
/// ��ʾʣ�������
/// </summary>
/// <param name="field"></param>
/// <param name="remainCount"></param>
void graph_remainMines(MineField* field, int remainCount);

/// <summary>
/// ��ʾ��Ϸ���
/// </summary>
/// <param name="field"></param>
/// <param name="resultStr"></param>
void graph_result(MineField* field, const char* resultStr);

//--------------------------------------------------------------------------------------
//----�ַ�������غ���
//----���º���������Ҫfield�������ڶ�λ���λ��
//----����ʵ����mine_sweeper_graph.cpp

/// <summary>
/// ����field������ʼ��ͼ�ν���
/// </summary>
/// <param name="field"></param>
void strView_init(MineField* field);

/// <summary>
/// ����ĳ��λ���ϵ�״̬������汾ʹ��Ĭ�����屳����ɫ��ǰ����ɫ
/// </summary>
/// <param name="field"></param>
/// <param name="x"></param>
/// <param name="y"></param>
/// <param name="stuff">��λ���ϵĶ��������ܵ�ֵ���μ�grid�����ķ���ֵ</param>
void strView_updateGrid_1(MineField* field, int x, int y, char stuff);

/// <summary>
/// ����ĳ��λ���ϵ�״̬������汾���ܻ�ʹ�ò�ͬ�����屳����ɫ��ǰ����ɫ�������ֲ��õ�״̬
/// </summary>
/// <param name="field"></param>
/// <param name="x"></param>
/// <param name="y"></param>
/// <param name="stuff">��λ���ϵĶ��������ܵ�ֵ���μ�grid�����ķ���ֵ</param>
void strView_updateGrid_2(MineField* field, int x, int y, char stuff);

/// <summary>
/// ���ַ������ͷ����ʾһ����Ϣ������Ϣ�ĳ��Ȳ�Ӧ�ó�����������̨���ڵĳ��ȣ�������ʾЧ��������
/// </summary>
/// <param name="str"></param>
void strView_headMsg(const char* str);

/// <summary>
/// ���ַ������β����ʾһ����Ϣ
/// </summary>
/// <param name="field"></param>
/// <param name="row">���ַ�����β����0��ʼƫ�Ƶ�����</param>
/// <param name="str"></param>
void strView_rearMsg(MineField* field, int row, const char* str);


//--------------------------------------------------------------------------------------
//----���봦����غ���
//----����ʵ����mine_sweeper_tools.cpp

/// <summary>
/// �����̰���ת���ɿ����룬���ת���ɹ�, colKey���ܵ�ֵ��'?', '!', '&', 'q';
/// </summary>
/// <param name="key">Ҫת���İ���</param>
/// <param name="colKey">���ڽ���ת����Ŀ�����</param>
/// <returns>ת���ɹ�����true������false</returns>
bool keycodeToControlKey(int key, char& colKey);

/// <summary>
/// �����̰���ת����������������
/// </summary>
/// <param name="fh">�����ĸ߶�</param>
/// <param name="key">Ҫת���İ���</param>
/// <param name="row">���ڽ���ת��������������꣬���ʧ�ܣ�row��ֵ������ı�</param>
/// <returns>�ɹ�����true��ʧ��false</returns>
bool keycodeToFieldRow(int fh, int key, int& row);

/// <summary>
/// �����̰���ת����������������
/// </summary>
/// <param name="fw">�����Ŀ��</param>
/// <param name="key">Ҫת���İ���</param>
/// <param name="col">���ڽ���ת��������������꣬���ʧ�ܣ�col��ֵ������ı�</param>
/// <returns>�ɹ�����true��ʧ��false</returns>
bool keycodeToFieldCol(int fw, int key, int& col);

/// <summary>
/// �����λ��ת��α����λ��
/// </summary>
/// <param name="mx">����xλ��</param>
/// <param name="my">����yλ��</param>
/// <param name="fw">�����Ŀ��</param>
/// <param name="fh">�����ĸ߶�</param>
/// <param name="fx">���ڽ���ת���ɹ�������������꣬���򱣳�ԭֵ</param>
/// <param name="fy">���ڽ���ת���ɹ�������������꣬���򱣳�ԭֵ</param>
/// <returns>�ɹ�����true������false</returns>
bool mousePosToFieldPos(int mx, int my, int fw, int fh, int& fx, int& fy);

/// <summary>
/// �ȴ��û�����Enter����������һֱ������enter�����²ŷ���
/// </summary>
void waitPressEnter();
