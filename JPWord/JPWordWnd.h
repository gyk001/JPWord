#pragma once

#include "JPWordInfo.h"
#include "JPWordInfoEx.h"
// CJPWordWnd

class CJPWordWnd : public CStatic
{
	DECLARE_DYNAMIC(CJPWordWnd)
public:
	//���ﵥ����Ϣ
	CJPWordInfoEx jpword;
	//ö����ʾģʽ{ȫ����ʾ����ʾ���ʣ���ʾע��}
	enum ShowMode{sm_show_all , sm_show_word , sm_show_zhuyin};
	//��ǰ��ʾģʽ
	ShowMode showMode;
	
	//ע������
	CFont fontZhuYin;
	//��������
	CFont fontWord;
	//���Ƶĺ����׼
	int allBaseX;
	//���Ƶ������׼
	int allBaseY;
	//�ͻ�����С
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
	//����һ������
	bool loadWord( CJPWordInfo wordInfo );

	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg void OnNcLButtonDown(UINT nHitTest, CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSizing(UINT fwSide, LPRECT pRect);
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
};


