
// MainFrm.cpp: CMainFrame 类的实现
//

#include "stdafx.h"
#include "mod.h"

#include "MainFrm.h"

#include "modDoc.h"
#include "modView.h"
#include "folderTree.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // 状态行指示器
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame 构造/析构

CMainFrame::CMainFrame() noexcept
{
	// TODO: 在此添加成员初始化代码
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("未能创建工具栏\n");
		return -1;      // 未能创建
	}

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("未能创建状态栏\n");
		return -1;      // 未能创建
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	// TODO: 如果不需要可停靠工具栏，则删除这三行
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);


	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return TRUE;
}

// CMainFrame 诊断

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame 消息处理程序



BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	// TODO: 在此添加专用代码和/或调用基类
	m_splitter.CreateStatic(this, 1, 2);
	m_splitter.CreateView(0, 0, RUNTIME_CLASS(CFolderTree), CSize(200, 500), pContext);
	m_splitter.CreateView(0, 1, RUNTIME_CLASS(CmodView), CSize(200, 500), pContext);
	return true;
}


// 创建目录
bool CMainFrame::CreateDirectoy(UINT nStyle)
{
	// TODO: 在此处添加实现代码.
	//MessageBox(_T("5"));
	CFolderTree *treeView = (CFolderTree*)m_splitter.GetPane(0, 0);
	CmodView    *view = (CmodView*)m_splitter.GetPane(0, 1);
	//MessageBox(_T("6"));
	CTreeCtrl &tree = treeView->GetTree();
	//MessageBox(_T("10"));
	CImageList *image = new CImageList();
	//MessageBox(_T("11"));
	image->Create(IDI_FILECLOSE, 32, 1, RGB(255, 255, 255));
	//MessageBox(_T("12"));
	image->Add(AfxGetApp()->LoadIcon(IDI_FILEOPEN));
	//MessageBox(_T("13"));
	DWORD dwStyle = GetWindowLong(tree.m_hWnd, GWL_STYLE);
	dwStyle |= TVS_HASLINES | TVS_HASBUTTONS | TVS_DISABLEDRAGDROP | TVS_LINESATROOT;
	SetWindowLong(tree.m_hWnd, GWL_STYLE,dwStyle);
	//tree.Create(TVS_HASLINES | TVS_HASBUTTONS | TVS_DISABLEDRAGDROP | TVS_LINESATROOT, CRect(0, 0, 200, 500), treeView, IDT_FOLDER);
	//MessageBox(_T("14"));
	tree.SetImageList(image,TVSIL_NORMAL);
	//MessageBox(_T("7"));
	if (nStyle | CD_NORMAL)
	{
		//MessageBox(_T("8"));
		if (path[path.GetLength() - 1] != '\\')
		{
			path.AppendChar(_T('\\'));
		}
		//MessageBox(_T("9"));
		CreateDirectory(path + name, NULL);
		CreateDirectory(path + name + _T("\\content"), NULL);
		TV_INSERTSTRUCT temp;
		HTREEITEM root, cur;
		temp.hParent = TVI_ROOT;
		temp.hInsertAfter = TVI_LAST;
		temp.item.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE;
		CString a = path + name;
		temp.item.pszText = (LPWSTR)(LPCWSTR)a;
		temp.item.iImage = 0;
		temp.item.iSelectedImage = 1;
		root = tree.InsertItem(&temp);
	}
	return false;
}
