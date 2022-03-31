
// Bank-managementDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "Bank-management.h"
#include "Bank-managementDlg.h"
#include "afxdialogex.h"
#include <winsock.h>
#include "mysql.h"
#include"CRegist.h"
#include"Cuser_operate.h"
#include"CManager_oper.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CString user_Account;
// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CBankmanagementDlg 对话框



CBankmanagementDlg::CBankmanagementDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_BANKMANAGEMENT_DIALOG, pParent)
	, m_account1(_T(""))
	, m_password1(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CBankmanagementDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_account1);
	DDX_Text(pDX, IDC_EDIT2, m_password1);
}

BEGIN_MESSAGE_MAP(CBankmanagementDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_LoginButton, &CBankmanagementDlg::OnBnClickedLoginbutton)

END_MESSAGE_MAP()


// CBankmanagementDlg 消息处理程序

BOOL CBankmanagementDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CBankmanagementDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CBankmanagementDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CBankmanagementDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}




void CBankmanagementDlg::OnBnClickedLoginbutton()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	MYSQL mysqlCon;
	if (m_account1.IsEmpty() || m_password1.IsEmpty())
	{
		MessageBox(_T("用户名和密码不能为空！"), _T("登录提示"));
		return;
	}
	mysql_init(&mysqlCon);
	if (!mysql_real_connect(&mysqlCon, "localhost", "root", "root", "information", 3306, NULL, 0))
	{
		MessageBox(_T("数据库连接失败！"));
		return;
	}
	else
	{
		UpdateData(true);
		mysql_query(&mysqlCon, "set names'GB2312'");
		char select1[1000];
		sprintf_s(select1, "select user_account,user_password from bank_information");
		mysql_real_query(&mysqlCon, select1, (unsigned long)strlen(select1));
		MYSQL_ROW row;
		MYSQL_RES* result;
		result = mysql_store_result(&mysqlCon);
		//选择数据库中的用户和密码，判断是否和编辑框中的用户密码相同
		while ((row = mysql_fetch_row(result)))
		{
			char* Account = row[0];
			char* Password = row[1];
			if ((m_account1 == Account) && (m_password1 == Password))
			{
				user_Account = m_account1;
				MessageBox(_T("登录成功"));
				Cuser_operate user_operate;
				user_operate.DoModal();
				return;
			}
		}
		char select2[1000];
		sprintf_s(select2, "select Account,Password from manager");
		mysql_real_query(&mysqlCon, select2, (unsigned long)strlen(select2));
		result = mysql_store_result(&mysqlCon);
		while ((row = mysql_fetch_row(result)))
		{
			char* Account = row[0];
			char* Password = row[1];
			if ((m_account1 == Account) && (m_password1 == Password))
			{
				MessageBox(_T("登录成功"));
				CManager_oper manager_ope;
				manager_ope.DoModal();
				return;
			}
		}
		MessageBox(_T("登录失败"));
	}
	mysql_close(&mysqlCon);
}



