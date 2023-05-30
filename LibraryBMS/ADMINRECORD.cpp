// ADMINRECORD.cpp: 实现文件
//

#include "pch.h"
#include "LibraryBMS.h"
#include "ADMINRECORD.h"
#include "afxdialogex.h"
#include"mysql.h"
#include"overtime.h"

// ADMINRECORD 对话框

IMPLEMENT_DYNAMIC(ADMINRECORD, CDialogEx)

ADMINRECORD::ADMINRECORD(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ADMINRECORD, pParent)
{

}

ADMINRECORD::~ADMINRECORD()
{
}

void ADMINRECORD::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST2, m_list);
}


BEGIN_MESSAGE_MAP(ADMINRECORD, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &ADMINRECORD::OnBnClickedButton1)
	
	ON_BN_CLICKED(IDC_BUTTON2, &ADMINRECORD::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON8, &ADMINRECORD::OnBnClickedButton8)
END_MESSAGE_MAP()


extern MYSQL sqlobj;

// ADMINRECORD 消息处理程序
void ADMINRECORD::DispBySql(CString sql)
{

	//1.删除列表控件中的数据
	int nColumnCount = m_list.GetHeaderCtrl()->GetItemCount();
	for (int i = 0; i < nColumnCount; i++)
	{
		m_list.DeleteColumn(0);//删除头部标题
	}
	m_list.DeleteAllItems();//删除所有行的数据


	//2.根据sql语句查询数据库
	//查询数据库
	mysql_query(&sqlobj, sql);
	//resultSet代表数据表中的每一行的数据
	MYSQL_RES* resultSet = mysql_store_result(&sqlobj);

	//如果数据库中的没有对应的信息的话
	if (!resultSet)
	{
		//可能是数据出现错误
		MessageBox(_T("出现错误,可能:数据库中没有对应的表..."), _T("MYSQL"), MB_OK | MB_ICONERROR);
		return;
	}


	//3.插入头部
	//遍历对应字符串的名称
	//数据库的宽高
	CRect rect;
	//把宽高进行四等分
	m_list.GetWindowRect(&rect);
	CString head[8];
	head[0] = _T("记录编号");
	head[1] = _T("用户ID");
	head[2] = _T("图书编号");
	head[3] = _T("图书名称");
	head[4] = _T("借阅时间");
	head[5] = _T("最晚归还时间");
	head[6] = _T("归还时间");
	head[7] = _T("是否已归还");
	MYSQL_FIELD* filed;//这是一个域  这个域就是把数据库中每个数据库的信息给遍历出来
	for (int i = 0; filed = mysql_fetch_field(resultSet); i++)
	{
		//每列的信息都是对应的平均分配的
		m_list.InsertColumn(i, head[i], LVCFMT_LEFT, rect.Width() / mysql_num_fields(resultSet));

	}
	//获取数据库中的真实数据行
	if (mysql_num_rows(resultSet) <= 0)
	{
		MessageBox(_T("数据库中没有任何记录"), _T("MYSQL"), MB_OK | MB_ICONWARNING);
		return;
	}

	//4.插入真实数据
	int nRow = 0;
	MYSQL_ROW row;//获取数据库一行的数据 row对应是一个二级指针
	while (row = mysql_fetch_row(resultSet))//获取到一行的真实数据
	{
		int nField = mysql_num_fields(resultSet);//获取到MySql数据库的字段//对应看他们有多少字段
		for (int i = 0; i < nField; i++)
		{
			if (i == 0)
			{
				m_list.InsertItem(nRow, row[i]);//插入第一列
			}
			else
			{
				m_list.SetItemText(nRow, i, row[i]);//插入第二三四列
			}
		}
		nRow++;
	}
	mysql_free_result(resultSet);


}

void ADMINRECORD::OnBnClickedButton1()//查询记录
{
	// TODO: 在此添加控件通知处理程序代码
	CString recordid, userid, bookid, bookname;
	GetDlgItemText(IDC_EDIT1, recordid);
	GetDlgItemText(IDC_EDIT2, userid);
	GetDlgItemText(IDC_EDIT3, bookid);
	GetDlgItemText(IDC_EDIT4, bookname);
	

	CString strSql;
	if (recordid.IsEmpty() && userid.IsEmpty() && bookid.IsEmpty() && bookname.IsEmpty())//都为空查询所有
	{
		strSql = _T("select * from record");
	}
	else//存在不为空
	{
		strSql = _T("select * from record where ");

		if (!recordid.IsEmpty())//编号不为空
		{
			strSql += _T("recordid=") + recordid;
		}
		if (!userid.IsEmpty())//用户id不为空
		{
			if (recordid.IsEmpty())
			{
				strSql += _T("userid=") + userid ;
			}
			else
			{
				strSql += _T(" and userid=") + userid;
			}
		}
		if (!bookid.IsEmpty())//书的编号不为空
		{
			if (recordid.IsEmpty() && userid.IsEmpty())
			{
				strSql += _T("bookid=") + bookid;
			}
			else
			{
				strSql += _T(" and bookid=") + bookid;
			}
		}

		if (!bookname.IsEmpty())//书的出版社不为空
		{
			if (recordid.IsEmpty() && userid.IsEmpty() && bookid.IsEmpty())
			{
				strSql += _T("bookname=\'") + bookname + _T("\'");
			}
			else
			{
				strSql += _T(" and bookname=\'") + bookname + _T("\'");
			}
		}


	}

	//MessageBox(strSql);
	DispBySql(strSql);


}





void ADMINRECORD::OnBnClickedButton2()//返回
{
	// TODO: 在此添加控件通知处理程序代码
	EndDialog(0);
}

//查询已超时
void ADMINRECORD::OnBnClickedButton8()
{
	// TODO: 在此添加控件通知处理程序代码
	overtime ot;
	ot.DoModal();
}
