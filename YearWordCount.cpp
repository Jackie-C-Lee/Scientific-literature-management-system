
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string>
#include <iostream>
#include <sstream>
#include "YearWordPick.h"
using namespace std;
static int biaoji = 0;
static int dakai = 1;

bool checkUselessWord(string& tmp)
{                                     //�����������ô�
	string strunim[] = { "a", "b","c","d","e","f","g","h","i","j","k","l","m","n","o","p0","q","r","s",
		"t","u","v","w","x","y","z","an", "are", "all", "any", "been", "both", "each", "either", "one", "two", "three",
		"four", "five", "six", "seven", "eigth", "nine", "ten", "none", "little", "few", "many", "much",
		"other", "another", "some", "no", "every", "nobody", "anybody", "somebody", "everybody", "when", "on",
		"at", "as", "first", "secend", "third", "fouth", "fifth", "sixth", "ninth", "above", "over", "below",
		"under", "beside", "behind", "of", "the", "after", "from", "since", "for", "which", "by", "next",
		"where", "how", "who", "there", "where", "is", "was", "were", "do", "did", "this", "that", "in",
		"last", "tomorrow", "yesterday", "before", "because", "against", "except", "beyond", "along", "among",
		"but", "so", "towards", "to", "it", "me", "i", "he", "she", "his", "they", "them", "her", "its", "and",
		"has", "have", "my", "would", "then", "too", "or", "our", "off", "we", "be", "into", "weel", "can",
		"having", "being", "even", "us", "these", "those", "if", "ours", "with", "using", "the", "based","-" ,"8","6"};
	for (int i = 0; i < 151; i++) {
		if (tmp == strunim[i]||tmp=="") return true;
	}
	return false;
}

int TrieTree::Insert(char* word_temp,string titleStr)                                                   //����һ������
{
	char* theWord = word_temp;
	Twigs p0 = myTrie;
	while (*(word_temp) != '\0')                                  //������ĸ
	{
		if (p0->flag[*word_temp - 'a'])
		{
			p0 = p0->links[*word_temp - 'a'];
			word_temp++;
		}
		else
		{
			do
			{
				p0->flag[*word_temp - 'a'] = 1;
				p0->links[*word_temp - 'a'] = new branchTrie;
				p0 = p0->links[*word_temp - 'a'];
				memset(p0->flag, 0, sizeof(p0->flag));                //�� p0->flag ���������Ԫ������Ϊ0��
				p0->current_char = *word_temp; 
				p0->flag_word_exist = 0;
				word_temp++;
			} while (*word_temp != '\0');
			p0->current_words = new Word;
			p0->current_words->word_value = theWord;
			
			p0->flag_word_exist = 1;
			p0->current_words->count = 1;

			p0->beInArticle.insert(titleStr);
			return 1;
		}
	}
	if (p0->flag_word_exist)
	{
		p0->current_words->count++;
		p0->beInArticle.insert(titleStr);
		return 0;
	}
	else
	{
		p0->flag_word_exist = 1;
		p0->current_words = new Word;
		p0->current_words->word_value = word_temp;
		p0->current_words->count = 1;
		p0->beInArticle.insert(titleStr);
		return 1;                       //����ɹ�
	}
	return 0;
}
void TrieTree::DFS_findWord(Twigs head)         //�򵥴��嵥�д��뵥��
{
	if (head->flag_word_exist)
	{
		head->current_words->dictionary_code = dictionary_number_for_search;
		word_list[dictionary_number_for_search++] = head->current_words;
	}
	for (int i = 0; i < ALPHA; i++)
		if (head->flag[i])
		{
			DFS_findWord(head->links[i]);
		}
}
void TrieTree::StoreWord()
{
	for (int i = 0; i < ALPHA; i++)
		if (myTrie->flag[i])                         //�൱���Ǵ�root��ʼ����
		{
			DFS_findWord(myTrie->links[i]);
		}
}
void TrieTree::giveValue(int n,WordNodePtr doObj)
{
	word_list[n]->count = doObj->count;
	word_list[n]->dictionary_code = doObj->dictionary_code;
	word_list[n]->word_value = doObj->word_value;
}
void TrieTree::Quick_Sort(int low, int high)
{
	if (low < high)
	{
		WordNodePtr base = new Word(*word_list[low]);
		int left = low, right = high;
		while (left < right)
		{
			while (left < high && (word_list[right]->count > base->count || ((word_list[right]->count == base->count) && (word_list[right]->dictionary_code < base->dictionary_code))))
			{
				right--;
			}
			giveValue(left, word_list[right]);
			while (left < right && (word_list[left]->count < base->count || ((word_list[left]->count == base->count) && (word_list[left]->dictionary_code > base->dictionary_code))))
			{
				left++;
			}
			giveValue(right, word_list[left]);
		}
		giveValue(left, base);
		delete base;
		Quick_Sort(low, left - 1);
		Quick_Sort(left + 1, high);
	}
}
void TrieTree::Outcome_Print()
{
	string out_year = save_url + "yearWordAnalysis\\" + temp_year + ".txt";
	FILE* out = fopen(out_year.c_str(), "w");
	int i, count = 0;
	int hunlimit = 0;
	if (out == nullptr)
	{
		cerr << "Error: Unable to open file!" << endl;
		return;
	}
	for (i = dictionary_number_for_search - 1; hunlimit<10; i--)
	{
		string s(word_list[i]->word_value);
		if (!checkUselessWord(s))
		{
			fprintf(out, "%s %d\n", word_list[i]->word_value, word_list[i]->count);
			hunlimit++;
		}
		delete word_list[i];
	}
	fclose(out);
}

void main_WriterTrieTree()
{
	for (int z = 2010; z <= 2017; z++)//1936
	{
		stringstream transformer;
			transformer << z;
			transformer >> temp_year;
			cout << temp_year << endl;
			TrieTree* tritree = new TrieTree();
			tritree->dictionary_number_for_search = 1;
			tritree->myTrie = new branchTrie;
			memset(tritree->myTrie->flag, 0, sizeof(tritree->myTrie->flag));
			string raw_year = save_url + "year\\" + temp_year + ".txt";
		
			ifstream in(raw_year.c_str());       // ���ļ���
			string lineTitle;                         // ���ڴ洢ÿһ�е�����
			char* wordTemp = new char[MAX_LEN]; // �洢���ʵ���ʱ����
			if (!in.is_open()) 
			{                                    // ����ļ��Ƿ�ɹ���
				cerr << "Error: Unable to open file!" << endl;
				return;
			}
			else
			{
				while (getline(in, lineTitle))
				{                                // ���ж�ȡ�ļ�����
					int index = 0;
					for (char ch : lineTitle)
					{                           // ����ÿ���ַ�
						if (isalpha(ch))
						{                       // �������ĸ
							wordTemp[index++] = tolower(ch); // ת��ΪСд��ĸ���洢
						}
						else
						{                      // ���������ĸ
							if (index > 0)
							{                  // ������ڵ���
								wordTemp[index] = '\0'; // ����ַ���������
								char* testR = wordTemp;
								if (tritree->Insert(testR, lineTitle))	wordTemp = new char[MAX_LEN];
								index = 0;     // ��������
							}
						}
					}
					                          // ����ÿһ�е����һ�����ʣ�������ڣ�
					if (index > 0)
					{
						wordTemp[index] = '\0'; // ����ַ���������
						char* testR = wordTemp;
						if (tritree->Insert(testR,lineTitle))	wordTemp = new char[MAX_LEN];
					}
				}
				in.close(); // �ر��ļ���
				tritree->StoreWord();
				tritree->Quick_Sort(1, tritree->dictionary_number_for_search - 1);
				tritree->Outcome_Print();
				delete tritree->myTrie;
			}
			delete[]wordTemp;
				delete tritree;
				cout << "over" << endl;
	}
	return;
}

//int main()
//{
//	main_WriterTrieTree();
//	return 0;
//}
