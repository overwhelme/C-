// CSelect.cpp: 实现文件
//

#include "pch.h"
#include "System.h"
#include "CSelect.h"
#include "afxdialogex.h"
#include "mysql.h"


// CSelect 对话框

IMPLEMENT_DYNAMIC(CSelect, CDialog)

CSelect::CSelect(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_Select, pParent)
	, m_select(0)
	, m_select_information(_T(""))
{

}

CSelect::~CSelect()
{
}

void CSelect::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_select_id, m_select);
	DDX_Text(pDX, IDC_select_information, m_select_information);
	DDX_Control(pDX, IDC_select_list, m_List1);
	DDX_Control(pDX, IDC_Select, CButton_select);
	DDX_Control(pDX, IDC_Refresh1, CButton_refresh);
}


BEGIN_MESSAGE_MAP(CSelect, CDialog)
	ON_BN_CLICKED(IDC_Select, &CSelect::OnBnClickedSelect)
	ON_BN_CLICKED(IDC_Refresh1, &CSelect::OnBnClickedRefresh1)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CSelect 消息处理程序


void CSelect::OnBnClickedSelect()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	MYSQL mysqlCon;
	MYSQL_ROW row;
	char use[15];
	MYSQL_RES* result;
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
	USES_CONVERSION;
	LPSTR str;
	switch (m_select)
	{
	case 0:
	{
		str = T2A(m_select_information);
		strcpy_s(use, str);
		char select[1000];
		sprintf_s(select, "select id,name,sex,birth,telephone from student where id='%s'", use);
		if (mysql_query(&mysqlCon, select))
		{
			MessageBox(_T("查询失败"));
			return;
		}
		else
		{
			mysql_real_query(&mysqlCon, select, (unsigned long)strlen(select));
			CButton_select.EnableWindow(0);
			break;
		}
	}
	case 1:
	{
		str = T2A(m_select_information);
		strcpy_s(use, str);
		char select[1000];
		sprintf_s(select, "select id,name,sex,birth,telephone from student where name='%s'", use);
		if (mysql_query(&mysqlCon, select))
		{
			MessageBox(_T("查询失败"));
			return;
		}
		else
		{
			mysql_real_query(&mysqlCon, select, (unsigned long)strlen(select));
			CButton_select.EnableWindow(0);
			break;
		}
	}
	case 2:
	{
		str = T2A(m_select_information);
		strcpy_s(use, str);
		char select[1000];
		sprintf_s(select, "select id,name,sex,birth,telephone from student where sex='%s'", use);
		if (mysql_query(&mysqlCon, select))
		{
			MessageBox(_T("查询失败"));
			return;
		}
		else
		{
			mysql_real_query(&mysqlCon, select, (unsigned long)strlen(select));
			CButton_select.EnableWindow(0);
			break;
		}
	}
	}
	result = mysql_store_result(&mysqlCon);
	if (NULL == result)
	{
		return;
	}
	int nIndex = m_List1.GetItemCount(); // 获取list里面有多少行
	CString num;
	num.Format(_T("%d"), nIndex);
	m_List1.InsertItem(nIndex - 1, num);
	int k = 0;
	while (row = mysql_fetch_row(result))
	{
		m_List1.InsertItem(k, num);
		for (int rols = 0; rols < 5; rols++)
		{
			CString myreaddata(row[rols]);
			m_List1.SetItemText(k, rols, myreaddata);//添加数据  分别是行 列 值
		}
		k++;
	}
	MessageBox(_T("如需继续查找请点击刷新"));
	UpdateData(false);
}


BOOL CSelect::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_List1.InsertColumn(0, _T("学号"), LVCFMT_CENTER, 60, -1);
	m_List1.InsertColumn(1, _T("姓名"), LVCFMT_CENTER, 60, -1);
	m_List1.InsertColumn(2, _T("性别"), LVCFMT_CENTER, 60, -1);
	m_List1.InsertColumn(3, _T("出生年月"), LVCFMT_CENTER, 100, -1);
	m_List1.InsertColumn(4, _T("电话号码"), LVCFMT_CENTER, 100, -1);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CSelect::OnBnClickedRefresh1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	if (m_List1.GetItemCount() > 0) m_List1.DeleteAllItems();
	CButton_select.EnableWindow(1);
	UpdateData(false);
}


void CSelect::OnPaint()
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
