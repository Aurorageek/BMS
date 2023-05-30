// MANAGERUI.cpp: 实现文件
//

#include "pch.h"
#include "LibraryBMS.h"
#include "MANAGERUI.h"
#include "afxdialogex.h"
#include "WRITE.h"
#include "LibraryBMSDlg.h"
#include"ADMINRECORD.h"

// MANAGERUI 对话框

IMPLEMENT_DYNAMIC(MANAGERUI, CDialogEx)

MANAGERUI::MANAGERUI(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MAINF1, pParent)
{

}

MANAGERUI::~MANAGERUI()
{
}

void MANAGERUI::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(MANAGERUI, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &MANAGERUI::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON4, &MANAGERUI::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON2, &MANAGERUI::OnBnClickedButton2)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON3, &MANAGERUI::OnBnClickedButton3)
END_MESSAGE_MAP()


// MANAGERUI 消息处理程序


void MANAGERUI::OnBnClickedButton1()//图书信息录入
{
	// TODO: 在此添加控件通知处理程序代码
	WRITE  Dlg;
	Dlg.DoModal();

}
void MANAGERUI::OnBnClickedButton2()//图书管理
{
	// TODO: 在此添加控件通知处理程序代码
	CLibraryBMSDlg Dlg;
	Dlg.DoModal();
}

void MANAGERUI::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	exit(0);
}





void MANAGERUI::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	exit(0);
	//CDialogEx::OnClose();
}

//查询借阅记录
void MANAGERUI::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	ADMINRECORD Dlg;
	Dlg.DoModal();

}
