
// app_crash_manager.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// Capp_crash_managerApp:
// �йش����ʵ�֣������ app_crash_manager.cpp
//

class Capp_crash_managerApp : public CWinApp
{
public:
	Capp_crash_managerApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern Capp_crash_managerApp theApp;