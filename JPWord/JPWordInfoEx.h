#pragma once

#include "JPWordInfo.h"
#include <string>
#include <vector>
using namespace std;

// CJPWordInfoEx ����Ŀ��

class CJPWordInfoEx : public CObject
{
public:
	CJPWordInfoEx();
	virtual ~CJPWordInfoEx();
public:
	
	//���ﵥ�ʣ��к��ֵ�д���֣�
	wstring jpWords;
	//���ﵥ���еĺ��ֻ�Ӣ�ĵȵ�ע��
	wstring jpZhuYin;
	//�ִʸ���
	int wordCount;
	//ÿ���ִʺͷִ�ע����λ��
	vector<int> distinguishPos[2];
	//distringuishPoz���±꣬word�����ﵥ�ʷִʣ�zhuYin��ע���ִ�
	enum {jp_dp_word,jp_dp_zhuYin};
	//��������(����½��ĺͲ��½���)������������
	enum {jp_tone_no_down,jp_tone_down};
	//��������������һ�顾���ͣ�������ʼλ�ã���������λ�á�
	vector<int> tone;
	/*
	//������˼
	wstring chinese;
	//����
	wstring cixing;
	//˵����Ϣ
	wstring introduction;
	//���ǵĴ�����0�����ס��
	int forgot;
	*/
private:
	//��ʼ��
	void init();
public:
	//��һ���ַ����ֽ�Ϊ���ﵥ�ʺ�ע������ͳ�Ʒִʸ���
	int loadWord(wstring jp);
	//����һ��������Ϣ
	int loadTone(vector<int> newTone);

	//����һ�����ﵥ����Ϣ
	//int load(CJPWordInfo wordInfo);
	
	//���ص�index�����ʵĵ�������
	wstring getWordAt(int index);
	//���ص�index�����ʵĵ��ʳ���
	int getWordLengthAt(int index);
	//���ص�index�����ʵ�ע������
	wstring getZhuYinAt(int index);
	//���ص�index�����ʵ�ע������
	int getZhuYinLengthAt(int index);
};


