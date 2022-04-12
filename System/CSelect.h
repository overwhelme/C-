#pragma once


// CSelect 对话框

class CSelect : public CDialog
{
	DECLARE_DYNAMIC(CSelect)

public:
	CSelect(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CSelect();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Select };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int m_select;
	CString m_select_information;
	CListCtrl m_List1;
	afx_msg void OnBnClickedSelect();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedRefresh1();
	CString m_select_onbirth;
	CString m_select_downbirth;
	CButton CButton_select;
	CButton CButton_refresh;
	afx_msg void OnPaint();
};
