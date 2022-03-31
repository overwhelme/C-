// CDeposit.cpp: 实现文件
//

#include "pch.h"
#include "Bank-management.h"
#include "CDeposit.h"
#include "afxdialogex.h"
#include<mysql.h>

struct user
{
	char name[20];
	char telephone[20];
	char identify[20];
	char account[10];
	char password[20];
	char native[20];
	double money;
	int state;
};
extern CString user_Account;
extern double dollar_rate, euro_rate,pound_rate;
// CDeposit 对话框

IMPLEMENT_DYNAMIC(CDeposit, CDialog)

CDeposit::CDeposit(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DEPOSIT, pParent)
	, m_money(0)
	, m_select_typemoney(0)
{

}

CDeposit::~CDeposit()
{
}

void CDeposit::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_money);
	DDX_Radio(pDX, IDC_Select_dollar, m_select_typemoney);
}


BEGIN_MESSAGE_MAP(CDeposit, CDialog)
	ON_BN_CLICKED(IDC_depositButton, &CDeposit::OnBnClickeddepositbutton)
	ON_BN_CLICKED(IDC_BUTTON2, &CDeposit::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CDeposit::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CDeposit::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CDeposit::OnBnClickedButton5)
END_MESSAGE_MAP()


// CDeposit 消息处理程序


void CDeposit::OnBnClickeddepositbutton()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	user us;
	char query[1000];
	MYSQL mysqlCon;
	mysql_init(&mysqlCon);
	mysql_query(&mysqlCon, "set names 'GB2312'");
	if (!mysql_real_connect(&mysqlCon, "localhost", "root", "root", "information", 3306, NULL, 0))
	{
		MessageBox(_T("数据库连接失败"));
		return;
	}
	USES_CONVERSION;
	LPSTR str;
	str = T2A(user_Account);
	strcpy_s(us.account, str);
	double money = truemoney(m_money);
	sprintf_s(query, "update bank_information set user_money=user_money+'%f' where user_account ='%s'", money, us.account);
	if (mysql_query(&mysqlCon, query))
	{
		MessageBox(_T("存款失败"));
		return;
	}
    else MessageBox(_T("存款成功"));
	m_money = 0;
	UpdateData(false);
}


void CDeposit::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	user us;
	char query[1000];
	MYSQL mysqlCon;
	mysql_init(&mysqlCon);
	mysql_query(&mysqlCon, "set names 'GB2312'");
	if (!mysql_real_connect(&mysqlCon, "localhost", "root", "root", "information", 3306, NULL, 0))
	{
		MessageBox(_T("数据库连接失败"));
		return;
	}
	USES_CONVERSION;
	LPSTR str;
	str = T2A(user_Account);
	strcpy_s(us.account, str);
	double money = truemoney(100);
	sprintf_s(query, "update bank_information set user_money=user_money+'%f' where user_account ='%s'", money, us.account);
	if (mysql_query(&mysqlCon, query))
	{
		MessageBox(_T("存款失败"));
		return;
	}
	else MessageBox(_T("存款成功"));
}


void CDeposit::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	user us;
	char query[1000];
	MYSQL mysqlCon;
	mysql_init(&mysqlCon);
	mysql_query(&mysqlCon, "set names 'GB2312'");
	if (!mysql_real_connect(&mysqlCon, "localhost", "root", "root", "information", 3306, NULL, 0))
	{
		MessageBox(_T("数据库连接失败"));
		return;
	}
	USES_CONVERSION;
	LPSTR str;
	str = T2A(user_Account);
	strcpy_s(us.account, str);
	double money = truemoney(200);
	sprintf_s(query, "update bank_information set user_money=user_money+'%f' where user_account ='%s'", money, us.account);
	if (mysql_query(&mysqlCon, query))
	{
		MessageBox(_T("存款失败"));
		return;
	}
	else MessageBox(_T("存款成功"));
}


void CDeposit::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	user us;
	char query[1000];
	MYSQL mysqlCon;
	mysql_init(&mysqlCon);
	mysql_query(&mysqlCon, "set names 'GB2312'");
	if (!mysql_real_connect(&mysqlCon, "localhost", "root", "root", "information", 3306, NULL, 0))
	{
		MessageBox(_T("数据库连接失败"));
		return;
	}
	USES_CONVERSION;
	LPSTR str;
	str = T2A(user_Account);
	strcpy_s(us.account, str);
	double money = truemoney(500);
	sprintf_s(query, "update bank_information set user_money=user_money+'%f' where user_account ='%s'", money, us.account);
	if (mysql_query(&mysqlCon, query))
	{
		MessageBox(_T("存款失败"));
		return;
	}
	else MessageBox(_T("存款成功"));
}


void CDeposit::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	user us;
	char query[1000];
	MYSQL mysqlCon;
	mysql_init(&mysqlCon);
	mysql_query(&mysqlCon, "set names 'GB2312'");
	if (!mysql_real_connect(&mysqlCon, "localhost", "root", "root", "information", 3306, NULL, 0))
	{
		MessageBox(_T("数据库连接失败"));
		return;
	}
	USES_CONVERSION;
	LPSTR str;
	str = T2A(user_Account);
	strcpy_s(us.account, str);
	double money = truemoney(1000);
	sprintf_s(query, "update bank_information set user_money=user_money+'%f' where user_account ='%s'", money, us.account);
	if (mysql_query(&mysqlCon, query))
	{
		MessageBox(_T("存款失败"));
		return;
	}
	else MessageBox(_T("存款成功"));
}

double CDeposit::truemoney(double money)
{
	UpdateData(true);
	switch (m_select_typemoney)
	{
	case 0:
	{
		money = money * dollar_rate;
		break;
	}
	case 1:
	{
		money = money * euro_rate;
		break;
	}
	case 2:
	{
		money = money * 1;
		break;
	}
	case 3:
	{
		money = money * pound_rate;
	}
	}
	return money;
}
