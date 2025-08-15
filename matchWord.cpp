#define _CRT_SECURE_NO_WARNINGS
#include <ctype.h>
#include <string>
#include <iostream>
#include<algorithm>
#include"matchWord.h"
#define MAX_LEN 66                                      //���Ƶ�����󳤶�
vector<set<string>>allSet;
vector<set<string>>zanCunSet;
void matchAlg::inserT(int N0, char* x1, string y1)
{
	superTree[N0].Insert(x1, y1);
}
set<string> matchAlg::mergeSets(const vector<set<string>>& sets)
{
	set<std::string> mergedSet;
	for (const auto& s : sets)
	{
		mergedSet.insert(s.begin(), s.end());
	}
	return mergedSet;
}
void matchAlg::addSet(TrieTree &tepTree, char* X)
{
	Twigs k0 = tepTree.myTrie;
	while (*(X) != '\0')
	{
		if (k0->flag[*X - 'a'])
		{
			k0 = k0->links[*X - 'a'];
			X++;
			if ((*X) == '\0')
			{
				if (k0->flag_word_exist)
				{
					zanCunSet.push_back(k0->beInArticle);
				}
				return;
			}
		}
		else return;
	}
}
void matchAlg::lookFor(int years,char* targetWord)
{
	for (int i = 0; i < years; i++)
	{
		if (superTree[i].myTrie == NULL)continue;
		addSet(superTree[i], targetWord);
	}
	allSet.push_back(mergeSets(zanCunSet));
	zanCunSet.clear();
}
set<string> matchAlg::intersTwo(const set<string>& set1, const set<string>& set2)
{
	set<string> result;
	set_intersection(set1.begin(), set1.end(), set2.begin(), set2.end(), inserter(result, result.begin()));
	return result;
}
set<string> matchAlg::intersMulti(const vector<set<string>>& bigSet)
{
	if (bigSet.empty()) 
		return std::set<std::string>();           // ���û�м��ϣ��򷵻ؿռ���

	set<string> bookList = bigSet[0];
	for (int i = 1; i < bigSet.size(); i++) 
		bookList = intersTwo(bookList, bigSet[i]);

	return bookList;
}
void matchAlg::printBook(const set<string>& setX)
{
	set<string>::iterator booker = setX.begin();                          //�����������ڱ���set����
	while (booker != setX.end())
	{
		cout << *booker << endl;
		++booker;
	}
}
void mainTest(matchAlg& a)
{
	for (int z = 2010; z <= 2024; z++)
	{
		//int z = 2007;
		stringstream transformer;
		transformer << z;
		transformer >> temp_year;
		string raw_year = save_url + "year\\" + temp_year + ".txt";
		ifstream in(raw_year.c_str());                // ���ļ���
		string lineTitle;                             // ���ڴ洢ÿһ�е�����
		char* wordTemp = new char[MAX_LEN];            // �洢���ʵ���ʱ����
		if (!in.is_open())
		{                                              // ����ļ��Ƿ�ɹ���
			cerr << z << "���" << "Error: Unable to open file!" << endl;
		}
		else
		{
			TrieTree* mm = new TrieTree();
			mm->dictionary_number_for_search = 1;
			mm->myTrie = new branchTrie;
			memset(mm->myTrie->flag, 0, sizeof(mm->myTrie->flag));
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
							if (mm->Insert(testR, lineTitle))	wordTemp = new char[MAX_LEN];
							index = 0;   // ��������
						}
					}
				}
				// ����ÿһ�е����һ�����ʣ�������ڣ�
				if (index > 0)
				{
					wordTemp[index] = '\0'; // ����ַ���������
					char* testR = wordTemp;
					if (mm->Insert(testR, lineTitle))	wordTemp = new char[MAX_LEN];
				}
			}
			in.close(); // �ر��ļ���
			delete[]wordTemp;
			a.superTree.push_back(*mm);
			delete mm;
		}
	}
	cout << "����׼������" << endl;
}
void matchSearch(matchAlg&a)
{
	int vSize = 0;
	vSize = a.superTree.size();
	int caozuo = 0;
	cout << "�����ؼ��ʣ�";
	cin >> caozuo;
	while (caozuo > 0)
	{
		char* oo = new char[MAX_LEN];
		cout << "���������֤��";
		cin >> oo;
		cout << '\n' << oo << "�������" << endl;
		a.lookFor(vSize, oo);
		caozuo--;
		delete[]oo;
	}
	a.printBook((a.intersMulti(allSet)));
	for (int i = 0; i < vSize; i++)
	{
		delete a.superTree[i].myTrie;
	}
	a.superTree.clear();
}
//
//int main()
//{
//	matchAlg b;
//	mainTest(b);
//	matchSearch(b);
//	return 0;
//}