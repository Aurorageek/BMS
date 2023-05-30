// LOGIN.cpp: 实现文件
//

#include "pch.h"
#include "LibraryBMS.h"
#include "LOGIN.h"
#include "afxdialogex.h"
#include "CInfoFile.h"
#include"mysql.h"
#include"MANAGERUI.h"
#include"STUDENTUI.h"
#include"test.h"
// LOGIN 对话框

IMPLEMENT_DYNAMIC(LOGIN, CDialogEx)

LOGIN::LOGIN(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LOGIN, pParent)
	, m_user(_T(""))
	, m_pwd(_T(""))
{
	
}

LOGIN::~LOGIN()
{
}

void LOGIN::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_user);
	DDX_Text(pDX, IDC_EDIT2, m_pwd);
}


BEGIN_MESSAGE_MAP(LOGIN, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &LOGIN::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &LOGIN::OnBnClickedButton2)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_RADIO1, &LOGIN::OnBnClickedRadio1)
END_MESSAGE_MAP()

CString userid;
// LOGIN 消息处理程序
extern MYSQL sqlobj;

void LOGIN::OnBnClickedButton1()
{
	UpdateData(TRUE);
	// TODO: 在此添加控件通知处理程序代码

	mysql_init(&sqlobj);
	if (mysql_real_connect(&sqlobj, "localhost", "root", "xuan1109lxy.", "bms", 3306, NULL, 0)) {
		//MessageBox("连接成功");
		mysql_query(&sqlobj, "set names 'gb2312'");
	}
	CInfoFile file;
	CString Account, Password;
	
	GetDlgItemText(IDC_EDIT1, Account);
	GetDlgItemText(IDC_EDIT2, Password);

	if (Account.GetLength() != 7&&Account.GetLength()!=5) {
		MessageBox("账号格式错误，正确位数为七位或五位！");
		return;
	}

	// 密码长度判断
	if (Password.GetLength() > 18 || Password.GetLength() < 6) {
		MessageBox("密码长度为6-18个字符！");
		return;
	}

	// 构造查询语句
	CString query;
	if (((CButton*)GetDlgItem(IDC_RADIO1))->GetCheck() == 1)//学生
	{
		query.Format("SELECT * FROM user WHERE user_id='%s' AND user_code='%s'", Account, Password);

		// 执行查询
		if (mysql_query(&sqlobj, query)) {
			MessageBox(mysql_error(&sqlobj));
			return;
		}

		// 获取查询结果
		MYSQL_RES* result = mysql_store_result(&sqlobj);

		// 判断结果集中是否有行
		if (mysql_num_rows(result) > 0) {
			// 匹配成功
			MYSQL_ROW row = mysql_fetch_row(result);
			CString name = CString(row[1]);
			userid = CString(row[0]);
			STUDENTUI dlg;
			// 读取结果集中的数据
			//dlg.name = name;
			//dlg.major_id = atoi(row[1]);
			//dlg.number = atoi(row[0]);

			CString str;
			str.Format("欢迎 %s", name);
			MessageBox(str);

			CDialog::OnOK();
			dlg.DoModal();

		}
		else {
			// 匹配失败
			MessageBox("账号或密码错误！");
		}

		// 释放结果集
		mysql_free_result(result);
	}

	if (((CButton*)GetDlgItem(IDC_RADIO2))->GetCheck() == 1)//管理员
	{
		query.Format("SELECT * FROM admin WHERE admin_id='%s' AND admin_code='%s'", Account, Password);

		// 执行查询
		if (mysql_query(&sqlobj, query)) {
			MessageBox(mysql_error(&sqlobj));
			return;
		}

		// 获取查询结果
		MYSQL_RES* result = mysql_store_result(&sqlobj);

		// 判断结果集中是否有行
		if (mysql_num_rows(result) > 0) {
			// 匹配成功
			MYSQL_ROW row = mysql_fetch_row(result);
			CString name = CString(row[1]);
			 userid= CString(row[0]);

			MANAGERUI dlg;
			// 读取结果集中的数据
			//dlg.name = name;
			//dlg.major_id = atoi(row[1]);
			//dlg.number = atoi(row[0]);

			CString str;
			str.Format("欢迎 %s", name);
			MessageBox(str);

			CDialog::OnOK();
			dlg.DoModal();

		}
		else {
			// 匹配失败
			MessageBox("账号或密码错误！");
		}

		// 释放结果集
		mysql_free_result(result);
	}
	if(((CButton*)GetDlgItem(IDC_RADIO2))->GetCheck() == 0&& ((CButton*)GetDlgItem(IDC_RADIO1))->GetCheck()==0) 
	{
		MessageBox(_T("请选择您的身份！"));
	}


	

}


BOOL LOGIN::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	//m_user = TEXT("lxy");
	//m_pwd = TEXT("123456");

	UpdateData(TRUE);//内容更新到对应控件

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE


	
}


void LOGIN::OnBnClickedButton2()//退出按钮
{

	// TODO: 在此添加控件通知处理程序代码
	exit(0);
}


void LOGIN::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	exit(0);
	//CDialogEx::OnClose();
}


void LOGIN::OnBnClickedRadio1()
{
	// TODO: 在此添加控件通知处理程序代码
}
