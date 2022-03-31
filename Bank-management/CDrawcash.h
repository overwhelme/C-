#pragma once


// CDrawcash 对话框

class CDrawcash : public CDialog
{
	DECLARE_DYNAMIC(CDrawcash)

public:
	CDrawcash(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDrawcash();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DRAWCASH };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	double m_money1;
	afx_msg void OnBnClickedDraw100();
	CButton CButton_draw100;
	CButton CButton_draw200;
	CButton CButton_draw500;
	CButton CButton_draw1000;
	afx_msg void OnBnClickedDraw200();
	afx_msg void OnBnClickedDraw500();
	afx_msg void OnBnClickedDraw1000();
	CButton CButton_drawcash;
	afx_msg void OnBnClickedDrawcashbutton();
	double truemoney(double money);
	int m_select_moneytype;
};
