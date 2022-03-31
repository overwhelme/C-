#pragma once


// CManager_oper 对话框

class CManager_oper : public CDialog
{
	DECLARE_DYNAMIC(CManager_oper)

public:
	CManager_oper(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CManager_oper();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ManagerOpe };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedRegist();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickeddelete();
	afx_msg void OnBnClickedUpdate();
	afx_msg void OnBnClickedRport();
	afx_msg void OnBnClickedOutputall();
	double m_dollar_rate;
	double m_euro_rate;
	afx_msg void OnBnClickedSetrate();
	virtual BOOL OnInitDialog();
	afx_msg void Onregistuser();
	afx_msg void Onregistmanager();
	afx_msg void Ondeleteuser();
	afx_msg void Onupdateuserinformation();
	afx_msg void Onreportuser();
	afx_msg void Onoutputuser();
	afx_msg void Onrate();
};
