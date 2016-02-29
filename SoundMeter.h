#pragma once

// GUID
#include <initguid.h>
// MZFC 头文件
#include <mzfc_inc.h>
// Shell 头文件
#include <ShellNotifyMsg.h>

// USB 事件
#include <UsbNotifyApi.h>
// 来电事件
#include <CallNotifyApi.h>

// FPS 引用文件
#include "Fps.h"

// 文件处理引用文件
#include "SoundMeterFile.h"
// 鼠标处理
#include "SoundMeterMouse.h"
// 游戏控制
#include "SoundMeterGame.h"
// 画面绘制
#include "SoundMeterDraw.h"
// 图形绘制
#include "SoundMeterPaint.h"
// 录音机
#include "SoundMeterRecorder.h"

// 程序
#define APP_MUTEX_NAME			L"SoundMeterMutex"
#define APP_WINDOW_TEXT			L"噪音检测"
#define APP_GUID				L"{9D3F7523-674D-48b6-8C76-D3DC996C58B3}"
#define APP_VERSION_MAIN		1
#define APP_VERSION_MIDDLE		0
#define APP_VERSION_LAST		0

//************************************************************************************************
//*************************** 主 窗 口 ***********************************************************
//************************************************************************************************

// 主窗口对象
class MyWindow : public CMzWndEx
{

	// MZFC窗口类及派生类的窗口类名声名宏
	MZ_DECLARE_DYNAMIC(MyWindow);

	// 公有成员
	public:

		// 构造函数
		MyWindow(void);
		// 析构函数
		~MyWindow(void);

		// 创建窗口
		bool CreateWindowNow(void);

	// 保护成员
	protected:

		// 初始化
		virtual BOOL OnInitDialog();
		// 当HOME按下时
		virtual int OnShellHomeKey(UINT, WPARAM, LPARAM);
		// 消息处理
		virtual LRESULT MzDefWndProc(UINT, WPARAM, LPARAM);
		// 鼠标双击
		virtual void OnLButtonDblClk(UINT, int, int);
		// 鼠标移动时
		virtual void OnMouseMove(UINT, int, int);		
		// 鼠标抬起时
		virtual void OnLButtonUp(UINT, int, int);
		// 鼠标按下时
		virtual void  OnLButtonDown(UINT, int, int);

	// 私有成员
	private:



};

//************************************************************************************************
//*************************** 主 程 序 ***********************************************************
//************************************************************************************************


// 从 CMzApp 派生的应用程序类
class MyApp : public CMzApp
{

	// 公有成员
	public:

		// 构造函数
		MyApp(void);
		// 析构函数
		~MyApp(void);

	// 保护成员
	protected:

		// 初始化
		virtual BOOL Init(void);
		// 运行
		virtual int Run(void);

	// 私有成员
	private:

		// 单例判断
		bool IsAppRunning(void);
		// 消息处理
		void MessageRegister(void);

};