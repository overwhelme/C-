#pragma once


// CInsert 对话框

class CInsert : public CDialog
{
	DECLARE_DYNAMIC(CInsert)

public:
	CInsert(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CInsert();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Insert };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_List;
	virtual BOOL OnInitDialog();
	CString m_new_id;
	CString m_new_name;
	CString m_new_sex;
	CString m_new_birth;
	CString m_new_telephone;
	afx_msg void OnBnClickeddeposit();
	afx_msg void OnBnClickedInsert();
	CButton deposit;
	CButton show;
	CButton Insert;
	afx_msg void OnBnClickedshow();
	CComboBox use_Sex;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedCancel();
	CButton update;
	CEdit CButton_id;
	afx_msg void OnPaint();
};


struct student
{
	char id[10];
	char name[10];
	char sex[10];
	char birth[15];
	char telephone[15];
};

typedef struct node
{
	char id[10];
	char name[10];
	char sex[10];
	char birth[15];
	char telephone[15];
	struct node *prior,*next;
}Node,*DLinklist;

inline DLinklist init(DLinklist h)
{
	h=(Node *)malloc(sizeof(Node));
    h->prior=NULL;
    h->next=NULL;
    return h;
}

/*inline int GetListLength(DLinklist h)
{
	if (h== NULL)
	{
		return 0;
	}
	DLinklist p = h;
	int aListLen = 0;
	while (p != NULL)    //判断当前节点指针是否为空
	{
		aListLen++;
		p = p->next;
	}
	return aListLen;
}*/
