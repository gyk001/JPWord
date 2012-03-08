#pragma once
#include <string>
#include <vector>
#include "JPWordInfo.h"
using namespace std;
// CJPWordsVector ����Ŀ��

class CJPWordsVector : public CObject
{
public:
	CJPWordsVector();
	virtual ~CJPWordsVector();
private:
	//���е���
	vector <CJPWordInfo> words;
	//��ǰ���ʵĵ����±�
	size_t current;
public:
	/** 
	 * ���ļ����ص�����Ϣ
	 * @param filename �ļ���
	 * @param clearOldWords �Ƿ�������еĵ�����Ϣ��Ĭ��Ϊ��
	 * @return ���سɹ������棬ʧ�ܷ��ؼ�
	 */
	bool LoadFile(wstring fileName , bool clearOldWords=true);
	/**
	 * ��ȡ��һ������
	 * @param Forgoten ֻ��û�м�ס�ĵ�����ѡ��Ĭ��Ϊture
	 */
	CJPWordInfo* getNextJPWord( bool Forgoten = true );
	/**
	 * ��ȡ��һ������
	 * @param Forgoten ֻ��û�м�ס�ĵ�����ѡ��Ĭ��Ϊture
	 */	
	CJPWordInfo* getPrevJPWord( bool Forgoten = true );
	/**
	 * ��ȡ��һ������
	 * @param Forgoten ֻ��û�м�ס�ĵ�����ѡ��Ĭ��Ϊture
	 */
	CJPWordInfo* getCurrentJPWord( bool Forgoten = true);
	//��������
	vector<int> makeTone(wstring str);
	//��������
	size_t getWordsCount();
};


