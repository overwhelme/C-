#pragma once


// COperator 对话框

class COperator : public CDialog
{
	DECLARE_DYNAMIC(COperator)

public:
	COperator(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~COperator();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Operator };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void Oninsertmanager();
	CListCtrl m_List;
	afx_msg void OnBnClickedOutlook();
	afx_msg void Oninsertstudent();
	afx_msg void OnBnClickedRefresh();
	afx_msg void Onupdatainfromation();
	afx_msg void OnRclickMlist(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRdblclkMlist(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void Ondelete();
	CString m_use_select;
	afx_msg void OnClickMlist(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclkMlist(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnEndlabeleditMlist(NMHDR* pNMHDR, LRESULT* pResult);
};
