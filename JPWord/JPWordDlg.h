// JPWordDlg.h : 头文件
//
#pragma once

#include "jpwordwnd.h"
#include "JPWordsVector.h"
#include "afxwin.h"

// CJPWordDlg 对话框
class CJPWordDlg : public CDialog
{
// 构造
public:
	CJPWordDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_JPWORD_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
	//原始单词信息
	CJPWordsVector wordsVector;
	//词性和解释等的字体信息
	CFont m_font;

	//显示模式枚举【便签模式，全部显示，单词和假名，日语单词，日语假名，汉语释义】
	enum dlg_show_mode{sm_notes,sm_jp,sm_zh,sm_jiaming };


	
	void LoadWordPrev();
	void LoadWordNext();
	void LoadWordCurrent();

	//单词绘制窗口
	CJPWordWnd jpwnd;
	//单词绘制位置
	CPoint jpWndPos;
	// 显示模式下拉框
	CComboBox ctrlShowMode;
	// 汉语释义窗口
	CStatic ctrlJPWordCH;
	// 附加说明信息
	CStatic ctrlJPWordMore;
	//改变显示模式
	afx_msg void OnCbnSelchangeComboShowMode();
	//改变单词自动切换模式
	afx_msg void OnCbnSelchangeComboAutoSwitch();
	// 单词框的显示模式
	int jpWordShowMode;
	// 最大时间
	int maxTime ;
	// 时间
	int time ;

	// 自动切换定时器
	UINT_PTR auto_switch_timer;

	//自动切换单词
	int autoSwitch;
	// 数字图片
	CBitmap m_bmpNumber;
	// 数字窗口位置
	CPoint numberPos;
	// 画数字
	void DrawNumber(CPaintDC &dc);
	// 关闭对话框
	afx_msg void OnClose();
	// 单词自动切换下拉框
	CComboBox ctrlAutoSwitch;
	afx_msg void OnBnClickedBtnLock();
	// 窗口置顶
	bool mb_dlg_topmost;

	void ResetTimerAndWord();

	void ResetTimer();

	afx_msg void OnTimer(UINT_PTR nIDEvent);
	// 初始化，主要是控件位置
	int Init(void);
};
