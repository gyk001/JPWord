// JPWordDlg.h : ͷ�ļ�
//
#pragma once

#include "jpwordwnd.h"
#include "JPWordsVector.h"
#include "afxwin.h"

// CJPWordDlg �Ի���
class CJPWordDlg : public CDialog
{
// ����
public:
	CJPWordDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_JPWORD_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
	afx_msg void OnBnClickedBtnNext();
	afx_msg void OnBnClickedBtnPrev();
	afx_msg void OnBnClickedBtnLoadFromFile();
	afx_msg LRESULT OnDlgMoveCtrls(WPARAM wParam, LPARAM lParam);
	//ԭʼ������Ϣ
	CJPWordsVector wordsVector;
	//���Ժͽ��͵ȵ�������Ϣ
	CFont m_font;

	//��ʾģʽö�١���ǩģʽ��ȫ����ʾ�����ʺͼ��������ﵥ�ʣ�����������������塿
	enum dlg_show_mode{sm_notes,sm_jp,sm_zh,sm_jiaming };


	
	void LoadWordPrev();
	void LoadWordNext();
	void LoadWordCurrent();

	//���ʻ��ƴ���
	CJPWordWnd jpwnd;
	//���ʻ���λ��
	CPoint jpWndPos;
	// ��ʾģʽ������
	CComboBox ctrlShowMode;
	// �������崰��
	CStatic ctrlJPWordCH;
	// ����˵����Ϣ
	CStatic ctrlJPWordMore;
	//�ı���ʾģʽ
	afx_msg void OnCbnSelchangeComboShowMode();
	//�ı䵥���Զ��л�ģʽ
	afx_msg void OnCbnSelchangeComboAutoSwitch();
	// ���ʿ����ʾģʽ
	int jpWordShowMode;
	// ���ʱ��
	int maxTime ;
	// ʱ��
	int time ;

	// �Զ��л���ʱ��
	UINT_PTR auto_switch_timer;

	//�Զ��л�����
	int autoSwitch;
	// ����ͼƬ
	CBitmap m_bmpNumber;
	// ���ִ���λ��
	CPoint numberPos;
	// ������
	void DrawNumber(CPaintDC &dc);
	// �رնԻ���
	afx_msg void OnClose();
	// �����Զ��л�������
	CComboBox ctrlAutoSwitch;
	afx_msg void OnBnClickedBtnLock();
	// �����ö�
	bool mb_dlg_topmost;

	void ResetTimerAndWord();

	void ResetTimer();

	afx_msg void OnTimer(UINT_PTR nIDEvent);
	// ��ʼ������Ҫ�ǿؼ�λ��
	int Init(void);
};
