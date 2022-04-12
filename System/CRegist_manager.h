#pragma once


// CRegist_manager 对话框

class CRegist_manager : public CDialog
{
	DECLARE_DYNAMIC(CRegist_manager)

public:
	CRegist_manager(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CRegist_manager();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Regist_manager };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_username;
	CString m_password;
	afx_msg void OnBnClickedRegist();
	afx_msg void OnPaint();
};
