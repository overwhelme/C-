#pragma once


// Cuser_operate 对话框

class Cuser_operate : public CDialog
{
	DECLARE_DYNAMIC(Cuser_operate)

public:
	Cuser_operate(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~Cuser_operate();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_UserOpe };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	CFont m_font;
	DECLARE_MESSAGE_MAP()
public:
	CString m_repeat_password;
	CButton CButton_query;
	CButton CButton_deposit;
	CButton CButton_drawcash;
	CButton CButton_transfermoney;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedQuery();
	//CString m_balance;
	afx_msg void OnBnClickedenter();
	afx_msg void OnBnClickedDeposit();
	afx_msg void OnBnClickedDrawcash();
	afx_msg void OnBnClickedTransfermoney();
	afx_msg void OnBnClickedSetfont();
};
