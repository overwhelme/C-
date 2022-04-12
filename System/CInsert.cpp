// CInsert.cpp: 实现文件
//

#include "pch.h"
#include "System.h"
#include "CInsert.h"
#include "afxdialogex.h"
#include"mysql.h"


// CInsert 对话框
int num;
DLinklist h,p,s;
//extern char useid[10];
extern int flag;
extern CString select_id;
//extern int GetListNodeLen(DLinklist h);
IMPLEMENT_DYNAMIC(CInsert, CDialog)

CInsert::CInsert(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_Insert, pParent)
	, m_new_id(_T(""))
	, m_new_name(_T(""))
	, m_new_sex(_T(""))
	, m_new_birth(_T(""))
	, m_new_telephone(_T(""))
{

}

CInsert::~CInsert()
{
}

void CInsert::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ListNode_List, m_List);
	DDX_Text(pDX, IDC_new_id, m_new_id);
	DDX_Text(pDX, IDC_new_name, m_new_name);
	DDX_Text(pDX, IDC_new_birth, m_new_birth);
	DDX_Text(pDX, IDC_new_telephone, m_new_telephone);
	DDX_Control(pDX, IDC_deposit, deposit);
	DDX_Control(pDX, IDC_show, show);
	DDX_Control(pDX, IDC_Insert, Insert);
	DDX_CBString(pDX, IDC_new_sex, m_new_sex);
	DDX_Control(pDX, IDC_new_sex, use_Sex);
	DDX_Control(pDX, IDC_Update, update);
	DDX_Control(pDX, IDC_new_id, CButton_id);
}


BEGIN_MESSAGE_MAP(CInsert, CDialog)
	ON_BN_CLICKED(IDC_deposit, &CInsert::OnBnClickeddeposit)
	ON_BN_CLICKED(IDC_Insert, &CInsert::OnBnClickedInsert)
	ON_BN_CLICKED(IDC_show, &CInsert::OnBnClickedshow)
	ON_BN_CLICKED(IDC_Update, &CInsert::OnBnClickedButton1)
	ON_BN_CLICKED(IDCANCEL, &CInsert::OnBnClickedCancel)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CInsert 消息处理程序


BOOL CInsert::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	//init();
	m_List.InsertColumn(0, _T("学号"), LVCFMT_CENTER, 60, -1);
	m_List.InsertColumn(1, _T("姓名"), LVCFMT_CENTER, 60, -1);
	m_List.InsertColumn(2, _T("性别"), LVCFMT_CENTER, 60, -1);
	m_List.InsertColumn(3, _T("出生年月"), LVCFMT_CENTER, 100, -1);
	m_List.InsertColumn(4, _T("电话号码"), LVCFMT_CENTER, 100, -1);
	use_Sex.AddString(_T("男"));
	use_Sex.AddString(_T("女"));
	h = init(h);
	p = h;
	if (flag == 0)
	{
		Insert.EnableWindow(0);
		show.EnableWindow(0);
		update.EnableWindow(0);
	}
	else if (flag == 1)
	{
		deposit.EnableWindow(0);
		Insert.EnableWindow(0);
		show.EnableWindow(0);
		CButton_id.EnableWindow(0);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CInsert::OnBnClickeddeposit()//存入
{
	// TODO: 在此添加控件通知处理程序代码
	/*h = init(h);
	p = h;*/
	MYSQL mysqlCon;
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
	UpdateData(true);
	int k = 0;
	char select[1000];
	s = (Node*)malloc(sizeof(Node));
	sprintf_s(select, "select id from student");
	mysql_real_query(&mysqlCon, select, (unsigned long)strlen(select));
	MYSQL_ROW row;
	MYSQL_RES* result;
	result = mysql_store_result(&mysqlCon);
	while ((row = mysql_fetch_row(result)))
	{
		char* ID = row[0];
		if (ID == m_new_id)
		{
			k = 1;
			MessageBox(_T("学号重复，请重新输入学号"), _T("提示"));
			break;
		}
	}
	if (k == 1)
	{
		return;
	}
	else
	{
		USES_CONVERSION;
		LPSTR str;
		str = T2A(m_new_id);
		strcpy_s(s->id, str);
		str = T2A(m_new_name);
		strcpy_s(s->name, str);
		str = T2A(m_new_sex);
		strcpy_s(s->sex, str);
		str = T2A(m_new_birth);
		strcpy_s(s->birth, str);
		str = T2A(m_new_telephone);
		strcpy_s(s->telephone, str);
		p->next = s;
		s->prior = p;
		p = s;
		p->next = NULL;
		int check= MessageBox(_T("继续添加吗？"), _T("添加确认"), MB_YESNO);
		if (check == IDNO)
		{
			deposit.EnableWindow(0);
			show.EnableWindow(1);
		}
		else
		{
			m_new_id = "";
			m_new_name = "";
			m_new_sex = "";
			m_new_birth = "";
			m_new_telephone = "";
		}
		UpdateData(false);
	}
}


void CInsert::OnBnClickedInsert()//入库
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	MYSQL mysqlCon;
	mysql_init(&mysqlCon);
	student st;
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
	DLinklist ptr = (Node*)malloc(sizeof(Node));
	ptr = h->next;
	while (ptr != NULL)
	{
		char insert[1000];
		sprintf_s(insert, "insert into student(id,name,sex,birth,telephone)values('%s','%s','%s','%s','%s')", ptr->id, ptr->name, ptr->sex, ptr->birth, ptr->telephone);
		if (mysql_query(&mysqlCon, insert))
		{
			AfxMessageBox(TEXT("数据入库失败！"));
			return;
		}
		ptr = ptr->next;
	}
	MessageBox(_T("入库成功"));
	Insert.EnableWindow(0);
	UpdateData(false);
	mysql_close(&mysqlCon);
}


void CInsert::OnBnClickedshow()
{
	// TODO: 在此添加控件通知处理程序代码
	DLinklist ptr = (Node*)malloc(sizeof(Node));
	ptr = h->next;
	CString Num;
	Num.Format(_T("%d"),num );
	m_List.InsertItem(num-1, Num);
	int k = 0;
	while (ptr != NULL)
	{
		m_List.InsertItem(k, Num);
		CString myreaddata(ptr->id);
		m_List.SetItemText(k, 0, myreaddata);//添加数据  分别是行 列 值
		myreaddata=ptr->name;
		m_List.SetItemText(k, 1, myreaddata);
		myreaddata=ptr->sex;
		m_List.SetItemText(k, 2, myreaddata);
		myreaddata=ptr->birth;
		m_List.SetItemText(k, 3, myreaddata);
		myreaddata=ptr->telephone;
		m_List.SetItemText(k, 4, myreaddata);
		k++;//这样就能实现数据库和链表的联系
		ptr = ptr->next;
	}
	show.EnableWindow(0);
	Insert.EnableWindow(1);
	UpdateData(false);
}


void CInsert::OnBnClickedButton1()//修改信息入库
{
	// TODO: 在此添加控件通知处理程序代码3
	UpdateData(true);
	student st;
	MYSQL mysqlCon;
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
	USES_CONVERSION;
	LPSTR str;
	str = T2A(select_id);
	strcpy_s(st.id, str);
	str = T2A(m_new_name);
	strcpy_s(st.name, str);
	str = T2A(m_new_sex);
	strcpy_s(st.sex, str);
	str = T2A(m_new_birth);
	strcpy_s(st.birth, str);
	str = T2A(m_new_telephone);
	strcpy_s(st.telephone, str);
	char query[1000];
	sprintf_s(query, "update student set name='%s',sex='%s',birth='%s',telephone='%s' where id='%s';", st.name, st.sex, st.birth, st.telephone, st.id);
	if (mysql_query(&mysqlCon, query))
	{
		MessageBox(_T("修改失败"));
		return;
	}
	else
	{
		MessageBox(_T("修改成功"));
	}
	mysql_close(&mysqlCon);
}


void CInsert::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialog::OnCancel();
}


void CInsert::OnPaint()
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
