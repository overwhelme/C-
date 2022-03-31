// CRegist.cpp: 实现文件
//

#include "pch.h"
#include "Bank-management.h"
#include "CRegist.h"
#include "afxdialogex.h"
#include<mysql.h>
#include<ctime>
#include"CManager_oper.h"

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
// CRegist 对话框

IMPLEMENT_DYNAMIC(CRegist, CDialog)

CRegist::CRegist(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_REGIST, pParent)
	, m_name(_T(""))
	, m_telephone(_T(""))
	, m_ID(_T(""))
	, m_password2(_T(""))
	, m_confirmPassword2(_T(""))
	, m_account2(_T(""))
	
	, user_jg1(_T(""))
{

}

CRegist::~CRegist()
{
}

void CRegist::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_name);
	DDX_Text(pDX, IDC_EDIT2, m_telephone);
	DDX_Text(pDX, IDC_EDIT3, m_ID);
	DDX_Text(pDX, IDC_EDIT4, m_password2);
	DDX_Text(pDX, IDC_EDIT5, m_confirmPassword2);
	DDX_Text(pDX, IDC_EDIT6, m_account2);
	DDX_Control(pDX, IDC_jiguan, m_jg1);
	DDX_CBString(pDX, IDC_jiguan, user_jg1);
}


BEGIN_MESSAGE_MAP(CRegist, CDialog)
	ON_BN_CLICKED(IDC_RegistButton, &CRegist::OnBnClickedRegistbutton)
END_MESSAGE_MAP()


// CRegist 消息处理程序



void CRegist::OnBnClickedRegistbutton()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	MYSQL mysqlCon;
	user us;
	if (m_name.IsEmpty() || m_telephone.IsEmpty() || m_ID.IsEmpty() || m_password2.IsEmpty() || m_confirmPassword2.IsEmpty())
	{
		MessageBox(_T("信息没有填完整"), _T("提示"));
		return;
	}
	if (m_password2 != m_confirmPassword2) //密码不一致
	{
		MessageBox(_T("两次密码不一致"), _T("提示"));
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
		srand((int)time(0));
		us.account[0] = (rand() % 9) + 1 + '0';
		for (int i = 1; i < 9; i++)
			us.account[i] = rand() % 10 + '0';
		us.account[9] = '\0';
		USES_CONVERSION;
		m_account2 = A2T(us.account);
		LPSTR str;
		str = T2A(m_password2);
		strcpy_s(us.password, str);
		str = T2A(m_name);
		strcpy_s(us.name, str);
		str = T2A(m_telephone);
		strcpy_s(us.telephone, str);
		str = T2A(m_ID);
		strcpy_s(us.identify, str);
		str = T2A(user_jg1);
		strcpy_s(us.native, str);
		us.money = 0;
		us.state = 1;
		char insert[1000];
		sprintf_s(insert, "insert into bank_information(user_account,user_password,user_name,user_telephone,user_ID,user_native,user_money,account_state)values('%s','%s','%s','%s','%s','%s','%f','%d')", us.account, us.password, us.name, us.telephone, us.identify,us.native,us.money,us.state);
		if (mysql_query(&mysqlCon, insert))
		{
			AfxMessageBox(TEXT("注册失败！"));
		}
		else
		{
			MessageBox(_T("注册成功"));
			UpdateData(false);
			MessageBox(m_account2, _T("新的账号为"));
			CDialog::OnCancel();
		}
	}
	mysql_close(&mysqlCon);
}


BOOL CRegist::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_jg1.AddString(_T("上海市"));
	m_jg1.AddString(_T("四川省"));
	m_jg1.AddString(_T("山东省"));
	m_jg1.AddString(_T("重庆市"));
	m_jg1.AddString(_T("北京市"));
	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


