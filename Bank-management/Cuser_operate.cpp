// Cuser_operate.cpp: 实现文件
//

#include "pch.h"
#include "Bank-management.h"
#include "Cuser_operate.h"
#include "afxdialogex.h"
#include"mysql.h"
#include"CDeposit.h"
#include"CDrawcash.h"
#include"CTransfer.h"

// Cuser_operate 对话框
extern CString user_Account;

IMPLEMENT_DYNAMIC(Cuser_operate, CDialog)

Cuser_operate::Cuser_operate(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_UserOpe, pParent)
	, m_repeat_password(_T(""))
	//, m_balance(_T(""))
{

}

Cuser_operate::~Cuser_operate()
{
}

void Cuser_operate::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_repreat_password, m_repeat_password);
	DDX_Control(pDX, IDC_QUERY, CButton_query);
	DDX_Control(pDX, IDC_DEPOSIT, CButton_deposit);
	DDX_Control(pDX, IDC_DRAWCASH, CButton_drawcash);
	DDX_Control(pDX, IDC_TRANSFERMONEY, CButton_transfermoney);
	//DDX_Text(pDX, IDC_balance, m_balance);
}


BEGIN_MESSAGE_MAP(Cuser_operate, CDialog)
	ON_BN_CLICKED(IDC_QUERY, &Cuser_operate::OnBnClickedQuery)
	ON_BN_CLICKED(IDC_enter, &Cuser_operate::OnBnClickedenter)
	ON_BN_CLICKED(IDC_DEPOSIT, &Cuser_operate::OnBnClickedDeposit)
	ON_BN_CLICKED(IDC_DRAWCASH, &Cuser_operate::OnBnClickedDrawcash)
	ON_BN_CLICKED(IDC_TRANSFERMONEY, &Cuser_operate::OnBnClickedTransfermoney)
	ON_BN_CLICKED(IDC_SETFONT, &Cuser_operate::OnBnClickedSetfont)
END_MESSAGE_MAP()


// Cuser_operate 消息处理程序


BOOL Cuser_operate::OnInitDialog()
{
	CDialog::OnInitDialog();
	CButton_query.EnableWindow(0);
	CButton_deposit.EnableWindow(0);
	CButton_drawcash.EnableWindow(0);
	CButton_transfermoney.EnableWindow(0);
	
	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void Cuser_operate::OnBnClickedQuery()
{
	// TODO: 在此添加控件通知处理程序代码
	MYSQL mysqlCon;
	mysql_init(&mysqlCon);
	MYSQL_ROW row;
	MYSQL_RES* result;
	if (!mysql_real_connect(&mysqlCon, "localhost", "root", "root", "information", 3306, NULL, 0))
	{
		MessageBox(_T("数据库连接失败"));
		return;
	}
	else
	{
		mysql_query(&mysqlCon, "set names 'GB2312'");
		char query[1000];
		CString money;
		sprintf_s(query, "select user_account,user_money from bank_information");
		mysql_real_query(&mysqlCon, query, (unsigned long)strlen(query));
		result = mysql_store_result(&mysqlCon);
		while ((row = mysql_fetch_row(result)))
		{
			char* Account = row[0];
			char* Money = row[1];
			if (Account == user_Account)
			{
				money = Money;
				MessageBox(money+_T("元人民币"), _T("您的余额为"));
				break;
			}
		}
	}
}


void Cuser_operate::OnBnClickedenter()
{
	// TODO: 在此添加控件通知处理程序代码
	MYSQL mysqlCon;
	mysql_init(&mysqlCon);
	if (!mysql_real_connect(&mysqlCon, "localhost", "root", "root", "information", 3306, NULL, 0))
	{
		MessageBox(_T("数据库连接失败！"));
		return ;
	}
	else
	{
		UpdateData(true);
		mysql_query(&mysqlCon, "set names'GB2312'");
		char select[1000];
		sprintf_s(select, "select user_password from bank_information");
		mysql_real_query(&mysqlCon, select, (unsigned long)strlen(select));
		MYSQL_ROW row;
		MYSQL_RES* result;
		result = mysql_store_result(&mysqlCon);
		while ((row = mysql_fetch_row(result)))
		{
			char* Password = row[0];
			if (m_repeat_password == Password)
			{
				CButton_query.EnableWindow(1);
				CButton_deposit.EnableWindow(1);
				CButton_drawcash.EnableWindow(1);
				CButton_transfermoney.EnableWindow(1);
				return;
			}
		}
		MessageBox(_T("密码输入错误"), _T("进入失败"), MB_OK);
		return;
	}
}


void Cuser_operate::OnBnClickedDeposit()
{
	// TODO: 在此添加控件通知处理程序代码
	MessageBox(_T("正在进入，请等待"));
	CDeposit deposit;
	deposit.DoModal();
}


void Cuser_operate::OnBnClickedDrawcash()
{
	// TODO: 在此添加控件通知处理程序代码
	MessageBox(_T("正在进入，请等待"));
	CDrawcash drawcash;
	drawcash.DoModal();
}


void Cuser_operate::OnBnClickedTransfermoney()
{
	// TODO: 在此添加控件通知处理程序代码
	MessageBox(_T("正在进入，请等待"));
	CTransfer transfer;
	transfer.DoModal();
}


void Cuser_operate::OnBnClickedSetfont()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strFontName;
	LOGFONT lf;
	memset(&lf, 0, sizeof(LOGFONT));
	_tcscpy_s(lf.lfFaceName, LF_FACESIZE, _T("宋体"));
	CFontDialog fontDlg(&lf);
	if (IDOK == fontDlg.DoModal())
	{
		if (m_font.m_hObject) m_font.DeleteObject();
		m_font.CreateFontIndirect(fontDlg.m_cf.lpLogFont);
		GetDlgItem(IDC_QUERY)->SetFont(&m_font);
		GetDlgItem(IDC_DEPOSIT)->SetFont(&m_font);
		GetDlgItem(IDC_DRAWCASH)->SetFont(&m_font);
		GetDlgItem(IDC_TRANSFERMONEY)->SetFont(&m_font);
		GetDlgItem(IDC_enter)->SetFont(&m_font);
		GetDlgItem(IDCANCEL)->SetFont(&m_font);
		GetDlgItem(IDC_SETFONT)->SetFont(&m_font);
	}
}
