#pragma once

// 系统录音类
#include <IRecorder.h>
#include <IRecorder_Guid.h>

// 绘图控制
#include "SoundMeterDraw.h"

// 初始数据
#define RECORDER_SAMPLE_WIDTH		16			// 采样宽度
#define RECORDER_SAMPLE_RATE		32000		// 采样率
#define RECORDER_BYTES_PER_SEC		64000		// 每秒采样字节数
#define RECORDER_CHANNEL_COUNT		1			// 声道数
#define RECORDER_BLOCK_ALIGN		1			// 每个样本的字节数
#define RECORDER_BUFFER_SIZE		1440		// 缓冲区大小
#define RECORDER_BUFFER_NUMBER		720			// 缓冲区彩样数
#define RECORDER_BUFFER_COUNT		64			// 缓冲区数量

//************************************************************************************************
//*************************** 录 音 机   *********************************************************
//************************************************************************************************

// 录音机初始化
bool RecorderInit(HWND);
// 打开录音设备前对参数进行设置
void RecorderSetParameter(WORD, DWORD, WORD, WORD, WORD, DWORD);
// 开始录音
void RecorderStart(void);
// 停止录音
void RecorderStop(void);
// 暂停录音
void RecorderPause(void);
// 结束录音
void RecorderEnd(void);
// 处理音频数据
void RecorderData(UINT, WPARAM, LPARAM);
// 设备打开
void RecorderOpen(UINT, WPARAM, LPARAM);
// 设备关闭
void RecorderClose(UINT, WPARAM, LPARAM);