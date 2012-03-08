#pragma once
#include "JPWordsVector.h"
#include "JPWordInfoEx.h"
// CAllInfo 命令目标

class CAllInfo : public CObject
{
public:
	CAllInfo();
	virtual ~CAllInfo();
private:
	//所有单词信息
	CJPWordsVector wordVector;
	//当前单词信息
	CJPWordInfoEx currentWord;
	//

};


