#pragma once


// CReport 对话框

class CReport : public CDialog
{
	DECLARE_DYNAMIC(CReport)

public:
	CReport(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CReport();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_REPORT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedReportbutton();
	CString m_lost_account;
	CString m_lost_ID;
	//CString m_lost_name;
	int m_select_drawcash;
	CButton CButton_report;
	CEdit CButton_lost_account;
	CEdit CButton_lost_ID;
	CButton CButton_select_way;
	afx_msg void OnBnClickedFreeze();
	afx_msg void OnBnClickedUnfreeze();
	CButton CButton_freeze;
	CButton CButton_unfreeze;
	CButton CButton_new_account;
};
