#pragma once


// MANAGERUI 对话框

class MANAGERUI : public CDialogEx
{
	DECLARE_DYNAMIC(MANAGERUI)

public:
	MANAGERUI(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~MANAGERUI();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MAINF1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnClose();
	afx_msg void OnBnClickedButton3();
};
