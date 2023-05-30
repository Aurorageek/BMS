#pragma once


// STUQUERY 对话框

class STUQUERY : public CDialogEx
{
	DECLARE_DYNAMIC(STUQUERY)

public:
	STUQUERY(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~STUQUERY();
	void DispBySql(CString sql);
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_STUQUERY };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedQuery();
	CListCtrl m_list;
	afx_msg void OnBnClickedButton5();
	afx_msg void OnNMClickList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBnClickedButton1();
	virtual BOOL OnInitDialog();
};
