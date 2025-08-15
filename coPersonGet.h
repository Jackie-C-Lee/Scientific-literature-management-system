#pragma once
#include "allFunc.h"
using namespace std;
struct authorFriend
{
	string coauthor_essay;
	long long coauthor_offset;
};
class CoauthorWriter
{
public:
	authorFriend* coauthor = new authorFriend();
	CoauthorWriter() {};
	~CoauthorWriter() {};
	void writeCoAuthor();
};
