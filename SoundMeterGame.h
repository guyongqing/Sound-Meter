#pragma once

// MZFC
#include "mzfc_inc.h"

// Shell 头文件
// #include <ShellNotifyMsg.h>


// 绘图处理
#include "SoundMeterDraw.h"

// 录音处理
#include "SoundMeterRecorder.h"

// 游戏状态
#define GAME_STATUS_START		0			// 开始
#define GAME_STATUS_LOADING		1			// 资料读取中
#define GAME_STATUS_RUN			2			// 运行

// 错误提示
#define GAME_ERROR				L"程序错误！"
#define GAME_ERROR_INIT			L"程序初始化错误！"
#define GAME_ERROR_FILE			L"资料读取错误！"
#define GAME_ERROR_COPY			L"授权文件校验失败，请重新下载安装！"
#define GAME_ERROR_FREE			L"您当前使用的是试用版本！"

//************************************************************************************************
//*************************** 游 戏 控 制 ********************************************************
//************************************************************************************************

// 游戏初始化
bool GameInit(HWND);
// 初始化游戏数据
void GameDataInit(void);
// 游戏开始
void GameRun(void);
// 游戏结束
void GameEnd(void);
// 激活游戏
void GameLive(void);
// 停止游戏
void GameDead(void);
// 暂停游戏
void GamePause(void);
// 继续游戏
void GameContinue(void);
// 游戏错误
void GameError(LPTSTR);
// 设置游戏状态
void GameStatus(int);

// 是否激活
bool GameIsLive(void);
// 取得当前游戏状态
int GameGetStatus(void);

