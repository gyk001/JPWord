#pragma once

// CJPWordInfo 命令目标
#include <string>
#include <vector>
using namespace std;

class CJPWordInfo : public CObject
{
public:
	CJPWordInfo();
	CJPWordInfo(const CJPWordInfo &wordInfo);
	virtual ~CJPWordInfo();
	//单词和注音信息
	wstring jpword;
	//音调类型(后边下降的和不下降的)，画音调线用
	enum {jp_tone_no_down,jp_tone_down};
	//音调，三个数字一组【类型，高音开始位置，高音结束位置】
	vector<int> tone;
	//汉语意思
	wstring chinese;
	//词性
	wstring cixing;
	//说明信息
	wstring introduction;
	//忘记的次数，0代表记住了
	int forgot;
public:
	void operator=(const CJPWordInfo &wordInfo);
	void clear();
	bool isCorrect();
};


