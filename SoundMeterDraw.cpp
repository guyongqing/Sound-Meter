// 预编译
#include "stdafx.h"

// 画面绘制
#include "SoundMeterDraw.h"
// 图形绘制
#include "SoundMeterPaint.h"
// 文件操作
#include "SoundMeterFile.h"

// DirectDraw 全局变量

DDSURFACEDESC			TheDDrawSurface;		// DirectDraw 表面结构
DDCOLORKEY				TheDDrawColorKey;		// DirectDraw 透明色
DDALPHABLTFX			TheDDrawAlphaBltfx;		// DirectDraw 半透明色	
DDPIXELFORMAT			TheDDrawPixelFormat;	// DirectDraw 像素格式结构

LPDIRECTDRAW			TheDDraw;				// DirectDraw 界面
LPDIRECTDRAWCLIPPER		TheDDrawClipper;		// DirectDraw 裁剪器
LPDIRECTDRAWSURFACE		TheDDrawPrimary;		// DirectDraw 主表面
LPDIRECTDRAWSURFACE		TheDDrawBackBuffer;		// DirectDraw 后备表面
LPDIRECTDRAWSURFACE		TheDDrawBackground;		// DirectDraw 背景表面
LPDIRECTDRAWSURFACE		TheDDrawForeground;		// DirectDraw 前景表面

//************************** 全局矩阵 *********************************************//

// 屏幕矩阵
RECT	TheRectScreen = {0,0,PAINT_MAX_WIDTH,PAINT_MAX_HEGITH};
// 目标矩阵
RECT	TheRectTarget = {0,0,0,0};
// 来源矩阵
RECT	TheRectSource = {0,0,0,0};

//************************** 颜色部分 *********************************************//

RECT	TheRectColorBlack = {162,72,163,73};	// 黑色矩阵
RECT	TheRectColorWhite = {104,464,105,465};	// 黑色矩阵

//************************** 显示部分 *********************************************//

RECT	TheRectTitle = {0,0,480,43};			// 标题黑色
RECT	TheRectTitleSample = {440,0,480,43};	// 标题取样
RECT	TheRectDot = {323,36,329,42};			// 小数点
RECT	TheRectMicSource = {390,2,469,24};		// MIC来源地址
RECT	TheRectMicTarget = {378,677,457,699};	// MIC目标地址
RECT	TheRectNumbers[10] = {					// 数字

	{7,8,31,42},{39,8,63,42},{70,8,94,42},{102,8,126,42},{133,8,157,42},
	{165,8,189,42},{196,8,220,42},{228,8,252,42},{260,8,284,42},{292,8,316,42}

};

// 最小值
RECT	TheRectNumbersShowMin[DRAW_NAME_NUMBER_COUNT] = {{58,109,82,143},{78,109,102,143},{108,109,132,143},{99,137,105,143}};
// 平均值
RECT	TheRectNumbersShowAvg[DRAW_NAME_NUMBER_COUNT] = {{189,109,213,143},{210,109,234,143},{240,109,264,143},{230,137,236,143}};
// 最大值
RECT	TheRectNumbersShowMax[DRAW_NAME_NUMBER_COUNT] = {{322,109,346,143},{342,109,366,143},{372,109,396,143},{362,137,368,143}};
// 当前值
RECT	TheRectNumbersShowNow[DRAW_NAME_NUMBER_COUNT] = {{58,198,82,232},{78,198,102,232},{108,198,132,232},{99,226,105,232}};

//************************** 音频数据 *********************************************//

SHORT*	TheDrawWaveData;

//************************** 状态数据 *********************************************//

SHORT	TheDrawWaveMinNow = 0;						// 当前最小值
SHORT	TheDrawWaveMaxNow = 0;						// 当前最大值
double	TheDrawWaveNow = 0;							// 当前差值

double	TheDrawWaveDBNow = 0;						// 当前分贝
double	TheDrawWaveDBMin = DRAW_WAVE_DB_MID;		// 最小分贝
double	TheDrawWaveDBMax = 0;						// 最大分贝
double	TheDrawWaveDBAvg = 0;						// 平均分贝
double	TheDrawWaveDBAvgTotal = 0;					// 平均分贝计数

BYTE	TheDrawWaveStep = DRAW_WAVE_STEP;			// 取样步伐
BYTE	TheDrawWaveIndex = 0;						// 当前步伐

double	TheDrawWaveTotal = 0;						// 差值统计
double	TheDrawWaveAvgTotal = 0;					// 平均分贝计数

bool	TheDrawWaveIsMic = true;					// 是否MIC

//************************** 显示数字 *********************************************//

// 当前分贝
double firstDB = 0;
double secondDB = 0;
double thirdDB = 0;

// 十位数字
BYTE firstShow = 0;
// 个位数字
BYTE secondShow = 0;
// 百位数字
BYTE thirdShow = 0;

//************************** 坐标数据 *********************************************//

// 分贝指针
SHORT	TheDrawLocationCenterX[DRAW_WAVE_LOCATION_CENTER] = {215,216,215,214,215};			// 圆心X坐标
SHORT	TheDrawLocationCenterY[DRAW_WAVE_LOCATION_CENTER] = {465,465,464,465,466};			// 圆心Y坐标
SHORT	TheDrawLocationStartX = 395;			// 起点X坐标
SHORT	TheDrawLocationStartY = 465;			// 起点Y坐标
SHORT	TheDrawLocationR = 160;					// 半径

// 速度指针
SHORT	TheDrawSpeedCenterX[DRAW_WAVE_LOCATION_CENTER] = {353,354,353,352,353};			// 圆心X坐标
SHORT	TheDrawSpeedCenterY[DRAW_WAVE_LOCATION_CENTER] = {325,325,326,325,324};			// 圆心Y坐标
SHORT	TheDrawSpeedStartX = 443;				// 起点X坐标
SHORT	TheDrawSpeedStartY = 325;				// 起点Y坐标
SHORT	TheDrawSpeedR = 90;						// 半径

double	TheDrawLocationAngle = 0;				// 角度
double	TheDrawLocationRadian = 0;				// 弧度
double	TheDrawLocationTargetX = 0;				// 目标X坐标
double	TheDrawLocationTargetY = 0;				// 目标Y坐标

//************************************************************************************************
//*************************** 音频部分 ***********************************************************
//************************************************************************************************

// 给绘图模块发送数据指针
void DrawSetWaveData(SHORT* data)
{

	// 复制指针
	TheDrawWaveData = data;

}

// 画指针
void DrawWaveLine(USHORT* bb, int lPitch)
{

	// 未能获取到数据
	if(TheDrawWaveData==NULL){
		return;
	}

	// 绘制分贝指针
	DrawWaveLineDB(bb,lPitch);

	// 画速度指针
	DrawWaveLineSpeed(bb,lPitch);

	/*p2.x   =   p0.x   +   (p1.x-p0.x)   *   cos   (a)   -   (p1.y-p0.y)   *   sin(a)
    p2.y   =   p0.y   +   (p1.y-p0.y)   *   cos(a)     +   (p1.x-p0.x)   *   sin(a); */

}

// 画速度指针
void DrawWaveLineSpeed(USHORT* bb, int lPitch)
{

	// 计算角度
	TheDrawLocationAngle = DRAW_WAVE_ANGLE_SPEEN_START + (TheDrawWaveStep-5) * DRAW_WAVE_ANGLE_PER * 2;

	// 小于起始角
	if(TheDrawLocationAngle<DRAW_WAVE_ANGLE_SPEEN_START){
		TheDrawLocationAngle = DRAW_WAVE_ANGLE_SPEEN_START;
	}

	// 大于终止角
	if(TheDrawLocationAngle>DRAW_WAVE_ANGLE_SPEEN_END){
		TheDrawLocationAngle = DRAW_WAVE_ANGLE_SPEEN_END;
	}

	// 计算弧度
	TheDrawLocationRadian = TheDrawLocationAngle * PI / 180;	

	// 画指针
	for(int i=0;i<DRAW_WAVE_LOCATION_CENTER;i++){
		// 计算X坐标
		TheDrawLocationTargetX = TheDrawSpeedCenterX[0] + TheDrawSpeedR * cos(TheDrawLocationRadian) ;
		// 计算Y坐标
		TheDrawLocationTargetY = TheDrawSpeedCenterY[0] + TheDrawSpeedR * sin(TheDrawLocationRadian); 
		// 绘图
		PaintLineNotClip(bb,TheDrawSpeedCenterX[i],TheDrawSpeedCenterY[i],(int)TheDrawLocationTargetX,(int)TheDrawLocationTargetY,DRAW_COLOR_RED,lPitch);
	}

}

// 绘制分贝指针
void DrawWaveLineDB(USHORT* bb, int lPitch)
{

	// 角度
	TheDrawLocationAngle = DRAW_WAVE_ANGLE_START + TheDrawWaveDBNow * DRAW_WAVE_ANGLE_PER;

	// 小于起始角
	if(TheDrawLocationAngle<DRAW_WAVE_ANGLE_START){
		TheDrawLocationAngle = DRAW_WAVE_ANGLE_START;
	}

	// 大于终止角
	if(TheDrawLocationAngle>DRAW_WAVE_ANGLE_END){
		TheDrawLocationAngle = DRAW_WAVE_ANGLE_END;
	}

	// 计算弧度
	TheDrawLocationRadian = TheDrawLocationAngle * PI / 180;	

	// 画指针
	for(int i=0;i<DRAW_WAVE_LOCATION_CENTER;i++){
		// 计算X坐标
		TheDrawLocationTargetX = TheDrawLocationCenterX[0] + TheDrawLocationR * cos(TheDrawLocationRadian) ;
		// 计算Y坐标
		TheDrawLocationTargetY = TheDrawLocationCenterY[0] + TheDrawLocationR * sin(TheDrawLocationRadian); 
		// 绘图
		PaintLineNotClip(bb,TheDrawLocationCenterX[i],TheDrawLocationCenterY[i],(int)TheDrawLocationTargetX,(int)TheDrawLocationTargetY,DRAW_COLOR_RED,lPitch);
	}

}

// 绘制声音图形
void DrawWaveData(void)
{

	// 计算数据
	DrawWaveCalculate();

	// 显示数据
	DrawWaveDataFinal();
	

}

// 设置速度
void DrawWaveSetWaveStep(BYTE step)
{

	// 计算新的速度
	TheDrawWaveStep += step;

	// 低于最小值
	if(TheDrawWaveStep<DRAW_WAVE_STEP_MIN){
		TheDrawWaveStep = DRAW_WAVE_STEP_MIN;
	}

	// 低于最小值
	if(TheDrawWaveStep>DRAW_WAVE_STEP_MAX){
		TheDrawWaveStep = DRAW_WAVE_STEP_MAX;
	}

}

// 变更麦克风状态
void DrawWaveSetMicStatus(void){

	TheDrawWaveIsMic = !TheDrawWaveIsMic;

}

// 显示数据
void DrawWaveDataFinal(void)
{

	// 当前分贝
	DrawWaveDataNumbers(TheDrawWaveDBNow,TheRectNumbersShowNow);
	// 最小分贝
	DrawWaveDataNumbers(TheDrawWaveDBMin,TheRectNumbersShowMin);
	// 平均分贝
	DrawWaveDataNumbers(TheDrawWaveDBAvg,TheRectNumbersShowAvg);
	// 最大分贝
	DrawWaveDataNumbers(TheDrawWaveDBMax,TheRectNumbersShowMax);

}

// 绘制数字
void DrawWaveDataNumbers(double db, RECT* targetRect)
{

	// 超出正常取值范围
	if(db<DRAW_WAVE_DB_MIN){db=DRAW_WAVE_DB_MIN;}
	if(db>DRAW_WAVE_DB_MAX){db=DRAW_WAVE_DB_MAX;}

	// 计算十位数字
	firstDB = db*10;
	firstShow = (BYTE)(firstDB/100);

	// 计算个位数字
	secondDB = firstDB-(firstShow*100);
	secondShow = (BYTE)(secondDB/10);

	// 计算百位数字
	thirdDB = firstDB-(firstShow*100)-(secondShow * 10);
	thirdShow = (BYTE)(thirdDB);

	// 绘制数字
	DrawRect(TheDDrawBackground,&TheRectNumbers[firstShow],&targetRect[DRAW_NAME_NUMBER_FIRST],DRAW_BLT_COLORKEY);
	DrawRect(TheDDrawBackground,&TheRectNumbers[secondShow],&targetRect[DRAW_NAME_NUMBER_SECOND],DRAW_BLT_COLORKEY);
	DrawRect(TheDDrawBackground,&TheRectNumbers[thirdShow],&targetRect[DRAW_NAME_NUMBER_THIRD],DRAW_BLT_COLORKEY);
	DrawRect(TheDDrawBackground,&TheRectDot,&targetRect[DRAW_NAME_NUMBER_DOT],DRAW_BLT_COLORKEY);

}

// 计算数据
void DrawWaveCalculate(void)
{

	// 未获得数据
	if(TheDrawWaveData==NULL){
		return;
	}

	// 数据重置
	TheDrawWaveMinNow = 0;
	TheDrawWaveMaxNow = 0;

	// 分析一次采样数据
	for(int i=0;i<DRAW_SCREEN_HEIGHT;i++){

		// 计算最小值
		if(TheDrawWaveData[i]<TheDrawWaveMinNow){
			TheDrawWaveMinNow = TheDrawWaveData[i];
		}

		// 计算最大值
		if(TheDrawWaveData[i]>TheDrawWaveMaxNow){
			TheDrawWaveMaxNow = TheDrawWaveData[i];
		}

	}

	// 计算当前差值
	TheDrawWaveNow = TheDrawWaveMaxNow - TheDrawWaveMinNow;

	// 统计差值
	TheDrawWaveTotal += TheDrawWaveNow;

	// 步伐前进
	TheDrawWaveIndex++;

	// 取样时间到
	if(TheDrawWaveIndex>TheDrawWaveStep){

		// 退一步
		TheDrawWaveIndex--;
		// 计算当前分贝值
		TheDrawWaveDBNow = TheDrawWaveTotal/TheDrawWaveIndex;

		if(TheDrawWaveIsMic){
			TheDrawWaveDBNow/=DRAW_WAVE_DB_MIC;
		}else{
			TheDrawWaveDBNow/=DRAW_WAVE_DB_HUMAN;
		}
		// 平均分贝统计
		TheDrawWaveDBAvgTotal += TheDrawWaveDBNow;
		// 平均分贝计数
		TheDrawWaveAvgTotal++;
		// 平均分贝
		TheDrawWaveDBAvg = TheDrawWaveDBAvgTotal / TheDrawWaveAvgTotal;

		// 计算最小分贝 
		if(TheDrawWaveDBNow<TheDrawWaveDBMin){
			TheDrawWaveDBMin = TheDrawWaveDBNow;
		}

		// 计算最小分贝 
		if(TheDrawWaveDBNow>TheDrawWaveDBMax){
			TheDrawWaveDBMax = TheDrawWaveDBNow;
		}
		
		// 重新开始统计
		TheDrawWaveIndex = 0;
		TheDrawWaveTotal = 0;

	}

}

//************************************************************************************************
//*************************** 画面绘制 ***********************************************************
//************************************************************************************************

// 游戏绘制入口
void Draw(void)
{

	// 绘制背景
	DrawBackground();

	// 绘制声音图形
	DrawWaveData();

	// 绘制前景
	DrawForeground();
	
	// 显示主表面
	DrawPrimary();

}

// 绘制背景
void DrawBackground(void)
{

	// 绘制矩形（背景图）
	DrawRect(TheDDrawBackground,&TheRectScreen,&TheRectScreen,DRAW_BLT_NORMAL);
	// 绘制矩形（标题栏）
	DrawRect(TheDDrawBackground,&TheRectTitleSample,&TheRectTitle,DRAW_BLT_NORMAL);
	// 绘制MIC状态
	if(!TheDrawWaveIsMic){
		DrawRect(TheDDrawBackground,&TheRectMicSource,&TheRectMicTarget,DRAW_BLT_NORMAL);
	}

}

// 绘制前景
void DrawForeground(void)
{

	// 初始化表面结构
	DDRAW_INIT_STRUCT(TheDDrawSurface);

	// 锁定表面失败
	if(TheDDrawBackBuffer->Lock(NULL,&TheDDrawSurface,DDLOCK_WAITNOTBUSY,NULL)!=DD_OK){
		return;
	}

	// 间距
	int pitch = 0;

	// 获取数据指针
	USHORT* bb = (USHORT*)TheDDrawSurface.lpSurface;
	// 计算间距
	pitch = (int)(TheDDrawSurface.lPitch>>1);

	// 这里直接对显存操作
	/*******************************/

	DrawWaveLine(bb,pitch);

	/*******************************/

	// 解锁表面
	TheDDrawBackBuffer->Unlock(NULL);

}

// 清屏幕（内存）
void DrawCls(USHORT* bb, int lPitch, USHORT color)
{
	
	// 宽度与屏幕相同
	if(lPitch==DRAW_SCREEN_WIDTH){
		
		// 填充颜色
		for(int i=0;i<DRAW_SCREEN_SIZE;i++){
			bb[i] = color;
		}

	// 有额外内存
	}else{

		// 依坐标填充颜色
		for(int x=0;x<DRAW_SCREEN_WIDTH;x++){
			for(int y=0;y<DRAW_SCREEN_HEIGHT;y++){
				bb[x+y*lPitch] = color;
			}		
		}
	
	}
	
}

// 清屏幕（矩阵）
void DrawClsRect(void)
{
	
	// 绘制矩形
	DrawRect(TheDDrawBackground,&TheRectColorBlack,&TheRectScreen,DRAW_BLT_NORMAL);
	
}

// 绘制主表面
void DrawPrimary(void)
{
	
	// 将后备表面复制到主表面
	TheDDrawPrimary->Blt(&TheRectScreen,TheDDrawBackBuffer,&TheRectScreen,DDBLT_WAITNOTBUSY,NULL);	

}

// 绘制暂停画面
void DrawPause(void)
{

	

}

//************************************************************************************************
//*************************** DirectDraw *********************************************************
//************************************************************************************************


// 初始化
bool DirectDrawInit(HWND hwnd)
{

	// 创建DirectDraw对象
	if(DirectDrawCreate(NULL,&TheDDraw,NULL)!=DD_OK){
		return false;
	}

	// 设置协作方式
	if(TheDDraw->SetCooperativeLevel(hwnd,DDSCL_NORMAL)!=DD_OK){
		return false;
	}

	/********************************主表面****************************************/

	// 初始化表面结构
	DDRAW_INIT_STRUCT(TheDDrawSurface);

	TheDDrawSurface.dwFlags = DDSD_CAPS;
	TheDDrawSurface.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE;

	// 创建主表面
	if(TheDDraw->CreateSurface(&TheDDrawSurface,&TheDDrawPrimary,NULL)!=DD_OK){
		return false;
	}

	// 设置像素格式	
	DDRAW_INIT_STRUCT(TheDDrawPixelFormat);
	// 获取像素格式
	TheDDrawPrimary->GetPixelFormat(&TheDDrawPixelFormat);

	// 如果不是16位色模式
	if(TheDDrawPixelFormat.dwRGBBitCount!=DRAW_SCREEN_COLOR){
		return false;
	}

	// 创建裁剪器
	if(TheDDraw->CreateClipper(0,&TheDDrawClipper,NULL)!=DD_OK){
		return false;
	}
	
	// 设置裁剪器窗口句柄
	if(TheDDrawClipper->SetHWnd(0,hwnd)!=DD_OK){
		return false;
	}

	// 关联裁剪器
	if(TheDDrawPrimary->SetClipper(TheDDrawClipper)!=DD_OK){
		return false;
	}

	// 创建后备表面
	if(!DirectDrawCreateSurface(&TheDDrawBackBuffer,DRAW_SCREEN_WIDTH,DRAW_SCREEN_HEIGHT)){
		return false;
	}

	// 创建背景表面
	if(!DirectDrawCreateSurface(&TheDDrawBackground,DRAW_BACKGROUND_WIDTH,DRAW_BACKGROUND_HEIGHT)){
		return false;
	}

	// 创建前景表面
	if(!DirectDrawCreateSurface(&TheDDrawForeground,DRAW_FOREGROUND_WIDTH,DRAW_FOREGROUND_HEIGHT)){
		return false;
	}

	// 设置透明色	
	TheDDrawColorKey.dwColorSpaceHighValue = 0;
	TheDDrawColorKey.dwColorSpaceLowValue = 0;
	TheDDrawBackground->SetColorKey(DDCKEY_SRCBLT,&TheDDrawColorKey);

	// 初始化半透明结构
	DDRAW_INIT_STRUCT(TheDDrawAlphaBltfx);

	return true;

}

// 创建表面
bool DirectDrawCreateSurface(LPDIRECTDRAWSURFACE* s, int w, int h)
{

	// 初始化表面结构
	DDRAW_INIT_STRUCT(TheDDrawSurface);

	// 设置资料读取中表面参数
	TheDDrawSurface.dwFlags = DDSD_CAPS | DDSD_WIDTH | DDSD_HEIGHT;
	TheDDrawSurface.ddsCaps.dwCaps = DDSCAPS_VIDEOMEMORY;
	TheDDrawSurface.dwWidth = w;
	TheDDrawSurface.dwHeight = h;

	// 创建资料读取中表面
	if(TheDDraw->CreateSurface(&TheDDrawSurface,s,NULL)!=DD_OK){
		return false;
	}

	return true;

}

// 销毁
void DirectDrawEnd(void)
{

	// 释放前景表面
	if(TheDDrawForeground){
		TheDDrawForeground->Release();
		TheDDrawForeground = NULL;
	}

	// 释放背景表面
	if(TheDDrawBackground){
		TheDDrawBackground->Release();
		TheDDrawBackground = NULL;
	}

	// 释放后备表面
	if(TheDDrawBackBuffer){
		TheDDrawBackBuffer->Release();
		TheDDrawBackBuffer = NULL;
	}

	// 释放主表面
	if(TheDDrawPrimary){
		TheDDrawPrimary->Release();
		TheDDrawPrimary = NULL;
	}

	// 销毁剪切版
	if(TheDDrawClipper){
		TheDDrawClipper->Release();
		TheDDrawClipper = NULL;
	}

	// 释放内部分配资源
	if(TheDDraw){
		TheDDraw->Release();
		TheDDraw = NULL;
	}

}

//************************************************************************************************
//*************************** 素 材 读 取 ********************************************************
//************************************************************************************************


// 读取图像文件
bool LoadingImageFile(LPTSTR imgFile, int imgSize)
{

	bool flag = false;

	// 初始化表面结构
	DDRAW_INIT_STRUCT(TheDDrawSurface);

	// 锁定主角表面
	if(TheDDrawBackground->Lock(NULL,&TheDDrawSurface,DDLOCK_WAITNOTBUSY,NULL)!=DD_OK){
		return false;
	}

	// 缓冲数据
	CHAR *bb = (CHAR *)TheDDrawSurface.lpSurface;

	// 读取文件
	flag = FileGetData(imgFile,bb,imgSize);

	// 解锁主角表面
	TheDDrawBackground->Unlock(NULL);

	// 操作成功
	return flag;	

}



//************************************************************************************************
//*************************** 矩 形 绘 制 ********************************************************
//************************************************************************************************

// 快速绘制矩形
void DrawRect(LPDIRECTDRAWSURFACE ddSurface, RECT* rSource, RECT* rTarget, int colorkey)
{

	// 复制源画面数据至后备画面
	TheDDrawBackBuffer->Blt(rTarget,ddSurface,rSource,DDBLT_WAITNOTBUSY|colorkey,NULL);

}

// 快速绘制矩形（半透明）
void DrawRectAlpha(LPDIRECTDRAWSURFACE ddSurface, RECT* rSource, RECT* rTarget, int alpha)
{

	// 设置半透明程度
	TheDDrawAlphaBltfx.ddargbScaleFactors.alpha = alpha;

	// 复制源画面数据至后备画面
	TheDDrawBackBuffer->AlphaBlt(rTarget,ddSurface,rSource,DDABLT_WAITNOTBUSY|DDABLT_ALPHASRCNEG,&TheDDrawAlphaBltfx);

}