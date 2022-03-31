#pragma once


// CRegist 对话框

class CRegist : public CDialog
{
	DECLARE_DYNAMIC(CRegist)

public:
	CRegist(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CRegist();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_REGIST };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_name;
	CString m_telephone;
	CString m_ID;
	CString m_password2;
	CString m_confirmPassword2;
	CString m_account2;
	afx_msg void OnBnClickedRegistbutton();
	int m_money1;
	CComboBox m_jg1;
	virtual BOOL OnInitDialog();
	CString user_jg1;
};
