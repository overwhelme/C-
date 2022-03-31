#pragma once


// CSetrate 对话框

class CSetrate : public CDialog
{
	DECLARE_DYNAMIC(CSetrate)

public:
	CSetrate(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CSetrate();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SETRATE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	double m_dollar_rate;
	double m_euro_rate;
	double m_pound_rate;
	afx_msg void OnBnClickedSetrate();
};
