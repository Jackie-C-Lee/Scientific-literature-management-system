#pragma once
#include "allFunc.h"
using namespace std;
class CoAuthorInfo
{
public:
	set<string> coauthorSet;
	string tempstr;
	long long locatePosition;
	CoAuthorInfo() {};
	~CoAuthorInfo() {};
	void BrowseSet();
	void setCoName();
	void personalWorks(string search_name);
	void showCoWriter(string search_name);
};
