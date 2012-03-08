#pragma once

#include "JPWordInfo.h"
#include "JPWordInfoEx.h"
// CJPWordWnd

class CJPWordWnd : public CStatic
{
	DECLARE_DYNAMIC(CJPWordWnd)
public:
	//日语单词信息
	CJPWordInfoEx jpword;
	//枚举显示模式{全部显示，显示单词，显示注音}
	enum ShowMode{sm_show_all , sm_show_word , sm_show_zhuyin};
	//当前显示模式
	ShowMode showMode;
	
	//注音字体
	CFont fontZhuYin;
	//单词字体
	CFont fontWord;
	//绘制的横向基准
	int allBaseX;
	//绘制的纵向基准
	int allBaseY;
	//客户区大小
	CRect clientRect;
public:
	CJPWordWnd();
	virtual ~CJPWordWnd();

protected:
	DECLARE_MESSAGE_MAP()

protected:
	virtual void PreSubclassWindow();
private:
	bool bInit;
public:
	afx_msg void OnPaint();
	//载入一个单词
	bool loadWord( CJPWordInfo wordInfo );

	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg void OnNcLButtonDown(UINT nHitTest, CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSizing(UINT fwSide, LPRECT pRect);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
};


