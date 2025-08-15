#pragma once
#include "allFunc.h"
#include <map>
using namespace std;
class AllAuthorWriter
{
public:
	map<string, int> personToWorks;          //most100中完成录入
	AllAuthorWriter() {};                      
	~AllAuthorWriter() {};
	void AuthorWriter();                        //把作者的名字都写入的函数
	void Author100();                     //统计前100的作者进行输出
};
