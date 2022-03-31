// CManager_regist.cpp: 实现文件
//

#include "pch.h"
#include "Bank-management.h"
#include "CManager_regist.h"
#include "afxdialogex.h"
#include<mysql.h>

struct manager
{
	char account[20];
	char password[20];
	char worknumber[20];
};
// CManager_regist 对话框

IMPLEMENT_DYNAMIC(CManager_regist, CDialog)

CManager_regist::CManager_regist(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_Manager_regist, pParent)
	, manager_account(_T(""))
	, manager_password(_T(""))
	, manager_work_number(_T(""))
{

}

CManager_regist::~CManager_regist()
{
}

void CManager_regist::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, manager_account);
	DDX_Text(pDX, IDC_EDIT2, manager_password);
	DDX_Text(pDX, IDC_EDIT3, manager_work_number);
}


BEGIN_MESSAGE_MAP(CManager_regist, CDialog)
	ON_BN_CLICKED(IDC_manager_regist, &CManager_regist::OnBnClickedmanagerregist)
END_MESSAGE_MAP()


// CManager_regist 消息处理程序


void CManager_regist::OnBnClickedmanagerregist()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	MYSQL mysqlCon;
	manager mag;
	if (manager_account.IsEmpty() || manager_password.IsEmpty() || manager_work_number.IsEmpty() )
	{
		MessageBox(_T("信息没有填完整"), _T("提示"));
		return;
	}
	mysql_init(&mysqlCon);
	if (!mysql_real_connect(&mysqlCon, "localhost", "root", "root", "information", 3306, NULL, 0))
	{
		MessageBox(_T("数据库连接失败"));
		return;
	}
	else
	{
		mysql_query(&mysqlCon, "set names 'GB2312'");
		USES_CONVERSION;
		LPSTR str;
		str = T2A(manager_account);
		strcpy_s(mag.account, str);
		str = T2A(manager_password);
		strcpy_s(mag.password, str);
		str = T2A(manager_work_number);
		strcpy_s(mag.worknumber, str);
		char insert[1000];
		sprintf_s(insert, "insert into manager(Account,Password,work_number)values('%s','%s','%s')", mag.account,mag.password,mag.worknumber);
		if (mysql_query(&mysqlCon, insert))
		{
			AfxMessageBox(TEXT("注册失败！"));
		}
		else
		{
			MessageBox(_T("注册成功"));
			CDialog::OnCancel();
		}
	}
	mysql_close(&mysqlCon);
}
