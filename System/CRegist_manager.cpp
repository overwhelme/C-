// CRegist_manager.cpp: 实现文件
//

#include "pch.h"
#include "System.h"
#include "CRegist_manager.h"
#include "afxdialogex.h"
#include"mysql.h"

// CRegist_manager 对话框

IMPLEMENT_DYNAMIC(CRegist_manager, CDialog)

CRegist_manager::CRegist_manager(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_Regist_manager, pParent)
	, m_username(_T(""))
	, m_password(_T(""))
{

}

CRegist_manager::~CRegist_manager()
{
}

void CRegist_manager::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_username, m_username);
	DDX_Text(pDX, IDC_password, m_password);
}


BEGIN_MESSAGE_MAP(CRegist_manager, CDialog)
	ON_BN_CLICKED(IDC_Regist, &CRegist_manager::OnBnClickedRegist)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CRegist_manager 消息处理程序


void CRegist_manager::OnBnClickedRegist()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	MYSQL mysqlCon;
	mysql_init(&mysqlCon);
	if (0 != mysql_options(&mysqlCon, MYSQL_SET_CHARSET_NAME, "GB2312"))
	{
		MessageBox(_T("mysql_options() failed失败"));
		return;
	}
	if (!mysql_real_connect(&mysqlCon, "localhost", "root", "root", "student_system", 3306, NULL, 0))
	{
		MessageBox(_T("数据库连接失败"));
		return;
	}
    char insert[1000];
	char username[10];
	char password[10];
	USES_CONVERSION;
	LPSTR str;
	str = T2A(m_username);
	strcpy_s(username, str);
	str = T2A(m_password);
	strcpy_s(password, str);
	sprintf_s(insert, "insert into manager(username,password)values('%s','%s')",username,password );
	if (mysql_query(&mysqlCon, insert))
	{
		AfxMessageBox(TEXT("注册失败！"));
		return;
	}
	MessageBox(_T("注册成功"));
	UpdateData(false);
	mysql_close(&mysqlCon);
}


void CRegist_manager::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CDialog::OnPaint()
	CRect rect;
	GetClientRect(&rect);
	CDC   dcMem;
	dcMem.CreateCompatibleDC(&dc);
	CBitmap   bmpBackground;
	bmpBackground.LoadBitmap(IDB_BITMAP2);

	BITMAP   bitmap;
	bmpBackground.GetBitmap(&bitmap);
	CBitmap* pbmpOld = dcMem.SelectObject(&bmpBackground);
	dc.StretchBlt(0, 0, rect.Width(), rect.Height(), &dcMem, 0, 0, bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);
}
