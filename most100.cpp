#include "AllAuthor_get.h"
#include <algorithm>

bool moreThan(const pair<string, int>& m1,const pair<string, int>& m2) {return m1.second > m2.second;}        //自定义降序排序

void AllAuthorWriter::Author100()
{
	string tempdata;                                                                                           //临时数据
	int counter = 0;
	ifstream infile;
	map<string, int>::iterator it = personToWorks.end();
	for (int fileNumber = 1; fileNumber <= 124; fileNumber++)
	{
		infile.open(save_url + "allAuthor\\nameList" + intStr(fileNumber) + ".txt", ios::in | ios::binary);//文件读取，注意函数的定义！
		while (!infile.eof())
		{
			getline(infile, tempdata);
			it = personToWorks.find(tempdata);
			if (it == personToWorks.end())                                                          //没有该作者信息，添加作者信息
				personToWorks.insert(make_pair(tempdata, 1));
			else (it->second)++;                                                                        //已有该作者信息，值++
		}
		infile.close();
		cout << "nameList" << fileNumber << ".txt导入完毕" << endl;
	}
	//写入vector,排序
	vector<pair<string, int>> authorWorks;
	map<string, int>::iterator maper;
	for (maper = personToWorks.begin(); maper != personToWorks.end(); maper++)
	{
		authorWorks.push_back(make_pair(maper->first, maper->second));
	}
	vector<pair<string, int>>::iterator workIter;
	std::sort(authorWorks.begin(), authorWorks.end(), moreThan);
	int workCounter = 0;
	ofstream outfile(save_url + "allauthor_result.txt", ios::app);
	for (workIter = authorWorks.begin(); workIter != authorWorks.end(); workIter++)
	{
		cout << workIter->first << endl;
		outfile << workIter->first << endl;                                                            //写入名字
		cout << workIter->second << endl;
		outfile << workIter->second << endl;                                                         //写入数量
		workCounter++;
		if (workCounter > 100)break;                                                                  //限制前100
	} 
}

//int main()
//{
//	AllAuthorWriter a;
//	a.Author100();
//}