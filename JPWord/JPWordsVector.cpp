// JPWordsVector.cpp : ʵ���ļ�
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


// CJPWordsVector ��Ա����
/** 
 * ���ļ����ص�����Ϣ
 * @param filename �ļ���
 * @param clearOldWords �Ƿ�������еĵ�����Ϣ��Ĭ��Ϊ��
 * @return ���سɹ������棬ʧ�ܷ��ؼ�
 */
bool CJPWordsVector::LoadFile(wstring fileName, bool clearOldWord /*= true*/)
{
	//��յ�ǰ����
	if(clearOldWord)
	{
		words.clear();
	}
	
	
	CJPWordInfo word;

	//��ȡ�ļ�
	TiXmlDocument* myDocument = new TiXmlDocument();
	bool loadOkay = myDocument->LoadFile( MzConvert::UnicodeToANSI(fileName).c_str() ,TIXML_ENCODING_UTF8);
	//�����ļ�ʧ��
	if ( !loadOkay )
	{
		//printf( "Could not load test file 'demotest.xml'. Error='%s'. Exiting.\n", doc.ErrorDesc() );
		return false;//exit( 1 );
	}

	TiXmlHandle docHandle( myDocument );
	//��ȡ����
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
	//��ȡ����
	TiXmlElement* wordElement = docHandle.FirstChild( "jproot" ).FirstChild( "words" ).FirstChild( "word" ).ToElement();
	if( ! wordElement )
	{
		return false;
	}
	
	//��������wordԪ�أ�ÿ��word����һ������
	while( wordElement )
	{
		word.clear();
		TiXmlElement* wordMetaElement = wordElement->FirstChildElement();//���word����Ԫ��
		//����word��������Ԫ�أ�ÿ����Ԫ�ش���һ�����ʵ�һ����Ϣ
		while(wordMetaElement)
		{
			//��ȡ�ڵ�����
			wstring name = MzConvert::UTF8ToUnicode( wordMetaElement->Value() );			
			//��ȡ�ڵ�ֵ
			const char* metaText = wordMetaElement->GetText();
			//�ڵ�ֵΪ������������Ϣ�Ĵ���
			if( metaText==NULL )
			{
				//��һ���ڵ㣬���õ��ʵ���һ����Ϣ
				wordMetaElement = wordMetaElement->NextSiblingElement();
				continue;
			}
			//�ڵ�ֵת��Ϊwstring
			wstring text = MzConvert::UTF8ToUnicode( metaText );

			//���ﵥ�ʺ�ע����Ϣ
			if( name==_T("string"))
			{
				word.jpword = text;
			}
			//���Ľ�����Ϣ
			if( name==_T("chinese") )
			{
				word.chinese = text;
			}
			//����
			if( name==_T("cixing") )
			{
				word.cixing = text;
			}
			//���ӽ�����Ϣ
			if( name==_T("introduction") )
			{
				word.introduction = text;
			}
			//������Ϣ
			if( name==_T("tone") )
			{
				word.tone = makeTone( text );
			}	


			//��һ���ڵ㣬���õ��ʵ���һ����Ϣ
			wordMetaElement = wordMetaElement->NextSiblingElement();
		}
		//������Ϣ���������
		if( word.isCorrect() )
		{
			words.push_back(word);
		}
		//�ƶ�����һ���ڵ㣬����һ������
		wordElement = wordElement->NextSiblingElement();
	}
	//�ͷſռ�
	delete myDocument;
	//����˳��
	random_shuffle(words.begin(), words.end());  
	//��ǰ����Ϊ��һ��
	current = 0;
	return true;
}

/**
 * ��ȡ��һ������
 * @param Forgoten ֻ��û�м�ס�ĵ�����ѡ��Ĭ��Ϊture
 * @return �е��ʷ�����һ������ָ�룬û���򷵻�NULL
 */
CJPWordInfo* CJPWordsVector::getNextJPWord( bool Forgoten /*= true*/)
{
	current ++ ;
	//ǿ���±�Ϸ�
	if( current>=words.size() || current<0 )
	{
		current = 0;
	}
	//û�е��ʣ����ؿ�
	if( words.size()==0 )
	{
		return NULL;
	}
	//���ص�ǰ����
	return &words[current];
}

/**
 * ��ȡ��һ������
 * @param Forgoten ֻ��û�м�ס�ĵ�����ѡ��Ĭ��Ϊture
 * @return �е��ʷ�����һ������ָ�룬û���򷵻�NULL
 */
CJPWordInfo* CJPWordsVector::getPrevJPWord( bool Forgoten /*= true*/)
{
	current -- ;
	//ǿ���±�Ϸ�
	if( current>=words.size() || current<0 )
	{
		current = words.size()-1 ;
	}
	//û�е��ʣ����ؿ�
	if( words.size()==0 )
	{
		return NULL;
	}
	//���ص�ǰ����
	return &words[current];
}

/**
 * ��ȡ��ǰ����
 * @param Forgoten ֻ��û�м�ס�ĵ�����ѡ��Ĭ��Ϊture
 * @return �е��ʷ��ص�ǰ����ָ�룬û���򷵻�NULL
 */
CJPWordInfo* CJPWordsVector::getCurrentJPWord( bool Forgoten /*= true*/)
{
	//ǿ���±�Ϸ�
	if( current>=words.size() || current<0 )
	{
		current = words.size()-1 ;
	}
	//û�е��ʣ����ؿ�
	if( words.size()==0 )
	{
		return NULL;
	}
	//���ص�ǰ����
	return &words[current];
}


/**
 * ���������ַ���Ϊ��������
 * @param str ��Ҫ�������ַ���
 * @return ���ؽ����õ���������
 */

vector<int> CJPWordsVector::makeTone(wstring str)
{
	//Ŀ����������
	vector<int> tone;
	//�ָ��ΪӢ�Ķ���
	wchar_t flag = ',';
	//��ʼλ��
	size_t start = 0;
	//����λ��
	size_t end = 0 ;
	for( ; end<str.size(); end++ )
	{
		//��ǰ����λ�ָ���
		if(str.at( end )== flag)
		{
			//��ȡ�Ӵ�
			wstring numStr = str.substr(start,end-start);
			//ת�������ּ�������
			int num = _wtoi(numStr.c_str());
			tone.push_back(num);
			//�����ָ��
			end++;
			//�ƶ���ʼλ��
			start = end;
		}
	}
	//��ȡ�Ӵ�
	wstring numStr = str.substr(start,end-start);
	//ת�������ּ�������
	int num = _wtoi(numStr.c_str());
	tone.push_back(num);
	return tone;
}

size_t CJPWordsVector::getWordsCount()
{
	return words.size();
}