#pragma once

#include "JPWordInfo.h"
#include <string>
#include <vector>
using namespace std;

// CJPWordInfoEx 命令目标

class CJPWordInfoEx : public CObject
{
public:
	CJPWordInfoEx();
	virtual ~CJPWordInfoEx();
public:
	
	//日语单词（有汉字的写汉字）
	wstring jpWords;
	//日语单词中的汉字或英文等的注音
	wstring jpZhuYin;
	//分词个数
	int wordCount;
	//每个分词和分词注音的位置
	vector<int> distinguishPos[2];
	//distringuishPoz的下标，word是日语单词分词，zhuYin是注音分词
	enum {jp_dp_word,jp_dp_zhuYin};
	//音调类型(后边下降的和不下降的)，画音调线用
	enum {jp_tone_no_down,jp_tone_down};
	//音调，三个数字一组【类型，高音开始位置，高音结束位置】
	vector<int> tone;
	/*
	//汉语意思
	wstring chinese;
	//词性
	wstring cixing;
	//说明信息
	wstring introduction;
	//忘记的次数，0代表记住了
	int forgot;
	*/
private:
	//初始化
	void init();
public:
	//将一个字符串分解为日语单词和注音，并统计分词个数
	int loadWord(wstring jp);
	//加载一个音调信息
	int loadTone(vector<int> newTone);

	//加载一个日语单词信息
	//int load(CJPWordInfo wordInfo);
	
	//返回第index个单词的单词内容
	wstring getWordAt(int index);
	//返回第index个单词的单词长度
	int getWordLengthAt(int index);
	//返回第index个单词的注音内容
	wstring getZhuYinAt(int index);
	//返回第index个单词的注音长度
	int getZhuYinLengthAt(int index);
};


