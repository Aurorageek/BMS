// WRITE.cpp: 实现文件
//

#include "pch.h"
#include "LibraryBMS.h"
#include "WRITE.h"
#include "afxdialogex.h"
#include"mysql.h"

// WRITE 对话框

IMPLEMENT_DYNAMIC(WRITE, CDialogEx)

WRITE::WRITE(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_WRITE, pParent)
{

}

WRITE::~WRITE()
{
}

void WRITE::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(WRITE, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON2, &WRITE::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON1, &WRITE::OnBnClickedButton1)
END_MESSAGE_MAP()




extern MYSQL sqlobj;
// WRITE 消息处理程序


void WRITE::OnBnClickedButton2()//图书信息录入
{

	
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	// TODO: 在此添加控件通知处理程序代码
	CString bookid, bookname, bookauthor, bookpub, bookclass;
	GetDlgItemText(IDC_EDIT1, bookid);
	GetDlgItemText(IDC_EDIT2, bookname);
	GetDlgItemText(IDC_EDIT3, bookauthor);
	GetDlgItemText(IDC_EDIT4, bookpub);
	GetDlgItemText(IDC_EDIT5, bookclass);

	CString booksum = _T("0");//借阅次数，录入时初始都为0
	CString bookstate = _T("未借出");//借阅，初始时都未借出
	//中文乱码问题
	mysql_query(&sqlobj, "set names 'gb2312'");



	//拼接str语句
	CString str_connect;
	str_connect = _T("insert into book(bookid,bookname,bookauthor,bookpublisher,bookclass,booksum,bookstate) values(");
	str_connect += bookid + _T(",\'") + bookname + _T("'\,\'") + bookauthor + _T("'\,\'") + bookpub + _T("'\,\'")
		+ bookclass + _T("'\,") + booksum + _T(",\'") + bookstate  + _T("'\)");

	//MessageBox(str_connect);


	if (bookid.IsEmpty() || bookname.IsEmpty() || bookauthor.IsEmpty() || bookpub.IsEmpty()
		|| bookclass.IsEmpty())//检测是否存在空
	{
		MessageBox(_T("请输入完整图书信息"));
		return;
	}

	int res = mysql_query(&sqlobj, str_connect);
	if (res)
	{
		MessageBox(_T("插入失败！可能图书编号(id)已经存在或你不符合要求"));
		return;
	}
	else
	{
		MessageBox(_T("插入成功！"));
	}

	

	UpdateData(false);

	
}


void WRITE::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	EndDialog(0);
}
