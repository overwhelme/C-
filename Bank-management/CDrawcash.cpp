// CDrawcash.cpp: 实现文件
//

#include "pch.h"
#include "Bank-management.h"
#include "CDrawcash.h"
#include "afxdialogex.h"
#include"mysql.h"
#include<string>

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
// CDrawcash 对话框
extern CString user_Account;
double alldrawmoney = 0;
extern double dollar_rate, euro_rate, pound_rate;
IMPLEMENT_DYNAMIC(CDrawcash, CDialog)

CDrawcash::CDrawcash(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DRAWCASH, pParent)
	, m_money1(0)
	, m_select_moneytype(0)
{

}

CDrawcash::~CDrawcash()
{
}

void CDrawcash::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_money1);
	DDX_Control(pDX, IDC_DRAW100, CButton_draw100);
	DDX_Control(pDX, IDC_DRAW200, CButton_draw200);
	DDX_Control(pDX, IDC_DRAW500, CButton_draw500);
	DDX_Control(pDX, IDC_DRAW1000, CButton_draw1000);
	DDX_Control(pDX, IDC_DRAWCASHBUTTON, CButton_drawcash);
	DDX_Radio(pDX, IDC_Select_dollar, m_select_moneytype);
}


BEGIN_MESSAGE_MAP(CDrawcash, CDialog)
	ON_BN_CLICKED(IDC_DRAW100, &CDrawcash::OnBnClickedDraw100)
	ON_BN_CLICKED(IDC_DRAW200, &CDrawcash::OnBnClickedDraw200)
	ON_BN_CLICKED(IDC_DRAW500, &CDrawcash::OnBnClickedDraw500)
	ON_BN_CLICKED(IDC_DRAW1000, &CDrawcash::OnBnClickedDraw1000)
	ON_BN_CLICKED(IDC_DRAWCASHBUTTON, &CDrawcash::OnBnClickedDrawcashbutton)
END_MESSAGE_MAP()


// CDrawcash 消息处理程序


void CDrawcash::OnBnClickedDraw100()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	user us;
	MYSQL mysqlCon;
	mysql_init(&mysqlCon);
	CString money;
	MYSQL_ROW row;
	MYSQL_RES* result;
	if (!mysql_real_connect(&mysqlCon, "localhost", "root", "root", "information", 3306, NULL, 0))
	{
		MessageBox(_T("数据库连接失败"));
		return;
	}
	mysql_query(&mysqlCon, "set names 'GB2312'");
	char query[1000];
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
			break;
		}
	}
	double drawmoney = truemoney(100);
	std::string user_money = CW2A(money.GetString());
	double sum = atof(user_money.c_str());
	if (sum < drawmoney)
	{
		MessageBox(_T("余额不足"), _T("取款失败"));
		CButton_draw100.EnableWindow(0);
		CButton_draw200.EnableWindow(0);
		CButton_draw500.EnableWindow(0);
		CButton_draw1000.EnableWindow(0);
		return;
	}
	else
	{
		USES_CONVERSION;
		LPSTR str;
		str = T2A(user_Account);
		strcpy_s(us.account, str);
		sprintf_s(query, "update bank_information set user_money=user_money-'%f' where user_account ='%s'", drawmoney, us.account);
		if (mysql_query(&mysqlCon, query))
		{
			MessageBox(_T("取款失败"));
			return;
		}
		else MessageBox(_T("取款成功"));
		alldrawmoney += drawmoney;
		int k;
		k = MessageBox(_T("继续取钱吗？"), _T("取钱确认"), MB_YESNO);
		if (k == IDYES)
		{
			if (alldrawmoney > 2000)
			{
				MessageBox(_T("已经超过了今日取款的上限,无法取款"), _T("取款提示"), MB_ICONSTOP);
				CButton_draw100.EnableWindow(0);
				CButton_draw200.EnableWindow(0);
				CButton_draw500.EnableWindow(0);
				CButton_draw1000.EnableWindow(0);
				CButton_drawcash.EnableWindow(0);
				return;
			}
		}
		else if (k == IDNO)
		{
			CButton_draw100.EnableWindow(0);
			CButton_draw200.EnableWindow(0);
			CButton_draw500.EnableWindow(0);
			CButton_draw1000.EnableWindow(0);
			CButton_drawcash.EnableWindow(0);
		}
	}
}


void CDrawcash::OnBnClickedDraw200()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	user us;
	MYSQL mysqlCon;
	mysql_init(&mysqlCon);
	CString money;
	MYSQL_ROW row;
	MYSQL_RES* result;
	if (!mysql_real_connect(&mysqlCon, "localhost", "root", "root", "information", 3306, NULL, 0))
	{
		MessageBox(_T("数据库连接失败"));
		return;
	}
	mysql_query(&mysqlCon, "set names 'GB2312'");
	char query[1000];
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
			break;
		}
	}
	double drawmoney = truemoney(200);
	std::string user_money = CW2A(money.GetString());
	double sum = atof(user_money.c_str());
	if (sum < drawmoney)
	{
		MessageBox(_T("余额不足"), _T("取款失败"));
		CButton_draw200.EnableWindow(0);
		CButton_draw500.EnableWindow(0);
		CButton_draw1000.EnableWindow(0);
		return;
	}
	else
	{
		USES_CONVERSION;
		LPSTR str;
		str = T2A(user_Account);
		strcpy_s(us.account, str);
		sprintf_s(query, "update bank_information set user_money=user_money-'%f' where user_account ='%s'", drawmoney, us.account);
		if (mysql_query(&mysqlCon, query))
		{
			MessageBox(_T("取款失败"));
			return;
		}
		else MessageBox(_T("取款成功"));
		alldrawmoney += drawmoney;
		int k;
		k = MessageBox(_T("继续取钱吗？"), _T("取钱确认"), MB_YESNO);
		if (k == IDYES)
		{
			if (alldrawmoney > 2000)
			{
				MessageBox(_T("已经超过了今日取款的上限,无法取款"), _T("取款提示"), MB_ICONSTOP);
				CButton_draw100.EnableWindow(0);
				CButton_draw200.EnableWindow(0);
				CButton_draw500.EnableWindow(0);
				CButton_draw1000.EnableWindow(0);
				CButton_drawcash.EnableWindow(0);
				return;
			}
		}
		else if (k == IDNO)
		{
			CButton_draw100.EnableWindow(0);
			CButton_draw200.EnableWindow(0);
			CButton_draw500.EnableWindow(0);
			CButton_draw1000.EnableWindow(0);
			CButton_drawcash.EnableWindow(0);
		}
	}
}


void CDrawcash::OnBnClickedDraw500()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	user us;
	MYSQL mysqlCon;
	mysql_init(&mysqlCon);
	CString money;
	MYSQL_ROW row;
	MYSQL_RES* result;
	if (!mysql_real_connect(&mysqlCon, "localhost", "root", "root", "information", 3306, NULL, 0))
	{
		MessageBox(_T("数据库连接失败"));
		return;
	}
	mysql_query(&mysqlCon, "set names 'GB2312'");
	char query[1000];
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
			break;
		}
	}
	double drawmoney = truemoney(500);
	std::string user_money = CW2A(money.GetString());
	double sum = atof(user_money.c_str());
	if (sum < drawmoney)
	{
		MessageBox(_T("余额不足"), _T("取款失败"));
		CButton_draw500.EnableWindow(0);
		CButton_draw1000.EnableWindow(0);
		return;
	}
	else
	{
		USES_CONVERSION;
		LPSTR str;
		str = T2A(user_Account);
		strcpy_s(us.account, str);
		sprintf_s(query, "update bank_information set user_money=user_money-'%f' where user_account ='%s'", drawmoney, us.account);
		if (mysql_query(&mysqlCon, query))
		{
			MessageBox(_T("取款失败"));
			return;
		}
		else MessageBox(_T("取款成功"));
		alldrawmoney += drawmoney;
		int k;
		k = MessageBox(_T("继续取钱吗？"), _T("取钱确认"), MB_YESNO);
		if (k == IDYES)
		{
			if (alldrawmoney > 2000)
			{
				MessageBox(_T("已经超过了今日取款的上限,无法取款"), _T("取款提示"), MB_ICONSTOP);
				CButton_draw100.EnableWindow(0);
				CButton_draw200.EnableWindow(0);
				CButton_draw500.EnableWindow(0);
				CButton_draw1000.EnableWindow(0);
				CButton_drawcash.EnableWindow(0);
				return;
			}
		}
		else if (k == IDNO)
		{
			CButton_draw100.EnableWindow(0);
			CButton_draw200.EnableWindow(0);
			CButton_draw500.EnableWindow(0);
			CButton_draw1000.EnableWindow(0);
			CButton_drawcash.EnableWindow(0);
		}
	}
}


void CDrawcash::OnBnClickedDraw1000()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	user us;
	MYSQL mysqlCon;
	mysql_init(&mysqlCon);
	CString money;
	MYSQL_ROW row;
	MYSQL_RES* result;
	if (!mysql_real_connect(&mysqlCon, "localhost", "root", "root", "information", 3306, NULL, 0))
	{
		MessageBox(_T("数据库连接失败"));
		return;
	}
	mysql_query(&mysqlCon, "set names 'GB2312'");
	char query[1000];
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
			break;
		}
	}
	double drawmoney = truemoney(1000);
	std::string user_money = CW2A(money.GetString());
	double sum = atof(user_money.c_str());
	if (sum < drawmoney)
	{
		MessageBox(_T("余额不足"), _T("取款失败"));
		CButton_draw1000.EnableWindow(0);
		return;
	}
	else
	{
		USES_CONVERSION;
		LPSTR str;
		str = T2A(user_Account);
		strcpy_s(us.account, str);
		sprintf_s(query, "update bank_information set user_money=user_money-'%f' where user_account ='%s'", drawmoney, us.account);
		if (mysql_query(&mysqlCon, query))
		{
			MessageBox(_T("取款失败"));
			return;
		}
		else MessageBox(_T("取款成功"));
		alldrawmoney += drawmoney;
		int k;
		k = MessageBox(_T("继续取钱吗？"), _T("取钱确认"), MB_YESNO);
		if (k == IDYES)
		{
			if (alldrawmoney >= 3000)
			{
				MessageBox(_T("已经超过了今日取款的上限,无法取款"), _T("取款提示"), MB_ICONSTOP);
				CButton_draw100.EnableWindow(0);
				CButton_draw200.EnableWindow(0);
				CButton_draw500.EnableWindow(0);
				CButton_draw1000.EnableWindow(0);
				CButton_drawcash.EnableWindow(0);
				return;
			}
		}
		else if (k == IDNO )
		{
			CButton_draw100.EnableWindow(0);
			CButton_draw200.EnableWindow(0);
			CButton_draw500.EnableWindow(0);
			CButton_draw1000.EnableWindow(0);
			CButton_drawcash.EnableWindow(0);
		}
	}
}


void CDrawcash::OnBnClickedDrawcashbutton()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	user us;
	char query[1000];
	MYSQL mysqlCon;
	MYSQL_ROW row;
	MYSQL_RES* result;
	CString money;
	mysql_init(&mysqlCon);
	mysql_query(&mysqlCon, "set names 'GB2312'");
	if (!mysql_real_connect(&mysqlCon, "localhost", "root", "root", "information", 3306, NULL, 0))
	{
		MessageBox(_T("数据库连接失败"));
		return;
	}
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
			break;
		}
	}
	m_money1 = truemoney(m_money1);
	std::string user_money = CW2A(money.GetString());
	double sum= atof(user_money.c_str());
	if (sum < m_money1)
	{
		MessageBox(_T("余额不足"), _T("取款失败"));
		CButton_drawcash.EnableWindow(0);
		return;
	}
	else if (m_money1 >= 3000)
	{
		MessageBox(_T("已经超过了今日取款的上限,无法取款"), _T("取款提示"), MB_ICONSTOP);
		CButton_draw100.EnableWindow(0);
		CButton_draw200.EnableWindow(0);
		CButton_draw500.EnableWindow(0);
		CButton_draw1000.EnableWindow(0);
		CButton_drawcash.EnableWindow(0);
		return;
	}
	else
	{
		USES_CONVERSION;
		LPSTR str;
		str = T2A(user_Account);
		strcpy_s(us.account, str);
		sprintf_s(query, "update bank_information set user_money=user_money-'%f' where user_account ='%s'", m_money1, us.account);
		if (mysql_query(&mysqlCon, query))
		{
			MessageBox(_T("取款失败"));
			return;
		}
		else MessageBox(_T("取款成功"));
		alldrawmoney += m_money1;
		m_money1 = 0;
		UpdateData(false);
		int k;
		k = MessageBox(_T("继续取钱吗？"), _T("取钱确认"), MB_YESNO);
		if (k == IDYES)
		{
			if (alldrawmoney > 2000)
			{
				MessageBox(_T("已经超过了今日取款的上限,无法取款"), _T("取款提示"), MB_ICONSTOP);
				CButton_draw100.EnableWindow(0);
				CButton_draw200.EnableWindow(0);
				CButton_draw500.EnableWindow(0);
				CButton_draw1000.EnableWindow(0);
				CButton_drawcash.EnableWindow(0);
				return;
			}
			else
			{
				CButton_draw100.EnableWindow(0);
				CButton_draw200.EnableWindow(0);
				CButton_draw500.EnableWindow(0);
				CButton_draw1000.EnableWindow(0);
			}
		}
		else if (k == IDNO)
		{
			CButton_draw100.EnableWindow(0);
			CButton_draw200.EnableWindow(0);
			CButton_draw500.EnableWindow(0);
			CButton_draw1000.EnableWindow(0);
			CButton_drawcash.EnableWindow(0);
		}
	}
}

double CDrawcash::truemoney(double money)
{
	UpdateData(true);
	switch (m_select_moneytype)
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
