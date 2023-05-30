// USERRECORD.cpp: 实现文件
//

#include "pch.h"
#include "LibraryBMS.h"
#include "USERRECORD.h"
#include "afxdialogex.h"
#include"mysql.h"
#include"LOGIN.h"

// USERRECORD 对话框

IMPLEMENT_DYNAMIC(USERRECORD, CDialogEx)

USERRECORD::USERRECORD(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_USERRECORD, pParent)
{

}

USERRECORD::~USERRECORD()
{
}

void USERRECORD::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
}


BEGIN_MESSAGE_MAP(USERRECORD, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON2, &USERRECORD::OnBnClickedButton2)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, &USERRECORD::OnNMClickList1)
	ON_BN_CLICKED(IDC_BUTTON1, &USERRECORD::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON5, &USERRECORD::OnBnClickedButton5)
END_MESSAGE_MAP()


extern MYSQL sqlobj;

// USERRECORD 消息处理程序
void USERRECORD::DispBySql(CString sql)
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
//返回
void USERRECORD::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	EndDialog(0);
}


void USERRECORD::OnNMClickList1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;

	NMLISTVIEW* pListView = (NMLISTVIEW*)pNMHDR;
	//pListView->iTem 代表选中的那一行
	if (-1 != pListView->iItem)//对应pListView->iItem!=-1代表我们选中一行
	{
		CString recordid = m_list.GetItemText(pListView->iItem, 0);
		CString bookid = m_list.GetItemText(pListView->iItem, 2);
		CString bookname = m_list.GetItemText(pListView->iItem, 3);
		CString bookstate = m_list.GetItemText(pListView->iItem, 7);
		//显示到下面的文本框中
		SetDlgItemText(IDC_EDIT1, recordid);
		SetDlgItemText(IDC_EDIT2, bookid);
		SetDlgItemText(IDC_EDIT3, bookname);
		SetDlgItemText(IDC_EDIT4, bookstate);
		
	}
}

extern CString userid;
//查阅
void USERRECORD::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CString recordid,bookid, bookname;
	GetDlgItemText(IDC_EDIT1, recordid);
	//GetDlgItemText(IDC_EDIT2, userid);
	GetDlgItemText(IDC_EDIT2, bookid);
	GetDlgItemText(IDC_EDIT3, bookname);


	CString strSql;
	if (recordid.IsEmpty() && bookid.IsEmpty() && bookname.IsEmpty())//都为空查询该用户所有
	{
		strSql.Format("select * from record where userid=%s",userid);
	}
	else//存在不为空
	{
		strSql = _T("select * from record where ");

		if (!recordid.IsEmpty())//编号不为空
		{
			strSql += _T("recordid=") + recordid;
		}
	
		if (!bookid.IsEmpty())//书的编号不为空
		{
			if (recordid.IsEmpty())
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
			if (recordid.IsEmpty() && bookid.IsEmpty())
			{
				strSql += _T("bookname=\'") + bookname + _T("\'");
			}
			else
			{
				strSql += _T(" and bookname=\'") + bookname + _T("\'");
			}
		}

		strSql += _T(" and userid=") + userid;

	}

	//MessageBox(strSql);
	DispBySql(strSql);




}

//还书
void USERRECORD::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	CString recordid, bookid, bookname,bookstate;
	GetDlgItemText(IDC_EDIT1, recordid);
	GetDlgItemText(IDC_EDIT2, bookid);
	GetDlgItemText(IDC_EDIT3, bookname);
	GetDlgItemText(IDC_EDIT4, bookstate);


	CTime currentTime = CTime::GetCurrentTime();
	CString strDateTime = currentTime.Format("%Y-%m-%d %H:%M:%S");//获取系统时间
	CString strsql;
	//strsql.Format("update record set returntime='%s',isreturn='是' where bookid=%s and isreturn='否' and recordid=%s",strDateTime,bookid,recordid);
	strsql.Format("call stateupdate(%s,%s,\'%s\')", bookid, recordid, bookstate);//调用存储过程
	
	//MessageBox(strsql);
	if (bookstate=="否")
	{
		mysql_query(&sqlobj, strsql);
		MessageBox(_T("还书成功，恭喜您又读完了一本书！"));
	}
	else
	{
		MessageBox(_T("还书失败！可能该书您已经归还！"));
	}
	//更新列表显示
	CString strr;
	strr.Format("select * from record where userid=%s", userid);
	DispBySql(strr);

	

}
