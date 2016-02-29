#pragma once

// MZFC
#include "mzfc_inc.h"

// Shell ͷ�ļ�
// #include <ShellNotifyMsg.h>


// ��ͼ����
#include "SoundMeterDraw.h"

// ¼������
#include "SoundMeterRecorder.h"

// ��Ϸ״̬
#define GAME_STATUS_START		0			// ��ʼ
#define GAME_STATUS_LOADING		1			// ���϶�ȡ��
#define GAME_STATUS_RUN			2			// ����

// ������ʾ
#define GAME_ERROR				L"�������"
#define GAME_ERROR_INIT			L"�����ʼ������"
#define GAME_ERROR_FILE			L"���϶�ȡ����"
#define GAME_ERROR_COPY			L"��Ȩ�ļ�У��ʧ�ܣ����������ذ�װ��"
#define GAME_ERROR_FREE			L"����ǰʹ�õ������ð汾��"

//************************************************************************************************
//*************************** �� Ϸ �� �� ********************************************************
//************************************************************************************************

// ��Ϸ��ʼ��
bool GameInit(HWND);
// ��ʼ����Ϸ����
void GameDataInit(void);
// ��Ϸ��ʼ
void GameRun(void);
// ��Ϸ����
void GameEnd(void);
// ������Ϸ
void GameLive(void);
// ֹͣ��Ϸ
void GameDead(void);
// ��ͣ��Ϸ
void GamePause(void);
// ������Ϸ
void GameContinue(void);
// ��Ϸ����
void GameError(LPTSTR);
// ������Ϸ״̬
void GameStatus(int);

// �Ƿ񼤻�
bool GameIsLive(void);
// ȡ�õ�ǰ��Ϸ״̬
int GameGetStatus(void);

