#pragma once
#include "allFunc.h"
#include <map>
using namespace std;
class AllAuthorWriter
{
public:
	map<string, int> personToWorks;          //most100�����¼��
	AllAuthorWriter() {};                      
	~AllAuthorWriter() {};
	void AuthorWriter();                        //�����ߵ����ֶ�д��ĺ���
	void Author100();                     //ͳ��ǰ100�����߽������
};
