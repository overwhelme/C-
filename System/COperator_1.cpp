// COperator.cpp: 实现文件
//

#include "pch.h"
#include "System.h"
#include "COperator.h"
#include "afxdialogex.h"
#include"mysql.h"
#include"CInsert.h"


// COperator 对话框

IMPLEMENT_DYNAMIC(COperator, CDialog)
char useid[10];
COperator::COperator(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_Operator, pParent)
	, m_use_select(_T(""))
{

}

COperator::~COperator()
{
}

void COperator::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MList, m_List);
	DDX_Text(pDX, IDC_Use_select, m_use_select);
}


BEGIN_MESSAGE_MAP(COperator, CDialog)
	ON_COMMAND(ID_insert_manager, &COperator::Oninsertmanager)
	ON_BN_CLICKED(IDC_Out_look, &COperator::OnBnClickedOutlook)
	ON_COMMAND(ID_insert_student, &COperator::Oninsertstudent)
	ON_BN_CLICKED(IDC_Refresh, &COperator::OnBnClickedRefresh)
	//ON_COMMAND(ID_updata_infromation, &COperator::Onupdatainfromation)
	ON_NOTIFY(NM_RCLICK, IDC_MList, &COperator::OnRclickMlist)
	ON_NOTIFY(NM_RDBLCLK, IDC_MList, &COperator::OnRdblclkMlist)
	ON_COMMAND(ID_delete, &COperator::Ondelete)
	ON_NOTIFY(NM_CLICK, IDC_MList, &COperator::OnClickMlist)
	ON_NOTIFY(NM_DBLCLK, IDC_MList, &COperator::OnDblclkMlist)
	ON_NOTIFY(LVN_ENDLABELEDIT, IDC_MList, &COperator::OnEndlabeleditMlist)
END_MESSAGE_MAP()


// COperator 消息处理程序


BOOL COperator::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CRect rect;

	m_List.GetClientRect(&rect);

	m_List.SetExtendedStyle(m_List.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	CMenu menu;
	menu.LoadMenu(IDR_MENU_Opera);
	SetMenu(&menu);
	 // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
	m_List.InsertColumn(0, _T("学号"), LVCFMT_CENTER, 60, -1);
	m_List.InsertColumn(1, _T("姓名"), LVCFMT_CENTER, 60, -1);
	m_List.InsertColumn(2, _T("性别"), LVCFMT_CENTER, 60, -1);
	m_List.InsertColumn(3, _T("出生年月"), LVCFMT_CENTER, 100, -1);
	m_List.InsertColumn(4, _T("电话号码"), LVCFMT_CENTER, 100, -1);
	return TRUE;
}


void COperator::Oninsertmanager()
{
	// TODO: 在此添加命令处理程序代码
	
}


void COperator::OnBnClickedOutlook()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	MYSQL mysqlCon;
	mysql_init(&mysqlCon);
	MYSQL_ROW row;
	MYSQL_RES* result;
	if (0 != mysql_options(&mysqlCon, MYSQL_SET_CHARSET_NAME, "GB2312"))
	{
		MessageBox(_T("mysql_options() failed失败"));
		return;
	}
	if (!mysql_real_connect(&mysqlCon, "localhost", "root", "root", "student_system", 3306, NULL, 0))
	{
		MessageBox(_T("数据库连接失败！"));
		return;
	}
	char select[1000];
	sprintf_s(select, "select id,name,sex,birth,telephone from student;");
	mysql_real_query(&mysqlCon, select, (unsigned long)strlen(select));
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
		for (int rols = 0; rols < 5; rols++)
		{
			CString myreaddata(row[rols]);
			m_List.SetItemText(k, rols, myreaddata);//添加数据  分别是行 列 值
		}
		k++;
	}
	UpdateData(false);
}


void COperator::Oninsertstudent()
{
	// TODO: 在此添加命令处理程序代码
	CInsert insert;
	insert.DoModal();
}


void COperator::OnBnClickedRefresh()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	if (m_List.GetItemCount() > 0) m_List.DeleteAllItems();
	m_use_select = "";
	UpdateData(false);
}



void COperator::OnRclickMlist(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	NMLISTVIEW* pNMListView = (NMLISTVIEW*)pNMHDR;
	
	if (pNMListView->iItem != -1)
	{

		CPoint pt;
		GetCursorPos(&pt);
		CMenu menu;
		menu.LoadMenu(IDR_MENU_Select);
		CMenu* popmenu;
		popmenu = menu.GetSubMenu(0);
		popmenu->TrackPopupMenu(TPM_RIGHTBUTTON, pt.x, pt.y, this);
	}

	*pResult = 0;
}



void COperator::OnRdblclkMlist(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	POSITION ps;
	int nIndex;

	ps = m_List.GetFirstSelectedItemPosition();
	nIndex = m_List.GetNextSelectedItem(ps);
	//TODO:添加多选的操作。
	if (nIndex == -1)
	{
		//m_list.SetItemState(-1,LVNI_SELECTED,LVNI_SELECTED);
		MessageBox(_T("无效学号，请重新选择"));
		return;

	}
	m_List.SetItemState(nIndex, LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT);
	CString str;
	str = m_List.GetItemText(nIndex, 0);
	MessageBox(str);
	str = str + m_List.GetItemText(nIndex, 1); //所有的
	*pResult = 0;
}


void COperator::Ondelete()
{
	// TODO: 在此添加命令处理程序代码
	UpdateData(true);
	int i, iState;
	
	int nItemSelected = m_List.GetSelectedCount();
	int nItemCount = m_List.GetItemCount();
	if (nItemSelected < 1)
		return;
	for (i = nItemCount - 1; i >= 0; i--)
	{
		iState = m_List.GetItemState(i, LVIS_SELECTED);
		if (iState != 0)
		{

			m_List.DeleteItem(i);
		}
	}
	MYSQL mysqlCon;
	mysql_init(&mysqlCon);
	mysql_query(&mysqlCon, "set names 'GB2312'");
	if (!mysql_real_connect(&mysqlCon, "localhost", "root", "root", "student_system", 3306, NULL, 0))
	{
		MessageBox(_T("数据库连接失败"));
		return;
	}
	
	char query[1000];
	sprintf_s(query, "delete from student where id='%s';", useid);
	if (mysql_query(&mysqlCon, query))
	{
		MessageBox(_T("删除失败"));
		return;
	}
	else { MessageBox(_T("删除成功")); return; }
}


void COperator::OnClickMlist(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	    // 选择语言的名称字符串   
	NMLISTVIEW* pNMListView = (NMLISTVIEW*)pNMHDR;
	CString select_id;
	if (-1 != pNMListView->iItem)        // 如果iItem不是-1，就说明有列表项被选择   
	{
		// 获取被选择列表项第一个子项的文本   
		select_id = m_List.GetItemText(pNMListView->iItem, 0);
		// 将选择的语言显示与编辑框中   
		SetDlgItemText(IDC_Use_select, select_id);
		USES_CONVERSION;
		LPSTR str;
		str = T2A(select_id);
		strcpy_s(useid, str);
	}
	*pResult = 0;
}


void COperator::OnDblclkMlist(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	POSITION pos = m_List.GetFirstSelectedItemPosition();
	int tIndex = m_List.GetNextSelectedItem(pos);

	if (tIndex >= 0)
	{
		m_List.SetFocus();
		CEdit* pEdit = m_List.EditLabel(tIndex);
	}
	
}


void COperator::OnEndlabeleditMlist(NMHDR* pNMHDR, LRESULT* pResult)
{
	NMLVDISPINFO* pDispInfo = reinterpret_cast<NMLVDISPINFO*>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	CString pName = pDispInfo->item.pszText;
	int tIndex = pDispInfo->item.iItem;
	m_List.SetFocus();

	if ((!pName.IsEmpty()) && tIndex >= 0)
	{
		m_List.SetItemText(tIndex, 0, pName);
	}
}
