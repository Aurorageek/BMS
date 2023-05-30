// overtime.cpp: 实现文件
//

#include "pch.h"
#include "LibraryBMS.h"
#include "overtime.h"
#include "afxdialogex.h"
#include"mysql.h"

// overtime 对话框

IMPLEMENT_DYNAMIC(overtime, CDialogEx)

overtime::overtime(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

overtime::~overtime()
{
}

void overtime::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
}


BEGIN_MESSAGE_MAP(overtime, CDialogEx)
END_MESSAGE_MAP()


// overtime 消息处理程序



extern MYSQL sqlobj;

BOOL overtime::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	//1.删除列表控件中的数据
	int nColumnCount = m_list.GetHeaderCtrl()->GetItemCount();
	for (int i = 0; i < nColumnCount; i++)
	{
		m_list.DeleteColumn(0);//删除头部标题
	}
	m_list.DeleteAllItems();//删除所有行的数据

	CString sql = _T("select * from overtime");
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
		return true;
	}


	//3.插入头部
	//遍历对应字符串的名称
	//数据库的宽高
	CRect rect;
	//把宽高进行四等分
	m_list.GetWindowRect(&rect);
	CString head[7];
	head[0] = _T("用户id");
	head[1] = _T("用户姓名");
	head[2] = _T("用户电话");
	head[3] = _T("记录编号");
	head[4] = _T("被借书籍编号");
	head[5] = _T("借阅时间");
	head[6] = _T("最晚归还时间");
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
		return true;
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

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
