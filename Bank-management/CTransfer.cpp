// CTransfer.cpp: 实现文件
//

#include "pch.h"
#include "Bank-management.h"
#include "CTransfer.h"
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
};
extern CString user_Account;
// CTransfer 对话框

IMPLEMENT_DYNAMIC(CTransfer, CDialog)

CTransfer::CTransfer(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_TRANSFER, pParent)
	, m_accept_account(_T(""))
	, m_transfermoney(0)
	//, m_accept_name(_T(""))
	, m_procedure_money(0)
{

}

CTransfer::~CTransfer()
{
}

void CTransfer::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_accept_account, m_accept_account);
	DDX_Text(pDX, IDC_TRANSFERMONEY, m_transfermoney);
	//DDX_Text(pDX, IDC_accept_name, m_accept_name);
	DDX_Text(pDX, IDC_procedure_money, m_procedure_money);
}


BEGIN_MESSAGE_MAP(CTransfer, CDialog)
	ON_BN_CLICKED(IDC_TransferButton, &CTransfer::OnBnClickedTransferbutton)
END_MESSAGE_MAP()


// CTransfer 消息处理程序


void CTransfer::OnBnClickedTransferbutton()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	user us;
	MYSQL mysqlCon;
	CString money;
	mysql_init(&mysqlCon);
	mysql_query(&mysqlCon, "set names 'GB2312'");
	if (!mysql_real_connect(&mysqlCon, "localhost", "root", "root", "information", 3306, NULL, 0))
	{
		MessageBox(_T("数据库连接失败"));
		return;
	}
	char query[1000];
	MYSQL_ROW row;
	MYSQL_RES* result;
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
	std::string user_money = CW2A(money.GetString());
	double sum = atof(user_money.c_str());
	m_procedure_money = m_transfermoney * 0.02;
	m_transfermoney += m_procedure_money;
	if (sum < m_transfermoney)
	{
		MessageBox(_T("余额不足，无法完成转账"), _T("转账提示"), MB_ICONSTOP);
		return;
	}
	else if (m_transfermoney > 2000)
	{
		MessageBox(_T("超出转账限额，无法完成转账"), _T("转账提示"), MB_ICONSTOP);
		return;
	}
	
	sprintf_s(query, "select user_account,user_name from bank_information");
	mysql_real_query(&mysqlCon, query, (unsigned long)strlen(query));
	result = mysql_store_result(&mysqlCon);
	while ((row = mysql_fetch_row(result)))
	{
		char* Account = row[0];
		if (Account == m_accept_account)
		{
			char query2[1000],query3[1000];
			int m = 0, n = 0;
			USES_CONVERSION;
			LPSTR str;
			str = T2A(user_Account);
			strcpy_s(us.account, str);
			sprintf_s(query2, "update bank_information set user_money=user_money-'%f' where user_account ='%s'", m_transfermoney, us.account);
			if (mysql_query(&mysqlCon, query2))
				n = 0;
			else n = 1;
			str = T2A(m_accept_account);
			strcpy_s(us.account, str);
			m_transfermoney -= m_procedure_money;
			sprintf_s(query3, "update bank_information set user_money=user_money+'%f' where user_account ='%s'", m_transfermoney, us.account);
			if (mysql_query(&mysqlCon, query3))
				m = 0;
			else m = 1;
			m_transfermoney = 0;
			UpdateData(false);
			if (m == 1 && n == 1)
			{
				MessageBox(_T("转账成功"));
				return;
			}
			else if (m == 0 || n == 0)
			{
				MessageBox(_T("转账失败"));
				return;
			}
		}
	}
	MessageBox(_T("未能找到账户，无法转账"), _T("转账提示"), MB_ICONSTOP);
	return;
}
