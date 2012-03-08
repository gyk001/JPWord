#pragma once
#include <string>
#include <vector>
#include "JPWordInfo.h"
using namespace std;
// CJPWordsVector 命令目标

class CJPWordsVector : public CObject
{
public:
	CJPWordsVector();
	virtual ~CJPWordsVector();
private:
	//所有单词
	vector <CJPWordInfo> words;
	//当前访问的单词下标
	size_t current;
public:
	/** 
	 * 从文件加载单词信息
	 * @param filename 文件名
	 * @param clearOldWords 是否清除现有的单词信息，默认为是
	 * @return 加载成功返回真，失败返回假
	 */
	bool LoadFile(wstring fileName , bool clearOldWords=true);
	/**
	 * 获取下一个单词
	 * @param Forgoten 只从没有记住的单词中选择，默认为ture
	 */
	CJPWordInfo* getNextJPWord( bool Forgoten = true );
	/**
	 * 获取上一个单词
	 * @param Forgoten 只从没有记住的单词中选择，默认为ture
	 */	
	CJPWordInfo* getPrevJPWord( bool Forgoten = true );
	/**
	 * 获取上一个单词
	 * @param Forgoten 只从没有记住的单词中选择，默认为ture
	 */
	CJPWordInfo* getCurrentJPWord( bool Forgoten = true);
	//解析声调
	vector<int> makeTone(wstring str);
	//单词数量
	size_t getWordsCount();
};


