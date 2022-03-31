// CDelete.cpp: 实现文件
//

#include "pch.h"
#include "Bank-management.h"
#include "CDelete.h"
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
};
// CDelete 对话框

IMPLEMENT_DYNAMIC(CDelete, CDialog)

CDelete::CDelete(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DELETE, pParent)
	, m_account2(_T(""))
	, m_password2(_T(""))
{

}

CDelete::~CDelete()
{
}

void CDelete::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_account2);
	DDX_Text(pDX, IDC_EDIT5, m_password2);
	DDX_Control(pDX, IDC_delete_user, Delete1);
}


BEGIN_MESSAGE_MAP(CDelete, CDialog)
	ON_BN_CLICKED(IDC_delete_user, &CDelete::OnBnClickeddeleteuser)
END_MESSAGE_MAP()

void CDelete::OnBnClickeddeleteuser()
{
	// TODO: 在此添加控件通知处理程序代码
	MYSQL mysqlCon;
	mysql_init(&mysqlCon);
	mysql_query(&mysqlCon, "set names 'GB2312'");
	if (!mysql_real_connect(&mysqlCon, "localhost", "root", "root", "information", 3306, NULL, 0))
	{
		MessageBox(_T("数据库连接失败"));
		return;
	}
	UpdateData(true);
	user us;
	USES_CONVERSION;
	LPSTR str;
	str = T2A(m_account2);
	strcpy_s(us.account, str);
	int k;
	k = MessageBox(_T("是否确认删除用户信息？"), _T("删除确认"), MB_YESNO);
	if (k == IDNO)  Delete1.EnableWindow(0);
	else if (k == IDYES)
	{
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
			if ((m_account2 == Account) && (m_password2 == Password))
			{
				char query2[1000];
				sprintf_s(query2, "delete from bank_information where user_account='%s';", us.account);
				if (mysql_query(&mysqlCon, query2))
				{
					MessageBox(_T("删除失败"));
					return;
				}
				else { MessageBox(_T("删除成功")); return; }
			}
		}
		MessageBox(_T("未能找到相匹配的信息"));
	}
}
/*int k;
k = MessageBox(_T("是否确认删除用户信息？"), _T("删除确认"), MB_OKCANCEL);
if (k == IDNO)  Delete1.EnableWindow(0);*/