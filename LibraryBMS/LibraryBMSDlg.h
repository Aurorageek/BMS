
// LibraryBMSDlg.h: 头文件
//

#pragma once


// CLibraryBMSDlg 对话框
class CLibraryBMSDlg : public CDialogEx
{
// 构造
public:
	CLibraryBMSDlg(CWnd* pParent = nullptr);	// 标准构造函数
	//查询数据库代码
	void DispBySql(CString sql);

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LIBRARYBMS_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;
	

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_list;

	afx_msg void OnBnClickedQuery();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	
	afx_msg void OnNMClickList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBnClickedButton7();
};
