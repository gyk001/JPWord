// JPWordInfoEx.cpp : ʵ���ļ�
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


// CJPWordInfoEx ��Ա����
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
	//��ǰ״̬����{���ܵ��ʣ�����ע��}
	enum{ls_word,ls_zhuYin};
	//��ʼ״̬Ϊ���ܵ���
	int state = ls_word;
	//���ʷִ��±�
	int fenciWord = 0;
	//ע���ִ��±�
	int fenciZhuYin = 0;

	//����ע����������
	wchar_t lp = 12300L;//'��'
	wchar_t rp = 12301L;//'��'

	//���ִ�λ�õ�һλ��0����������
	distinguishPos[jp_dp_word].push_back( 0 );
	distinguishPos[jp_dp_zhuYin].push_back( 0 );

	//ѭ�������ַ�������
	for(size_t jpIndex=0 ; jpIndex<jp.size();jpIndex++ )
	{

		//ȡ�õ�ǰ�ַ�
		wchar_t ch = jp[jpIndex];
		//cout<<ch<<" ";
		//��ǰΪ���ܵ���״̬
		if( state == ls_word )
		{
			//��ǰ�ַ�Ϊ�����ţ����Ų�ƥ��
			if( ch==rp )
			{
				//���ش���
				return 1;
			}
			//��ǰ�ַ�Ϊ������
			else if( ch==lp )
			{
				//�л�״̬������ע��
				state = ls_zhuYin;
				//��¼���ʷִʳ���
				distinguishPos[jp_dp_word].push_back( fenciWord );
				//��Ч--���ִʳ�������
				//fenciWord = 0;
				//��������1
				wordCount++;
			}		
			else
			{
				//�����ַ����뵥������
				jpWords.append( 1,ch );
				//�����ʷִ��±��1
				fenciWord ++;
			}
		}
		//��ǰΪ����ע��״̬
		else if( state == ls_zhuYin )
		{
			//��ǰ�ַ�Ϊ�����ţ����Ų�ƥ��
			if( ch==lp )
			{
				//���ش���
				return 1;
			}
			//��ǰ�ַ�Ϊ������
			else if( ch==rp )
			{
				//�л�״̬�����ܵ���
				state = ls_word ;
				//��¼ע���ִ��±�
				distinguishPos[jp_dp_zhuYin].push_back( fenciZhuYin );
				//��Ч--��ע���ִʳ�������
				//fenciZhuYin = 0;
			}		
			else
			{
				//����ע���ַ�����ע������
				jpZhuYin.append( 1 , ch );
				//��ע���ִ��±��1
				fenciZhuYin++;
			}
		}

	}
	return 0;	
}

//����������Ϣ
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

//���ص�index�����ʵĵ�������
wstring CJPWordInfoEx::getWordAt(int index)
{
	wstring word;
	if(index>wordCount)
		return word;

	word = jpWords.substr(distinguishPos[jp_dp_word][index],distinguishPos[jp_dp_word][index+1]-distinguishPos[jp_dp_word][index]);
	return word;
}

//���ص�index�����ʵĵ��ʳ���
int CJPWordInfoEx::getWordLengthAt(int index)
{
	if(index>wordCount)
		return -1;
	return distinguishPos[jp_dp_word][index],distinguishPos[jp_dp_word][index+1]-distinguishPos[jp_dp_word][index] ;
}

//���ص�index�����ʵ�ע������
wstring CJPWordInfoEx::getZhuYinAt(int index)
{
	wstring zhuYin;
	if(index>wordCount)
		return zhuYin;
	zhuYin = jpZhuYin.substr( distinguishPos[jp_dp_zhuYin][index], distinguishPos[jp_dp_zhuYin][index+1]-distinguishPos[jp_dp_zhuYin][index]);
	return zhuYin;
}

//���ص�index�����ʵ�ע������
int CJPWordInfoEx::getZhuYinLengthAt(int index)
{
	if(index>wordCount)
		return -1;
	return distinguishPos[jp_dp_zhuYin][index], distinguishPos[jp_dp_zhuYin][index+1]-distinguishPos[jp_dp_zhuYin][index];
}

/*
int CJPWordInfoEx::load(CJPWordInfo wordInfo)
{
	//����
	init();
	//��������
	load(wordInfo.jpword);
	//��������	
	//tone = wordInfo.
	//����
	cixing = wordInfo.cixing;
	//���ķ���
	chinese = wordInfo.chinese;
	//����˵��
	introduction = wordInfo.introduction;
	//���Ǵ���
	forgot = wordInfo.forgot;
	return 0;
}*/