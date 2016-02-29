
// 预编译
#include "stdafx.h"
// 头文件
#include "SoundMeterMouse.h"
#include "SoundMeterDraw.h"

// 鼠标区域
RECT	TheRectMouseMic = {353,655,479,719};

// 坐标
int TheMousePositionX = 0;
int TheMousePositionY = 0;

//************************************************************************************************
//*************************** 鼠标处理 ***********************************************************
//************************************************************************************************

/************************ 鼠标区间 **********************************/

// 鼠标坐标是否在某个矩阵中
bool MouseRectArea(RECT* rect, int x, int y)
{

	// 横坐标
	if((x>rect->left)&&(x<rect->right)){

		// 纵坐标
		if((y>rect->top)&&(y<rect->bottom)){
		
			return true;

		}
	
	}

	return false;

}

/************************ 鼠标双击时 **********************************/

// 鼠标双击时
void MouseClick(int x, int y)
{

}

/************************ 鼠标移动时 **********************************/

// 鼠标移动时
void MouseMove(int x, int y)
{

	

}

/************************ 鼠标抬起时 **********************************/

// 鼠标抬起时
void MouseUp(int x, int y)
{

	// 在范围内
	if(MouseRectArea(&TheRectMouseMic,x,y)){

		// 变更状态
		DrawWaveSetMicStatus();
		return;

	}

	// 不是水平滑动
	if(abs(y-TheMousePositionY)>200){
		return;
	}

	// 滑动不够长
	if(abs(x-TheMousePositionX)<200){
		return;
	}

	// 向右滑动
	if(x>TheMousePositionX){
		DrawWaveSetWaveStep(1);
	// 向左滑动
	}else{
		DrawWaveSetWaveStep(-1);
	}

}

/************************ 鼠标按下时 **********************************/

// 鼠标按下时
void MouseDown(int x, int y)
{

	// 记录坐标
	TheMousePositionX = x;
	TheMousePositionY = y;

}