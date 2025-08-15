#pragma once
#include "allFunc.h"
#include"YearWordPick.h"
using namespace std;
class matchAlg {
public:
	vector<TrieTree>superTree;

	matchAlg() {};
	~matchAlg() {};

	void inserT(int,char*,string);
	void lookFor(int,char*);
	void addSet(TrieTree&, char*);
	void printBook(const set<string>&);

	set<string> mergeSets(const vector<set<string>>& );
	set<string> intersTwo(const set<string>& , const set<string>& );
	set<string> intersMulti(const vector<set<string>>& );
};
void mainTest(matchAlg&);
void matchSearch(matchAlg&);