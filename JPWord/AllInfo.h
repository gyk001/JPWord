#pragma once
#include "JPWordsVector.h"
#include "JPWordInfoEx.h"
// CAllInfo ����Ŀ��

class CAllInfo : public CObject
{
public:
	CAllInfo();
	virtual ~CAllInfo();
private:
	//���е�����Ϣ
	CJPWordsVector wordVector;
	//��ǰ������Ϣ
	CJPWordInfoEx currentWord;
	//

};


