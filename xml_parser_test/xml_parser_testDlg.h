
// xml_parser_testDlg.h : ͷ�ļ�
//

#pragma once


// Cxml_parser_testDlg �Ի���
class Cxml_parser_testDlg : public CDialogEx
{
// ����
public:
	Cxml_parser_testDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_XML_PARSER_TEST_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonXMLParser_Memory();
	afx_msg void OnBnClickedButtonXMLParser_File();
};
