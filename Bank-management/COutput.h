#pragma once


// COutput 对话框

class COutput : public CDialog
{
	DECLARE_DYNAMIC(COutput)

public:
	COutput(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~COutput();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_OUTPUTALL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOutput();
	CListCtrl m_List;
	virtual BOOL OnInitDialog();
	CButton CButton_output;
	int select_lookway;
	afx_msg void OnBnClickedRefresh();
	CButton CButton_ascend;
	CButton CButton_look;
	CButton CButton_descend;
};
