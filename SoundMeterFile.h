#pragma once

// MZ ��Ȩ�ļ�
#include <MyStoreLib.h>

//************************************************************************************************
//*************************** �ļ����� ***********************************************************
//************************************************************************************************

// ��ȡ����ǰĿ¼
void FileGetPath(void);
// ��ȡ�ļ�·��
void FileGetName(LPTSTR);
// ��ȡ�ļ�����
bool FileGetData(LPTSTR, char*, int);

//************************************************************************************************
//*************************** �� Ȩ �� �� ********************************************************
//************************************************************************************************

// �շ������Ϸ�����֤
bool LicenseVerify(void);