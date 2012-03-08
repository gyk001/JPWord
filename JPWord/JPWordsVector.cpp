// JPWordsVector.cpp : 实现文件
//

#include "stdafx.h"
#include "JPWord.h"
#include "JPWordsVector.h"
#include <algorithm>
#include <iostream>
#include "JPWordDlg.h"
using namespace std;

#include "./tinyxml/tinyxml.h"
#include "MzConvert.h"
// CJPWordsVector

CJPWordsVector::CJPWordsVector()
{

}

CJPWordsVector::~CJPWordsVector()
{
}


// CJPWordsVector 成员函数
/** 
 * 从文件加载单词信息
 * @param filename 文件名
 * @param clearOldWords 是否清除现有的单词信息，默认为是
 * @return 加载成功返回真，失败返回假
 */
bool CJPWordsVector::LoadFile(wstring fileName, bool clearOldWord /*= true*/)
{
	//清空当前单词
	if(clearOldWord)
	{
		words.clear();
	}
	
	
	CJPWordInfo word;

	//读取文件
	TiXmlDocument* myDocument = new TiXmlDocument();
	bool loadOkay = myDocument->LoadFile( MzConvert::UnicodeToANSI(fileName).c_str() ,TIXML_ENCODING_UTF8);
	//加载文件失败
	if ( !loadOkay )
	{
		//printf( "Could not load test file 'demotest.xml'. Error='%s'. Exiting.\n", doc.ErrorDesc() );
		return false;//exit( 1 );
	}

	TiXmlHandle docHandle( myDocument );
	//读取配置
	TiXmlElement* configElement = docHandle.FirstChild( "jproot" ).FirstChild( "config" ).ToElement();
	if ( configElement )
	{
		TiXmlElement * timeNode = configElement->FirstChildElement();
		if(timeNode)
		{
			string timestr = timeNode->GetText();
			int time = atoi(timestr.c_str());
			((CJPWordDlg*)(AfxGetApp()->GetMainWnd()))->maxTime = time;
		}

	}
	//读取单词
	TiXmlElement* wordElement = docHandle.FirstChild( "jproot" ).FirstChild( "words" ).FirstChild( "word" ).ToElement();
	if( ! wordElement )
	{
		return false;
	}
	
	//遍历所有word元素，每个word代表一个单词
	while( wordElement )
	{
		word.clear();
		TiXmlElement* wordMetaElement = wordElement->FirstChildElement();//获得word的子元素
		//遍历word的所有子元素，每个子元素代表一个单词的一项信息
		while(wordMetaElement)
		{
			//获取节点名称
			wstring name = MzConvert::UTF8ToUnicode( wordMetaElement->Value() );			
			//获取节点值
			const char* metaText = wordMetaElement->GetText();
			//节点值为空则跳过该信息的处理
			if( metaText==NULL )
			{
				//下一个节点，即该单词的下一个信息
				wordMetaElement = wordMetaElement->NextSiblingElement();
				continue;
			}
			//节点值转换为wstring
			wstring text = MzConvert::UTF8ToUnicode( metaText );

			//日语单词和注音信息
			if( name==_T("string"))
			{
				word.jpword = text;
			}
			//中文解释信息
			if( name==_T("chinese") )
			{
				word.chinese = text;
			}
			//词性
			if( name==_T("cixing") )
			{
				word.cixing = text;
			}
			//附加解释信息
			if( name==_T("introduction") )
			{
				word.introduction = text;
			}
			//声调信息
			if( name==_T("tone") )
			{
				word.tone = makeTone( text );
			}	


			//下一个节点，即该单词的下一个信息
			wordMetaElement = wordMetaElement->NextSiblingElement();
		}
		//单词信息无误则添加
		if( word.isCorrect() )
		{
			words.push_back(word);
		}
		//移动到下一个节点，即下一个单词
		wordElement = wordElement->NextSiblingElement();
	}
	//释放空间
	delete myDocument;
	//打乱顺序
	random_shuffle(words.begin(), words.end());  
	//当前单词为第一个
	current = 0;
	return true;
}

/**
 * 获取下一个单词
 * @param Forgoten 只从没有记住的单词中选择，默认为ture
 * @return 有单词返回下一个单词指针，没有则返回NULL
 */
CJPWordInfo* CJPWordsVector::getNextJPWord( bool Forgoten /*= true*/)
{
	current ++ ;
	//强制下标合法
	if( current>=words.size() || current<0 )
	{
		current = 0;
	}
	//没有单词，返回空
	if( words.size()==0 )
	{
		return NULL;
	}
	//返回当前单词
	return &words[current];
}

/**
 * 获取上一个单词
 * @param Forgoten 只从没有记住的单词中选择，默认为ture
 * @return 有单词返回上一个单词指针，没有则返回NULL
 */
CJPWordInfo* CJPWordsVector::getPrevJPWord( bool Forgoten /*= true*/)
{
	current -- ;
	//强制下标合法
	if( current>=words.size() || current<0 )
	{
		current = words.size()-1 ;
	}
	//没有单词，返回空
	if( words.size()==0 )
	{
		return NULL;
	}
	//返回当前单词
	return &words[current];
}

/**
 * 获取当前单词
 * @param Forgoten 只从没有记住的单词中选择，默认为ture
 * @return 有单词返回当前单词指针，没有则返回NULL
 */
CJPWordInfo* CJPWordsVector::getCurrentJPWord( bool Forgoten /*= true*/)
{
	//强制下标合法
	if( current>=words.size() || current<0 )
	{
		current = words.size()-1 ;
	}
	//没有单词，返回空
	if( words.size()==0 )
	{
		return NULL;
	}
	//返回当前单词
	return &words[current];
}


/**
 * 解析声调字符串为整形数组
 * @param str 需要解析的字符穿
 * @return 返回解析好的整形数组
 */

vector<int> CJPWordsVector::makeTone(wstring str)
{
	//目标整形数组
	vector<int> tone;
	//分割符为英文逗号
	wchar_t flag = ',';
	//起始位置
	size_t start = 0;
	//结束位置
	size_t end = 0 ;
	for( ; end<str.size(); end++ )
	{
		//当前符号位分隔符
		if(str.at( end )== flag)
		{
			//截取子串
			wstring numStr = str.substr(start,end-start);
			//转换成数字加入数组
			int num = _wtoi(numStr.c_str());
			tone.push_back(num);
			//跳过分割符
			end++;
			//移动开始位置
			start = end;
		}
	}
	//截取子串
	wstring numStr = str.substr(start,end-start);
	//转换成数字加入数组
	int num = _wtoi(numStr.c_str());
	tone.push_back(num);
	return tone;
}

size_t CJPWordsVector::getWordsCount()
{
	return words.size();
}