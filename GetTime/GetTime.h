
// GetTime.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CGetTimeApp:
// �йش����ʵ�֣������ GetTime.cpp
//

class CGetTimeApp : public CWinApp
{
public:
	CGetTimeApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CGetTimeApp theApp;