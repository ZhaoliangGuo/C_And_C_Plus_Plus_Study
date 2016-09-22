#pragma once 
#include <windows.h>  
#include <DbgHelp.h>  
#include <stdlib.h>  
#include <stdio.h>

#pragma comment(lib, "dbghelp.lib")  

#include "pxMiniDump.h"

#ifndef _M_IX86  
#error "The following code only works for x86!"  
#endif  

BOOL PxDirExists(LPCTSTR pszPath)
{
	DWORD dwAttributes = ::GetFileAttributes(pszPath);

	if (dwAttributes == INVALID_FILE_ATTRIBUTES) {
		DWORD dwErr = ::GetLastError();

		if (dwErr == ERROR_ACCESS_DENIED)
			return TRUE;

		return FALSE;
	}

	return (dwAttributes & FILE_ATTRIBUTE_DIRECTORY) ? TRUE : FALSE;
}

BOOL PxCreateDir(LPCTSTR pszPath)
{
	if (!PxDirExists(pszPath) && !CreateDirectory(pszPath, NULL))
		return FALSE;

	return TRUE;
}

inline BOOL IsDataSectionNeeded(const WCHAR* pModuleName)  
{  
	if(pModuleName == 0)  
	{  
		return FALSE;  
	}  

	WCHAR szFileName[_MAX_FNAME] = L"";  
	_wsplitpath(pModuleName, NULL, NULL, szFileName, NULL);  

	if(wcsicmp(szFileName, L"ntdll") == 0) 
	{
		return TRUE;  
	}
		
	return FALSE;  
}  

inline BOOL CALLBACK MiniDumpCallback(PVOID pParam,  
	const PMINIDUMP_CALLBACK_INPUT   pInput,  
	PMINIDUMP_CALLBACK_OUTPUT        pOutput)  
{  
	if(pInput == 0 || pOutput == 0)  
		return FALSE;  

	switch(pInput->CallbackType)  
	{  
	case ModuleCallback:  
		if(pOutput->ModuleWriteFlags & ModuleWriteDataSeg)  
			if(!IsDataSectionNeeded(pInput->Module.FullPath))  
				pOutput->ModuleWriteFlags &= (~ModuleWriteDataSeg);  
	case IncludeModuleCallback:  
	case IncludeThreadCallback:  
	case ThreadCallback:  
	case ThreadExCallback:  
		return TRUE;  
	default:;  
	}  

	return FALSE;  
}  

inline void CreateMiniDump(PEXCEPTION_POINTERS pep, LPCTSTR strFileName)  
{  
	char strDumpPath[_MAX_PATH] = {0};
	sprintf_s(strDumpPath,_MAX_PATH, ".\\DumpFile");
	if (!PxDirExists((LPCTSTR)strDumpPath))
	{
		PxCreateDir((LPCTSTR)strDumpPath);
	}

	char szDumpFileName[_MAX_PATH] = {0};
	SYSTEMTIME sysTime; 
	GetLocalTime(&sysTime); 
	sprintf(szDumpFileName, "%s\\DumpFile-%4d-%02d-%02d-%02d-%02d-%02d-%03d.dmp",
		strDumpPath,
		sysTime.wYear,
		sysTime.wMonth,
		sysTime.wDay,
		sysTime.wHour,
		sysTime.wMinute, 
		sysTime.wSecond,
		sysTime.wMilliseconds);

	HANDLE hFile = CreateFile((LPCTSTR)szDumpFileName, 
							  GENERIC_READ | GENERIC_WRITE,  
							  FILE_SHARE_WRITE, 
							  NULL, 
							  CREATE_ALWAYS, 
							  FILE_ATTRIBUTE_NORMAL, 
							  NULL);  

	if((hFile != NULL) && (hFile != INVALID_HANDLE_VALUE))  
	{  
		MINIDUMP_EXCEPTION_INFORMATION mdei;  
		mdei.ThreadId           = GetCurrentThreadId();  
		mdei.ExceptionPointers  = pep;  
		mdei.ClientPointers     = NULL;  

		MINIDUMP_CALLBACK_INFORMATION mci;  
		mci.CallbackRoutine     = (MINIDUMP_CALLBACK_ROUTINE)MiniDumpCallback;  
		mci.CallbackParam       = 0;  

		::MiniDumpWriteDump(::GetCurrentProcess(), 
							::GetCurrentProcessId(), 
							hFile, 
							MiniDumpNormal, 
							//MiniDumpWithFullMemory, // modified by ZL Guo
							(pep != 0) ? &mdei : 0, 
							NULL, 
							&mci);  

		CloseHandle(hFile);  
	}  
}  

LONG __stdcall MyUnhandledExceptionFilter(PEXCEPTION_POINTERS pExceptionInfo)  
{ 
	CreateMiniDump(pExceptionInfo, "");  

	return EXCEPTION_EXECUTE_HANDLER;  
}  

// 此函数一旦成功调用，之后对 SetUnhandledExceptionFilter 的调用将无效  
void DisableSetUnhandledExceptionFilter()  
{  
	void* addr = (void*)GetProcAddress(LoadLibrary("kernel32.dll"),  
						"SetUnhandledExceptionFilter");  

	if (addr)  
	{  
		unsigned char code[16];  
		int size = 0;  

		code[size++] = 0x33;  
		code[size++] = 0xC0;  
		code[size++] = 0xC2;  
		code[size++] = 0x04;  
		code[size++] = 0x00;  

		DWORD dwOldFlag, dwTempFlag;  
		VirtualProtect(addr, size, PAGE_READWRITE, &dwOldFlag);  
		WriteProcessMemory(GetCurrentProcess(), addr, code, size, NULL);  
		VirtualProtect(addr, size, dwOldFlag, &dwTempFlag);  
	}  
}  

void InitMinDump()  
{  
	//注册异常处理函数  
	SetUnhandledExceptionFilter(MyUnhandledExceptionFilter);  

	//使SetUnhandledExceptionFilter  
	DisableSetUnhandledExceptionFilter();  
}  