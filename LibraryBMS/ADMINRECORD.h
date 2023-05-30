#pragma once


// ADMINRECORD 对话框

class ADMINRECORD : public CDialogEx
{
	DECLARE_DYNAMIC(ADMINRECORD)

public:
	ADMINRECORD(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~ADMINRECORD();
	void ADMINRECORD::DispBySql(CString sql);
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ADMINRECORD };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_list;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton8();
};
