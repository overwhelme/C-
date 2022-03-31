#pragma once


// CTransfer 对话框

class CTransfer : public CDialog
{
	DECLARE_DYNAMIC(CTransfer)

public:
	CTransfer(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CTransfer();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TRANSFER };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_accept_account;
	double m_transfermoney;
	//CString m_accept_name;
	afx_msg void OnBnClickedTransferbutton();
	double m_procedure_money;
};
