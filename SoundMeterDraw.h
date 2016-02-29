#pragma once

// DirectDraw
#include <ddraw.h>

// 屏幕属性
#define	DRAW_SCREEN_WIDTH			480			// 屏幕宽度
#define	DRAW_SCREEN_HEIGHT			720			// 屏幕高度
#define DRAW_SCREEN_COLOR			16			// 16 位色
#define DRAW_SCREEN_SIZE			345600		// 屏幕占用字节数

// 常用颜色
#define DRAW_COLOR_BLACK			0					// 黑色
#define DRAW_COLOR_WHITE			0xFFFF				// 白色
#define DRAW_COLOR_GREEN			0x07E0				// 绿色
#define DRAW_COLOR_BLUE				0x001F				// 蓝色
#define DRAW_COLOR_RED				0xF800				// 红色


// 定义是否透明
#define DRAW_BLT_NORMAL				0				// 正常填充
#define DRAW_BLT_COLORKEY			DDBLT_KEYSRC	// 透明填充

// 半透明数据
#define DRAW_ALPHA_MIN				0				// 最小半透明色
#define DRAW_ALPHA_MID				128				// 50% 半透明色
#define DRAW_ALPHA_MAX				255				// 最大半透明色

// 图像缓冲
#define DRAW_BACKGROUND_WIDTH		480				// 背景宽度
#define DRAW_BACKGROUND_HEIGHT		720				// 背景高度
#define DRAW_BACKGROUND_SIZE		691200			// 背景大小
#define DRAW_BACKGROUND_FILE		L"10611824.dat"

#define DRAW_FOREGROUND_WIDTH		1				// 前景宽度
#define DRAW_FOREGROUND_HEIGHT		1				// 前景高度
#define DRAW_FOREGROUND_SIZE		4				// 前景大小
#define DRAW_FOREGROUND_FILE		L"10611825.dat"

// 波形显示设置
#define DRAW_WAVE_MIN				-32767			// 最小值
#define DRAW_WAVE_MIDDLE			0				// 中间值
#define DRAW_WAVE_MAX				32767			// 最大值
#define DRAW_WAVE_STEP				15				// 采样步伐
#define DRAW_WAVE_STEP_MIN			5				// 采样步伐最小值
#define DRAW_WAVE_STEP_MAX			35				// 采样步伐最大值
#define	DRAW_WAVE_DB_MIN			0				// 分贝最小值
#define	DRAW_WAVE_DB_MID			48				// 分贝中间值
#define	DRAW_WAVE_DB_MAX			96.3			// 分贝最大值
#define DRAW_WAVE_DB_MIC			682.66			// 以麦克风为标准时的参考值
#define DRAW_WAVE_DB_HUMAN			227				// 人耳
#define DRAW_WAVE_LOCATION_CENTER	5				// 5个圆心
#define DRAW_WAVE_ANGLE_START		128.5714		// 起始角度
#define DRAW_WAVE_ANGLE_END			376.1972		// 终止角度
#define DRAW_WAVE_ANGLE_SPEEN_START	231.4322		// 起始角度
#define DRAW_WAVE_ANGLE_SPEEN_END	411.4302		// 终止角度
#define DRAW_WAVE_ANGLE_PER			2.5714			// 角度单位

// 名称定义
#define DRAW_NAME_NUMBER_FIRST		0
#define DRAW_NAME_NUMBER_SECOND		1
#define DRAW_NAME_NUMBER_THIRD		2
#define DRAW_NAME_NUMBER_DOT		3
#define DRAW_NAME_NUMBER_COUNT		4

//************************************************************************************************
//*************************** DirectDraw *********************************************************
//************************************************************************************************

#define DDRAW_INIT_STRUCT(ddsd) {memset(&ddsd,0,sizeof(ddsd));ddsd.dwSize=sizeof(ddsd);}

// 初始化
bool DirectDrawInit(HWND);
// 销毁
void DirectDrawEnd(void);
// 创建表面
bool DirectDrawCreateSurface(LPDIRECTDRAWSURFACE*, int, int);

//************************************************************************************************
//*************************** 画面绘制 ***********************************************************
//************************************************************************************************

// 游戏绘制入口
void Draw(void);
// 绘制背景
void DrawBackground(void);
// 绘制前景
void DrawForeground(void);
// 清屏幕（内存）
void DrawCls(USHORT*, int, USHORT);
// 清屏
void DrawClsRect(void);
// 绘制主表面
void DrawPrimary(void);

/*************************** 矩形绘制 ****************************************/

// 绘制矩形
void DrawRect(LPDIRECTDRAWSURFACE, RECT*, RECT*, int);
// 快速绘制矩形（半透明）
void DrawRectAlpha(LPDIRECTDRAWSURFACE, RECT*, RECT*, int);

//************************************************************************************************
//*************************** 音频部分 ***********************************************************
//************************************************************************************************

// 给绘图模块发送数据指针
void DrawSetWaveData(SHORT*);
// 画指针
void DrawWaveLine(USHORT*, int);
// 画分贝指针
void DrawWaveLineDB(USHORT*, int);
// 画速度指针
void DrawWaveLineSpeed(USHORT*, int);
// 绘制声音图形
void DrawWaveData(void);
// 显示数据
void DrawWaveDataFinal(void);
// 绘制数字
void DrawWaveDataNumbers(double, RECT*);
// 计算数据
void DrawWaveCalculate(void);
// 变更麦克风状态
void DrawWaveSetMicStatus(void);
// 设置速度
void DrawWaveSetWaveStep(BYTE);

//************************************************************************************************
//*************************** 素 材 读 取 ********************************************************
//************************************************************************************************

// 读取图像文件
bool LoadingImageFile(LPTSTR, int);