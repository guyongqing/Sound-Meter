#pragma once

// DirectDraw
#include <ddraw.h>

// ��Ļ����
#define	DRAW_SCREEN_WIDTH			480			// ��Ļ���
#define	DRAW_SCREEN_HEIGHT			720			// ��Ļ�߶�
#define DRAW_SCREEN_COLOR			16			// 16 λɫ
#define DRAW_SCREEN_SIZE			345600		// ��Ļռ���ֽ���

// ������ɫ
#define DRAW_COLOR_BLACK			0					// ��ɫ
#define DRAW_COLOR_WHITE			0xFFFF				// ��ɫ
#define DRAW_COLOR_GREEN			0x07E0				// ��ɫ
#define DRAW_COLOR_BLUE				0x001F				// ��ɫ
#define DRAW_COLOR_RED				0xF800				// ��ɫ


// �����Ƿ�͸��
#define DRAW_BLT_NORMAL				0				// �������
#define DRAW_BLT_COLORKEY			DDBLT_KEYSRC	// ͸�����

// ��͸������
#define DRAW_ALPHA_MIN				0				// ��С��͸��ɫ
#define DRAW_ALPHA_MID				128				// 50% ��͸��ɫ
#define DRAW_ALPHA_MAX				255				// ����͸��ɫ

// ͼ�񻺳�
#define DRAW_BACKGROUND_WIDTH		480				// �������
#define DRAW_BACKGROUND_HEIGHT		720				// �����߶�
#define DRAW_BACKGROUND_SIZE		691200			// ������С
#define DRAW_BACKGROUND_FILE		L"10611824.dat"

#define DRAW_FOREGROUND_WIDTH		1				// ǰ�����
#define DRAW_FOREGROUND_HEIGHT		1				// ǰ���߶�
#define DRAW_FOREGROUND_SIZE		4				// ǰ����С
#define DRAW_FOREGROUND_FILE		L"10611825.dat"

// ������ʾ����
#define DRAW_WAVE_MIN				-32767			// ��Сֵ
#define DRAW_WAVE_MIDDLE			0				// �м�ֵ
#define DRAW_WAVE_MAX				32767			// ���ֵ
#define DRAW_WAVE_STEP				15				// ��������
#define DRAW_WAVE_STEP_MIN			5				// ����������Сֵ
#define DRAW_WAVE_STEP_MAX			35				// �����������ֵ
#define	DRAW_WAVE_DB_MIN			0				// �ֱ���Сֵ
#define	DRAW_WAVE_DB_MID			48				// �ֱ��м�ֵ
#define	DRAW_WAVE_DB_MAX			96.3			// �ֱ����ֵ
#define DRAW_WAVE_DB_MIC			682.66			// ����˷�Ϊ��׼ʱ�Ĳο�ֵ
#define DRAW_WAVE_DB_HUMAN			227				// �˶�
#define DRAW_WAVE_LOCATION_CENTER	5				// 5��Բ��
#define DRAW_WAVE_ANGLE_START		128.5714		// ��ʼ�Ƕ�
#define DRAW_WAVE_ANGLE_END			376.1972		// ��ֹ�Ƕ�
#define DRAW_WAVE_ANGLE_SPEEN_START	231.4322		// ��ʼ�Ƕ�
#define DRAW_WAVE_ANGLE_SPEEN_END	411.4302		// ��ֹ�Ƕ�
#define DRAW_WAVE_ANGLE_PER			2.5714			// �Ƕȵ�λ

// ���ƶ���
#define DRAW_NAME_NUMBER_FIRST		0
#define DRAW_NAME_NUMBER_SECOND		1
#define DRAW_NAME_NUMBER_THIRD		2
#define DRAW_NAME_NUMBER_DOT		3
#define DRAW_NAME_NUMBER_COUNT		4

//************************************************************************************************
//*************************** DirectDraw *********************************************************
//************************************************************************************************

#define DDRAW_INIT_STRUCT(ddsd) {memset(&ddsd,0,sizeof(ddsd));ddsd.dwSize=sizeof(ddsd);}

// ��ʼ��
bool DirectDrawInit(HWND);
// ����
void DirectDrawEnd(void);
// ��������
bool DirectDrawCreateSurface(LPDIRECTDRAWSURFACE*, int, int);

//************************************************************************************************
//*************************** ������� ***********************************************************
//************************************************************************************************

// ��Ϸ�������
void Draw(void);
// ���Ʊ���
void DrawBackground(void);
// ����ǰ��
void DrawForeground(void);
// ����Ļ���ڴ棩
void DrawCls(USHORT*, int, USHORT);
// ����
void DrawClsRect(void);
// ����������
void DrawPrimary(void);

/*************************** ���λ��� ****************************************/

// ���ƾ���
void DrawRect(LPDIRECTDRAWSURFACE, RECT*, RECT*, int);
// ���ٻ��ƾ��Σ���͸����
void DrawRectAlpha(LPDIRECTDRAWSURFACE, RECT*, RECT*, int);

//************************************************************************************************
//*************************** ��Ƶ���� ***********************************************************
//************************************************************************************************

// ����ͼģ�鷢������ָ��
void DrawSetWaveData(SHORT*);
// ��ָ��
void DrawWaveLine(USHORT*, int);
// ���ֱ�ָ��
void DrawWaveLineDB(USHORT*, int);
// ���ٶ�ָ��
void DrawWaveLineSpeed(USHORT*, int);
// ��������ͼ��
void DrawWaveData(void);
// ��ʾ����
void DrawWaveDataFinal(void);
// ��������
void DrawWaveDataNumbers(double, RECT*);
// ��������
void DrawWaveCalculate(void);
// �����˷�״̬
void DrawWaveSetMicStatus(void);
// �����ٶ�
void DrawWaveSetWaveStep(BYTE);

//************************************************************************************************
//*************************** �� �� �� ȡ ********************************************************
//************************************************************************************************

// ��ȡͼ���ļ�
bool LoadingImageFile(LPTSTR, int);