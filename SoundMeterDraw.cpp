// Ԥ����
#include "stdafx.h"

// �������
#include "SoundMeterDraw.h"
// ͼ�λ���
#include "SoundMeterPaint.h"
// �ļ�����
#include "SoundMeterFile.h"

// DirectDraw ȫ�ֱ���

DDSURFACEDESC			TheDDrawSurface;		// DirectDraw ����ṹ
DDCOLORKEY				TheDDrawColorKey;		// DirectDraw ͸��ɫ
DDALPHABLTFX			TheDDrawAlphaBltfx;		// DirectDraw ��͸��ɫ	
DDPIXELFORMAT			TheDDrawPixelFormat;	// DirectDraw ���ظ�ʽ�ṹ

LPDIRECTDRAW			TheDDraw;				// DirectDraw ����
LPDIRECTDRAWCLIPPER		TheDDrawClipper;		// DirectDraw �ü���
LPDIRECTDRAWSURFACE		TheDDrawPrimary;		// DirectDraw ������
LPDIRECTDRAWSURFACE		TheDDrawBackBuffer;		// DirectDraw �󱸱���
LPDIRECTDRAWSURFACE		TheDDrawBackground;		// DirectDraw ��������
LPDIRECTDRAWSURFACE		TheDDrawForeground;		// DirectDraw ǰ������

//************************** ȫ�־��� *********************************************//

// ��Ļ����
RECT	TheRectScreen = {0,0,PAINT_MAX_WIDTH,PAINT_MAX_HEGITH};
// Ŀ�����
RECT	TheRectTarget = {0,0,0,0};
// ��Դ����
RECT	TheRectSource = {0,0,0,0};

//************************** ��ɫ���� *********************************************//

RECT	TheRectColorBlack = {162,72,163,73};	// ��ɫ����
RECT	TheRectColorWhite = {104,464,105,465};	// ��ɫ����

//************************** ��ʾ���� *********************************************//

RECT	TheRectTitle = {0,0,480,43};			// �����ɫ
RECT	TheRectTitleSample = {440,0,480,43};	// ����ȡ��
RECT	TheRectDot = {323,36,329,42};			// С����
RECT	TheRectMicSource = {390,2,469,24};		// MIC��Դ��ַ
RECT	TheRectMicTarget = {378,677,457,699};	// MICĿ���ַ
RECT	TheRectNumbers[10] = {					// ����

	{7,8,31,42},{39,8,63,42},{70,8,94,42},{102,8,126,42},{133,8,157,42},
	{165,8,189,42},{196,8,220,42},{228,8,252,42},{260,8,284,42},{292,8,316,42}

};

// ��Сֵ
RECT	TheRectNumbersShowMin[DRAW_NAME_NUMBER_COUNT] = {{58,109,82,143},{78,109,102,143},{108,109,132,143},{99,137,105,143}};
// ƽ��ֵ
RECT	TheRectNumbersShowAvg[DRAW_NAME_NUMBER_COUNT] = {{189,109,213,143},{210,109,234,143},{240,109,264,143},{230,137,236,143}};
// ���ֵ
RECT	TheRectNumbersShowMax[DRAW_NAME_NUMBER_COUNT] = {{322,109,346,143},{342,109,366,143},{372,109,396,143},{362,137,368,143}};
// ��ǰֵ
RECT	TheRectNumbersShowNow[DRAW_NAME_NUMBER_COUNT] = {{58,198,82,232},{78,198,102,232},{108,198,132,232},{99,226,105,232}};

//************************** ��Ƶ���� *********************************************//

SHORT*	TheDrawWaveData;

//************************** ״̬���� *********************************************//

SHORT	TheDrawWaveMinNow = 0;						// ��ǰ��Сֵ
SHORT	TheDrawWaveMaxNow = 0;						// ��ǰ���ֵ
double	TheDrawWaveNow = 0;							// ��ǰ��ֵ

double	TheDrawWaveDBNow = 0;						// ��ǰ�ֱ�
double	TheDrawWaveDBMin = DRAW_WAVE_DB_MID;		// ��С�ֱ�
double	TheDrawWaveDBMax = 0;						// ���ֱ�
double	TheDrawWaveDBAvg = 0;						// ƽ���ֱ�
double	TheDrawWaveDBAvgTotal = 0;					// ƽ���ֱ�����

BYTE	TheDrawWaveStep = DRAW_WAVE_STEP;			// ȡ������
BYTE	TheDrawWaveIndex = 0;						// ��ǰ����

double	TheDrawWaveTotal = 0;						// ��ֵͳ��
double	TheDrawWaveAvgTotal = 0;					// ƽ���ֱ�����

bool	TheDrawWaveIsMic = true;					// �Ƿ�MIC

//************************** ��ʾ���� *********************************************//

// ��ǰ�ֱ�
double firstDB = 0;
double secondDB = 0;
double thirdDB = 0;

// ʮλ����
BYTE firstShow = 0;
// ��λ����
BYTE secondShow = 0;
// ��λ����
BYTE thirdShow = 0;

//************************** �������� *********************************************//

// �ֱ�ָ��
SHORT	TheDrawLocationCenterX[DRAW_WAVE_LOCATION_CENTER] = {215,216,215,214,215};			// Բ��X����
SHORT	TheDrawLocationCenterY[DRAW_WAVE_LOCATION_CENTER] = {465,465,464,465,466};			// Բ��Y����
SHORT	TheDrawLocationStartX = 395;			// ���X����
SHORT	TheDrawLocationStartY = 465;			// ���Y����
SHORT	TheDrawLocationR = 160;					// �뾶

// �ٶ�ָ��
SHORT	TheDrawSpeedCenterX[DRAW_WAVE_LOCATION_CENTER] = {353,354,353,352,353};			// Բ��X����
SHORT	TheDrawSpeedCenterY[DRAW_WAVE_LOCATION_CENTER] = {325,325,326,325,324};			// Բ��Y����
SHORT	TheDrawSpeedStartX = 443;				// ���X����
SHORT	TheDrawSpeedStartY = 325;				// ���Y����
SHORT	TheDrawSpeedR = 90;						// �뾶

double	TheDrawLocationAngle = 0;				// �Ƕ�
double	TheDrawLocationRadian = 0;				// ����
double	TheDrawLocationTargetX = 0;				// Ŀ��X����
double	TheDrawLocationTargetY = 0;				// Ŀ��Y����

//************************************************************************************************
//*************************** ��Ƶ���� ***********************************************************
//************************************************************************************************

// ����ͼģ�鷢������ָ��
void DrawSetWaveData(SHORT* data)
{

	// ����ָ��
	TheDrawWaveData = data;

}

// ��ָ��
void DrawWaveLine(USHORT* bb, int lPitch)
{

	// δ�ܻ�ȡ������
	if(TheDrawWaveData==NULL){
		return;
	}

	// ���Ʒֱ�ָ��
	DrawWaveLineDB(bb,lPitch);

	// ���ٶ�ָ��
	DrawWaveLineSpeed(bb,lPitch);

	/*p2.x   =   p0.x   +   (p1.x-p0.x)   *   cos   (a)   -   (p1.y-p0.y)   *   sin(a)
    p2.y   =   p0.y   +   (p1.y-p0.y)   *   cos(a)     +   (p1.x-p0.x)   *   sin(a); */

}

// ���ٶ�ָ��
void DrawWaveLineSpeed(USHORT* bb, int lPitch)
{

	// ����Ƕ�
	TheDrawLocationAngle = DRAW_WAVE_ANGLE_SPEEN_START + (TheDrawWaveStep-5) * DRAW_WAVE_ANGLE_PER * 2;

	// С����ʼ��
	if(TheDrawLocationAngle<DRAW_WAVE_ANGLE_SPEEN_START){
		TheDrawLocationAngle = DRAW_WAVE_ANGLE_SPEEN_START;
	}

	// ������ֹ��
	if(TheDrawLocationAngle>DRAW_WAVE_ANGLE_SPEEN_END){
		TheDrawLocationAngle = DRAW_WAVE_ANGLE_SPEEN_END;
	}

	// ���㻡��
	TheDrawLocationRadian = TheDrawLocationAngle * PI / 180;	

	// ��ָ��
	for(int i=0;i<DRAW_WAVE_LOCATION_CENTER;i++){
		// ����X����
		TheDrawLocationTargetX = TheDrawSpeedCenterX[0] + TheDrawSpeedR * cos(TheDrawLocationRadian) ;
		// ����Y����
		TheDrawLocationTargetY = TheDrawSpeedCenterY[0] + TheDrawSpeedR * sin(TheDrawLocationRadian); 
		// ��ͼ
		PaintLineNotClip(bb,TheDrawSpeedCenterX[i],TheDrawSpeedCenterY[i],(int)TheDrawLocationTargetX,(int)TheDrawLocationTargetY,DRAW_COLOR_RED,lPitch);
	}

}

// ���Ʒֱ�ָ��
void DrawWaveLineDB(USHORT* bb, int lPitch)
{

	// �Ƕ�
	TheDrawLocationAngle = DRAW_WAVE_ANGLE_START + TheDrawWaveDBNow * DRAW_WAVE_ANGLE_PER;

	// С����ʼ��
	if(TheDrawLocationAngle<DRAW_WAVE_ANGLE_START){
		TheDrawLocationAngle = DRAW_WAVE_ANGLE_START;
	}

	// ������ֹ��
	if(TheDrawLocationAngle>DRAW_WAVE_ANGLE_END){
		TheDrawLocationAngle = DRAW_WAVE_ANGLE_END;
	}

	// ���㻡��
	TheDrawLocationRadian = TheDrawLocationAngle * PI / 180;	

	// ��ָ��
	for(int i=0;i<DRAW_WAVE_LOCATION_CENTER;i++){
		// ����X����
		TheDrawLocationTargetX = TheDrawLocationCenterX[0] + TheDrawLocationR * cos(TheDrawLocationRadian) ;
		// ����Y����
		TheDrawLocationTargetY = TheDrawLocationCenterY[0] + TheDrawLocationR * sin(TheDrawLocationRadian); 
		// ��ͼ
		PaintLineNotClip(bb,TheDrawLocationCenterX[i],TheDrawLocationCenterY[i],(int)TheDrawLocationTargetX,(int)TheDrawLocationTargetY,DRAW_COLOR_RED,lPitch);
	}

}

// ��������ͼ��
void DrawWaveData(void)
{

	// ��������
	DrawWaveCalculate();

	// ��ʾ����
	DrawWaveDataFinal();
	

}

// �����ٶ�
void DrawWaveSetWaveStep(BYTE step)
{

	// �����µ��ٶ�
	TheDrawWaveStep += step;

	// ������Сֵ
	if(TheDrawWaveStep<DRAW_WAVE_STEP_MIN){
		TheDrawWaveStep = DRAW_WAVE_STEP_MIN;
	}

	// ������Сֵ
	if(TheDrawWaveStep>DRAW_WAVE_STEP_MAX){
		TheDrawWaveStep = DRAW_WAVE_STEP_MAX;
	}

}

// �����˷�״̬
void DrawWaveSetMicStatus(void){

	TheDrawWaveIsMic = !TheDrawWaveIsMic;

}

// ��ʾ����
void DrawWaveDataFinal(void)
{

	// ��ǰ�ֱ�
	DrawWaveDataNumbers(TheDrawWaveDBNow,TheRectNumbersShowNow);
	// ��С�ֱ�
	DrawWaveDataNumbers(TheDrawWaveDBMin,TheRectNumbersShowMin);
	// ƽ���ֱ�
	DrawWaveDataNumbers(TheDrawWaveDBAvg,TheRectNumbersShowAvg);
	// ���ֱ�
	DrawWaveDataNumbers(TheDrawWaveDBMax,TheRectNumbersShowMax);

}

// ��������
void DrawWaveDataNumbers(double db, RECT* targetRect)
{

	// ��������ȡֵ��Χ
	if(db<DRAW_WAVE_DB_MIN){db=DRAW_WAVE_DB_MIN;}
	if(db>DRAW_WAVE_DB_MAX){db=DRAW_WAVE_DB_MAX;}

	// ����ʮλ����
	firstDB = db*10;
	firstShow = (BYTE)(firstDB/100);

	// �����λ����
	secondDB = firstDB-(firstShow*100);
	secondShow = (BYTE)(secondDB/10);

	// �����λ����
	thirdDB = firstDB-(firstShow*100)-(secondShow * 10);
	thirdShow = (BYTE)(thirdDB);

	// ��������
	DrawRect(TheDDrawBackground,&TheRectNumbers[firstShow],&targetRect[DRAW_NAME_NUMBER_FIRST],DRAW_BLT_COLORKEY);
	DrawRect(TheDDrawBackground,&TheRectNumbers[secondShow],&targetRect[DRAW_NAME_NUMBER_SECOND],DRAW_BLT_COLORKEY);
	DrawRect(TheDDrawBackground,&TheRectNumbers[thirdShow],&targetRect[DRAW_NAME_NUMBER_THIRD],DRAW_BLT_COLORKEY);
	DrawRect(TheDDrawBackground,&TheRectDot,&targetRect[DRAW_NAME_NUMBER_DOT],DRAW_BLT_COLORKEY);

}

// ��������
void DrawWaveCalculate(void)
{

	// δ�������
	if(TheDrawWaveData==NULL){
		return;
	}

	// ��������
	TheDrawWaveMinNow = 0;
	TheDrawWaveMaxNow = 0;

	// ����һ�β�������
	for(int i=0;i<DRAW_SCREEN_HEIGHT;i++){

		// ������Сֵ
		if(TheDrawWaveData[i]<TheDrawWaveMinNow){
			TheDrawWaveMinNow = TheDrawWaveData[i];
		}

		// �������ֵ
		if(TheDrawWaveData[i]>TheDrawWaveMaxNow){
			TheDrawWaveMaxNow = TheDrawWaveData[i];
		}

	}

	// ���㵱ǰ��ֵ
	TheDrawWaveNow = TheDrawWaveMaxNow - TheDrawWaveMinNow;

	// ͳ�Ʋ�ֵ
	TheDrawWaveTotal += TheDrawWaveNow;

	// ����ǰ��
	TheDrawWaveIndex++;

	// ȡ��ʱ�䵽
	if(TheDrawWaveIndex>TheDrawWaveStep){

		// ��һ��
		TheDrawWaveIndex--;
		// ���㵱ǰ�ֱ�ֵ
		TheDrawWaveDBNow = TheDrawWaveTotal/TheDrawWaveIndex;

		if(TheDrawWaveIsMic){
			TheDrawWaveDBNow/=DRAW_WAVE_DB_MIC;
		}else{
			TheDrawWaveDBNow/=DRAW_WAVE_DB_HUMAN;
		}
		// ƽ���ֱ�ͳ��
		TheDrawWaveDBAvgTotal += TheDrawWaveDBNow;
		// ƽ���ֱ�����
		TheDrawWaveAvgTotal++;
		// ƽ���ֱ�
		TheDrawWaveDBAvg = TheDrawWaveDBAvgTotal / TheDrawWaveAvgTotal;

		// ������С�ֱ� 
		if(TheDrawWaveDBNow<TheDrawWaveDBMin){
			TheDrawWaveDBMin = TheDrawWaveDBNow;
		}

		// ������С�ֱ� 
		if(TheDrawWaveDBNow>TheDrawWaveDBMax){
			TheDrawWaveDBMax = TheDrawWaveDBNow;
		}
		
		// ���¿�ʼͳ��
		TheDrawWaveIndex = 0;
		TheDrawWaveTotal = 0;

	}

}

//************************************************************************************************
//*************************** ������� ***********************************************************
//************************************************************************************************

// ��Ϸ�������
void Draw(void)
{

	// ���Ʊ���
	DrawBackground();

	// ��������ͼ��
	DrawWaveData();

	// ����ǰ��
	DrawForeground();
	
	// ��ʾ������
	DrawPrimary();

}

// ���Ʊ���
void DrawBackground(void)
{

	// ���ƾ��Σ�����ͼ��
	DrawRect(TheDDrawBackground,&TheRectScreen,&TheRectScreen,DRAW_BLT_NORMAL);
	// ���ƾ��Σ���������
	DrawRect(TheDDrawBackground,&TheRectTitleSample,&TheRectTitle,DRAW_BLT_NORMAL);
	// ����MIC״̬
	if(!TheDrawWaveIsMic){
		DrawRect(TheDDrawBackground,&TheRectMicSource,&TheRectMicTarget,DRAW_BLT_NORMAL);
	}

}

// ����ǰ��
void DrawForeground(void)
{

	// ��ʼ������ṹ
	DDRAW_INIT_STRUCT(TheDDrawSurface);

	// ��������ʧ��
	if(TheDDrawBackBuffer->Lock(NULL,&TheDDrawSurface,DDLOCK_WAITNOTBUSY,NULL)!=DD_OK){
		return;
	}

	// ���
	int pitch = 0;

	// ��ȡ����ָ��
	USHORT* bb = (USHORT*)TheDDrawSurface.lpSurface;
	// ������
	pitch = (int)(TheDDrawSurface.lPitch>>1);

	// ����ֱ�Ӷ��Դ����
	/*******************************/

	DrawWaveLine(bb,pitch);

	/*******************************/

	// ��������
	TheDDrawBackBuffer->Unlock(NULL);

}

// ����Ļ���ڴ棩
void DrawCls(USHORT* bb, int lPitch, USHORT color)
{
	
	// �������Ļ��ͬ
	if(lPitch==DRAW_SCREEN_WIDTH){
		
		// �����ɫ
		for(int i=0;i<DRAW_SCREEN_SIZE;i++){
			bb[i] = color;
		}

	// �ж����ڴ�
	}else{

		// �����������ɫ
		for(int x=0;x<DRAW_SCREEN_WIDTH;x++){
			for(int y=0;y<DRAW_SCREEN_HEIGHT;y++){
				bb[x+y*lPitch] = color;
			}		
		}
	
	}
	
}

// ����Ļ������
void DrawClsRect(void)
{
	
	// ���ƾ���
	DrawRect(TheDDrawBackground,&TheRectColorBlack,&TheRectScreen,DRAW_BLT_NORMAL);
	
}

// ����������
void DrawPrimary(void)
{
	
	// ���󱸱��渴�Ƶ�������
	TheDDrawPrimary->Blt(&TheRectScreen,TheDDrawBackBuffer,&TheRectScreen,DDBLT_WAITNOTBUSY,NULL);	

}

// ������ͣ����
void DrawPause(void)
{

	

}

//************************************************************************************************
//*************************** DirectDraw *********************************************************
//************************************************************************************************


// ��ʼ��
bool DirectDrawInit(HWND hwnd)
{

	// ����DirectDraw����
	if(DirectDrawCreate(NULL,&TheDDraw,NULL)!=DD_OK){
		return false;
	}

	// ����Э����ʽ
	if(TheDDraw->SetCooperativeLevel(hwnd,DDSCL_NORMAL)!=DD_OK){
		return false;
	}

	/********************************������****************************************/

	// ��ʼ������ṹ
	DDRAW_INIT_STRUCT(TheDDrawSurface);

	TheDDrawSurface.dwFlags = DDSD_CAPS;
	TheDDrawSurface.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE;

	// ����������
	if(TheDDraw->CreateSurface(&TheDDrawSurface,&TheDDrawPrimary,NULL)!=DD_OK){
		return false;
	}

	// �������ظ�ʽ	
	DDRAW_INIT_STRUCT(TheDDrawPixelFormat);
	// ��ȡ���ظ�ʽ
	TheDDrawPrimary->GetPixelFormat(&TheDDrawPixelFormat);

	// �������16λɫģʽ
	if(TheDDrawPixelFormat.dwRGBBitCount!=DRAW_SCREEN_COLOR){
		return false;
	}

	// �����ü���
	if(TheDDraw->CreateClipper(0,&TheDDrawClipper,NULL)!=DD_OK){
		return false;
	}
	
	// ���òü������ھ��
	if(TheDDrawClipper->SetHWnd(0,hwnd)!=DD_OK){
		return false;
	}

	// �����ü���
	if(TheDDrawPrimary->SetClipper(TheDDrawClipper)!=DD_OK){
		return false;
	}

	// �����󱸱���
	if(!DirectDrawCreateSurface(&TheDDrawBackBuffer,DRAW_SCREEN_WIDTH,DRAW_SCREEN_HEIGHT)){
		return false;
	}

	// ������������
	if(!DirectDrawCreateSurface(&TheDDrawBackground,DRAW_BACKGROUND_WIDTH,DRAW_BACKGROUND_HEIGHT)){
		return false;
	}

	// ����ǰ������
	if(!DirectDrawCreateSurface(&TheDDrawForeground,DRAW_FOREGROUND_WIDTH,DRAW_FOREGROUND_HEIGHT)){
		return false;
	}

	// ����͸��ɫ	
	TheDDrawColorKey.dwColorSpaceHighValue = 0;
	TheDDrawColorKey.dwColorSpaceLowValue = 0;
	TheDDrawBackground->SetColorKey(DDCKEY_SRCBLT,&TheDDrawColorKey);

	// ��ʼ����͸���ṹ
	DDRAW_INIT_STRUCT(TheDDrawAlphaBltfx);

	return true;

}

// ��������
bool DirectDrawCreateSurface(LPDIRECTDRAWSURFACE* s, int w, int h)
{

	// ��ʼ������ṹ
	DDRAW_INIT_STRUCT(TheDDrawSurface);

	// �������϶�ȡ�б������
	TheDDrawSurface.dwFlags = DDSD_CAPS | DDSD_WIDTH | DDSD_HEIGHT;
	TheDDrawSurface.ddsCaps.dwCaps = DDSCAPS_VIDEOMEMORY;
	TheDDrawSurface.dwWidth = w;
	TheDDrawSurface.dwHeight = h;

	// �������϶�ȡ�б���
	if(TheDDraw->CreateSurface(&TheDDrawSurface,s,NULL)!=DD_OK){
		return false;
	}

	return true;

}

// ����
void DirectDrawEnd(void)
{

	// �ͷ�ǰ������
	if(TheDDrawForeground){
		TheDDrawForeground->Release();
		TheDDrawForeground = NULL;
	}

	// �ͷű�������
	if(TheDDrawBackground){
		TheDDrawBackground->Release();
		TheDDrawBackground = NULL;
	}

	// �ͷź󱸱���
	if(TheDDrawBackBuffer){
		TheDDrawBackBuffer->Release();
		TheDDrawBackBuffer = NULL;
	}

	// �ͷ�������
	if(TheDDrawPrimary){
		TheDDrawPrimary->Release();
		TheDDrawPrimary = NULL;
	}

	// ���ټ��а�
	if(TheDDrawClipper){
		TheDDrawClipper->Release();
		TheDDrawClipper = NULL;
	}

	// �ͷ��ڲ�������Դ
	if(TheDDraw){
		TheDDraw->Release();
		TheDDraw = NULL;
	}

}

//************************************************************************************************
//*************************** �� �� �� ȡ ********************************************************
//************************************************************************************************


// ��ȡͼ���ļ�
bool LoadingImageFile(LPTSTR imgFile, int imgSize)
{

	bool flag = false;

	// ��ʼ������ṹ
	DDRAW_INIT_STRUCT(TheDDrawSurface);

	// �������Ǳ���
	if(TheDDrawBackground->Lock(NULL,&TheDDrawSurface,DDLOCK_WAITNOTBUSY,NULL)!=DD_OK){
		return false;
	}

	// ��������
	CHAR *bb = (CHAR *)TheDDrawSurface.lpSurface;

	// ��ȡ�ļ�
	flag = FileGetData(imgFile,bb,imgSize);

	// �������Ǳ���
	TheDDrawBackground->Unlock(NULL);

	// �����ɹ�
	return flag;	

}



//************************************************************************************************
//*************************** �� �� �� �� ********************************************************
//************************************************************************************************

// ���ٻ��ƾ���
void DrawRect(LPDIRECTDRAWSURFACE ddSurface, RECT* rSource, RECT* rTarget, int colorkey)
{

	// ����Դ�����������󱸻���
	TheDDrawBackBuffer->Blt(rTarget,ddSurface,rSource,DDBLT_WAITNOTBUSY|colorkey,NULL);

}

// ���ٻ��ƾ��Σ���͸����
void DrawRectAlpha(LPDIRECTDRAWSURFACE ddSurface, RECT* rSource, RECT* rTarget, int alpha)
{

	// ���ð�͸���̶�
	TheDDrawAlphaBltfx.ddargbScaleFactors.alpha = alpha;

	// ����Դ�����������󱸻���
	TheDDrawBackBuffer->AlphaBlt(rTarget,ddSurface,rSource,DDABLT_WAITNOTBUSY|DDABLT_ALPHASRCNEG,&TheDDrawAlphaBltfx);

}