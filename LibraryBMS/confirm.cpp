// confirm.cpp: 实现文件
//

#include "pch.h"
#include "LibraryBMS.h"
#include "confirm.h"
#include "afxdialogex.h"
#include"LibraryBMSDlg.h"
#include"mysql.h"
// confirm 对话框

IMPLEMENT_DYNAMIC(confirm, CDialogEx)

confirm::confirm(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CONFIRM, pParent)
{

}

confirm::~confirm()
{
}

void confirm::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(confirm, CDialogEx)
	ON_BN_CLICKED(IDOK, &confirm::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &confirm::OnBnClickedCancel)
END_MESSAGE_MAP()

extern CString strSqldel;
extern CString strSqldel1;
extern MYSQL sqlobj;
// confirm 消息处理程序


void confirm::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	mysql_query(&sqlobj, "start transaction");
	mysql_query(&sqlobj, strSqldel);
	mysql_query(&sqlobj, strSqldel1);
	mysql_query(&sqlobj, "if book.bookstate='未借出' THEN");
	mysql_query(&sqlobj, "commit");
	mysql_query(&sqlobj, "ELSE");
	mysql_query(&sqlobj, "ROLLBACK");
	CDialogEx::OnOK();
}


void confirm::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码

	CDialogEx::OnCancel();
}
