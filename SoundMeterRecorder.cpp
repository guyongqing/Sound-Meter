#pragma once

// 预编译
#include "stdafx.h"

// 图形绘制
#include "SoundMeterRecorder.h"

// 声音结构
WAVEFORMATEX	TheRecorderWaveFormat;

// 声音设备句柄
HWAVEIN			TheRecorderWaveIn;

// 缓冲区
BYTE			TheRecorderBuffer[RECORDER_BUFFER_COUNT][RECORDER_BUFFER_SIZE];

// 数据备份
BYTE			TheRecorderWaveData[RECORDER_BUFFER_SIZE];

// 声音句柄
PWAVEHDR		TheRecorderWaveHandle[RECORDER_BUFFER_COUNT];

// 系统录音机对象
IRecord*		TheRecorder;

// 缓冲区计数
int TheRecorderBufferIndex = 0;

// 是否在录音状态
bool TheRecorderStatus = false;

//************************************************************************************************
//*************************** 录 音 机   *********************************************************
//************************************************************************************************

// 录音机初始化
bool RecorderInit(HWND hwnd)
{

	// 注册录音机COM对象
	if(FAILED( CoCreateInstance(CLSID_Recorder,NULL,CLSCTX_INPROC_SERVER,IID_MZ_Record,(void **)&TheRecorder))){
      return false;
    }

	// 设定回调窗口
	TheRecorder->SetCallBackWindow(hwnd, RECORDER_MODE);

	// 释放系统录音机
	if(TheRecorder){
		TheRecorder->Release();
	}

	// 准备数据
	for(int i=0;i<RECORDER_BUFFER_COUNT;i++){

		// 申请缓冲区
		ZeroMemory(TheRecorderBuffer[i],RECORDER_BUFFER_SIZE);
		// 分配声音句柄内存
		TheRecorderWaveHandle[i]=reinterpret_cast<PWAVEHDR>(malloc(sizeof(WAVEHDR)));

	}

	// 初始化声音结构
	RecorderSetParameter(RECORDER_SAMPLE_WIDTH,RECORDER_SAMPLE_RATE,RECORDER_CHANNEL_COUNT,WAVE_FORMAT_PCM, RECORDER_BLOCK_ALIGN, RECORDER_BYTES_PER_SEC);

	// 打开录音设备失败
	if(waveInOpen(&TheRecorderWaveIn,WAVE_MAPPER,&TheRecorderWaveFormat,(DWORD)hwnd,NULL,CALLBACK_WINDOW)!=MMSYSERR_NOERROR){
		return false;
	}

	// 初始化声音句柄
	for(int i=0;i<RECORDER_BUFFER_COUNT;i++){

		// 填充声音句柄结构
		TheRecorderWaveHandle[i]->lpData = (LPSTR)TheRecorderBuffer[i];	
		TheRecorderWaveHandle[i]->dwBufferLength = RECORDER_BUFFER_SIZE;
		TheRecorderWaveHandle[i]->dwBytesRecorded = 0;
		TheRecorderWaveHandle[i]->dwUser = 0;
		TheRecorderWaveHandle[i]->dwFlags = 0;
		TheRecorderWaveHandle[i]->dwLoops = 1;
		TheRecorderWaveHandle[i]->lpNext = NULL;
		TheRecorderWaveHandle[i]->reserved = 0;

		// 准备缓冲区
		waveInPrepareHeader(TheRecorderWaveIn,TheRecorderWaveHandle[i],sizeof(WAVEHDR));
		// 添加缓冲区
		waveInAddBuffer(TheRecorderWaveIn,TheRecorderWaveHandle[i],sizeof (WAVEHDR)) ;

	}

	// 声音数据清空
	ZeroMemory(TheRecorderWaveData,RECORDER_BUFFER_SIZE);

	// 给绘图模块发送数据指针
	DrawSetWaveData((SHORT*)TheRecorderWaveData);

	// 返回真
	return true;

}

// 打开录音设备前对参数进行设置
void RecorderSetParameter(WORD sampleWidth, DWORD sampleRate, WORD channelCount, WORD dataType, WORD blockAlign, DWORD bytesPerSec)
{

	// 音频格式类型
	TheRecorderWaveFormat.wFormatTag = dataType;
	// 声道数
	TheRecorderWaveFormat.nChannels = channelCount;
	// 采样频率
	TheRecorderWaveFormat.nSamplesPerSec = sampleRate;
	// 采样宽度
	TheRecorderWaveFormat.wBitsPerSample = sampleWidth;
	// 每个样本的字节数
	TheRecorderWaveFormat.nBlockAlign = blockAlign;
	// 每秒采集的字节数
	TheRecorderWaveFormat.nAvgBytesPerSec = bytesPerSec;

}

// 开始录音
void RecorderStart(void)
{

	// 开始录音
	waveInStart(TheRecorderWaveIn) ;

}

// 停止录音
void RecorderStop(void)
{

	// 停止录音
	waveInReset(TheRecorderWaveIn);

}

// 结束录音
void RecorderEnd(void)
{

	// 关闭设备
	waveInClose(TheRecorderWaveIn);

	// 释放声音句柄
	for(int i=0;i<RECORDER_BUFFER_COUNT;i++){
		if(TheRecorderWaveHandle[i]){free(TheRecorderWaveHandle[i]);}
	}

}

// 处理录音数据
void RecorderData(UINT message, WPARAM  wParam, LPARAM  lParam)
{

	// 已经录音数据
	DWORD size = ((PWAVEHDR)lParam)->dwBytesRecorded;
	LPSTR data = ((PWAVEHDR)lParam)->lpData;

	// 宽度相等
	if(size==RECORDER_BUFFER_SIZE){
		// 复制数据
		CopyMemory(TheRecorderWaveData,data,size);
	}
	
	// 将缓冲区还给系统
	waveInAddBuffer(TheRecorderWaveIn, (PWAVEHDR)lParam, sizeof(WAVEHDR));	

}

// 设备打开
void RecorderOpen(UINT message, WPARAM  wParam, LPARAM  lParam)
{

	// 开始录音
	TheRecorderStatus = true;

}

// 设备关闭
void RecorderClose(UINT message, WPARAM  wParam, LPARAM  lParam)
{

	// 释放缓冲区
	for(int i=0;i<RECORDER_BUFFER_COUNT;i++){
		waveInUnprepareHeader(TheRecorderWaveIn, TheRecorderWaveHandle[i], sizeof (WAVEHDR));
	}

	// 开始录音
	TheRecorderStatus = false;

}