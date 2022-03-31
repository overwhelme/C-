#pragma once


// CDelete 对话框

class CDelete : public CDialog
{
	DECLARE_DYNAMIC(CDelete)

public:
	CDelete(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDelete();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DELETE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_account2;
	CString m_password2;
	afx_msg void OnBnClickeddeleteuser();
	CButton Delete1;
};
