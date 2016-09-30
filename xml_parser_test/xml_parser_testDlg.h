
// xml_parser_testDlg.h : 头文件
//

#pragma once


// Cxml_parser_testDlg 对话框
class Cxml_parser_testDlg : public CDialogEx
{
// 构造
public:
	Cxml_parser_testDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_XML_PARSER_TEST_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonXMLParser_Memory();
	afx_msg void OnBnClickedButtonXMLParser_File();
};
