// 预编译
#include "stdafx.h"

// 文件处理
#include "SoundMeterFile.h"

// 路径全局变量
TCHAR	ThePath[MAX_PATH];
TCHAR	TheFileName[MAX_PATH];

//************************************************************************************************
//*************************** 授 权 控 制 ********************************************************
//************************************************************************************************

// 收费软件合法性验证
bool LicenseVerify(void)
{

	TCHAR pszFileName[MAX_PATH] = {0};
    GetModuleFileName(0, pszFileName, MAX_PATH);            // 当前进程EXE的文件名
    MYSTORE_VERIFY_CONTEXT mystore = {0};
    DWORD dwRet = MyStoreVerify(pszFileName, &mystore);     // 验证此文件是否合法

	// 验证合法
	if(dwRet==0){

		// 过期
		if(mystore.Expired){

			return false;
			
		}else{

			// 免费
			if((mystore.Reserved[0]&0x40)==0x40){

				return false;
			
			// 收费
			}else{

				return true;
			
			}
		
		}

	}

	return false;

}

//************************************************************************************************
//*************************** 文件操作 ***********************************************************
//************************************************************************************************

// 获取程序当前目录
void FileGetPath(void)
{

	// 获取
	GetModuleFileName(NULL,ThePath,MAX_PATH);
	
	// 去掉文件名
	for(int i=MAX_PATH;i>0;i--){
		if(ThePath[i]=='\\'){
			break;
		}else{
			ThePath[i]='\0';
		}
	}

}

// 获取文件路径
void FileGetName(LPTSTR fileName)
{

	int j = 0;

	// 复制路径到文件名
	for(int i=0;i<MAX_PATH;i++){

		if(ThePath[i]=='\0'){

			TheFileName[i] = fileName[j];
			if(fileName[j]=='\0'){break;}	
			j++;
		
		}else{

			TheFileName[i] = ThePath[i];

		}

	}

}

// 读取文件数据
bool FileGetData(LPTSTR fileName, char* fileBuffer, int fileSize)
{

	// 获取文件名
	FileGetName(fileName);

	// 文件句柄
	HANDLE hFile = CreateFile(TheFileName,GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
	// 读取字节数
	DWORD dSize = 0;

	// 无法打开文件
	if(hFile==INVALID_HANDLE_VALUE){
		return false;
	}

	// 读取文件
	if(!ReadFile(hFile,fileBuffer,fileSize,&dSize,NULL)){
		return false;
	}

	// 关闭文件句柄
	CloseHandle(hFile);

	return true;

}