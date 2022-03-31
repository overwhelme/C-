// CUpdate.cpp: 实现文件
//

#include "pch.h"
#include "Bank-management.h"
#include "CUpdate.h"
#include "afxdialogex.h"
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
// CUpdate 对话框

IMPLEMENT_DYNAMIC(CUpdate, CDialog)

CUpdate::CUpdate(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_UPDATE, pParent)
	, m_newpassword(_T(""))
	, m_newtelephone(_T(""))
	, m_select(0)
	, m_update_account(_T(""))
{

}

CUpdate::~CUpdate()
{
}

void CUpdate::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_newpassword, m_newpassword);
	DDX_Text(pDX, IDC_newtelephone, m_newtelephone);
	DDX_Radio(pDX, IDC_RADIO1, m_select);
	DDX_Text(pDX, IDC_update_account, m_update_account);
}


BEGIN_MESSAGE_MAP(CUpdate, CDialog)
	ON_BN_CLICKED(IDC_Update, &CUpdate::OnBnClickedUpdate)
END_MESSAGE_MAP()


// CUpdate 消息处理程序

void CUpdate::OnBnClickedUpdate()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	user us;
	MYSQL mysqlCon;
	mysql_init(&mysqlCon);
	if (!mysql_real_connect(&mysqlCon, "localhost", "root", "root", "information", 3306, NULL, 0))
	{
		MessageBox(_T("数据库连接失败"));
		return;
	}
	else
	{
		USES_CONVERSION;
		LPSTR str;
		str = T2A(m_update_account);
		strcpy_s(us.account, str);
		str = T2A(m_newpassword);
		strcpy_s(us.password, str);
		str = T2A(m_newtelephone);
		strcpy_s(us.telephone, str);
		MYSQL_ROW row;
		MYSQL_RES* result;
		CString password;
		mysql_query(&mysqlCon, "set names 'GB2312'");
		char query[1000];
		sprintf_s(query, "select user_account,user_password from bank_information");
		mysql_real_query(&mysqlCon, query, (unsigned long)strlen(query));
		result = mysql_store_result(&mysqlCon);
		while ((row = mysql_fetch_row(result)))
		{
			char* Account = row[0];
			char* Password = row[1];
			if (Account == m_update_account)
			{
				password=Password;
			}
		}
		switch (m_select)
		{
		case 0:
		{
			if (password == m_newpassword)
			{
				MessageBox(_T("新密码不能于与原来的密码一样"));
				return;
			}
			sprintf_s(query, "update bank_information set user_password='%s' where user_account='%s'", us.password, us.account);
			if (mysql_query(&mysqlCon, query))
			{
				MessageBox(_T("更新失败"));
				return;
			}
			else
			{
				MessageBox(_T("更新成功"));
				break;
			}
		}
		case 1:
		{
			sprintf_s(query, "update bank_information set user_telephone='%s' where user_account='%s'", us.telephone, us.account);
			if (mysql_query(&mysqlCon, query))
			{
				MessageBox(_T("更新失败"));
				return;
			}
			else
			{
				MessageBox(_T("更新成功"));
				break;
			}
		}
		}
	}
}
