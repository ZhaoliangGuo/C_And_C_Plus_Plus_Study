// pxPlayground.cpp : 定义控制台应用程序的入口点。
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

