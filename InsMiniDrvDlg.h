
// InsMiniDrvDlg.h : header file
//

#pragma once


// CInsMiniDrvDlg dialog
class CInsMiniDrvDlg : public CDialogEx
{
// Construction
public:
	CInsMiniDrvDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_INSMINIDRV_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;
	CString DriverName;
	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedButtonInstall();
	afx_msg void OnBnClickedButtonDel();
private:
	CMFCEditBrowseCtrl m_editPath;
};
