
// xml_parser_testDlg.cpp : ʵ���ļ�
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

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// Cxml_parser_testDlg �Ի���




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


// Cxml_parser_testDlg ��Ϣ�������

BOOL Cxml_parser_testDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void Cxml_parser_testDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR Cxml_parser_testDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


// ���ڴ��ж�ȡxml���ݽ��н���
void Cxml_parser_testDlg::OnBnClickedButtonXMLParser_Memory()
{
	char szXML[] = "<?xml version=\"1.0\" encoding=\"utf-8\"?> \
					<MediaServerRequest> \
						<ServerAccount>admin</ServerAccount> \
						<ServerPassword>123456</ServerPassword> \
					</MediaServerRequest>";

	IXMLDOMDocumentPtr		    m_pXMLDoc;      // ָ������XML�ĵ�  
	IXMLDOMElementPtr		    m_pRootElement; // ָ����ڵ�

	// ����Document����
	HRESULT hr = CoCreateInstance(CLSID_DOMDocument,
								  NULL,
		                          CLSCTX_INPROC_SERVER,
								  IID_IXMLDOMDocument,
								  (void**)&m_pXMLDoc);

	if(SUCCEEDED(hr))
	{
		VARIANT_BOOL bIsSuccessful;
		hr = m_pXMLDoc->loadXML(_bstr_t(szXML), &bIsSuccessful); // ����Ҫ������XML�ļ�
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

	// �������XML��ָ��
	IXMLDOMNodePtr	pXMLNode	 = NULL; // ָ���2��ڵ�
	IXMLDOMNodePtr	pNextXMLNode = NULL; // ָ���2�����һ���ڵ�

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

		// ��ȡ�ڵ������
		pXMLNode->get_nodeName(&bstrName);

		// ��ȡ�ڵ������
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
		pXMLNode->get_nextSibling(&pNextXMLNode); // ָ����һ��2���ڵ�
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
	strMsg = "�������:\n strServerAcount: ";
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
