// JPWord.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "JPWord.h"
#include "JPWordDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CJPWordApp

BEGIN_MESSAGE_MAP(CJPWordApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CJPWordApp ����

CJPWordApp::CJPWordApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CJPWordApp ����

CJPWordApp theApp;


// CJPWordApp ��ʼ��

BOOL CJPWordApp::InitInstance()
{
#ifdef _DEBUG
	/***********����ض���������̨****************/
	/**/AllocConsole();
	/**/freopen("CONOUT$","w+t",stdout); 
	/**/freopen("CONIN$","r+t",stdin); 
	/********************************************/
#endif
	CWinApp::InitInstance();

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	//SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));

	CJPWordDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: �ڴ˴����ô����ʱ�á�ȷ�������ر�
		//  �Ի���Ĵ���
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: �ڴ˷��ô����ʱ�á�ȡ�������ر�
		//  �Ի���Ĵ���
	}

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�

#ifdef _DEBUG	
	/*�ͷſ���̨*/
	FreeConsole();
#endif

	return FALSE;
}
