// JPWordInfoEx.cpp : 实现文件
//

#include "stdafx.h"
#include "JPWord.h"
#include "JPWordInfoEx.h"
#include "iostream"

// CJPWordInfoEx

CJPWordInfoEx::CJPWordInfoEx()
{
}

CJPWordInfoEx::~CJPWordInfoEx()
{
}


// CJPWordInfoEx 成员函数
void CJPWordInfoEx::init()
{
	wordCount = 0;
	jpWords.clear();
	jpZhuYin.clear();
	tone.clear();
	distinguishPos[0].clear();
	distinguishPos[1].clear();
}

int CJPWordInfoEx::loadWord(wstring jp)
{
	init();
	//当前状态集合{接受单词，接受注音}
	enum{ls_word,ls_zhuYin};
	//初始状态为接受单词
	int state = ls_word;
	//单词分词下标
	int fenciWord = 0;
	//注音分词下标
	int fenciZhuYin = 0;

	//日语注音左右括号
	wchar_t lp = 12300L;//'「'
	wchar_t rp = 12301L;//'」'

	//将分词位置第一位置0，方便运算
	distinguishPos[jp_dp_word].push_back( 0 );
	distinguishPos[jp_dp_zhuYin].push_back( 0 );

	//循环读入字符并处理
	for(size_t jpIndex=0 ; jpIndex<jp.size();jpIndex++ )
	{

		//取得当前字符
		wchar_t ch = jp[jpIndex];
		//cout<<ch<<" ";
		//当前为接受单词状态
		if( state == ls_word )
		{
			//当前字符为右括号，括号不匹配
			if( ch==rp )
			{
				//返回错误
				return 1;
			}
			//当前字符为左括号
			else if( ch==lp )
			{
				//切换状态至接受注音
				state = ls_zhuYin;
				//记录单词分词长度
				distinguishPos[jp_dp_word].push_back( fenciWord );
				//无效--将分词长度置零
				//fenciWord = 0;
				//单词数加1
				wordCount++;
			}		
			else
			{
				//将新字符置入单词数组
				jpWords.append( 1,ch );
				//将单词分词下标加1
				fenciWord ++;
			}
		}
		//当前为接受注音状态
		else if( state == ls_zhuYin )
		{
			//当前字符为左括号，括号不匹配
			if( ch==lp )
			{
				//返回错误
				return 1;
			}
			//当前字符为右括号
			else if( ch==rp )
			{
				//切换状态至接受单词
				state = ls_word ;
				//记录注音分词下标
				distinguishPos[jp_dp_zhuYin].push_back( fenciZhuYin );
				//无效--将注音分词长度置零
				//fenciZhuYin = 0;
			}		
			else
			{
				//将新注音字符置入注音数组
				jpZhuYin.append( 1 , ch );
				//将注音分词下标加1
				fenciZhuYin++;
			}
		}

	}
	return 0;	
}

//加载声调信息
int CJPWordInfoEx::loadTone(vector<int> newTone)
{
	tone.clear();
	/*vector<int>::iterator iter = newTone.begin();
	while ( iter != newTone.end() )
	{
		tone.push_back(*iter);
		iter ++;
	}
	*/
	//jpword.tone.assign( wordInfo.tone.begin(),wordInfo.tone.end());
	//jpword.tone = wordInfo.tone;

	tone = newTone;
	return 0;
}

//返回第index个单词的单词内容
wstring CJPWordInfoEx::getWordAt(int index)
{
	wstring word;
	if(index>wordCount)
		return word;

	word = jpWords.substr(distinguishPos[jp_dp_word][index],distinguishPos[jp_dp_word][index+1]-distinguishPos[jp_dp_word][index]);
	return word;
}

//返回第index个单词的单词长度
int CJPWordInfoEx::getWordLengthAt(int index)
{
	if(index>wordCount)
		return -1;
	return distinguishPos[jp_dp_word][index],distinguishPos[jp_dp_word][index+1]-distinguishPos[jp_dp_word][index] ;
}

//返回第index个单词的注音内容
wstring CJPWordInfoEx::getZhuYinAt(int index)
{
	wstring zhuYin;
	if(index>wordCount)
		return zhuYin;
	zhuYin = jpZhuYin.substr( distinguishPos[jp_dp_zhuYin][index], distinguishPos[jp_dp_zhuYin][index+1]-distinguishPos[jp_dp_zhuYin][index]);
	return zhuYin;
}

//返回第index个单词的注音长度
int CJPWordInfoEx::getZhuYinLengthAt(int index)
{
	if(index>wordCount)
		return -1;
	return distinguishPos[jp_dp_zhuYin][index], distinguishPos[jp_dp_zhuYin][index+1]-distinguishPos[jp_dp_zhuYin][index];
}

/*
int CJPWordInfoEx::load(CJPWordInfo wordInfo)
{
	//重置
	init();
	//分析单词
	load(wordInfo.jpword);
	//分析声调	
	//tone = wordInfo.
	//词性
	cixing = wordInfo.cixing;
	//中文翻译
	chinese = wordInfo.chinese;
	//解释说明
	introduction = wordInfo.introduction;
	//忘记次数
	forgot = wordInfo.forgot;
	return 0;
}*/