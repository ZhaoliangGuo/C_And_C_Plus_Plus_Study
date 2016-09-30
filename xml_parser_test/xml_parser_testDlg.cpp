
// xml_parser_testDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "xml_parser_test.h"
#include "xml_parser_testDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#import "msxml4.dll"
//using namespace MSXML2;
#include <string>
using namespace std;

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


// Cxml_parser_testDlg 对话框




Cxml_parser_testDlg::Cxml_parser_testDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(Cxml_parser_testDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Cxml_parser_testDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(Cxml_parser_testDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &Cxml_parser_testDlg::OnBnClickedButtonXMLParser_Memory)
	ON_BN_CLICKED(IDC_BUTTON2, &Cxml_parser_testDlg::OnBnClickedButtonTest)
END_MESSAGE_MAP()


// Cxml_parser_testDlg 消息处理程序

BOOL Cxml_parser_testDlg::OnInitDialog()
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

void Cxml_parser_testDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void Cxml_parser_testDlg::OnPaint()
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
HCURSOR Cxml_parser_testDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


// 从内存中读取xml内容进行解析
void Cxml_parser_testDlg::OnBnClickedButtonXMLParser_Memory()
{
	char szXML[] = "<?xml version=\"1.0\" encoding=\"utf-8\"?> \
					<MediaServerRequest> \
						<ServerAccount>admin</ServerAccount> \
						<ServerPassword>123456</ServerPassword> \
					</MediaServerRequest>";

	IXMLDOMDocumentPtr		    m_pXMLDoc;      // 指向整个XML文档  
	IXMLDOMElementPtr		    m_pRootElement; // 指向根节点

	// 创建Document对象
	HRESULT hr = CoCreateInstance(CLSID_DOMDocument,
								  NULL,
		                          CLSCTX_INPROC_SERVER,
								  IID_IXMLDOMDocument,
								  (void**)&m_pXMLDoc);

	if(SUCCEEDED(hr))
	{
		VARIANT_BOOL bIsSuccessful;
		hr = m_pXMLDoc->loadXML(_bstr_t(szXML), &bIsSuccessful); // 加载要解析的XML文件
		if (!bIsSuccessful)
		{
			AfxMessageBox("m_pXMLDoc->loadXML Fail");
			return ;
		}
	}

	hr = m_pXMLDoc->get_documentElement(&m_pRootElement);
	if (FAILED(hr))
	{
		AfxMessageBox("m_pXMLDoc->get_documentElement Fail");
		return ;
	}

	// 定义访问XML的指针
	IXMLDOMNodePtr	pXMLNode	 = NULL; // 指向第2层节点
	IXMLDOMNodePtr	pNextXMLNode = NULL; // 指向第2层的下一个节点

	BSTR bstrName = NULL;
	BSTR bstrText = NULL;

	hr = m_pRootElement->get_firstChild(&pXMLNode); 
	if (FAILED(hr))
	{
		AfxMessageBox("m_pRootElement->get_firstChild Fail");
		return ;
	}

	CString strServerAcount("");
	CString strServerPassword("");

	while(SUCCEEDED(hr) && (pXMLNode != NULL))
	{
		USES_CONVERSION;

		bstrName = NULL;
		bstrText = NULL;

		// 获取节点的名字
		pXMLNode->get_nodeName(&bstrName);

		// 获取节点的内容
		pXMLNode->get_text(&bstrText);     

		_bstr_t bstr_t(bstrText);
		string strTest(bstr_t);
		const char* lpszText = strTest.c_str();

		if(!wcscmp(bstrName, L"ServerAccount"))
		{
			if (0 != strlen(lpszText))
			{
				strServerAcount.Format("%s", lpszText);
			}
		}
		else if(!wcscmp(bstrName, L"ServerPassword"))
		{
			if (0 != strlen(lpszText))
			{
				strServerPassword.Format("%s", lpszText);
			}	
		}

		pNextXMLNode = NULL;
		pXMLNode->get_nextSibling(&pNextXMLNode); // 指向下一个2级节点
		pXMLNode = pNextXMLNode;

		if (NULL != bstrName)
		{
			SysFreeString(bstrName);
			bstrName = NULL;
		}

		if (NULL != bstrText)
		{
			SysFreeString(bstrText);
			bstrText = NULL;
		}
	}

	CString strMsg("");
	strMsg = "解析结果:\n strServerAcount: ";
	strMsg += strServerAcount;
	strMsg += "\n strServerPassword: ";
	strMsg += strServerPassword;

	AfxMessageBox(strMsg);
}

void Cxml_parser_testDlg::OnBnClickedButtonTest()
{
	/*for (int i = 0; i < 10000; i++)
	{
	OnBnClickedButtonXMLParser_Memory();
	}

	AfxMessageBox("Done");*/
}
