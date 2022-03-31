#pragma once


// CDeposit 对话框

class CDeposit : public CDialog
{
	DECLARE_DYNAMIC(CDeposit)

public:
	CDeposit(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDeposit();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DEPOSIT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	double m_money;
	afx_msg void OnBnClickeddepositbutton();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	int m_select_typemoney;
	double truemoney(double money);
};
