
// LibraryBMSDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "LibraryBMS.h"
#include "LibraryBMSDlg.h"
#include "afxdialogex.h"
#include"mysql.h"
#include"confirm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
public:

};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	
END_MESSAGE_MAP()


// CLibraryBMSDlg 对话框



CLibraryBMSDlg::CLibraryBMSDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LIBRARYBMS_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	
}

void CLibraryBMSDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
}

BEGIN_MESSAGE_MAP(CLibraryBMSDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_QUERY, &CLibraryBMSDlg::OnBnClickedQuery)
	ON_BN_CLICKED(IDC_BUTTON5, &CLibraryBMSDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CLibraryBMSDlg::OnBnClickedButton6)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, &CLibraryBMSDlg::OnNMClickList1)
	ON_BN_CLICKED(IDC_BUTTON7, &CLibraryBMSDlg::OnBnClickedButton7)
END_MESSAGE_MAP()


extern MYSQL sqlobj;
// CLibraryBMSDlg 消息处理程序

BOOL CLibraryBMSDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	//GetDlgItem(IDC_BUTTON3)->EnableWindow(FALSE);
	//只用添加这一句话，其他的都是自动生成的
	//在系统启动的时候禁用断开服务器按钮，防止误操作
	
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CLibraryBMSDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CLibraryBMSDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CLibraryBMSDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CLibraryBMSDlg::DispBySql(CString sql)
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

//查询
void CLibraryBMSDlg::OnBnClickedQuery()
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
			if (bookid.IsEmpty()&&bookname.IsEmpty())
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
			if (bookid.IsEmpty() && bookname.IsEmpty()&&bookauthor.IsEmpty())
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
			if (bookid.IsEmpty() && bookname.IsEmpty() && bookauthor.IsEmpty()&&bookpub.IsEmpty())
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


void CLibraryBMSDlg::OnBnClickedButton5()//返回
{
	// TODO: 在此添加控件通知处理程序代码
	EndDialog(0);

}
CString bookstate1;
CString strSqldel;
CString strSqldel1;
void CLibraryBMSDlg::OnBnClickedButton6()//删除
{
	// TODO: 在此添加控件通知处理程序代码
	CString bookid, bookname, bookauthor, bookpub, bookclass;
	GetDlgItemText(IDC_EDIT1, bookid);
	GetDlgItemText(IDC_EDIT2, bookname);
	GetDlgItemText(IDC_EDIT3, bookauthor);
	GetDlgItemText(IDC_EDIT4, bookpub);
	GetDlgItemText(IDC_EDIT5, bookclass);

	
	strSqldel = _T("delete from book where ");
	if (bookid.IsEmpty() && bookname.IsEmpty() && bookauthor.IsEmpty() && bookpub.IsEmpty() && bookclass.IsEmpty())//都为空跳出弹框
	{
		MessageBox(_T("请输入删除的查询条件"));
	}

	
	else
	{
			if (!bookid.IsEmpty())//编号不为空
			{
				if (bookstate1 == "未借出")
				{
					strSqldel += _T("bookid=") + bookid;
				}
				else 
				{
					MessageBox("该书已被借出！");
					return;
				}
			}
			else
			{
				MessageBox("请确定要删除书籍的ID！");
				return;
			}
		}

	


	strSqldel1 = _T("delete from record where bookid=") + bookid;
	confirm  Dlg;
	Dlg.DoModal();

	

	DispBySql(_T("select * from book"));

}



void CLibraryBMSDlg::OnNMClickList1(NMHDR* pNMHDR, LRESULT* pResult)
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
		bookstate1=m_list.GetItemText(pListView->iItem, 6);

		//显示到下面的文本框中
		SetDlgItemText(IDC_EDIT1, bookid);
		SetDlgItemText(IDC_EDIT2, bookname);
		SetDlgItemText(IDC_EDIT3, bookauthor);
		SetDlgItemText(IDC_EDIT4, bookpub);
		SetDlgItemText(IDC_EDIT5, bookclass);
	}

	
}


void CLibraryBMSDlg::OnBnClickedButton7()//修改
{
	// TODO: 在此添加控件通知处理程序代码
	CString bookid, bookname, bookauthor, bookpub, bookclass;
	GetDlgItemText(IDC_EDIT1, bookid);
	GetDlgItemText(IDC_EDIT2, bookname);
	GetDlgItemText(IDC_EDIT3, bookauthor);
	GetDlgItemText(IDC_EDIT4, bookpub);
	GetDlgItemText(IDC_EDIT5, bookclass);

	//update book set bookname="八体", where bookid=1000001;
	
	CString strSqlchange = _T("update book set ");
	if (bookid.IsEmpty())
	{
		MessageBox(_T("请输入要修改的Id"), _T("修改操作"), MB_ICONWARNING);
		return;
	}
	strSqlchange += _T("bookname=\'") + bookname + _T("\'");
	strSqlchange += _T(",bookauthor=\'") + bookauthor + _T("\'");
	strSqlchange += _T(",bookpublisher=\'") + bookpub + _T("\'");
	strSqlchange += _T(",bookclass=\'") + bookclass + _T("\'");
	strSqlchange += _T(" where bookid=") + bookid;

	//MessageBox(strSqlchange);
	mysql_query(&sqlobj, strSqlchange);

	//更新列表显示
	DispBySql(_T("select* from book"));

}

