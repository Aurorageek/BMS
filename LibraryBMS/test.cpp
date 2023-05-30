// test.cpp: 实现文件
//

#include "pch.h"
#include "LibraryBMS.h"
#include "test.h"
#include "afxdialogex.h"


// test 对话框

IMPLEMENT_DYNAMIC(test, CDialogEx)

test::test(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG2, pParent)
{

}

test::~test()
{
}

void test::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(test, CDialogEx)
END_MESSAGE_MAP()


// test 消息处理程序
