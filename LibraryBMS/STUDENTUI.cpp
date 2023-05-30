// STUDENTUI.cpp: 实现文件
//

#include "pch.h"
#include "LibraryBMS.h"
#include "STUDENTUI.h"
#include "afxdialogex.h"
#include"STUQUERY.h"
#include"USERRECORD.h"
// STUDENTUI 对话框

IMPLEMENT_DYNAMIC(STUDENTUI, CDialogEx)

STUDENTUI::STUDENTUI(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MAINF2, pParent)
{

}

STUDENTUI::~STUDENTUI()
{
}

void STUDENTUI::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(STUDENTUI, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &STUDENTUI::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON4, &STUDENTUI::OnBnClickedButton4)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON2, &STUDENTUI::OnBnClickedButton2)
END_MESSAGE_MAP()


// STUDENTUI 消息处理程序


void STUDENTUI::OnBnClickedButton1()//图书借阅
{
	// TODO: 在此添加控件通知处理程序代码
	STUQUERY Dlg;
	Dlg.DoModal();
}


void STUDENTUI::OnBnClickedButton4()//退出登录
{
	// TODO: 在此添加控件通知处理程序代码
	exit(0);
}


void STUDENTUI::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	exit(0);
	//CDialogEx::OnClose();
}

//查询借阅记录/还书
void STUDENTUI::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	USERRECORD Dlg;
	Dlg.DoModal();

}
