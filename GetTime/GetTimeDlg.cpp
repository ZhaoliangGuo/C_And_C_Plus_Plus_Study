
// GetTimeDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "GetTime.h"
#include "GetTimeDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include <time.h>
#include <sys/timeb.h>
#include <iostream>  
#include <time.h>  
#include <stdlib.h>  
#include <string.h>  

static LONG initializeLock_gettimeofday = 0;  

int gettimeofday(struct timeval* tp, int* /*tz*/);

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CGetTimeDlg 对话框




CGetTimeDlg::CGetTimeDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CGetTimeDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGetTimeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CGetTimeDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CGetTimeDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CGetTimeDlg 消息处理程序

BOOL CGetTimeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CGetTimeDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CGetTimeDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CGetTimeDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

int gettimeofday(struct timeval* tp, int* /*tz*/) 
{
	static LARGE_INTEGER tickFrequency, epochOffset;

	static bool isInitialized = false;

	LARGE_INTEGER tickNow;

#if !defined(_WIN32_WCE)
	QueryPerformanceCounter(&tickNow);
#else
	tickNow.QuadPart = GetTickCount();
#endif

	if (!isInitialized) 
	{
		if(1 == InterlockedIncrement(&initializeLock_gettimeofday)) 
		{
#if !defined(_WIN32_WCE)
			// For our first call, use "ftime()", so that we get a time with a proper epoch.
			// For subsequent calls, use "QueryPerformanceCount()", because it's more fine-grain.
			struct timeb tb;
			ftime(&tb);

			tp->tv_sec  = (long)tb.time;
			tp->tv_usec = 1000*tb.millitm;

			// Also get our counter frequency:
			QueryPerformanceFrequency(&tickFrequency);
#else
			/* FILETIME of Jan 1 1970 00:00:00. */
			const LONGLONG epoch = 116444736000000000LL;
			FILETIME fileTime;
			LARGE_INTEGER time;
			GetSystemTimeAsFileTime(&fileTime);

			time.HighPart = fileTime.dwHighDateTime;
			time.LowPart = fileTime.dwLowDateTime;

			// convert to from 100ns time to unix timestamp in seconds, 1000*1000*10
			tp->tv_sec = (long)((time.QuadPart - epoch) / 10000000L);

			/*
			GetSystemTimeAsFileTime has just a seconds resolution,
			thats why wince-version of gettimeofday is not 100% accurate, usec accuracy would be calculated like this:
			// convert 100 nanoseconds to usec
			tp->tv_usec= (long)((time.QuadPart - epoch)%10000000L) / 10L;
			*/
			tp->tv_usec = 0;

			// resolution of GetTickCounter() is always milliseconds
			tickFrequency.QuadPart = 1000;
#endif     
			// compute an offset to add to subsequent counter times, so we get a proper epoch:
			epochOffset.QuadPart = tp->tv_sec * tickFrequency.QuadPart 
				                   + (tp->tv_usec * tickFrequency.QuadPart) / 1000000L 
								   - tickNow.QuadPart;

			// next caller can use ticks for time calculation
			isInitialized = true; 
			return 0;
		} 
		else 
		{
			InterlockedDecrement(&initializeLock_gettimeofday);
			// wait until first caller has initialized static values
			while(!isInitialized)
			{
				Sleep(1);
			}
		}
	}

	// adjust our tick count so that we get a proper epoch:
	tickNow.QuadPart += epochOffset.QuadPart;

	tp->tv_sec  =  (long)(tickNow.QuadPart / tickFrequency.QuadPart);
	tp->tv_usec = (long)(((tickNow.QuadPart % tickFrequency.QuadPart) * 1000000L) / tickFrequency.QuadPart);

	return 0;
}



void CGetTimeDlg::OnBnClickedButton1()
{
	struct timeval timeNow;
	gettimeofday(&timeNow, NULL);

	CString strMsg;

}
