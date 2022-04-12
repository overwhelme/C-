
// SystemDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "System.h"
#include "SystemDlg.h"
#include "afxdialogex.h"
#include"mysql.h"
#include"COperator.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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


// CSystemDlg 对话框



CSystemDlg::CSystemDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SYSTEM_DIALOG, pParent)
	, user_name(_T(""))
	, pass_word(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSystemDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_username, user_name);
	DDX_Text(pDX, IDC_password, pass_word);
}

BEGIN_MESSAGE_MAP(CSystemDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_Connect, &CSystemDlg::OnBnClickedConnect)
END_MESSAGE_MAP()


// CSystemDlg 消息处理程序

BOOL CSystemDlg::OnInitDialog()
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

void CSystemDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CSystemDlg::OnPaint()
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
HCURSOR CSystemDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CSystemDlg::OnBnClickedConnect()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	MYSQL mysqlCon;//定义MYSQL类的对象
	if (user_name.IsEmpty() || pass_word.IsEmpty())
	{
		MessageBox(_T("用户名和密码不能位空！"), _T("登录提示"));
		return;
	}
	mysql_init(&mysqlCon);//初始化MYSQL对象
	if (0 != mysql_options(&mysqlCon, MYSQL_SET_CHARSET_NAME, "GB2312"))
	{
		MessageBox(_T("mysql_options() failed失败"));
		return;
	}//设置字符格式"GB2312"
	if (!mysql_real_connect(&mysqlCon, "localhost", "root", "root", "student_system", 3306, NULL, 0))
	{
		MessageBox(_T("数据库连接失败!"));
		return;
	}//连接数据库，"localhost"代表是本地地址，"root"分别代表为账号和密码，"student_sysytem"是数据库名
	else
	{
		UpdateData(true);
		//mysql_query(&mysqlCon, "set names 'GB2312'");
		char select[1000];
		sprintf_s(select, "select username,password from manager");//读取数据库中的数据表manager中的账号密码
		mysql_real_query(&mysqlCon, select, (unsigned long)strlen(select));//执行查询操作
		MYSQL_ROW row;
		MYSQL_RES* result;
		result = mysql_store_result(&mysqlCon);
		while ((row = mysql_fetch_row(result)))
		{
			char* Username = row[0];
			char* Password = row[1];
			if ((user_name == Username) && (pass_word == Password))//依次对比实现账号密码的匹配
			{
				MessageBox(_T("登录成功"));
				COperator oper;
				oper.DoModal();//谈出新的对话框
				return;
			}
		}
		MessageBox(_T("登录失败"));
	}
	mysql_close(&mysqlCon);//释放定义的MYSQL对象所占的内存
}
