
// Ԥ����
#include "stdafx.h"
// ͷ�ļ�
#include "SoundMeterMouse.h"
#include "SoundMeterDraw.h"

// �������
RECT	TheRectMouseMic = {353,655,479,719};

// ����
int TheMousePositionX = 0;
int TheMousePositionY = 0;

//************************************************************************************************
//*************************** ��괦�� ***********************************************************
//************************************************************************************************

/************************ ������� **********************************/

// ��������Ƿ���ĳ��������
bool MouseRectArea(RECT* rect, int x, int y)
{

	// ������
	if((x>rect->left)&&(x<rect->right)){

		// ������
		if((y>rect->top)&&(y<rect->bottom)){
		
			return true;

		}
	
	}

	return false;

}

/************************ ���˫��ʱ **********************************/

// ���˫��ʱ
void MouseClick(int x, int y)
{

}

/************************ ����ƶ�ʱ **********************************/

// ����ƶ�ʱ
void MouseMove(int x, int y)
{

	

}

/************************ ���̧��ʱ **********************************/

// ���̧��ʱ
void MouseUp(int x, int y)
{

	// �ڷ�Χ��
	if(MouseRectArea(&TheRectMouseMic,x,y)){

		// ���״̬
		DrawWaveSetMicStatus();
		return;

	}

	// ����ˮƽ����
	if(abs(y-TheMousePositionY)>200){
		return;
	}

	// ����������
	if(abs(x-TheMousePositionX)<200){
		return;
	}

	// ���һ���
	if(x>TheMousePositionX){
		DrawWaveSetWaveStep(1);
	// ���󻬶�
	}else{
		DrawWaveSetWaveStep(-1);
	}

}

/************************ ��갴��ʱ **********************************/

// ��갴��ʱ
void MouseDown(int x, int y)
{

	// ��¼����
	TheMousePositionX = x;
	TheMousePositionY = y;

}