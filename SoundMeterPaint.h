#pragma once

// 基本设定
#define		PAINT_MAX_WIDTH		480			// 绘图宽度
#define		PAINT_MAX_HEGITH	720			// 绘图高度
#define		PAINT_CENTER_X		240			// X 轴中间
#define		PAINT_CENTER_Y		360			// Y 轴中间

// 数学常数
#define		PI				3.1415926		// 圆周率

// internal clipping codes
#define CLIP_CODE_C  0x0000
#define CLIP_CODE_N  0x0008
#define CLIP_CODE_S  0x0004
#define CLIP_CODE_E  0x0002
#define CLIP_CODE_W  0x0001

#define CLIP_CODE_NE 0x000a
#define CLIP_CODE_SE 0x0006
#define CLIP_CODE_NW 0x0009 
#define CLIP_CODE_SW 0x0005

//************************************************************************************************
//*************************** 绘 图 函 数 ********************************************************
//************************************************************************************************

// 画点
void PaintPixel(USHORT*, int, int, USHORT, int);
// 画线（未裁剪）
void PaintLineNotClip(USHORT*, int, int, int, int, USHORT, int);
// 画线（已裁剪）
void PaintLine(USHORT*, int, int, int, int, USHORT, int);
// 矩形裁剪
bool PaintClip(int &x1,int &y1,int &x2, int &y2);