// COperator.cpp: 实现文件
//

#include "pch.h"
#include "System.h"
#include "COperator.h"
#include "afxdialogex.h"
#include"mysql.h"
#include"CInsert.h"
#include"CSelect.h"
#include"CRegist_manager.h"


// COperator 对话框

IMPLEMENT_DYNAMIC(COperator, CDialog)
CString stu_id, stu_name, stu_sex, stu_birth, stu_telephone;
CString select_id;
char useid[10];
int flag;
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
	DDX_Control(pDX, IDC_Out_look, CButton_look);
}


BEGIN_MESSAGE_MAP(COperator, CDialog)
	ON_COMMAND(ID_insert_manager, &COperator::Oninsertmanager)
	ON_BN_CLICKED(IDC_Out_look, &COperator::OnBnClickedOutlook)
	ON_COMMAND(ID_insert_student, &COperator::Oninsertstudent)
	ON_BN_CLICKED(IDC_Refresh, &COperator::OnBnClickedRefresh)
	ON_NOTIFY(NM_RCLICK, IDC_MList, &COperator::OnRclickMlist)
	ON_COMMAND(ID_delete, &COperator::Ondelete)
	ON_NOTIFY(NM_CLICK, IDC_MList, &COperator::OnClickMlist)
	ON_NOTIFY(LVN_ENDLABELEDIT, IDC_MList, &COperator::OnEndlabeleditMlist)
	ON_COMMAND(ID_update, &COperator::Onupdate)
	ON_COMMAND(ID_asc_id, &COperator::Onascid)
	ON_COMMAND(ID_desc_id, &COperator::Ondescid)
	ON_COMMAND(ID_sort_name, &COperator::Onsortname)
	ON_COMMAND(ID_asc_age, &COperator::Onascage)
	ON_COMMAND(ID_desc_age, &COperator::Ondescage)
	ON_COMMAND(ID_select_information, &COperator::Onselectinformation)
	ON_WM_PAINT()
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
	CRegist_manager regist;
	regist.DoModal();
}


void COperator::OnBnClickedOutlook()//查看
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	MYSQL mysqlCon;
	mysql_init(&mysqlCon);
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
	MYSQL_ROW row;
	MYSQL_RES* result;
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
	CButton_look.EnableWindow(0);
	UpdateData(false);
}


void COperator::Oninsertstudent()
{
	// TODO: 在此添加命令处理程序代码
	CInsert insert;
	flag = 0;
	insert.DoModal();
}


void COperator::OnBnClickedRefresh()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	if (m_List.GetItemCount() > 0) m_List.DeleteAllItems();
	m_use_select = "";
	CButton_look.EnableWindow(1);
	UpdateData(false);
}



void COperator::OnRclickMlist(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate ;
	pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
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
	sprintf_s(query, "delete from student where id='%s'", useid);
	if (mysql_query(&mysqlCon,query))
	{
		MessageBox(_T("删除失败"));
		return;
	}
	else { MessageBox(_T("删除成功")); return; }
}




void COperator::Onupdate()
{
	// TODO: 在此添加命令处理程序代码
	MYSQL mysqlCon;
	MYSQL_ROW row;
	MYSQL_RES* result;
	mysql_init(&mysqlCon);
	if (0 != mysql_options(&mysqlCon, MYSQL_SET_CHARSET_NAME, "GB2312"))
	{
		MessageBox(_T("mysql_options() failed失败"));
		return;
	}
	if (!mysql_real_connect(&mysqlCon, "localhost", "root", "root", "student_system", 3306, NULL, 0))
	{
		MessageBox(_T("数据库连接失败!"));
		return;
	}
	char select[1000];
	sprintf_s(select, "select name,sex,birth,telephone from student where id='%s'",useid);
	mysql_real_query(&mysqlCon, select, (unsigned long)strlen(select));
	result = mysql_store_result(&mysqlCon);
	while ((row = mysql_fetch_row(result)))
	{
		stu_name = row[0];
		stu_sex = row[1];
		stu_birth = row[2];
		stu_telephone = row[3];
	}
	CInsert insert;
	insert.m_new_id = select_id;
	insert.m_new_name = stu_name;
	insert.m_new_sex = stu_sex;
	insert.m_new_birth = stu_birth;
	insert.m_new_telephone = stu_telephone;
	flag = 1;
	insert.DoModal();
}



void COperator::OnClickMlist(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate;
	pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	    // 选择语言的名称字符串   
	NMLISTVIEW* pNMListView = (NMLISTVIEW*)pNMHDR;
	if (-1 != pNMListView->iItem)        // 如果iItem不是-1，就说明有列表项被选择   
	{
		// 获取被选择列表项第一个子项的文本   
		stu_id = m_List.GetItemText(pNMListView->iItem, 0);
		stu_name = m_List.GetItemText(pNMListView->iItem, 1);
		stu_sex= m_List.GetItemText(pNMListView->iItem, 2);
		stu_birth= m_List.GetItemText(pNMListView->iItem, 3);
		stu_telephone= m_List.GetItemText(pNMListView->iItem, 4);
		select_id = m_List.GetItemText(pNMListView->iItem, 0);
		SetDlgItemText(IDC_Use_select, select_id);
		USES_CONVERSION;
		LPSTR str;
		str = T2A(select_id);
		strcpy_s(useid, str);
	}
	*pResult = 0;
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


void COperator::Onascid()//学号升序
{
	// TODO: 在此添加命令处理程序代码
	UpdateData(true);
	MYSQL mysqlCon;
	MYSQL_ROW row;
	MYSQL_RES* result;
	mysql_init(&mysqlCon);
	if (0 != mysql_options(&mysqlCon, MYSQL_SET_CHARSET_NAME, "GB2312"))
	{
		MessageBox(_T("mysql_options() failed失败"));
		return;
	}
	if (!mysql_real_connect(&mysqlCon, "localhost", "root", "root", "student_system", 3306, NULL, 0))
	{
		MessageBox(_T("数据库连接失败"));
		return;
	}
	char query[1000];
	sprintf_s(query, "select id,name,sex,birth,telephone from student order by id ASC;");
	if (mysql_query(&mysqlCon, query))
	{
		MessageBox(_T("排序失败"));
		return;
	}
	else
	{
		mysql_real_query(&mysqlCon, query, (unsigned long)strlen(query));
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
		for (int rols = 0; rols < 5; rols++)
		{
			CString myreaddata(row[rols]);
			m_List.SetItemText(k, rols, myreaddata);//添加数据  分别是行 列 值
		}
		k++;
	}
	UpdateData(false);
}


void COperator::Ondescid()//学号降序
{
	// TODO: 在此添加命令处理程序代码
	UpdateData(true);
	MYSQL mysqlCon;
	MYSQL_ROW row;
	MYSQL_RES* result;
	mysql_init(&mysqlCon);
	if (0 != mysql_options(&mysqlCon, MYSQL_SET_CHARSET_NAME, "GB2312"))
	{
		MessageBox(_T("mysql_options() failed失败"));
		return;
	}
	if (!mysql_real_connect(&mysqlCon, "localhost", "root", "root", "student_system", 3306, NULL, 0))
	{
		MessageBox(_T("数据库连接失败"));
		return;
	}
	char query[1000];
	sprintf_s(query, "select id,name,sex,birth,telephone from student order by id DESC;");
	if (mysql_query(&mysqlCon, query))
	{
		MessageBox(_T("排序失败"));
		return;
	}
	else
	{
		mysql_real_query(&mysqlCon, query, (unsigned long)strlen(query));
	}
	result = mysql_store_result(&mysqlCon);
	if (NULL == result)
	{
		return;
	}
	int nIndex = m_List.GetItemCount(); // 获取list里面有多少行
	CString num;
	num.Format(_T("%d"), nIndex);
	m_List.InsertItem(nIndex - 1, num);
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


void COperator::Onsortname()//姓名排序
{
	// TODO: 在此添加命令处理程序代码
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
	sprintf_s(select, "select id,name,sex,birth,telephone from student order by name desc;");
	mysql_real_query(&mysqlCon, select, (unsigned long)strlen(select));
	result = mysql_store_result(&mysqlCon);
	if (NULL == result)
	{
		return;
	}
	int nIndex = m_List.GetItemCount(); // 获取list里面有多少行
	CString num;
	num.Format(_T("%d"), nIndex);
	m_List.InsertItem(nIndex - 1, num);
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


void COperator::Onascage()//年龄升序
{
	// TODO: 在此添加命令处理程序代码
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
	sprintf_s(select, "select id,name,sex,birth,telephone from student order by birth desc;");
	mysql_real_query(&mysqlCon, select, (unsigned long)strlen(select));
	result = mysql_store_result(&mysqlCon);
	if (NULL == result)
	{
		return;
	}
	int nIndex = m_List.GetItemCount(); // 获取list里面有多少行
	CString num;
	num.Format(_T("%d"), nIndex);
	m_List.InsertItem(nIndex - 1, num);
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


void COperator::Ondescage()//年龄降序
{
	// TODO: 在此添加命令处理程序代码
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
	sprintf_s(select, "select id,name,sex,birth,telephone from student order by birth asc;");
	mysql_real_query(&mysqlCon, select, (unsigned long)strlen(select));
	result = mysql_store_result(&mysqlCon);
	if (NULL == result)
	{
		return;
	}
	int nIndex = m_List.GetItemCount(); // 获取list里面有多少行
	CString num;
	num.Format(_T("%d"), nIndex);
	m_List.InsertItem(nIndex - 1, num);
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


void COperator::Onselectinformation()
{
	// TODO: 在此添加命令处理程序代码
	CSelect select;
	select.DoModal();
}


void COperator::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CDialog::OnPaint()
	CRect rect;
	GetClientRect(&rect);
	CDC   dcMem;
	dcMem.CreateCompatibleDC(&dc);
	CBitmap   bmpBackground;
	bmpBackground.LoadBitmap(IDB_BITMAP2);

	BITMAP   bitmap;
	bmpBackground.GetBitmap(&bitmap);
	CBitmap* pbmpOld = dcMem.SelectObject(&bmpBackground);
	dc.StretchBlt(0, 0, rect.Width(), rect.Height(), &dcMem, 0, 0, bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);
}
