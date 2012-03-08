// JPWordInfo.cpp : 实现文件
//

#include "stdafx.h"
#include "JPWord.h"
#include "JPWordInfo.h"


// CJPWordInfo



CJPWordInfo::CJPWordInfo()
{

}

CJPWordInfo::CJPWordInfo(const CJPWordInfo &wordInfo)
{
	chinese = wordInfo.chinese;
	cixing = wordInfo.cixing;
	forgot = wordInfo.forgot;
	introduction = wordInfo.introduction;
	jpword = wordInfo.jpword;
	tone = wordInfo.tone;
}


CJPWordInfo::~CJPWordInfo()
{
}

void CJPWordInfo::operator =(const CJPWordInfo &wordInfo)
{
	chinese = wordInfo.chinese;
	cixing = wordInfo.cixing;
	forgot = wordInfo.forgot;
	introduction = wordInfo.introduction;
	jpword = wordInfo.jpword;
	tone = wordInfo.tone;
}

void CJPWordInfo::clear()
{
	jpword.clear();
	chinese.clear();
	introduction.clear();
	cixing.clear();
	tone.clear();
	forgot=0;
}
//
bool CJPWordInfo::isCorrect()
{
	if(jpword.empty())
	{
		return false;
	}
	return true;
}





