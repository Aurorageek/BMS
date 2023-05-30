#pragma once


// WRITE 对话框

class WRITE : public CDialogEx
{
	DECLARE_DYNAMIC(WRITE)

public:
	WRITE(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~WRITE();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_WRITE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton1();
};
