// CManager_oper.cpp: 实现文件
//

#include "pch.h"
#include "Bank-management.h"
#include "CManager_oper.h"
#include "afxdialogex.h"
#include"CRegist.h"
#include"CManager_regist.h"
#include"CDelete.h"
#include"CUpdate.h"
#include"CReport.h"
#include"COutput.h"
#include"CSetrate.h"

// CManager_oper 对话框
IMPLEMENT_DYNAMIC(CManager_oper, CDialog)

CManager_oper::CManager_oper(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_ManagerOpe, pParent)
{

}

CManager_oper::~CManager_oper()
{
}

void CManager_oper::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CManager_oper, CDialog)
	ON_COMMAND(ID_regist_user, &CManager_oper::Onregistuser)
	ON_COMMAND(ID_regist_manager, &CManager_oper::Onregistmanager)
	ON_COMMAND(ID_delete_user, &CManager_oper::Ondeleteuser)
	ON_COMMAND(ID_update_userinformation, &CManager_oper::Onupdateuserinformation)
	ON_COMMAND(ID_report_user, &CManager_oper::Onreportuser)
	ON_COMMAND(ID_output_user, &CManager_oper::Onoutputuser)
	ON_COMMAND(ID_rate, &CManager_oper::Onrate)
END_MESSAGE_MAP()


// CManager_oper 消息处理程序


BOOL CManager_oper::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CMenu menu;
	menu.LoadMenu(IDR_MENU_managerOpe);
	SetMenu(&menu);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CManager_oper::Onregistuser()
{
	// TODO: 在此添加命令处理程序代码
	CRegist regist;
	regist.DoModal();
}


void CManager_oper::Onregistmanager()
{
	// TODO: 在此添加命令处理程序代码
	CManager_regist manager_regsit;
	manager_regsit.DoModal();
}


void CManager_oper::Ondeleteuser()
{
	// TODO: 在此添加命令处理程序代码
	CDelete Delete;
	Delete.DoModal();
}


void CManager_oper::Onupdateuserinformation()
{
	// TODO: 在此添加命令处理程序代码
	CUpdate Update;
	Update.DoModal();
}


void CManager_oper::Onreportuser()
{
	// TODO: 在此添加命令处理程序代码
	CReport report;
	report.DoModal();
}


void CManager_oper::Onoutputuser()
{
	// TODO: 在此添加命令处理程序代码
	COutput output;
	output.DoModal();
}


void CManager_oper::Onrate()
{
	// TODO: 在此添加命令处理程序代码
	CSetrate setrate;
	setrate.DoModal();
}
