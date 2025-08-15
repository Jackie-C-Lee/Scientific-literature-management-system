#pragma once
#include "allFunc.h"
using namespace std;
#define MAX_CATEGORY 1000000                                //���Ƶ��������������
#define MAX_LEN 66                                      //���Ƶ�����󳤶�
#define MAX_OUT_SCREEN 100                              //��Ļ��������������ֵ
#define ALPHA 26

void main_WriterTrieTree();
static string temp_year;                             //
typedef struct Word
{
	int count;
	char* word_value;
	int dictionary_code;        //�ֵ������ֵ�����(��������ʱ������)
}*WordNodePtr;

typedef struct branchTrie
{
	char current_char;
	int flag[ALPHA];                                    //��Ӧ�ý���26�����ӵ����״̬
	int flag_word_exist;
	branchTrie* links[ALPHA];
	WordNodePtr current_words;                            //���������*WordNodePtr�ڴ�
	set<string>beInArticle;
}*Twigs;

class TrieTree {
public:
	Twigs myTrie;
	int dictionary_number_for_search;
	WordNodePtr word_list[MAX_CATEGORY];

	void giveValue(int,WordNodePtr);
	int Insert(char*,string=0);
	void StoreWord();
	void Quick_Sort(int, int);
	void DFS_findWord(Twigs restrict);
	void Outcome_Print();
};
struct YearData
{
	string yearTime;
	string yearText;
};

class YearHotWord
{
public:
	YearData* yearer = new YearData();
	YearHotWord() {};
	~YearHotWord() {};
	void YearAna_Writer();
};