// pxPlayground.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <windows.h>
#include <iostream>
using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	SYSTEM_INFO sysInfo;
	::ZeroMemory( &sysInfo, sizeof( SYSTEM_INFO ) );

	::GetSystemInfo( &sysInfo );

	cout << sysInfo.dwPageSize << endl;

	return 0;
}

