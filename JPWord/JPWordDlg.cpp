// JPWordDlg.cpp : ʵ���ļ�
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


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

	// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	// ʵ��
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


// CJPWordDlg �Ի���




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


// CJPWordDlg ��Ϣ�������

BOOL CJPWordDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	
	//��������
	m_font.CreatePointFont(140,_T("����"),NULL);
	//���ÿؼ�����
	this->ctrlJPWordCH.SetFont(&m_font);
	this->ctrlJPWordMore.SetFont(&m_font);
	this->ctrlShowMode.SetFont(&m_font);
	this->ctrlAutoSwitch.SetFont(&m_font);
	GetDlgItem(ID_BTN_NEXT)->SetFont(&m_font);
	GetDlgItem(ID_BTN_PREV)->SetFont(&m_font);
	GetDlgItem(IDC_BTN_LOAD_FROM_FILE)->SetFont(&m_font);
	
	//��ʼ��������ѡ���һ��
	ctrlAutoSwitch.SetCurSel(0);
	ctrlShowMode.SetCurSel(0);

	//���õ��ʻ��ƴ���λ��
	this->jpWndPos.x = 0;
	this->jpWndPos.y = 60;
	//���õ��ʻ��ƴ���λ��
	this->numberPos.x = 230;
	this->numberPos.y = 30 ;

	//��������ͼƬ
	if(!m_bmpNumber.LoadBitmap(IDB_NUM_COLOR))
	{
		return FALSE;
	}
	//ʱ��
	time = 0;
	//���ʱ��
	maxTime = 20;
	//�������Զ��л�
	autoSwitch = 0;
	//���ö�
	mb_dlg_topmost = false;
	//��ʱ��
	auto_switch_timer = 0;

	//
	Init();
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CJPWordDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ��������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������
		DrawNumber(dc);
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù����ʾ��
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
		//���Ժ���˼�����һ��ŵ��������崰��
		CString ch (w->cixing.c_str());
		ch.Append( _T(":") );
		ch.Append( w->chinese.c_str() );
		ctrlJPWordCH.SetWindowText( ch );
		//����˵���ŵ�more����
		ctrlJPWordMore.SetWindowText( CString ( w->introduction.c_str() ) );
	}
}

void CJPWordDlg::LoadWordNext()
{
	CJPWordInfo* w = wordsVector.getNextJPWord();
	if(w)
	{
		jpwnd.loadWord( *w );
		//���Ժ���˼�����һ��ŵ��������崰��
		CString ch (w->cixing.c_str());
		ch.Append( _T(":") );
		ch.Append( w->chinese.c_str() );
		ctrlJPWordCH.SetWindowText( ch );
		//����˵���ŵ�more����
		ctrlJPWordMore.SetWindowText( CString ( w->introduction.c_str() ) );
	}
}

void CJPWordDlg::LoadWordPrev()
{
	CJPWordInfo* w = wordsVector.getPrevJPWord();
	if(w)
	{
		jpwnd.loadWord( *w );

		//���Ժ���˼�����һ��ŵ��������崰��
		CString ch (w->cixing.c_str());
		ch.Append( _T(":") );
		ch.Append( w->chinese.c_str() );
		ctrlJPWordCH.SetWindowText( ch );
		//����˵���ŵ�more����
		ctrlJPWordMore.SetWindowText( CString ( w->introduction.c_str() ) );
	}
}



void CJPWordDlg::OnBnClickedBtnLoadFromFile()
{
	//���ļ��Ի���
	CFileDialog dlg( TRUE, _T("*.xml") ,NULL,OFN_HIDEREADONLY |OFN_OVERWRITEPROMPT, _T("����ʿ��ļ�(*.xml)|*.xml|�����ļ�(*.*)|*.*|| "));
	//��ʼ·��
	//dlg.m_ofn.lpstrInitialDir= _T("V:\\"); 
	//��ʾ�Ի���
	if( dlg.DoModal() ==IDOK)
	{
		CString file = dlg.GetPathName();
		wstring fileName =file.GetBuffer();
		
		//����ʿ�
		bool clear = false; 
		//�Ѿ����شʿ�
		if( wordsVector.getWordsCount() > 0  )
		{
			int select = MessageBox(_T("ֱ��׷�Ӵʿ��������Ѽ��ص����ݣ�"),_T("��ѡ��"),MB_YESNOCANCEL|MB_ICONQUESTION);
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
		//���شʿ��ļ�
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
			MessageBox(_T("���شʿ����"),_T("��ʾ"),MB_OK|MB_ICONWARNING);
		}
	}
}

//���ö�ʱ��
void CJPWordDlg::ResetTimer()
{
	//��ʼ��ʱ��Ϊ��
	time = 0;
	//ˢ��ʱ����ʾ����
	this->InvalidateRect(CRect(numberPos ,CSize(42, 26)));

	if( wordsVector.getWordsCount()==0 )
	{
		AfxMessageBox(_T("���ʿ�Ϊ�գ������¼��شʿ⣡"));
		KillTimer(0);
		auto_switch_timer = 0;
		return ;
	}
	if(auto_switch_timer==0)
	{
		//���춨ʱ��
		auto_switch_timer = SetTimer(0,1000,NULL);
	}

	jpwnd.Invalidate();
}

//���ö�ʱ��
void CJPWordDlg::ResetTimerAndWord()
{
	if( wordsVector.getWordsCount()==0 )
	{
		AfxMessageBox(_T("���ʿ�Ϊ�գ������¼��شʿ⣡"));
		KillTimer(0);
		auto_switch_timer = 0;
		time = 0;
		this->InvalidateRect(CRect(numberPos ,CSize(42, 26)));
		return ;
	}

	if(auto_switch_timer==0)
	{
		//���춨ʱ��
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
	//ˢ��ʱ����ʾ����
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
	// TODO: �ڴ˴������Ϣ����������
}

void CJPWordDlg::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	//���ƴ�����СΪ300*200
	lpMMI-> ptMinTrackSize=CPoint(360,200);
	CDialog::OnGetMinMaxInfo(lpMMI);
}

//������ʾģʽ�����б�
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

//���ĵ����Զ��л������б�
void CJPWordDlg::OnCbnSelchangeComboAutoSwitch()
{
	UpdateData();
}



//�Զ�����Ϣ��Ӧ�������ı䵥�ʻ��ƴ��ڴ�Сʱ���ƶ��·��Ĵ�������ȿؼ�
LRESULT CJPWordDlg::OnDlgMoveCtrls(WPARAM wParam, LPARAM lParam)
{
	this->ctrlJPWordCH.SetWindowPos( NULL, 0, (LONG)wParam + 5, 0, 0, SWP_NOSIZE|SWP_NOZORDER );
	this->ctrlJPWordMore.SetWindowPos( NULL, 0, (LONG)wParam + 40, 0, 0, SWP_NOSIZE|SWP_NOZORDER );
	return 0;
}

//�رհ�ť
void CJPWordDlg::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	EndDialog(0);
}

//���ƶ�ʱ��
void CJPWordDlg::DrawNumber(CPaintDC &dc)
{

	CDC dcMemory;
	dcMemory.CreateCompatibleDC(&dc);
	dcMemory.SelectObject(m_bmpNumber);
	dc.Draw3dRect(numberPos.x-1,numberPos.y-1,42,26,RGB(150,150,150),RGB(245,245,245));

	int num;
	//��λ
	num=time/100;
	dc.StretchBlt( numberPos.x,numberPos.y,13,23,&dcMemory,0,276-23*(num+1),13,23,SRCCOPY);
	//ʮλ
	num=(time-num*100)/10;
	dc.StretchBlt(numberPos.x+13, numberPos.y,13,23,&dcMemory,0,276-23*(num+1),13,23,SRCCOPY);
	//��λ
	num=time%10;
	dc.StretchBlt(numberPos.x+26, numberPos.y,13,23,&dcMemory,0,276-23*(num+1),13,23,SRCCOPY);
}
void CJPWordDlg::OnBnClickedBtnLock()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(this->mb_dlg_topmost)
	{
		//ȡ���ö�
		SetWindowPos(&CWnd::wndNoTopMost, 0, 0, 0, 0, SWP_NOMOVE|SWP_NOSIZE);
		GetDlgItem(IDC_BTN_LOCK)->SetWindowText(_T("�ö�"));
	}
	else
	{	//�ö�
		SetWindowPos(&CWnd::wndTopMost, 0, 0, 0, 0, SWP_NOMOVE|SWP_NOSIZE);
		GetDlgItem(IDC_BTN_LOCK)->SetWindowText(_T("���ö�"));
	}
	//ȡ��
	mb_dlg_topmost = ! mb_dlg_topmost;
}



void CJPWordDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if(nIDEvent == 0)
	{
		time++;
		//������ʾ��Χ
		if(time>999)
		{
			time =0;
		}
		//ˢ��ͼƬ��ʾ����
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

// ��ʼ������Ҫ�ǿؼ�λ��
int CJPWordDlg::Init(void)
{
	CRect rc;
	jpwnd.GetWindowRect(rc);
	SendMessage(WM_DLG_MOVE_CTRLS, rc.Height()+jpWndPos.y+10);
	return 0;
}
