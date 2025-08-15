#pragma once
#include "allFunc.h"
using namespace std;
#define MAX_CATEGORY 1000000                                //估计单词种类最多数量
#define MAX_LEN 66                                      //限制单词最大长度
#define MAX_OUT_SCREEN 100                              //屏幕输出单词数量最大值
#define ALPHA 26

void main_WriterTrieTree();
static string temp_year;                             //
typedef struct Word
{
	int count;
	char* word_value;
	int dictionary_code;        //字典树中字典序编号(最后遍历的时候输入)
}*WordNodePtr;

typedef struct branchTrie
{
	char current_char;
	int flag[ALPHA];                                    //对应该结点的26个链接点存在状态
	int flag_word_exist;
	branchTrie* links[ALPHA];
	WordNodePtr current_words;                            //若有则分配*WordNodePtr内存
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