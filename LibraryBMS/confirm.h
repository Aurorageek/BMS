#pragma once


// confirm 对话框

class confirm : public CDialogEx
{
	DECLARE_DYNAMIC(confirm)

public:
	confirm(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~confirm();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CONFIRM };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
