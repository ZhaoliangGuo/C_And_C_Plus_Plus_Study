
// app_crash_manager.h : PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号


// Capp_crash_managerApp:
// 有关此类的实现，请参阅 app_crash_manager.cpp
//

class Capp_crash_managerApp : public CWinApp
{
public:
	Capp_crash_managerApp();

// 重写
public:
	virtual BOOL InitInstance();

// 实现

	DECLARE_MESSAGE_MAP()
};

extern Capp_crash_managerApp theApp;