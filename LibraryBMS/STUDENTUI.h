#pragma once


// STUDENTUI 对话框

class STUDENTUI : public CDialogEx
{
	DECLARE_DYNAMIC(STUDENTUI)

public:
	STUDENTUI(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~STUDENTUI();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MAINF2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnClose();
	afx_msg void OnBnClickedButton2();
};
