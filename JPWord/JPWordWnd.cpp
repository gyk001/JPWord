// JPWordWnd.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "JPWord.h"
#include "JPWordWnd.h"

#include "iostream"
// CJPWordWnd

IMPLEMENT_DYNAMIC(CJPWordWnd, CStatic)

CJPWordWnd::CJPWordWnd()
{
	bInit = false;
}

CJPWordWnd::~CJPWordWnd()
{
}


BEGIN_MESSAGE_MAP(CJPWordWnd, CStatic)
	ON_WM_PAINT()
	ON_WM_NCHITTEST()
	ON_WM_NCLBUTTONDOWN()
	ON_WM_SIZE()
	ON_WM_SIZING()
	ON_WM_GETMINMAXINFO()
END_MESSAGE_MAP()



// CJPWordWnd ��Ϣ�������
void CJPWordWnd::PreSubclassWindow()
{
	//�޸�CStatic����Ϊ���Խ���֪ͨ����������Ӧ�����Ϣ��	
	ModifyStyle(NULL,SS_NOTIFY);
	//���໯
	CStatic::PreSubclassWindow();
	//ע�������ʼ��
	fontZhuYin.CreatePointFont(120,_T("����"),NULL);
	//���������ʼ��
	fontWord.CreatePointFont(200,_T("����"),NULL);
	//��ʾģʽ
	showMode = sm_show_all;
	//��׼
	allBaseX = 0;
	allBaseY = 0;
	//��ȡ��������
	GetWindowRect(clientRect);
	//��Ļ����ת��
	ScreenToClient(clientRect);
}
/*
void CJPWordWnd::OnPaint()
{
//TRACE(_T(" -> OnPaint��������������������"));
CPaintDC dc(this); // device context for painting
// ��������
CFont font;
font.CreatePointFont(160,_T("����"),NULL);
// ������ѡ��DC
CFont* pOldFont = dc.SelectObject(&font);
//�������屳��ɫ
dc.SetBkColor(RGB(200,255,200));
//��ȡ�ͻ�����С
CRect clientRect;
GetClientRect(clientRect);
//���òü�����
CRgn rgn ;
rgn.CreateRectRgnIndirect(clientRect);
dc.SelectClipRgn(&rgn);
//�����ɫ
dc.FillSolidRect(clientRect , RGB(200,255,200));

//������Ƶĺ����׼
int baseX = 0 ;
//������Ƶ������׼
int baseY = 0 ;

//���������ߵ������׼
int toneBaseY = baseY + 10;

//����ע���������׼
int zhuYinBaseY = baseY + 20 ;

//���Ƶ��ʵ������׼,Ҳ���ǡ�ע���������׼+����߶�+3��
int wordBaseY = -1 ;
//һ������߶�
int rowHeight = -1;

//�����ַ��Ļ��ƿ�ȣ�����������ʱ��
int charWidth = -1;

//ѭ�����Ƹ������ʺ�ע��
for(int i=0 ; i< jpword.wordCount ; i++ )
{
//ȡ�õ�ǰ����
CString currentWord = CString( jpword.getWordAt(i).c_str());
//ȡ�õ�ǰע��
CString currentZhuYin = CString( jpword.getZhuYinAt(i).c_str());
//ȡ�õ��ʳ��ȣ��ַ�����
int wordLen = jpword.getWordLengthAt(i);
//ȡ��ע�����ȣ��ַ�����
int zhuYinLen = jpword.getZhuYinLengthAt(i);
//����ע��ռ�ݵľ�������
CRect rcZhuYin = CRect(0,0,0,0);
dc.DrawText( currentZhuYin, &rcZhuYin, DT_CALCRECT);
//�����ǰע��Ϊ�յĻ����ä������������С
if(zhuYinLen==0)
{
dc.DrawText( _T("��"), &rcZhuYin, DT_CALCRECT);
charWidth = rcZhuYin.Width();
}
//��ȡ����������ƻ�׼λ�ã�ֻ�е�һ����Ҫ���㣩			}
if(wordBaseY==-1)
{
wordBaseY = zhuYinBaseY + rcZhuYin.Height()+3;
}
//��ȡ�ַ��Ŀ��
if(charWidth==-1)
{
charWidth = rcZhuYin.Width() / zhuYinLen ;
}
//���㵥��ռ�ݵľ�������
CRect rcWord = CRect(0,0,0,0);
dc.DrawText( currentWord , &rcWord, DT_CALCRECT);
//����һ�е��ʵĸ߶ȣ�����������ע���͵��ʣ���ֻ�е�һ����Ҫ���㣩
if(rowHeight==-1)
{
rowHeight = wordBaseY + rcWord.Width();
}

//����һ���¾���rcʹ֮Ϊע���͵��ʵľ��ο�Ƚϴ���
CRect rc  = rcWord;
if(rcWord.Width()<rcZhuYin.Width())
{
rc = rcZhuYin;
}

//��������׼+���������� ���ڴ��ڿ����������ʾ
if( rc.Width()+ baseX > clientRect.Width() )
{
//����λ�ô�ͷ��ʼ
baseX = 0;
//����λ�� = ����߶�+
baseY += rowHeight ;

}

//��ǰ��ʾģʽΪ����ģʽ
if( showMode==sm_show_word )
{
//�ƶ��¾��������ʻ�׼λ��
rc.MoveToXY( baseX, wordBaseY + baseY );
//���Ƶ���
dc.DrawText( currentWord, rc, DT_CENTER );
}
//ע��ģʽ
else if( showMode==sm_show_zhuyin )
{
//�ƶ��¾�����ע����׼λ��
rc.MoveToXY(baseX, zhuYinBaseY + baseY );
//�����ǰ��û��ע������Ƶ��ʣ��������ע��
if( currentZhuYin.IsEmpty() )
{
//���Ƶ���
dc.DrawText( currentWord, rc, DT_CENTER );
}
else
{
//����ע��
dc.DrawText( currentZhuYin,rc, DT_CENTER );
}
//������Ϣ����Ϊ3�ı��������򲻻���
if( jpword.tone.size()%3 == 0 )
{
//����������
for( size_t i=0; i<jpword.tone.size(); i+=3 )
{

//��������
int style = jpword.tone[i];
//������
dc.MoveTo( jpword.tone[i+1]*charWidth +6 ,toneBaseY + baseY );
dc.LineTo( jpword.tone[i+2]*charWidth -6 ,toneBaseY + baseY );
//���½���
if( style == CJPWordInfoEx::jp_tone_down )
{
dc.LineTo( jpword.tone[i+2]*charWidth-6 ,toneBaseY + 5 + baseY );
}

}
}

}
//����ģʽ
else
{
//�ƶ��¾��������ʻ�׼λ��
rc.MoveToXY( baseX, wordBaseY + baseY );
//���Ƶ���
dc.DrawText( currentWord, rc, DT_CENTER );
//�ƶ��¾�����ע����׼λ��
rc.MoveToY( zhuYinBaseY + baseY );
//����ע��
dc.DrawText( currentZhuYin,rc, DT_CENTER );

//������Ϣ����Ϊ3�ı��������򲻻���
if( jpword.tone.size()%3 == 0 )
{
//����������
for( size_t i=0; i<jpword.tone.size(); i+=3 )
{

//��������
int style = jpword.tone[i];
//������
dc.MoveTo( jpword.tone[i+1]*charWidth +6 ,toneBaseY + baseY );
dc.LineTo( jpword.tone[i+2]*charWidth -6 ,toneBaseY + baseY );
//���½���
if( style == CJPWordInfoEx::jp_tone_down )
{
dc.LineTo( jpword.tone[i+2]*charWidth-6 ,toneBaseY + 5 + baseY );
}

}
}
}


//������һ�������׼λ��
baseX += rc.Width()+2;
}

// �ָ�������-���Ǳ����
dc.SelectObject( pOldFont );
//�ָ�����ģʽ
//	dc.SetBkMode( oldBkMode );
}
*/
bool CJPWordWnd::loadWord(CJPWordInfo wordInfo)
{
	bInit = false;
	//���ص�����Ϣ
	if( jpword.loadWord( wordInfo.jpword )!=0 )
	{
		return false;
	}
	//����������Ϣ
	if( jpword.loadTone( wordInfo.tone )!=0)
	{
		return false;
	}
	bInit = true;
	//this->Invalidate();
	return true;
}

void CJPWordWnd::OnPaint()
{
	#define JP_PAINT_X_ 5
	CPaintDC dc(this);
	CDC dcMemory;
	CBitmap bitmap;
	if (!dc.IsPrinting())
	{
		if (dcMemory.CreateCompatibleDC(&dc))
		{
			if (bitmap.CreateCompatibleBitmap(&dc,clientRect.right,clientRect.bottom))
			{
				dcMemory.SelectObject(&bitmap);
				/*CBrush br;
				br.CreateSysColorBrush(CSCB);
				br.CreateSolidBrush(RGB(200,200,200));
				dcMemory.FillRect(&clientRect,&br);*/
				//���û���
				CPen pen;
				pen.CreatePen(PS_SOLID, 0, RGB(255, 0, 0));
				CPen *pOldPen = dcMemory.SelectObject(&pen);
				//���û�ˢ
				CBrush brush;
				brush.CreateSolidBrush( RGB(200,255,000) );
				CBrush* pOldBrush = dcMemory.SelectObject(&brush);
				//���Բ�Ǿ���
				dcMemory.RoundRect(clientRect.left+4, clientRect.top+4, clientRect.right-4, clientRect.bottom-4, 20, 20);

				// ������ѡ��DC
				CFont* pOldFont = dcMemory.SelectObject(&fontZhuYin);
				//�������屳��ɫ
				COLORREF oldBkColor = dcMemory.SetBkColor(RGB(200,255,0));
				COLORREF oldTextColor = dcMemory.SetTextColor(RGB(0,0,0));

				//���òü�����
				CRgn rgn ;
				rgn.CreateRoundRectRgn(clientRect.left+6, clientRect.top+6, clientRect.right-8, clientRect.bottom-8, 20, 20);
				dcMemory.SelectClipRgn(&rgn);


				if(bInit)
				{
					//cout<<"paint^"<<endl;
					allBaseX = JP_PAINT_X_;
					allBaseY = 0;
					//һ������߶�,����ʱʹ��
					int rowHeight = -1;
					//����ע���ַ��Ļ��ƿ�ȣ�����������ʱ��
					int charZhuYinWidth = -1;
					// ע���ַ��߶�
					int charZhuYinHeight = -1;

					// �����ַ��߶�
					int charWordHeight = -1;

					//�����߸߶�
					int toneHeight = 0;//10 ;

					//���������ߵ������׼
					int toneBaseY = allBaseY + 5 ;

					//����ע���������׼
					int zhuYinBaseY = toneBaseY + toneHeight + 2 ;

					//���Ƶ��ʵ������׼
					int wordBaseY = -1 ;


					//ѭ�����Ƹ������ʺ�ע��
					for(int i=0 ; i< jpword.wordCount ; i++ )
					{
						//ȡ�õ�ǰ����
						CString currentWord = CString( jpword.getWordAt(i).c_str());
						//ȡ�õ�ǰע��
						CString currentZhuYin = CString( jpword.getZhuYinAt(i).c_str());
						//ȡ�õ��ʳ��ȣ��ַ�����
						int wordLen = jpword.getWordLengthAt(i);
						//ȡ��ע�����ȣ��ַ�����
						int zhuYinLen = jpword.getZhuYinLengthAt(i);
						//��ע������ѡ��DC
						dcMemory.SelectObject(&fontZhuYin);
						//����ע��ռ�ݵľ�������
						CRect rcZhuYin = CRect(0,0,0,0);
						dcMemory.DrawText( currentZhuYin, &rcZhuYin, DT_CALCRECT);
						// �����ַ��Ŀ�Ⱥ͸߶�
						if(zhuYinLen > 0)
						{
							//��ȡע���ַ��Ļ��ƿ��
							charZhuYinWidth = rcZhuYin.Width() / zhuYinLen;
							//��ȡע���ַ��Ļ��Ƹ߶�
							charZhuYinHeight = rcZhuYin.Height();			
						}
						//��ǰע��Ϊ��
						else
						{
							//���ַ���������
							dcMemory.DrawText( _T("��"), &rcZhuYin, DT_CALCRECT);
							//��ȡע���ַ��Ļ��ƿ��
							charZhuYinWidth = rcZhuYin.Width();
							//��ȡע���ַ��Ļ��Ƹ߶�
							charZhuYinHeight = rcZhuYin.Height();
						}

						//��ȡ����������ƻ�׼λ�ã�ֻ�е�һ����Ҫ���㣩			}
						if(wordBaseY==-1)
						{
							wordBaseY = zhuYinBaseY + charZhuYinHeight +3;
						}

						//ѡ�񵥴ʻ�������
						dcMemory.SelectObject(&fontWord);
						//���㵥��ռ�ݵľ�������
						CRect rcWord = CRect(0,0,0,0);
						dcMemory.DrawText( currentWord , &rcWord, DT_CALCRECT);

						//��ȡ����������Ƹ߶�
						if(charWordHeight==-1)
						{
							//��ȡע���ַ��Ļ��Ƹ߶�
							charWordHeight = rcWord.Height();	
						}

						//����һ�е��ʵĸ߶ȣ�����������ע���͵��ʣ���ֻ�е�һ����Ҫ���㣩
						if(rowHeight==-1)
						{
							rowHeight = toneHeight + charZhuYinHeight + charWordHeight +10 ;
						}

						//ȡ�����������еĽϴ���
						int finalWidth = rcWord.Width();   
						if(rcWord.Width()<rcZhuYin.Width())
						{
							finalWidth = rcZhuYin.Width();
						}

						//��������׼+���������� ���ڴ��ڿ����������ʾ
						if( finalWidth + allBaseX > clientRect.Width() )
						{
							//����λ�ô�ͷ��ʼ
							allBaseX = JP_PAINT_X_;
							//����λ�� = ����߶�+
							allBaseY += rowHeight ;

						}
						//��ǰ��ʾģʽΪ����ģʽ
						if( showMode==sm_show_word )
						{
							//ѡ�񵥴�����
							dcMemory.SelectObject( fontWord );
							//�ƶ��¾��������ʻ�׼λ��
							CPoint pos(allBaseX, wordBaseY + allBaseY);
							CSize size(finalWidth , rcWord.Height());
							CRect rc( pos,size );
							//���Ƶ���
							dcMemory.DrawText( currentWord, rc, DT_CENTER );
						}
						//ע��ģʽ
						else if( showMode==sm_show_zhuyin )
						{
							//ѡ��ע������
							dcMemory.SelectObject( fontZhuYin );
							CPoint pos(allBaseX, zhuYinBaseY + allBaseY);
							CSize size(finalWidth , rcZhuYin.Height());
							CRect rc( pos,size );
							//�ƶ��¾�����ע����׼λ��

							//�����ǰ��û��ע������Ƶ��ʣ��������ע��
							if( currentZhuYin.IsEmpty() )
							{
								//���Ƶ���
								dcMemory.DrawText( currentWord, rc, DT_CENTER );
							}
							else
							{
								//����ע��
								dcMemory.DrawText( currentZhuYin,rc, DT_CENTER );
							}
							/*
							//������Ϣ����Ϊ3�ı��������򲻻���
							if( jpword.tone.size()%3 == 0 )
							{
							//����������
							for( size_t i=0; i<jpword.tone.size(); i+=3 )
							{

							//��������
							int style = jpword.tone[i];
							//������
							dcMemory.MoveTo( jpword.tone[i+1]*charZhuYinWidth  ,toneBaseY + allBaseY );
							dcMemory.LineTo( jpword.tone[i+2]*charZhuYinWidth  ,toneBaseY + allBaseY );
							//���½���
							if( style == CJPWordInfoEx::jp_tone_down )
							{
							dcMemory.LineTo( jpword.tone[i+2]*charZhuYinWidth-6 ,toneBaseY + 5 + allBaseY );
							}

							}
							}*/

						}
						//����ģʽ
						else
						{
							//ѡ�񵥴�����
							dcMemory.SelectObject( fontWord );
							CPoint pos(allBaseX, wordBaseY + allBaseY);
							CSize size(finalWidth , rcWord.Height());
							CRect rc( pos,size );
							//�ƶ��¾��������ʻ�׼λ��
							//���Ƶ���
							dcMemory.DrawText( currentWord, rc, DT_CENTER );
							//ѡ��ע������
							dcMemory.SelectObject( fontZhuYin );
							//�ƶ��¾�����ע����׼λ��
							pos = CPoint(allBaseX, zhuYinBaseY + allBaseY);
							size = CSize(finalWidth , rcZhuYin.Height());
							rc = CRect( pos,size );
							//����ע��
							dcMemory.DrawText( currentZhuYin,rc, DT_CENTER );
							/*
							//������Ϣ����Ϊ3�ı��������򲻻���
							if( jpword.tone.size()%3 == 0 )
							{
							//����������
							for( size_t i=0; i<jpword.tone.size(); i+=3 )
							{

							//��������
							int style = jpword.tone[i];
							//������
							dcMemory.MoveTo( jpword.tone[i+1]*charZhuYinWidth +6 ,toneBaseY + allBaseY );
							dcMemory.LineTo( jpword.tone[i+2]*charZhuYinWidth -6 ,toneBaseY + allBaseY );
							//���½���
							if( style == CJPWordInfoEx::jp_tone_down )
							{
							dcMemory.LineTo( jpword.tone[i+2]*charZhuYinWidth-6 ,toneBaseY + 5 + allBaseY );
							}

							}
							}
							*/
						}


						//������һ�������׼λ��
						allBaseX += finalWidth+2;
					}
				}
				//�ָ�����
				dcMemory.SelectObject( pOldPen);
				pen.DeleteObject();
				//�ָ���ˢ
				dcMemory.SelectObject( pOldBrush );
				brush.DeleteObject();
				//�ͷŲü�����
				dcMemory.SelectClipRgn(NULL);
				// �ָ�������
				dcMemory.SelectObject( pOldFont );
				dcMemory.SetTextColor( oldTextColor );
				dcMemory.SetBkColor( oldBkColor );
				dc.BitBlt(clientRect.left,clientRect.top,clientRect.right,clientRect.bottom,&dcMemory,0,0,SRCCOPY);
				bitmap.DeleteObject();
			}
		}
	}
}

/*
void CJPWordWnd::OnPaint()
{
CPaintDC dc(this);
CDC dcMemory;
CBitmap bitmap;
if (!dc.IsPrinting())
{
if (dcMemory.CreateCompatibleDC(&dc))
{
if (bitmap.CreateCompatibleBitmap(&dc,m_rcClient.right,m_rcClient.bottom))
{
dcMemory.SelectObject(&bitmap);
CBrush br;
br.CreateSolidBrush(RGB(200,200,200));
dcMemory.FillRect(&m_rcClient,&br);

dc.BitBlt(m_rcClient.left,m_rcClient.top,m_rcClient.right,m_rcClient.bottom,&dcMemory,0,0,SRCCOPY);
bitmap.DeleteObject();
}
}
}
#define JP_PAINT_X_ 5;

CPaintDC dc(this); // device context for painting
//���û���
CPen pen;
pen.CreatePen(PS_SOLID, 0, RGB(255, 0, 0));
CPen *pOldPen = dc.SelectObject(&pen);
//���û�ˢ
CBrush brush;
brush.CreateSolidBrush( RGB(200,255,000) );
CBrush* pOldBrush = dc.SelectObject(&brush);
//���Բ�Ǿ���
dc.RoundRect(clientRect.left+4, clientRect.top+4, clientRect.right-4, clientRect.bottom-4, 20, 20);

// ������ѡ��DC
CFont* pOldFont = dc.SelectObject(&fontZhuYin);
//�������屳��ɫ
COLORREF oldBkColor = dc.SetBkColor(RGB(200,255,0));
COLORREF oldTextColor = dc.SetTextColor(RGB(0,0,0));

//���òü�����
CRgn rgn ;
rgn.CreateRoundRectRgn(clientRect.left+6, clientRect.top+6, clientRect.right-8, clientRect.bottom-8, 20, 20);
dc.SelectClipRgn(&rgn);

//�����ɫ
//	dc.FillSolidRect(clientRect ,);

if(bInit)
{
//cout<<"paint^"<<endl;
allBaseX = JP_PAINT_X_;
allBaseY = 0;
//һ������߶�,����ʱʹ��
int rowHeight = -1;
//����ע���ַ��Ļ��ƿ�ȣ�����������ʱ��
int charZhuYinWidth = -1;
// ע���ַ��߶�
int charZhuYinHeight = -1;

// �����ַ��߶�
int charWordHeight = -1;

//�����߸߶�
int toneHeight = 0;//10 ;

//���������ߵ������׼
int toneBaseY = allBaseY + 5 ;

//����ע���������׼
int zhuYinBaseY = toneBaseY + toneHeight + 2 ;

//���Ƶ��ʵ������׼
int wordBaseY = -1 ;


//ѭ�����Ƹ������ʺ�ע��
for(int i=0 ; i< jpword.wordCount ; i++ )
{
//ȡ�õ�ǰ����
CString currentWord = CString( jpword.getWordAt(i).c_str());
//ȡ�õ�ǰע��
CString currentZhuYin = CString( jpword.getZhuYinAt(i).c_str());
//ȡ�õ��ʳ��ȣ��ַ�����
int wordLen = jpword.getWordLengthAt(i);
//ȡ��ע�����ȣ��ַ�����
int zhuYinLen = jpword.getZhuYinLengthAt(i);
//��ע������ѡ��DC
dc.SelectObject(&fontZhuYin);
//����ע��ռ�ݵľ�������
CRect rcZhuYin = CRect(0,0,0,0);
dc.DrawText( currentZhuYin, &rcZhuYin, DT_CALCRECT);
// �����ַ��Ŀ�Ⱥ͸߶�
if(zhuYinLen > 0)
{
//��ȡע���ַ��Ļ��ƿ��
charZhuYinWidth = rcZhuYin.Width() / zhuYinLen;
//��ȡע���ַ��Ļ��Ƹ߶�
charZhuYinHeight = rcZhuYin.Height();			
}
//��ǰע��Ϊ��
else
{
//���ַ���������
dc.DrawText( _T("��"), &rcZhuYin, DT_CALCRECT);
//��ȡע���ַ��Ļ��ƿ��
charZhuYinWidth = rcZhuYin.Width();
//��ȡע���ַ��Ļ��Ƹ߶�
charZhuYinHeight = rcZhuYin.Height();
}

//��ȡ����������ƻ�׼λ�ã�ֻ�е�һ����Ҫ���㣩			}
if(wordBaseY==-1)
{
wordBaseY = zhuYinBaseY + charZhuYinHeight +3;
}

//ѡ�񵥴ʻ�������
dc.SelectObject(&fontWord);
//���㵥��ռ�ݵľ�������
CRect rcWord = CRect(0,0,0,0);
dc.DrawText( currentWord , &rcWord, DT_CALCRECT);

//��ȡ����������Ƹ߶�
if(charWordHeight==-1)
{
//��ȡע���ַ��Ļ��Ƹ߶�
charWordHeight = rcWord.Height();	
}

//����һ�е��ʵĸ߶ȣ�����������ע���͵��ʣ���ֻ�е�һ����Ҫ���㣩
if(rowHeight==-1)
{
rowHeight = toneHeight + charZhuYinHeight + charWordHeight +10 ;
}

//ȡ�����������еĽϴ���
int finalWidth = rcWord.Width();   
if(rcWord.Width()<rcZhuYin.Width())
{
finalWidth = rcZhuYin.Width();
}

//��������׼+���������� ���ڴ��ڿ����������ʾ
if( finalWidth + allBaseX > clientRect.Width() )
{
//����λ�ô�ͷ��ʼ
allBaseX = JP_PAINT_X_;
//����λ�� = ����߶�+
allBaseY += rowHeight ;

}
//��ǰ��ʾģʽΪ����ģʽ
if( showMode==sm_show_word )
{
//ѡ�񵥴�����
dc.SelectObject( fontWord );
//�ƶ��¾��������ʻ�׼λ��
CPoint pos(allBaseX, wordBaseY + allBaseY);
CSize size(finalWidth , rcWord.Height());
CRect rc( pos,size );
//���Ƶ���
dc.DrawText( currentWord, rc, DT_CENTER );
}
//ע��ģʽ
else if( showMode==sm_show_zhuyin )
{
//ѡ��ע������
dc.SelectObject( fontZhuYin );
CPoint pos(allBaseX, zhuYinBaseY + allBaseY);
CSize size(finalWidth , rcZhuYin.Height());
CRect rc( pos,size );
//�ƶ��¾�����ע����׼λ��

//�����ǰ��û��ע������Ƶ��ʣ��������ע��
if( currentZhuYin.IsEmpty() )
{
//���Ƶ���
dc.DrawText( currentWord, rc, DT_CENTER );
}
else
{
//����ע��
dc.DrawText( currentZhuYin,rc, DT_CENTER );
}
/*
//������Ϣ����Ϊ3�ı��������򲻻���
if( jpword.tone.size()%3 == 0 )
{
//����������
for( size_t i=0; i<jpword.tone.size(); i+=3 )
{

//��������
int style = jpword.tone[i];
//������
dc.MoveTo( jpword.tone[i+1]*charZhuYinWidth  ,toneBaseY + allBaseY );
dc.LineTo( jpword.tone[i+2]*charZhuYinWidth  ,toneBaseY + allBaseY );
//���½���
if( style == CJPWordInfoEx::jp_tone_down )
{
dc.LineTo( jpword.tone[i+2]*charZhuYinWidth-6 ,toneBaseY + 5 + allBaseY );
}

}
}*//*

}
//����ģʽ
else
{
//ѡ�񵥴�����
dc.SelectObject( fontWord );
CPoint pos(allBaseX, wordBaseY + allBaseY);
CSize size(finalWidth , rcWord.Height());
CRect rc( pos,size );
//�ƶ��¾��������ʻ�׼λ��
//���Ƶ���
dc.DrawText( currentWord, rc, DT_CENTER );
//ѡ��ע������
dc.SelectObject( fontZhuYin );
//�ƶ��¾�����ע����׼λ��
pos = CPoint(allBaseX, zhuYinBaseY + allBaseY);
size = CSize(finalWidth , rcZhuYin.Height());
rc = CRect( pos,size );
//����ע��
dc.DrawText( currentZhuYin,rc, DT_CENTER );
/*
//������Ϣ����Ϊ3�ı��������򲻻���
if( jpword.tone.size()%3 == 0 )
{
//����������
for( size_t i=0; i<jpword.tone.size(); i+=3 )
{

//��������
int style = jpword.tone[i];
//������
dc.MoveTo( jpword.tone[i+1]*charZhuYinWidth +6 ,toneBaseY + allBaseY );
dc.LineTo( jpword.tone[i+2]*charZhuYinWidth -6 ,toneBaseY + allBaseY );
//���½���
if( style == CJPWordInfoEx::jp_tone_down )
{
dc.LineTo( jpword.tone[i+2]*charZhuYinWidth-6 ,toneBaseY + 5 + allBaseY );
}

}
}
*//*
}


//������һ�������׼λ��
allBaseX += finalWidth+2;
}
}
//�ָ�����
dc.SelectObject( pOldPen);
pen.DeleteObject();
//�ָ���ˢ
dc.SelectObject( pOldBrush );
brush.DeleteObject();
//�ͷŲü�����
dc.SelectClipRgn(NULL);
// �ָ�������
dc.SelectObject( pOldFont );
dc.SetTextColor( oldTextColor );
dc.SetBkColor( oldBkColor );
}
*/
LRESULT CJPWordWnd::OnNcHitTest(CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	ScreenToClient(&point);
	if(point.y >clientRect.Height()-10)
	{
		//cout<<point.y<<endl;
		return HTBOTTOM ;
	}
	else
	{
		return CStatic::OnNcHitTest(point);
	}
}

void CJPWordWnd::OnNcLButtonDown(UINT nHitTest, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	SendMessage(WM_SYSCOMMAND, SC_SIZE | WMSZ_BOTTOM, MAKELPARAM(point.x, point.y));
	CStatic::OnNcLButtonDown(nHitTest, point);
}

void CJPWordWnd::OnSize(UINT nType, int cx, int cy)
{
	CStatic::OnSize(nType, cx, cy);
	// TODO: �ڴ˴������Ϣ����������
	//���»�ȡ�ͻ�����С��GetClientRect�ᵼ�´���һ�����С��ֱ����Ϊһ���ߣ�
	GetWindowRect(clientRect);
	//��Ļ����ת��
	ScreenToClient(clientRect);
	//cout<<"dddd "<<clientRect.Height()<<endl;
	this->Invalidate();
}

void CJPWordWnd::OnSizing(UINT fwSide, LPRECT pRect)
{
	CStatic::OnSizing(fwSide, pRect);

	// TODO: �ڴ˴������Ϣ����������

	//ֻ���±�Ե�ƶ�ʹ���ƶ������ؼ�
	if( fwSide == WMSZ_BOTTOM )
	{
		CRect rc = *pRect;
		//����ת��
		GetParent()->ScreenToClient(rc);
		//�����ڵ��±�Ե��������Ϣ����ȥ
		GetParent()->SendMessage(WM_DLG_MOVE_CTRLS,(WPARAM)rc.bottom);
	}
	//cout<<rc.top<<endl;
}

void CJPWordWnd::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	lpMMI->ptMinTrackSize.y = 60;
	CStatic::OnGetMinMaxInfo(lpMMI);
}
