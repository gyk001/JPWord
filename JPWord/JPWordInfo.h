#pragma once

// CJPWordInfo ����Ŀ��
#include <string>
#include <vector>
using namespace std;

class CJPWordInfo : public CObject
{
public:
	CJPWordInfo();
	CJPWordInfo(const CJPWordInfo &wordInfo);
	virtual ~CJPWordInfo();
	//���ʺ�ע����Ϣ
	wstring jpword;
	//��������(����½��ĺͲ��½���)������������
	enum {jp_tone_no_down,jp_tone_down};
	//��������������һ�顾���ͣ�������ʼλ�ã���������λ�á�
	vector<int> tone;
	//������˼
	wstring chinese;
	//����
	wstring cixing;
	//˵����Ϣ
	wstring introduction;
	//���ǵĴ�����0�����ס��
	int forgot;
public:
	void operator=(const CJPWordInfo &wordInfo);
	void clear();
	bool isCorrect();
};


