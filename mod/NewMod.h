#pragma once


// CNewMod 对话框

class CNewMod : public CDialogEx
{
	DECLARE_DYNAMIC(CNewMod)

public:
	CNewMod(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CNewMod();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_NEWMOD };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnModView();
	afx_msg void OnModCreate();
};
