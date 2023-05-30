#pragma once


// USERRECORD 对话框

class USERRECORD : public CDialogEx
{
	DECLARE_DYNAMIC(USERRECORD)

public:
	USERRECORD(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~USERRECORD();
	void USERRECORD::DispBySql(CString sql);
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_USERRECORD };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_list;
	afx_msg void OnBnClickedButton2();
	afx_msg void OnNMClickList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton5();
};
