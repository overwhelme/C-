#pragma once


// CManager_regist 对话框

class CManager_regist : public CDialog
{
	DECLARE_DYNAMIC(CManager_regist)

public:
	CManager_regist(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CManager_regist();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Manager_regist };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString manager_account;
	CString manager_password;
	CString manager_work_number;
	afx_msg void OnBnClickedmanagerregist();
};
