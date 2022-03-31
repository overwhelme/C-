#pragma once


// CUpdate 对话框

class CUpdate : public CDialog
{
	DECLARE_DYNAMIC(CUpdate)

public:
	CUpdate(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CUpdate();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_UPDATE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_newpassword;
	CString m_newtelephone;
	CComboBox CButton_newnative;
//	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedUpdate();
	int m_select;
	CString m_update_account;
	CString m_newnative;
};
