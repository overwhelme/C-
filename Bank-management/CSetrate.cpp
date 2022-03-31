// CSetrate.cpp: 实现文件
//

#include "pch.h"
#include "Bank-management.h"
#include "CSetrate.h"
#include "afxdialogex.h"


double dollar_rate = 0, euro_rate = 0,pound_rate=0;
// CSetrate 对话框

IMPLEMENT_DYNAMIC(CSetrate, CDialog)

CSetrate::CSetrate(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_SETRATE, pParent)
	, m_dollar_rate(7)
	, m_euro_rate(10)
	, m_pound_rate(8)
{

}

CSetrate::~CSetrate()
{
}

void CSetrate::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_dollar_rate, m_dollar_rate);
	DDX_Text(pDX, IDC_euro_rate, m_euro_rate);
	DDX_Text(pDX, IDC_pound_rate, m_pound_rate);
}


BEGIN_MESSAGE_MAP(CSetrate, CDialog)
	ON_BN_CLICKED(IDC_Setrate, &CSetrate::OnBnClickedSetrate)
END_MESSAGE_MAP()


// CSetrate 消息处理程序


void CSetrate::OnBnClickedSetrate()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	dollar_rate = m_dollar_rate;
	euro_rate = m_euro_rate;
	pound_rate = m_pound_rate;
	MessageBox(_T("已经更新汇率"), _T("消息提示"), MB_OK);
}
