// CReport.cpp: 实现文件
//

#include "pch.h"
#include "Bank-management.h"
#include "CReport.h"
#include "afxdialogex.h"
#include"CRegist.h"
#include<mysql.h>
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
// CReport 对话框

IMPLEMENT_DYNAMIC(CReport, CDialog)

CReport::CReport(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_REPORT, pParent)
	, m_lost_account(_T(""))
	, m_lost_ID(_T(""))
	//, m_lost_name(_T(""))
	, m_select_drawcash(0)
{

}

CReport::~CReport()
{
}

void CReport::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_lost_account, m_lost_account);
	DDX_Text(pDX, IDC_lost_ID, m_lost_ID);
	//DDX_Text(pDX, IDC_lost_name, m_lost_name);
	DDX_Radio(pDX, IDC_Radio_drawcash, m_select_drawcash);
	DDX_Control(pDX, IDC_ReportButton, CButton_report);
	DDX_Control(pDX, IDC_lost_account, CButton_lost_account);
	DDX_Control(pDX, IDC_lost_ID, CButton_lost_ID);
	DDX_Control(pDX, IDC_Radio_drawcash, CButton_select_way);
	DDX_Control(pDX, IDC_Freeze, CButton_freeze);
	DDX_Control(pDX, IDC_Unfreeze, CButton_unfreeze);
	DDX_Control(pDX, IDC_Radio_newuser, CButton_new_account);
}


BEGIN_MESSAGE_MAP(CReport, CDialog)
	ON_BN_CLICKED(IDC_ReportButton, &CReport::OnBnClickedReportbutton)
	ON_BN_CLICKED(IDC_Freeze, &CReport::OnBnClickedFreeze)
	ON_BN_CLICKED(IDC_Unfreeze, &CReport::OnBnClickedUnfreeze)
END_MESSAGE_MAP()


// CReport 消息处理程序


void CReport::OnBnClickedReportbutton()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	user us;
	MYSQL mysqlCon;
	mysql_init(&mysqlCon);
	mysql_query(&mysqlCon, "set names 'GB2312'");
	if (!mysql_real_connect(&mysqlCon, "localhost", "root", "root", "information", 3306, NULL, 0))
	{
		MessageBox(_T("数据库连接失败"));
		return;
	}
	char select1[1000];
	sprintf_s(select1, "select user_account,user_ID,user_money,account_state from bank_information");
	mysql_real_query(&mysqlCon, select1, (unsigned long)strlen(select1));
	MYSQL_ROW row;
	MYSQL_RES* result;
	CString money,state;
	result = mysql_store_result(&mysqlCon);
	while ((row = mysql_fetch_row(result)))
	{
		char* Account = row[0];
		char* ID = row[1];
		char* Money = row[2];
		char* State = row[3];
		if ((Account == m_lost_account)  && (ID == m_lost_ID))
		{
			money = Money;
			state = State;
			std::string user_money = CW2A(money.GetString());
			double sum = atof(user_money.c_str());
			std::string user_state = CW2A(state.GetString());
			int account_state = atof(user_state.c_str());
			if (account_state != 1)
			{
				USES_CONVERSION;
				LPSTR str;
				str = T2A(m_lost_account);
				strcpy_s(us.account, str);
				str = T2A(m_lost_ID);
				strcpy_s(us.identify, str);
				switch (m_select_drawcash)
				{
				case 0:
				{
					char query2[1000];
					sprintf_s(query2, "delete from bank_information where user_account='%s';", us.account);
					if (mysql_query(&mysqlCon, query2))
					{
						MessageBox(_T("删除失败"));
						return;
					}
					char query[1000];
					sprintf_s(query, "update bank_information set user_money = user_money - '%f' where user_account = '%s'", sum, us.account);
					if (mysql_query(&mysqlCon, query))
					{
						MessageBox(_T("取款失败"));
						return;
					}
					else MessageBox(_T("取款成功，账户已经删除不可使用"));
					//CButton_report.EnableWindow(0);
					return;
				}
				case 1:
				{
					char query2[1000];
					sprintf_s(query2, "delete from bank_information where user_account='%s';", us.account);
					if (mysql_query(&mysqlCon, query2))
					{
						MessageBox(_T("删除失败"));
						return;
					}
					CRegist regist;
					regist.DoModal();
					char query1[1000];
					sprintf_s(query1, "update bank_information set user_money =user_money+'%f' where user_ID = '%s'", sum, us.identify);
					if (mysql_query(&mysqlCon, query1))
					{
						MessageBox(_T("存款失败"));
						return;
					}
					else MessageBox(_T("存款成功,已经转入新的账户"));
					CButton_lost_account.EnableWindow(0);
					CButton_lost_ID.EnableWindow(0);
					CButton_report.EnableWindow(0);
					CButton_select_way.EnableWindow(0);
					CButton_new_account.EnableWindow(0);
					CButton_freeze.EnableWindow(0);
					CButton_unfreeze.EnableWindow(0);
					return;
				}
				}
			}
			else
			{
				MessageBox(_T("账户未被冻结，无法挂失"), _T("信息提示"), MB_ICONSTOP);
				CButton_lost_account.EnableWindow(0);
				CButton_lost_ID.EnableWindow(0);
				CButton_report.EnableWindow(0);
				CButton_select_way.EnableWindow(0);
				CButton_new_account.EnableWindow(0);
				return;
			}
		}
	}
	MessageBox(_T("未找到对应的账户"), _T("信息提示"), MB_ICONSTOP);
	int k;
	k = MessageBox(_T("是否重新输入丢失信息？"), _T("输入提示"), MB_YESNO);
	if (k == IDNO)
	{
		CButton_lost_account.EnableWindow(0);
		CButton_lost_ID.EnableWindow(0);
		CButton_report.EnableWindow(0);
		CButton_select_way.EnableWindow(0);
		CButton_new_account.EnableWindow(0);
		CButton_freeze.EnableWindow(0);
		CButton_unfreeze.EnableWindow(0);
	}
	else
	{
		m_lost_account = "";
		m_lost_ID = "";
		UpdateData(false);
	}
}


void CReport::OnBnClickedFreeze()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	user us;
	MYSQL mysqlCon;
	mysql_init(&mysqlCon);
	mysql_query(&mysqlCon, "set names 'GB2312'");
	if (!mysql_real_connect(&mysqlCon, "localhost", "root", "root", "information", 3306, NULL, 0))
	{
		MessageBox(_T("数据库连接失败"));
		return;
	}
	char select1[1000];
	sprintf_s(select1, "select user_account,user_ID,user_money,account_state from bank_information");
	mysql_real_query(&mysqlCon, select1, (unsigned long)strlen(select1));
	MYSQL_ROW row;
	MYSQL_RES* result;
	CString money, state;
	result = mysql_store_result(&mysqlCon);
	while ((row = mysql_fetch_row(result)))
	{
		char* Account = row[0];
		char* ID = row[1];
		if ((Account == m_lost_account) && (ID == m_lost_ID))
		{
			USES_CONVERSION;
			LPSTR str;
			str = T2A(m_lost_account);
			strcpy_s(us.account, str);
			int state = 0;
			char query[1000];
			sprintf_s(query, "update bank_information set account_state='%d' where user_account='%s'", state, us.account);
			if (mysql_query(&mysqlCon, query))
			{
				MessageBox(_T("冻结失败"));
				return;
			}
			else
			{
				MessageBox(_T("冻结成功"));
				CButton_lost_account.EnableWindow(1);
				CButton_lost_ID.EnableWindow(1);
				CButton_report.EnableWindow(1);
				CButton_select_way.EnableWindow(1);
				CButton_new_account.EnableWindow(1);
				return;
			}
		}
	}
	MessageBox(_T("未找到对应的账户，无法冻结"), _T("信息提示"), MB_ICONSTOP);
	int k;
	k = MessageBox(_T("是否重新输入丢失信息？"), _T("输入提示"), MB_YESNO);
	if (k == IDNO)
	{
		CButton_lost_account.EnableWindow(0);
		CButton_lost_ID.EnableWindow(0);
		CButton_report.EnableWindow(0);
		CButton_select_way.EnableWindow(0);
		CButton_new_account.EnableWindow(0);
		CButton_freeze.EnableWindow(0);
		CButton_unfreeze.EnableWindow(0);
	}
	else
	{
		m_lost_account = "";
		m_lost_ID = "";
		UpdateData(false);
	}
}


void CReport::OnBnClickedUnfreeze()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	user us;
	MYSQL mysqlCon;
	mysql_init(&mysqlCon);
	mysql_query(&mysqlCon, "set names 'GB2312'");
	if (!mysql_real_connect(&mysqlCon, "localhost", "root", "root", "information", 3306, NULL, 0))
	{
		MessageBox(_T("数据库连接失败"));
		return;
	}
	char select1[1000];
	sprintf_s(select1, "select user_account,user_ID,user_money,account_state from bank_information");
	mysql_real_query(&mysqlCon, select1, (unsigned long)strlen(select1));
	MYSQL_ROW row;
	MYSQL_RES* result;
	CString money, state;
	result = mysql_store_result(&mysqlCon);
	while ((row = mysql_fetch_row(result)))
	{
		char* Account = row[0];
		char* ID = row[1];
		if ((Account == m_lost_account) && (ID == m_lost_ID))
		{
			USES_CONVERSION;
			LPSTR str;
			str = T2A(m_lost_account);
			strcpy_s(us.account, str);
			int state = 1;
			char query[1000];
			sprintf_s(query, "update bank_information set account_state='%d' where user_account='%s'", state, us.account);
			if (mysql_query(&mysqlCon, query))
			{
				MessageBox(_T("解冻失败"));
				return;
			}
			else
			{
				MessageBox(_T("解冻成功"));
				CButton_lost_account.EnableWindow(0);
				CButton_lost_ID.EnableWindow(0);
				CButton_report.EnableWindow(0);
				CButton_select_way.EnableWindow(0);
				CButton_new_account.EnableWindow(0);
				return;
			}
		}
	}
	MessageBox(_T("未找到对应的账户，无法解冻"), _T("信息提示"), MB_ICONSTOP);
	int k;
	k = MessageBox(_T("是否重新输入丢失信息？"), _T("输入提示"), MB_YESNO);
	if (k == IDNO)
	{
		CButton_lost_account.EnableWindow(0);
		CButton_lost_ID.EnableWindow(0);
		CButton_report.EnableWindow(0);
		CButton_select_way.EnableWindow(0);
		CButton_new_account.EnableWindow(0);
		CButton_freeze.EnableWindow(0);
		CButton_unfreeze.EnableWindow(0);
	}
	else
	{
		m_lost_account = "";
		m_lost_ID = "";
		UpdateData(false);
	}
}
