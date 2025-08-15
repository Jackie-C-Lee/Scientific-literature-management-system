#pragma once
#include"allFunc.h"
using namespace std;
struct Publications
{
	string pubName;
	long long pubUrlpt;
};

class PubWriter
{
public:
	Publications* publication = new Publications();
	PubWriter() {};
	~PubWriter() {};
	void writePub();
};