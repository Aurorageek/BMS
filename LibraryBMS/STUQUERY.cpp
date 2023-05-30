// STUQUERY.cpp: 实现文件
//

#include "pch.h"
#include "LibraryBMS.h"
#include "STUQUERY.h"
#include "afxdialogex.h"
#include"mysql.h"
#include"LOGIN.h"
#include<fstream>
// STUQUERY 对话框

IMPLEMENT_DYNAMIC(STUQUERY, CDialogEx)

STUQUERY::STUQUERY(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_STUQUERY, pParent)
{

}

STUQUERY::~STUQUERY()
{
}

void STUQUERY::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
}


BEGIN_MESSAGE_MAP(STUQUERY, CDialogEx)
	ON_BN_CLICKED(IDC_QUERY, &STUQUERY::OnBnClickedQuery)
	
	ON_BN_CLICKED(IDC_BUTTON5, &STUQUERY::OnBnClickedButton5)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, &STUQUERY::OnNMClickList1)
	ON_BN_CLICKED(IDC_BUTTON1, &STUQUERY::OnBnClickedButton1)
END_MESSAGE_MAP()

extern MYSQL sqlobj;
extern CString userid;
// STUQUERY 消息处理程序

void STUQUERY::DispBySql(CString sql)
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
	CString head[7];
	head[0] = _T("图书编号");
	head[1] = _T("图书名称");
	head[2] = _T("作者");
	head[3] = _T("出版社");
	head[4] = _T("类别");
	head[5] = _T("借阅总次数");
	head[6] = _T("当前状态");
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
void STUQUERY::OnBnClickedQuery()
{
	// TODO: 在此添加控件通知处理程序代码

	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	// TODO: 在此添加控件通知处理程序代码
	CString bookid, bookname, bookauthor, bookpub, bookclass;
	GetDlgItemText(IDC_EDIT1, bookid);
	GetDlgItemText(IDC_EDIT2, bookname);
	GetDlgItemText(IDC_EDIT3, bookauthor);
	GetDlgItemText(IDC_EDIT4, bookpub);
	GetDlgItemText(IDC_EDIT5, bookclass);

	CString strSql;
	if (bookid.IsEmpty() && bookname.IsEmpty() && bookauthor.IsEmpty() && bookpub.IsEmpty() && bookclass.IsEmpty())//都为空查询所有
	{
		strSql = _T("select * from book");
	}
	else//存在不为空
	{
		strSql = _T("select * from book where ");

		if (!bookid.IsEmpty())//编号不为空
		{
			strSql += _T("bookid=") + bookid;
		}
		if (!bookname.IsEmpty())//书的名字不为空
		{
			if (bookid.IsEmpty())
			{
				strSql += _T("bookname=\'") + bookname + _T("\'");
			}
			else
			{
				strSql += _T(" and bookname=\'") + bookname + _T("\'");
			}
		}
		if (!bookauthor.IsEmpty())//书的作者不为空
		{
			if (bookid.IsEmpty() && bookname.IsEmpty())
			{
				strSql += _T("bookauthor=\'") + bookauthor + _T("\'");
			}
			else
			{
				strSql += _T(" and bookauthor=\'") + bookauthor + _T("\'");
			}
		}

		if (!bookpub.IsEmpty())//书的出版社不为空
		{
			if (bookid.IsEmpty() && bookname.IsEmpty() && bookauthor.IsEmpty())
			{
				strSql += _T("bookpublisher=\'") + bookpub + _T("\'");
			}
			else
			{
				strSql += _T(" and bookpublisher=\'") + bookpub + _T("\'");
			}
		}

		if (!bookclass.IsEmpty())//书的类别不为空
		{
			if (bookid.IsEmpty() && bookname.IsEmpty() && bookauthor.IsEmpty() && bookpub.IsEmpty())
			{
				strSql += _T("bookclass=\'") + bookclass + _T("\'");
			}
			else
			{
				strSql += _T(" and bookclass=\'") + bookclass + _T("\'");
			}
		}


	}

	//MessageBox(strSql);
	
	DispBySql(strSql);
}




void STUQUERY::OnBnClickedButton5()//返回主页面
{
	// TODO: 在此添加控件通知处理程序代码
	EndDialog(0);
}

CString bookstate;
void STUQUERY::OnNMClickList1(NMHDR* pNMHDR, LRESULT* pResult)//查询
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;


	NMLISTVIEW* pListView = (NMLISTVIEW*)pNMHDR;
	//pListView->iTem 代表选中的那一行
	if (-1 != pListView->iItem)//对应pListView->iItem!=-1代表我们选中一行
	{
		CString bookid = m_list.GetItemText(pListView->iItem, 0);
		CString bookname = m_list.GetItemText(pListView->iItem, 1);
		CString bookauthor = m_list.GetItemText(pListView->iItem, 2);
		CString bookpub = m_list.GetItemText(pListView->iItem, 3);
		CString bookclass = m_list.GetItemText(pListView->iItem, 4);
		bookstate= m_list.GetItemText(pListView->iItem, 6);

		//显示到下面的文本框中
		SetDlgItemText(IDC_EDIT1, bookid);
		SetDlgItemText(IDC_EDIT2, bookname);
		SetDlgItemText(IDC_EDIT3, bookauthor);
		SetDlgItemText(IDC_EDIT4, bookpub);
		SetDlgItemText(IDC_EDIT5, bookclass);
	}

}
using namespace std;
CString recordid;
BOOL STUQUERY::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	
	fstream file;
	file.open("recordid.txt", ios::in);
	char buf[10];
	file.getline(buf, 10); //普通读取
	recordid = buf;

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
//借阅功能
void STUQUERY::OnBnClickedButton1()
{
	
	CString id;
	id = recordid;
	// TODO: 在此添加控件通知处理程序代码
	CString bookid, bookname, bookauthor, bookpub, bookclass;
	GetDlgItemText(IDC_EDIT1, bookid);
	GetDlgItemText(IDC_EDIT2, bookname);
	GetDlgItemText(IDC_EDIT3, bookauthor);
	GetDlgItemText(IDC_EDIT4, bookpub);
	GetDlgItemText(IDC_EDIT5, bookclass);

	CTime currentTime = CTime::GetCurrentTime();
	CString strDateTime = currentTime.Format("%Y-%m-%d %H:%M:%S");
	//insert into record values(id,userid,bookid,bookname,strDateTime,null,'否')

	//设置最晚归还时间为借阅时间的一个月之后
	int currentMonth = currentTime.GetMonth();
	int nextMonth = currentMonth + 1;
	int currentYear = currentTime.GetYear();
	if (nextMonth > 12) {
		nextMonth = 1;
		currentYear++;
	}

	int currentDay = currentTime.GetDay();
	int currentHour = currentTime.GetHour();
	int currentMinute = currentTime.GetMinute();
	int currentSecond = currentTime.GetSecond();
	CTime nextMonthTime(currentYear, nextMonth, currentDay, currentHour, currentMinute, currentSecond);

	CString deadline = nextMonthTime.Format("%Y-%m-%d %H:%M:%S");



	CString recordstr="insert into record values(";
	recordstr += id + _T(",");
	recordstr += userid + _T(",");
	recordstr += bookid + _T(",\'");
	recordstr += bookname + _T("\',\'");
	recordstr += strDateTime + _T("\',\'");
	recordstr += deadline+ _T("\',");
	recordstr += "null,\'否\')";

	if (bookstate == "已借出")
	{
		MessageBox(_T("该书已被借出"));
	}
	else {
		if (!mysql_query(&sqlobj, recordstr))//借阅成功
		{
			fstream file;
			file.open("recordid.txt", ios::in);
			char buf[10];
			file.getline(buf, 10); //普通读取
			recordid = buf;
			int id = _ttoi(recordid);
			id++;
			recordid.Format("%d", id);//加一
			file.close();

			string file_name = "recordid.txt";
			ofstream file_writer(file_name, ios_base::out);
			file_writer << recordid << "\n";
			file_writer.close();


			MessageBox(_T("借阅成功！"));
		}
		else
		{
			MessageBox(_T("借阅失败，借阅信息不正确！"));
		}

	}
	
	
	//MessageBox(recordstr);
	CString strall = "select * from book";
	DispBySql(strall);
	

}



