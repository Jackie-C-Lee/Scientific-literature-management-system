#include "AllAuthor_get.h"
#include <algorithm>

bool moreThan(const pair<string, int>& m1,const pair<string, int>& m2) {return m1.second > m2.second;}        //�Զ��彵������

void AllAuthorWriter::Author100()
{
	string tempdata;                                                                                           //��ʱ����
	int counter = 0;
	ifstream infile;
	map<string, int>::iterator it = personToWorks.end();
	for (int fileNumber = 1; fileNumber <= 124; fileNumber++)
	{
		infile.open(save_url + "allAuthor\\nameList" + intStr(fileNumber) + ".txt", ios::in | ios::binary);//�ļ���ȡ��ע�⺯���Ķ��壡
		while (!infile.eof())
		{
			getline(infile, tempdata);
			it = personToWorks.find(tempdata);
			if (it == personToWorks.end())                                                          //û�и�������Ϣ�����������Ϣ
				personToWorks.insert(make_pair(tempdata, 1));
			else (it->second)++;                                                                        //���и�������Ϣ��ֵ++
		}
		infile.close();
		cout << "nameList" << fileNumber << ".txt�������" << endl;
	}
	//д��vector,����
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
		outfile << workIter->first << endl;                                                            //д������
		cout << workIter->second << endl;
		outfile << workIter->second << endl;                                                         //д������
		workCounter++;
		if (workCounter > 100)break;                                                                  //����ǰ100
	} 
}

//int main()
//{
//	AllAuthorWriter a;
//	a.Author100();
//}