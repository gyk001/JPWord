// JPWordDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "JPWord.h"
#include "JPWordDlg.h"

#include "JPWordInfoEx.h"
#include "JPWordInfo.h"

#include "iostream"
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

	// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CJPWordDlg 对话框




CJPWordDlg::CJPWordDlg(CWnd* pParent /*=NULL*/)
: CDialog(CJPWordDlg::IDD, pParent)
, jpWordShowMode(0)
, mb_dlg_topmost(false)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CJPWordDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC__JP_WND, jpwnd);
	DDX_Control(pDX, IDC_COMBO_SHOW_MODE, ctrlShowMode);
	DDX_Control(pDX, IDC_JP_WORD_CH, ctrlJPWordCH);
	DDX_Control(pDX, IDC_JP_WORD_MORE, ctrlJPWordMore);
	DDX_Control(pDX, IDC_COMBO_AUTO_SWITCH, ctrlAutoSwitch);

	DDX_CBIndex(pDX, IDC_COMBO_SHOW_MODE, jpWordShowMode);
	DDX_CBIndex(pDX, IDC_COMBO_AUTO_SWITCH, autoSwitch);
}

BEGIN_MESSAGE_MAP(CJPWordDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(WM_DLG_MOVE_CTRLS, OnDlgMoveCtrls)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(ID_BTN_NEXT, &CJPWordDlg::OnBnClickedBtnNext)
	ON_BN_CLICKED(ID_BTN_PREV, &CJPWordDlg::OnBnClickedBtnPrev)
	ON_BN_CLICKED(IDC_BTN_LOAD_FROM_FILE, &CJPWordDlg::OnBnClickedBtnLoadFromFile)
	ON_WM_SIZE()
	ON_WM_GETMINMAXINFO()
	ON_CBN_SELCHANGE(IDC_COMBO_SHOW_MODE, &CJPWordDlg::OnCbnSelchangeComboShowMode)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BTN_LOCK, &CJPWordDlg::OnBnClickedBtnLock)
	ON_CBN_SELCHANGE(IDC_COMBO_AUTO_SWITCH, &CJPWordDlg::OnCbnSelchangeComboAutoSwitch)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CJPWordDlg 消息处理程序

BOOL CJPWordDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	
	//构造字体
	m_font.CreatePointFont(140,_T("宋体"),NULL);
	//设置控件字体
	this->ctrlJPWordCH.SetFont(&m_font);
	this->ctrlJPWordMore.SetFont(&m_font);
	this->ctrlShowMode.SetFont(&m_font);
	this->ctrlAutoSwitch.SetFont(&m_font);
	GetDlgItem(ID_BTN_NEXT)->SetFont(&m_font);
	GetDlgItem(ID_BTN_PREV)->SetFont(&m_font);
	GetDlgItem(IDC_BTN_LOAD_FROM_FILE)->SetFont(&m_font);
	
	//初始化下拉框选择第一项
	ctrlAutoSwitch.SetCurSel(0);
	ctrlShowMode.SetCurSel(0);

	//设置单词绘制窗口位置
	this->jpWndPos.x = 0;
	this->jpWndPos.y = 60;
	//设置单词绘制窗口位置
	this->numberPos.x = 230;
	this->numberPos.y = 30 ;

	//加载数字图片
	if(!m_bmpNumber.LoadBitmap(IDB_NUM_COLOR))
	{
		return FALSE;
	}
	//时间
	time = 0;
	//最大时间
	maxTime = 20;
	//不进行自动切换
	autoSwitch = 0;
	//不置顶
	mb_dlg_topmost = false;
	//定时器
	auto_switch_timer = 0;

	//
	Init();
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CJPWordDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CJPWordDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CPaintDC dc(this); // 用于绘制的设备上下文
		DrawNumber(dc);
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标显示。
//
HCURSOR CJPWordDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}




void CJPWordDlg::OnBnClickedBtnNext()
{
	ResetTimer();
	LoadWordNext();
}

void CJPWordDlg::OnBnClickedBtnPrev()
{
	ResetTimer();
	LoadWordPrev();

}

void CJPWordDlg::LoadWordCurrent()
{
	CJPWordInfo* w = wordsVector.getCurrentJPWord();
	if(w)
	{
		jpwnd.loadWord( *w );
		//词性和意思组合在一起放到汉语释义窗口
		CString ch (w->cixing.c_str());
		ch.Append( _T(":") );
		ch.Append( w->chinese.c_str() );
		ctrlJPWordCH.SetWindowText( ch );
		//其他说明放到more窗口
		ctrlJPWordMore.SetWindowText( CString ( w->introduction.c_str() ) );
	}
}

void CJPWordDlg::LoadWordNext()
{
	CJPWordInfo* w = wordsVector.getNextJPWord();
	if(w)
	{
		jpwnd.loadWord( *w );
		//词性和意思组合在一起放到汉语释义窗口
		CString ch (w->cixing.c_str());
		ch.Append( _T(":") );
		ch.Append( w->chinese.c_str() );
		ctrlJPWordCH.SetWindowText( ch );
		//其他说明放到more窗口
		ctrlJPWordMore.SetWindowText( CString ( w->introduction.c_str() ) );
	}
}

void CJPWordDlg::LoadWordPrev()
{
	CJPWordInfo* w = wordsVector.getPrevJPWord();
	if(w)
	{
		jpwnd.loadWord( *w );

		//词性和意思组合在一起放到汉语释义窗口
		CString ch (w->cixing.c_str());
		ch.Append( _T(":") );
		ch.Append( w->chinese.c_str() );
		ctrlJPWordCH.SetWindowText( ch );
		//其他说明放到more窗口
		ctrlJPWordMore.SetWindowText( CString ( w->introduction.c_str() ) );
	}
}



void CJPWordDlg::OnBnClickedBtnLoadFromFile()
{
	//打开文件对话框
	CFileDialog dlg( TRUE, _T("*.xml") ,NULL,OFN_HIDEREADONLY |OFN_OVERWRITEPROMPT, _T("日语词库文件(*.xml)|*.xml|所有文件(*.*)|*.*|| "));
	//初始路径
	//dlg.m_ofn.lpstrInitialDir= _T("V:\\"); 
	//显示对话框
	if( dlg.DoModal() ==IDOK)
	{
		CString file = dlg.GetPathName();
		wstring fileName =file.GetBuffer();
		
		//清除词库
		bool clear = false; 
		//已经加载词库
		if( wordsVector.getWordsCount() > 0  )
		{
			int select = MessageBox(_T("直接追加词库而不清除已加载的数据？"),_T("请选择"),MB_YESNOCANCEL|MB_ICONQUESTION);
			switch (select )
			{
			case IDYES:
				clear = false;
				break;
			case IDNO:
				clear = true;
				break;
			case IDCANCEL:
				return;
			}
		
		}
		//加载词库文件
		if( wordsVector.LoadFile(fileName , clear) )
		{
			ResetTimerAndWord();
		}
		else
		{
			if(auto_switch_timer!=0)
			{
				KillTimer(0);
				auto_switch_timer=0;
			}
			MessageBox(_T("加载词库出错！"),_T("提示"),MB_OK|MB_ICONWARNING);
		}
	}
}

//重置定时器
void CJPWordDlg::ResetTimer()
{
	//初始化时间为零
	time = 0;
	//刷新时间显示区域
	this->InvalidateRect(CRect(numberPos ,CSize(42, 26)));

	if( wordsVector.getWordsCount()==0 )
	{
		AfxMessageBox(_T("单词库为空，请重新加载词库！"));
		KillTimer(0);
		auto_switch_timer = 0;
		return ;
	}
	if(auto_switch_timer==0)
	{
		//构造定时器
		auto_switch_timer = SetTimer(0,1000,NULL);
	}

	jpwnd.Invalidate();
}

//重置定时器
void CJPWordDlg::ResetTimerAndWord()
{
	if( wordsVector.getWordsCount()==0 )
	{
		AfxMessageBox(_T("单词库为空，请重新加载词库！"));
		KillTimer(0);
		auto_switch_timer = 0;
		time = 0;
		this->InvalidateRect(CRect(numberPos ,CSize(42, 26)));
		return ;
	}

	if(auto_switch_timer==0)
	{
		//构造定时器
		auto_switch_timer = SetTimer(0,1000,NULL);
	}
	switch(autoSwitch)
	{
	case 0:
		LoadWordCurrent();
		break;
	case 1:
		time = 0;
		LoadWordNext();
		break;
	case 2:
		time = 0;
		LoadWordPrev();
		break;
	}
	jpwnd.Invalidate();
	//刷新时间显示区域
	this->InvalidateRect(CRect(numberPos ,CSize(42, 26)));
}

void CJPWordDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
	if(this->ctrlJPWordCH.m_hWnd)
	{
		CRect rc;
		GetClientRect(rc);
		jpwnd.MoveWindow(jpWndPos.x, jpWndPos.y ,rc.Width(), jpwnd.clientRect.Height());
		ctrlJPWordCH.MoveWindow(jpWndPos.x, jpWndPos.y+jpwnd.clientRect.Height()+5 ,rc.Width(),30);
		ctrlJPWordMore.MoveWindow(jpWndPos.x, jpWndPos.y+jpwnd.clientRect.Height()+40 ,rc.Width(),30);
		jpwnd.Invalidate();
	}
	// TODO: 在此处添加消息处理程序代码
}

void CJPWordDlg::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//限制窗口最小为300*200
	lpMMI-> ptMinTrackSize=CPoint(360,200);
	CDialog::OnGetMinMaxInfo(lpMMI);
}

//更改显示模式下拉列表
void CJPWordDlg::OnCbnSelchangeComboShowMode()
{
	UpdateData();
	switch( jpWordShowMode )
	{
	case CJPWordWnd::sm_show_all:
		jpwnd.showMode = CJPWordWnd::sm_show_all;
		break;
	case CJPWordWnd::sm_show_word:
		jpwnd.showMode = CJPWordWnd::sm_show_word;
		break;
	case CJPWordWnd::sm_show_zhuyin:
		jpwnd.showMode = CJPWordWnd::sm_show_zhuyin;
		break;
	}
	jpwnd.Invalidate();
}

//更改单词自动切换下拉列表
void CJPWordDlg::OnCbnSelchangeComboAutoSwitch()
{
	UpdateData();
}



//自定义消息响应函数，改变单词绘制窗口大小时，移动下方的词性释义等控件
LRESULT CJPWordDlg::OnDlgMoveCtrls(WPARAM wParam, LPARAM lParam)
{
	this->ctrlJPWordCH.SetWindowPos( NULL, 0, (LONG)wParam + 5, 0, 0, SWP_NOSIZE|SWP_NOZORDER );
	this->ctrlJPWordMore.SetWindowPos( NULL, 0, (LONG)wParam + 40, 0, 0, SWP_NOSIZE|SWP_NOZORDER );
	return 0;
}

//关闭按钮
void CJPWordDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	EndDialog(0);
}

//绘制定时器
void CJPWordDlg::DrawNumber(CPaintDC &dc)
{

	CDC dcMemory;
	dcMemory.CreateCompatibleDC(&dc);
	dcMemory.SelectObject(m_bmpNumber);
	dc.Draw3dRect(numberPos.x-1,numberPos.y-1,42,26,RGB(150,150,150),RGB(245,245,245));

	int num;
	//百位
	num=time/100;
	dc.StretchBlt( numberPos.x,numberPos.y,13,23,&dcMemory,0,276-23*(num+1),13,23,SRCCOPY);
	//十位
	num=(time-num*100)/10;
	dc.StretchBlt(numberPos.x+13, numberPos.y,13,23,&dcMemory,0,276-23*(num+1),13,23,SRCCOPY);
	//个位
	num=time%10;
	dc.StretchBlt(numberPos.x+26, numberPos.y,13,23,&dcMemory,0,276-23*(num+1),13,23,SRCCOPY);
}
void CJPWordDlg::OnBnClickedBtnLock()
{
	// TODO: 在此添加控件通知处理程序代码
	if(this->mb_dlg_topmost)
	{
		//取消置顶
		SetWindowPos(&CWnd::wndNoTopMost, 0, 0, 0, 0, SWP_NOMOVE|SWP_NOSIZE);
		GetDlgItem(IDC_BTN_LOCK)->SetWindowText(_T("置顶"));
	}
	else
	{	//置顶
		SetWindowPos(&CWnd::wndTopMost, 0, 0, 0, 0, SWP_NOMOVE|SWP_NOSIZE);
		GetDlgItem(IDC_BTN_LOCK)->SetWindowText(_T("不置顶"));
	}
	//取反
	mb_dlg_topmost = ! mb_dlg_topmost;
}



void CJPWordDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(nIDEvent == 0)
	{
		time++;
		//超出显示范围
		if(time>999)
		{
			time =0;
		}
		//刷新图片显示区域
		this->InvalidateRect(CRect(numberPos ,CSize(42, 26)));

		if(time >= maxTime)
		{
			ResetTimerAndWord();
		}
	}
	else
	{
		CDialog::OnTimer(nIDEvent);
	}

}

// 初始化，主要是控件位置
int CJPWordDlg::Init(void)
{
	CRect rc;
	jpwnd.GetWindowRect(rc);
	SendMessage(WM_DLG_MOVE_CTRLS, rc.Height()+jpWndPos.y+10);
	return 0;
}
