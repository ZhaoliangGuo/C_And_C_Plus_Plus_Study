
// xml_parser_test.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// Cxml_parser_testApp:
// �йش����ʵ�֣������ xml_parser_test.cpp
//

class Cxml_parser_testApp : public CWinApp
{
public:
	Cxml_parser_testApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern Cxml_parser_testApp theApp;