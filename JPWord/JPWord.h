// JPWord.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������

#define WM_DLG_MOVE_CTRLS (WM_USER + 1)

// CJPWordApp:
// �йش����ʵ�֣������ JPWord.cpp
//

class CJPWordApp : public CWinApp
{
public:
	CJPWordApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CJPWordApp theApp;