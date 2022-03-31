// COutput.cpp: 实现文件
//

#include "pch.h"
#include "Bank-management.h"
#include "COutput.h"
#include "afxdialogex.h"
#include<mysql.h>


// COutput 对话框

IMPLEMENT_DYNAMIC(COutput, CDialog)

COutput::COutput(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_OUTPUTALL, pParent)
	, select_lookway(0)
{

}

COutput::~COutput()
{
}

void COutput::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROGRAM_LANG_LIST, m_List);
	DDX_Control(pDX, IDC_Output, CButton_output);
	DDX_Radio(pDX, IDC_direct_look, select_lookway);
	DDX_Control(pDX, IDC_ascend_look, CButton_ascend);
	DDX_Control(pDX, IDC_direct_look, CButton_look);
	DDX_Control(pDX, IDC_descend_look, CButton_descend);
}


BEGIN_MESSAGE_MAP(COutput, CDialog)
	ON_BN_CLICKED(IDC_Output, &COutput::OnBnClickedOutput)
	ON_BN_CLICKED(IDC_Refresh, &COutput::OnBnClickedRefresh)
END_MESSAGE_MAP()


// COutput 消息处理程序


void COutput::OnBnClickedOutput()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	MYSQL mysqlCon;
	MYSQL_ROW row;
	MYSQL_RES* result;
	mysql_init(&mysqlCon);
	if (0 != mysql_options(&mysqlCon, MYSQL_SET_CHARSET_NAME,"GB2312"))
	{
		MessageBox(_T("mysql_options() failed失败"));
		return;
	}
	if (!mysql_real_connect(&mysqlCon, "localhost", "root", "root", "information", 3306, NULL, 0))
	{
		MessageBox(_T("数据库连接失败"));
		return;
	}
	switch (select_lookway)
	{
	case 0: 
	{
		char select[1000];
		sprintf_s(select, "select user_account,user_name,user_telephone,user_ID,user_native,user_money from bank_information");
		mysql_real_query(&mysqlCon, select, (unsigned long)strlen(select));
		CButton_ascend.EnableWindow(0);
		CButton_descend.EnableWindow(0);
		break; 
	}
	case 1:
	{
		char query[1000];
		sprintf_s(query, "select user_account,user_name,user_telephone,user_ID,user_native,user_money from bank_information order by user_money ASC;");
		if (mysql_query(&mysqlCon, query))
		{
			MessageBox(_T("排序失败"));
			return;
		}
		else
		{
			mysql_real_query(&mysqlCon, query, (unsigned long)strlen(query));
			CButton_look.EnableWindow(0);
			CButton_descend.EnableWindow(0);
			break;
		}
	}
	case 2:
	{
		char select[1000];
		sprintf_s(select, "select user_account,user_name,user_telephone,user_ID,user_native,user_money from bank_information order by user_money DESC;");
		if (mysql_query(&mysqlCon, select))
		{
			MessageBox(_T("排序失败"));
			return;
		}
		else
		{
			mysql_real_query(&mysqlCon, select, (unsigned long)strlen(select));
			CButton_ascend.EnableWindow(0);
			CButton_look.EnableWindow(0);
			break;
		}
	}
	}
	result = mysql_store_result(&mysqlCon);
	if (NULL == result)
	{
		return;
	}
	int nIndex = m_List.GetItemCount(); // 获取list里面有多少行
	CString num;
	num.Format(_T("%d"), nIndex);
	m_List.InsertItem(nIndex-1, num);
	int k = 0;
	while (row = mysql_fetch_row(result))
	{
		m_List.InsertItem(k, num);
		for (int rols = 0; rols < 6; rols++)
		{
			CString myreaddata(row[rols]);
			m_List.SetItemText(k, rols , myreaddata);//添加数据  分别是行 列 值
		}
		k++;
	}
	UpdateData(false);
}


BOOL COutput::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_List.InsertColumn(0, _T("账号"), LVCFMT_CENTER, 70, -1);
	m_List.InsertColumn(1, _T("姓名"), LVCFMT_CENTER, 70, -1);
	m_List.InsertColumn(2, _T("电话号码"), LVCFMT_CENTER, 100, -1);
	m_List.InsertColumn(3, _T("身份证号码"), LVCFMT_CENTER, 80, -1);
	m_List.InsertColumn(4, _T("籍贯"), LVCFMT_CENTER, 70, -1);
	m_List.InsertColumn(5, _T("余额"), LVCFMT_CENTER, 70, -1);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}





void COutput::OnBnClickedRefresh()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	if (m_List.GetItemCount() > 0) m_List.DeleteAllItems();
	CButton_look.EnableWindow(1);
	CButton_ascend.EnableWindow(1);
	CButton_descend.EnableWindow(1);
	UpdateData(false);
}
