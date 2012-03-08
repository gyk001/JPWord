// JPWordWnd.cpp : 实现文件
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



// CJPWordWnd 消息处理程序
void CJPWordWnd::PreSubclassWindow()
{
	//修改CStatic属性为可以接受通知，否则不能相应鼠标消息等	
	ModifyStyle(NULL,SS_NOTIFY);
	//子类化
	CStatic::PreSubclassWindow();
	//注音字体初始化
	fontZhuYin.CreatePointFont(120,_T("宋体"),NULL);
	//单词字体初始化
	fontWord.CreatePointFont(200,_T("宋体"),NULL);
	//显示模式
	showMode = sm_show_all;
	//基准
	allBaseX = 0;
	allBaseY = 0;
	//获取窗口区域
	GetWindowRect(clientRect);
	//屏幕作标转换
	ScreenToClient(clientRect);
}
/*
void CJPWordWnd::OnPaint()
{
//TRACE(_T(" -> OnPaint…………………………"));
CPaintDC dc(this); // device context for painting
// 创建字体
CFont font;
font.CreatePointFont(160,_T("宋体"),NULL);
// 将字体选进DC
CFont* pOldFont = dc.SelectObject(&font);
//设置字体背景色
dc.SetBkColor(RGB(200,255,200));
//获取客户区大小
CRect clientRect;
GetClientRect(clientRect);
//设置裁剪区域
CRgn rgn ;
rgn.CreateRectRgnIndirect(clientRect);
dc.SelectClipRgn(&rgn);
//填充颜色
dc.FillSolidRect(clientRect , RGB(200,255,200));

//总体绘制的横向基准
int baseX = 0 ;
//总体绘制的纵向基准
int baseY = 0 ;

//绘制声调线的纵向基准
int toneBaseY = baseY + 10;

//绘制注音的纵向基准
int zhuYinBaseY = baseY + 20 ;

//绘制单词的纵向基准,也就是【注音的纵向基准+字体高度+3】
int wordBaseY = -1 ;
//一行总体高度
int rowHeight = -1;

//单个字符的绘制宽度，绘制声调线时用
int charWidth = -1;

//循环绘制各个单词和注音
for(int i=0 ; i< jpword.wordCount ; i++ )
{
//取得当前单词
CString currentWord = CString( jpword.getWordAt(i).c_str());
//取得当前注音
CString currentZhuYin = CString( jpword.getZhuYinAt(i).c_str());
//取得单词长度（字符数）
int wordLen = jpword.getWordLengthAt(i);
//取得注音长度（字符数）
int zhuYinLen = jpword.getZhuYinLengthAt(i);
//计算注音占据的矩形区域
CRect rcZhuYin = CRect(0,0,0,0);
dc.DrawText( currentZhuYin, &rcZhuYin, DT_CALCRECT);
//如果当前注音为空的话就用わ来计算区域大小
if(zhuYinLen==0)
{
dc.DrawText( _T("わ"), &rcZhuYin, DT_CALCRECT);
charWidth = rcZhuYin.Width();
}
//获取单词纵向绘制基准位置（只有第一次需要计算）			}
if(wordBaseY==-1)
{
wordBaseY = zhuYinBaseY + rcZhuYin.Height()+3;
}
//获取字符的宽度
if(charWidth==-1)
{
charWidth = rcZhuYin.Width() / zhuYinLen ;
}
//计算单词占据的矩形区域
CRect rcWord = CRect(0,0,0,0);
dc.DrawText( currentWord , &rcWord, DT_CALCRECT);
//计算一行单词的高度（包括声调，注音和单词）（只有第一次需要计算）
if(rowHeight==-1)
{
rowHeight = wordBaseY + rcWord.Width();
}

//构造一个新矩形rc使之为注音和单词的矩形宽度较大者
CRect rc  = rcWord;
if(rcWord.Width()<rcZhuYin.Width())
{
rc = rcZhuYin;
}

//如果横向基准+绘制区域宽度 大于窗口宽度则折行显示
if( rc.Width()+ baseX > clientRect.Width() )
{
//横向位置从头开始
baseX = 0;
//纵向位置 = 字体高度+
baseY += rowHeight ;

}

//当前显示模式为单词模式
if( showMode==sm_show_word )
{
//移动新矩形至单词基准位置
rc.MoveToXY( baseX, wordBaseY + baseY );
//绘制单词
dc.DrawText( currentWord, rc, DT_CENTER );
}
//注音模式
else if( showMode==sm_show_zhuyin )
{
//移动新矩形至注音基准位置
rc.MoveToXY(baseX, zhuYinBaseY + baseY );
//如果当前词没有注音则绘制单词，否则绘制注音
if( currentZhuYin.IsEmpty() )
{
//绘制单词
dc.DrawText( currentWord, rc, DT_CENTER );
}
else
{
//绘制注音
dc.DrawText( currentZhuYin,rc, DT_CENTER );
}
//声调信息必须为3的倍数，否则不绘制
if( jpword.tone.size()%3 == 0 )
{
//绘制声调线
for( size_t i=0; i<jpword.tone.size(); i+=3 )
{

//声调类型
int style = jpword.tone[i];
//划横线
dc.MoveTo( jpword.tone[i+1]*charWidth +6 ,toneBaseY + baseY );
dc.LineTo( jpword.tone[i+2]*charWidth -6 ,toneBaseY + baseY );
//画下降线
if( style == CJPWordInfoEx::jp_tone_down )
{
dc.LineTo( jpword.tone[i+2]*charWidth-6 ,toneBaseY + 5 + baseY );
}

}
}

}
//正常模式
else
{
//移动新矩形至单词基准位置
rc.MoveToXY( baseX, wordBaseY + baseY );
//绘制单词
dc.DrawText( currentWord, rc, DT_CENTER );
//移动新矩形至注音基准位置
rc.MoveToY( zhuYinBaseY + baseY );
//绘制注音
dc.DrawText( currentZhuYin,rc, DT_CENTER );

//声调信息必须为3的倍数，否则不绘制
if( jpword.tone.size()%3 == 0 )
{
//绘制声调线
for( size_t i=0; i<jpword.tone.size(); i+=3 )
{

//声调类型
int style = jpword.tone[i];
//划横线
dc.MoveTo( jpword.tone[i+1]*charWidth +6 ,toneBaseY + baseY );
dc.LineTo( jpword.tone[i+2]*charWidth -6 ,toneBaseY + baseY );
//画下降线
if( style == CJPWordInfoEx::jp_tone_down )
{
dc.LineTo( jpword.tone[i+2]*charWidth-6 ,toneBaseY + 5 + baseY );
}

}
}
}


//计算下一个横向基准位置
baseX += rc.Width()+2;
}

// 恢复旧字体-这是必须的
dc.SelectObject( pOldFont );
//恢复背景模式
//	dc.SetBkMode( oldBkMode );
}
*/
bool CJPWordWnd::loadWord(CJPWordInfo wordInfo)
{
	bInit = false;
	//加载单词信息
	if( jpword.loadWord( wordInfo.jpword )!=0 )
	{
		return false;
	}
	//加载声调信息
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
				//设置画笔
				CPen pen;
				pen.CreatePen(PS_SOLID, 0, RGB(255, 0, 0));
				CPen *pOldPen = dcMemory.SelectObject(&pen);
				//设置画刷
				CBrush brush;
				brush.CreateSolidBrush( RGB(200,255,000) );
				CBrush* pOldBrush = dcMemory.SelectObject(&brush);
				//填充圆角矩形
				dcMemory.RoundRect(clientRect.left+4, clientRect.top+4, clientRect.right-4, clientRect.bottom-4, 20, 20);

				// 将字体选进DC
				CFont* pOldFont = dcMemory.SelectObject(&fontZhuYin);
				//设置字体背景色
				COLORREF oldBkColor = dcMemory.SetBkColor(RGB(200,255,0));
				COLORREF oldTextColor = dcMemory.SetTextColor(RGB(0,0,0));

				//设置裁剪区域
				CRgn rgn ;
				rgn.CreateRoundRectRgn(clientRect.left+6, clientRect.top+6, clientRect.right-8, clientRect.bottom-8, 20, 20);
				dcMemory.SelectClipRgn(&rgn);


				if(bInit)
				{
					//cout<<"paint^"<<endl;
					allBaseX = JP_PAINT_X_;
					allBaseY = 0;
					//一行总体高度,换行时使用
					int rowHeight = -1;
					//单个注音字符的绘制宽度，绘制声调线时用
					int charZhuYinWidth = -1;
					// 注音字符高度
					int charZhuYinHeight = -1;

					// 单词字符高度
					int charWordHeight = -1;

					//声调线高度
					int toneHeight = 0;//10 ;

					//绘制声调线的纵向基准
					int toneBaseY = allBaseY + 5 ;

					//绘制注音的纵向基准
					int zhuYinBaseY = toneBaseY + toneHeight + 2 ;

					//绘制单词的纵向基准
					int wordBaseY = -1 ;


					//循环绘制各个单词和注音
					for(int i=0 ; i< jpword.wordCount ; i++ )
					{
						//取得当前单词
						CString currentWord = CString( jpword.getWordAt(i).c_str());
						//取得当前注音
						CString currentZhuYin = CString( jpword.getZhuYinAt(i).c_str());
						//取得单词长度（字符数）
						int wordLen = jpword.getWordLengthAt(i);
						//取得注音长度（字符数）
						int zhuYinLen = jpword.getZhuYinLengthAt(i);
						//将注音字体选进DC
						dcMemory.SelectObject(&fontZhuYin);
						//计算注音占据的矩形区域
						CRect rcZhuYin = CRect(0,0,0,0);
						dcMemory.DrawText( currentZhuYin, &rcZhuYin, DT_CALCRECT);
						// 计算字符的宽度和高度
						if(zhuYinLen > 0)
						{
							//获取注音字符的绘制宽度
							charZhuYinWidth = rcZhuYin.Width() / zhuYinLen;
							//获取注音字符的绘制高度
							charZhuYinHeight = rcZhuYin.Height();			
						}
						//当前注音为空
						else
						{
							//用字符わ来计算
							dcMemory.DrawText( _T("わ"), &rcZhuYin, DT_CALCRECT);
							//获取注音字符的绘制宽度
							charZhuYinWidth = rcZhuYin.Width();
							//获取注音字符的绘制高度
							charZhuYinHeight = rcZhuYin.Height();
						}

						//获取单词纵向绘制基准位置（只有第一次需要计算）			}
						if(wordBaseY==-1)
						{
							wordBaseY = zhuYinBaseY + charZhuYinHeight +3;
						}

						//选择单词绘制字体
						dcMemory.SelectObject(&fontWord);
						//计算单词占据的矩形区域
						CRect rcWord = CRect(0,0,0,0);
						dcMemory.DrawText( currentWord , &rcWord, DT_CALCRECT);

						//获取单词字体绘制高度
						if(charWordHeight==-1)
						{
							//获取注音字符的绘制高度
							charWordHeight = rcWord.Height();	
						}

						//计算一行单词的高度（包括声调，注音和单词）（只有第一次需要计算）
						if(rowHeight==-1)
						{
							rowHeight = toneHeight + charZhuYinHeight + charWordHeight +10 ;
						}

						//取出两个矩形中的较大宽度
						int finalWidth = rcWord.Width();   
						if(rcWord.Width()<rcZhuYin.Width())
						{
							finalWidth = rcZhuYin.Width();
						}

						//如果横向基准+绘制区域宽度 大于窗口宽度则折行显示
						if( finalWidth + allBaseX > clientRect.Width() )
						{
							//横向位置从头开始
							allBaseX = JP_PAINT_X_;
							//纵向位置 = 字体高度+
							allBaseY += rowHeight ;

						}
						//当前显示模式为单词模式
						if( showMode==sm_show_word )
						{
							//选择单词字体
							dcMemory.SelectObject( fontWord );
							//移动新矩形至单词基准位置
							CPoint pos(allBaseX, wordBaseY + allBaseY);
							CSize size(finalWidth , rcWord.Height());
							CRect rc( pos,size );
							//绘制单词
							dcMemory.DrawText( currentWord, rc, DT_CENTER );
						}
						//注音模式
						else if( showMode==sm_show_zhuyin )
						{
							//选择注音字体
							dcMemory.SelectObject( fontZhuYin );
							CPoint pos(allBaseX, zhuYinBaseY + allBaseY);
							CSize size(finalWidth , rcZhuYin.Height());
							CRect rc( pos,size );
							//移动新矩形至注音基准位置

							//如果当前词没有注音则绘制单词，否则绘制注音
							if( currentZhuYin.IsEmpty() )
							{
								//绘制单词
								dcMemory.DrawText( currentWord, rc, DT_CENTER );
							}
							else
							{
								//绘制注音
								dcMemory.DrawText( currentZhuYin,rc, DT_CENTER );
							}
							/*
							//声调信息必须为3的倍数，否则不绘制
							if( jpword.tone.size()%3 == 0 )
							{
							//绘制声调线
							for( size_t i=0; i<jpword.tone.size(); i+=3 )
							{

							//声调类型
							int style = jpword.tone[i];
							//划横线
							dcMemory.MoveTo( jpword.tone[i+1]*charZhuYinWidth  ,toneBaseY + allBaseY );
							dcMemory.LineTo( jpword.tone[i+2]*charZhuYinWidth  ,toneBaseY + allBaseY );
							//画下降线
							if( style == CJPWordInfoEx::jp_tone_down )
							{
							dcMemory.LineTo( jpword.tone[i+2]*charZhuYinWidth-6 ,toneBaseY + 5 + allBaseY );
							}

							}
							}*/

						}
						//正常模式
						else
						{
							//选择单词字体
							dcMemory.SelectObject( fontWord );
							CPoint pos(allBaseX, wordBaseY + allBaseY);
							CSize size(finalWidth , rcWord.Height());
							CRect rc( pos,size );
							//移动新矩形至单词基准位置
							//绘制单词
							dcMemory.DrawText( currentWord, rc, DT_CENTER );
							//选择注音字体
							dcMemory.SelectObject( fontZhuYin );
							//移动新矩形至注音基准位置
							pos = CPoint(allBaseX, zhuYinBaseY + allBaseY);
							size = CSize(finalWidth , rcZhuYin.Height());
							rc = CRect( pos,size );
							//绘制注音
							dcMemory.DrawText( currentZhuYin,rc, DT_CENTER );
							/*
							//声调信息必须为3的倍数，否则不绘制
							if( jpword.tone.size()%3 == 0 )
							{
							//绘制声调线
							for( size_t i=0; i<jpword.tone.size(); i+=3 )
							{

							//声调类型
							int style = jpword.tone[i];
							//划横线
							dcMemory.MoveTo( jpword.tone[i+1]*charZhuYinWidth +6 ,toneBaseY + allBaseY );
							dcMemory.LineTo( jpword.tone[i+2]*charZhuYinWidth -6 ,toneBaseY + allBaseY );
							//画下降线
							if( style == CJPWordInfoEx::jp_tone_down )
							{
							dcMemory.LineTo( jpword.tone[i+2]*charZhuYinWidth-6 ,toneBaseY + 5 + allBaseY );
							}

							}
							}
							*/
						}


						//计算下一个横向基准位置
						allBaseX += finalWidth+2;
					}
				}
				//恢复画笔
				dcMemory.SelectObject( pOldPen);
				pen.DeleteObject();
				//恢复画刷
				dcMemory.SelectObject( pOldBrush );
				brush.DeleteObject();
				//释放裁剪区域
				dcMemory.SelectClipRgn(NULL);
				// 恢复旧字体
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
//设置画笔
CPen pen;
pen.CreatePen(PS_SOLID, 0, RGB(255, 0, 0));
CPen *pOldPen = dc.SelectObject(&pen);
//设置画刷
CBrush brush;
brush.CreateSolidBrush( RGB(200,255,000) );
CBrush* pOldBrush = dc.SelectObject(&brush);
//填充圆角矩形
dc.RoundRect(clientRect.left+4, clientRect.top+4, clientRect.right-4, clientRect.bottom-4, 20, 20);

// 将字体选进DC
CFont* pOldFont = dc.SelectObject(&fontZhuYin);
//设置字体背景色
COLORREF oldBkColor = dc.SetBkColor(RGB(200,255,0));
COLORREF oldTextColor = dc.SetTextColor(RGB(0,0,0));

//设置裁剪区域
CRgn rgn ;
rgn.CreateRoundRectRgn(clientRect.left+6, clientRect.top+6, clientRect.right-8, clientRect.bottom-8, 20, 20);
dc.SelectClipRgn(&rgn);

//填充颜色
//	dc.FillSolidRect(clientRect ,);

if(bInit)
{
//cout<<"paint^"<<endl;
allBaseX = JP_PAINT_X_;
allBaseY = 0;
//一行总体高度,换行时使用
int rowHeight = -1;
//单个注音字符的绘制宽度，绘制声调线时用
int charZhuYinWidth = -1;
// 注音字符高度
int charZhuYinHeight = -1;

// 单词字符高度
int charWordHeight = -1;

//声调线高度
int toneHeight = 0;//10 ;

//绘制声调线的纵向基准
int toneBaseY = allBaseY + 5 ;

//绘制注音的纵向基准
int zhuYinBaseY = toneBaseY + toneHeight + 2 ;

//绘制单词的纵向基准
int wordBaseY = -1 ;


//循环绘制各个单词和注音
for(int i=0 ; i< jpword.wordCount ; i++ )
{
//取得当前单词
CString currentWord = CString( jpword.getWordAt(i).c_str());
//取得当前注音
CString currentZhuYin = CString( jpword.getZhuYinAt(i).c_str());
//取得单词长度（字符数）
int wordLen = jpword.getWordLengthAt(i);
//取得注音长度（字符数）
int zhuYinLen = jpword.getZhuYinLengthAt(i);
//将注音字体选进DC
dc.SelectObject(&fontZhuYin);
//计算注音占据的矩形区域
CRect rcZhuYin = CRect(0,0,0,0);
dc.DrawText( currentZhuYin, &rcZhuYin, DT_CALCRECT);
// 计算字符的宽度和高度
if(zhuYinLen > 0)
{
//获取注音字符的绘制宽度
charZhuYinWidth = rcZhuYin.Width() / zhuYinLen;
//获取注音字符的绘制高度
charZhuYinHeight = rcZhuYin.Height();			
}
//当前注音为空
else
{
//用字符わ来计算
dc.DrawText( _T("わ"), &rcZhuYin, DT_CALCRECT);
//获取注音字符的绘制宽度
charZhuYinWidth = rcZhuYin.Width();
//获取注音字符的绘制高度
charZhuYinHeight = rcZhuYin.Height();
}

//获取单词纵向绘制基准位置（只有第一次需要计算）			}
if(wordBaseY==-1)
{
wordBaseY = zhuYinBaseY + charZhuYinHeight +3;
}

//选择单词绘制字体
dc.SelectObject(&fontWord);
//计算单词占据的矩形区域
CRect rcWord = CRect(0,0,0,0);
dc.DrawText( currentWord , &rcWord, DT_CALCRECT);

//获取单词字体绘制高度
if(charWordHeight==-1)
{
//获取注音字符的绘制高度
charWordHeight = rcWord.Height();	
}

//计算一行单词的高度（包括声调，注音和单词）（只有第一次需要计算）
if(rowHeight==-1)
{
rowHeight = toneHeight + charZhuYinHeight + charWordHeight +10 ;
}

//取出两个矩形中的较大宽度
int finalWidth = rcWord.Width();   
if(rcWord.Width()<rcZhuYin.Width())
{
finalWidth = rcZhuYin.Width();
}

//如果横向基准+绘制区域宽度 大于窗口宽度则折行显示
if( finalWidth + allBaseX > clientRect.Width() )
{
//横向位置从头开始
allBaseX = JP_PAINT_X_;
//纵向位置 = 字体高度+
allBaseY += rowHeight ;

}
//当前显示模式为单词模式
if( showMode==sm_show_word )
{
//选择单词字体
dc.SelectObject( fontWord );
//移动新矩形至单词基准位置
CPoint pos(allBaseX, wordBaseY + allBaseY);
CSize size(finalWidth , rcWord.Height());
CRect rc( pos,size );
//绘制单词
dc.DrawText( currentWord, rc, DT_CENTER );
}
//注音模式
else if( showMode==sm_show_zhuyin )
{
//选择注音字体
dc.SelectObject( fontZhuYin );
CPoint pos(allBaseX, zhuYinBaseY + allBaseY);
CSize size(finalWidth , rcZhuYin.Height());
CRect rc( pos,size );
//移动新矩形至注音基准位置

//如果当前词没有注音则绘制单词，否则绘制注音
if( currentZhuYin.IsEmpty() )
{
//绘制单词
dc.DrawText( currentWord, rc, DT_CENTER );
}
else
{
//绘制注音
dc.DrawText( currentZhuYin,rc, DT_CENTER );
}
/*
//声调信息必须为3的倍数，否则不绘制
if( jpword.tone.size()%3 == 0 )
{
//绘制声调线
for( size_t i=0; i<jpword.tone.size(); i+=3 )
{

//声调类型
int style = jpword.tone[i];
//划横线
dc.MoveTo( jpword.tone[i+1]*charZhuYinWidth  ,toneBaseY + allBaseY );
dc.LineTo( jpword.tone[i+2]*charZhuYinWidth  ,toneBaseY + allBaseY );
//画下降线
if( style == CJPWordInfoEx::jp_tone_down )
{
dc.LineTo( jpword.tone[i+2]*charZhuYinWidth-6 ,toneBaseY + 5 + allBaseY );
}

}
}*//*

}
//正常模式
else
{
//选择单词字体
dc.SelectObject( fontWord );
CPoint pos(allBaseX, wordBaseY + allBaseY);
CSize size(finalWidth , rcWord.Height());
CRect rc( pos,size );
//移动新矩形至单词基准位置
//绘制单词
dc.DrawText( currentWord, rc, DT_CENTER );
//选择注音字体
dc.SelectObject( fontZhuYin );
//移动新矩形至注音基准位置
pos = CPoint(allBaseX, zhuYinBaseY + allBaseY);
size = CSize(finalWidth , rcZhuYin.Height());
rc = CRect( pos,size );
//绘制注音
dc.DrawText( currentZhuYin,rc, DT_CENTER );
/*
//声调信息必须为3的倍数，否则不绘制
if( jpword.tone.size()%3 == 0 )
{
//绘制声调线
for( size_t i=0; i<jpword.tone.size(); i+=3 )
{

//声调类型
int style = jpword.tone[i];
//划横线
dc.MoveTo( jpword.tone[i+1]*charZhuYinWidth +6 ,toneBaseY + allBaseY );
dc.LineTo( jpword.tone[i+2]*charZhuYinWidth -6 ,toneBaseY + allBaseY );
//画下降线
if( style == CJPWordInfoEx::jp_tone_down )
{
dc.LineTo( jpword.tone[i+2]*charZhuYinWidth-6 ,toneBaseY + 5 + allBaseY );
}

}
}
*//*
}


//计算下一个横向基准位置
allBaseX += finalWidth+2;
}
}
//恢复画笔
dc.SelectObject( pOldPen);
pen.DeleteObject();
//恢复画刷
dc.SelectObject( pOldBrush );
brush.DeleteObject();
//释放裁剪区域
dc.SelectClipRgn(NULL);
// 恢复旧字体
dc.SelectObject( pOldFont );
dc.SetTextColor( oldTextColor );
dc.SetBkColor( oldBkColor );
}
*/
LRESULT CJPWordWnd::OnNcHitTest(CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
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
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	SendMessage(WM_SYSCOMMAND, SC_SIZE | WMSZ_BOTTOM, MAKELPARAM(point.x, point.y));
	CStatic::OnNcLButtonDown(nHitTest, point);
}

void CJPWordWnd::OnSize(UINT nType, int cx, int cy)
{
	CStatic::OnSize(nType, cx, cy);
	// TODO: 在此处添加消息处理程序代码
	//重新获取客户区大小（GetClientRect会导致窗口一点点缩小，直至成为一条线）
	GetWindowRect(clientRect);
	//屏幕作标转换
	ScreenToClient(clientRect);
	//cout<<"dddd "<<clientRect.Height()<<endl;
	this->Invalidate();
}

void CJPWordWnd::OnSizing(UINT fwSide, LPRECT pRect)
{
	CStatic::OnSizing(fwSide, pRect);

	// TODO: 在此处添加消息处理程序代码

	//只有下边缘移动使才移动其他控件
	if( fwSide == WMSZ_BOTTOM )
	{
		CRect rc = *pRect;
		//坐标转换
		GetParent()->ScreenToClient(rc);
		//将窗口的下边缘坐标随消息发出去
		GetParent()->SendMessage(WM_DLG_MOVE_CTRLS,(WPARAM)rc.bottom);
	}
	//cout<<rc.top<<endl;
}

void CJPWordWnd::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	lpMMI->ptMinTrackSize.y = 60;
	CStatic::OnGetMinMaxInfo(lpMMI);
}
