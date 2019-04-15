
// InsMiniDrvDlg.cpp : implementation file
//

#include "stdafx.h"
#include "InsMiniDrv.h"
#include "InsMiniDrvDlg.h"
#include "afxdialogex.h"

#include "DriversUtils.h"
#include "txfutility.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CInsMiniDrvDlg dialog



CInsMiniDrvDlg::CInsMiniDrvDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_INSMINIDRV_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CInsMiniDrvDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MFCEDITBROWSE, m_editPath);
}

BEGIN_MESSAGE_MAP(CInsMiniDrvDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_INSTALL, &CInsMiniDrvDlg::OnBnClickedButtonInstall)
	ON_BN_CLICKED(IDC_BUTTON_DEL, &CInsMiniDrvDlg::OnBnClickedButtonDel)
	ON_WM_DROPFILES()
END_MESSAGE_MAP()


// CInsMiniDrvDlg message handlers

BOOL CInsMiniDrvDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CInsMiniDrvDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CInsMiniDrvDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CInsMiniDrvDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



BOOL CInsMiniDrvDlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_RETURN ||
			pMsg->wParam == VK_ESCAPE)
		{
			return TRUE;
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}


void CInsMiniDrvDlg::OnBnClickedButtonInstall()
{
	CString strPath;

	m_editPath.GetWindowText(strPath);

	if (strPath.Trim() == L"")
	{
		return;
	}

	std::wstring Path = strPath;

	auto [name,ext] = TXF::utility::GetFileNameExt(TXF::utility::WstringToString(Path));

	CString extName (ext.c_str());

	if (extName.CompareNoCase(L".sys"))
	{
		AfxMessageBox(_T("请选择.sys驱动文件"));

		return;
	}

	DriverName = name.c_str();

	BOOL bRet = InstallMinifilter(strPath, DriverName,L"360123");

	if (bRet == FALSE)
	{
		TCHAR* buffer = nullptr;

		DWORD error = ERROR_DS_OBJ_STRING_NAME_EXISTS;

		::FormatMessage(
			FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
			NULL,
			error,
			0,
			(LPTSTR)&buffer,
			0,
			NULL);

		::MessageBox(NULL, buffer, NULL, 0);

		LocalFree(buffer);

		AfxMessageBox(buffer);
	}
}


void CInsMiniDrvDlg::OnBnClickedButtonDel()
{
	if (DriverName != "")
	{
		DeleteDriver(DriverName);
	}
	
}


void CInsMiniDrvDlg::OnDropFiles(HDROP hDropInfo)
{
	int DropCount = DragQueryFile(hDropInfo, -1, NULL, 0);//取得被拖动文件的数目

	for (int i = 0; i < DropCount; i++)
	{
		WCHAR wcStr[MAX_PATH];

		DragQueryFile(hDropInfo, i, wcStr, MAX_PATH);//获得拖曳的第i个文件的文件名

		m_editPath.SetWindowText(wcStr);
	}

	DragFinish(hDropInfo);  //拖放结束后,释放内存

	CDialogEx::OnDropFiles(hDropInfo);
}
