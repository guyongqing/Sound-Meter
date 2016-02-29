
// 预编译
#include "stdafx.h"

// 游戏处理
#include "SoundMeterGame.h"

HWND TheGameHwnd;

// 游戏全局变量
bool TheGameLive = false;		// 游戏活动状态
bool TheGamePause = false;		// 游戏暂停状态

// 当前游戏状态
int TheGameStatus = GAME_STATUS_START;

//************************************************************************************************
//*************************** 游 戏 控 制 ********************************************************
//************************************************************************************************

// 游戏错误
void GameError(LPTSTR msg)
{

	// 游戏暂停
	GamePause();

	// 游戏结束
	GameEnd();

	// 显示错误信息
	MzMessageBox(0,msg,GAME_ERROR,MB_OK,0,false);

	// 退出程序
	PostQuitMessage(0);

}

// 游戏初始化
bool GameInit(HWND hwnd)
{

	// 窗口没有正确创建
	if(!hwnd){
		return false;
	}

	// 初始化 DirectDraw 失败
	if(!DirectDrawInit(hwnd)){
		return false;
	}

	// 窗口句柄
	TheGameHwnd = hwnd;

	// 初始化成功，进入显示标志过程
	GameStatus(GAME_STATUS_LOADING);

	// 激活游戏
	TheGameLive = true;

	// 初始化游戏数据
	GameDataInit();

	return true;

}

// 初始化游戏数据
void GameDataInit(void)
{

	LoadingImageFile(DRAW_BACKGROUND_FILE, DRAW_BACKGROUND_SIZE);

}

// 游戏开始
void GameRun(void)
{
	
	// 绘制画面
	Draw();

}

// 继续游戏
void GameContinue(void)
{

	// 暂停游戏
	TheGamePause = false;

}		

// 暂停游戏
void GamePause(void)
{

	// 暂停游戏
	TheGamePause = true;	

}

// 停止游戏
void GameDead(void)
{

	// 关闭游戏状态
	TheGameLive = false;	
	// 暂停游戏
	GamePause();	
	// 显示顶栏
	// ShowMzTopBar();
	// 停止录音
	RecorderStop();

}

// 游戏结束
void GameEnd(void)
{

	// 停止游戏
	GameDead();	
	// 结束录音
	RecorderEnd();
	// 销毁 DDraw 对象
	DirectDrawEnd();

}

// 游戏激活
void GameLive(void)
{

	// 窗口句柄
	if(TheGameHwnd){

		// 打开游戏状态
		TheGameLive = true;						
		// 隐藏顶栏
		// HideMzTopBar();
		// 开始录音
		RecorderStart();
		
	}

}

// 设置游戏状态
void GameStatus(int s)
{

	// 设置游戏状态
	TheGameStatus = s;

}

// 是否激活
bool GameIsLive(void)
{

	// 返回是否激活
	return TheGameLive;

}

// 取得当前游戏状态
int GameGetStatus(void)
{

	// 返回游戏状态
	return TheGameStatus;

}