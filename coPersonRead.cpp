#include "coPersonRead.h"
using namespace std;

bool checkTailElem(string tempstr)                                                //判定截止条件
{
	if ((tempstr.find("</article>") != string::npos) || (tempstr.find("</inproceedings>") != string::npos) ||
		(tempstr.find("</proceedings>") != string::npos) || (tempstr.find("</book>") != string::npos) ||
		(tempstr.find("</incollection>") != string::npos) || (tempstr.find("</phdthesis>") != string::npos) ||
		(tempstr.find("</mastersthesis>") != string::npos) || (tempstr.find("</www>") != string::npos))
		return true;
	else return false;
};

void CoAuthorInfo::BrowseSet()
{
	set<string>::iterator MJiter = coauthorSet.begin();                          //迭代器，用于遍历set容器
	while (MJiter != coauthorSet.end())
	{
		cout << *MJiter << endl;
		++MJiter;
	}
}

void CoAuthorInfo::setCoName()
{
	if (locatePosition != 0)
	{
		ifstream finderDblp(save_url + "dblp.xml", ios::in | ios::binary);
		finderDblp.seekg(locatePosition, ios::beg);    //根据偏移量定位到文献所处的位置
		getline(finderDblp, tempstr);//1。吃掉第一行(因为有的记录异常，结尾标志与起始标志在同一行)
		getline(finderDblp, tempstr);//2。然后就从第二行开始判定以及操作
		while (!checkTailElem(tempstr))
		{
			if (tempstr.find("<author>") != string::npos)                       //将author名字存入到set中去
			{
				size_t startPos = tempstr.find_first_of(">");
				size_t endPos = tempstr.find_last_of("<");
				coauthorSet.insert(tempstr.substr(startPos + 1, endPos - (startPos + 1)));
			}
			getline(finderDblp, tempstr);
		}
	}
}

void CoAuthorInfo::personalWorks(string search_name)                                
{
	locatePosition = 0;
	CoAuthorInfo* coareader = new CoAuthorInfo();
	string tmp_nickname = search_name.substr(0, 3);
	transfFileName(tmp_nickname);
	ifstream infile(save_url + "coauthor\\" + tmp_nickname + ".txt", ios::in);
	getline(infile, tempstr);
	while (!infile.eof())                                                          //是输出该作者的所有论文名称
	{
		if (tempstr.find(search_name) != string::npos)
		{
			size_t startPos = tempstr.find_last_of("=") + 1;             //寻找偏移量的起始位置，即：“=”的位置后一个
			size_t endPos = tempstr.find_last_of("\"");                  //截止位置
			locatePosition = strToLong(tempstr.substr(startPos + 1, endPos - (startPos + 1)));

			size_t pub_startPos = tempstr.find("Essayname=") + 10;
			size_t pub_endPos = tempstr.find("\" urlpt");
			string pub_name = tempstr.substr(pub_startPos + 1, pub_endPos - (pub_startPos + 1));
			cout << pub_name << endl;
		}
		getline(infile, tempstr);
	}
	infile.close();
}

void CoAuthorInfo::showCoWriter(string search_name)                                                //输出所有合作作者的姓名
{
	locatePosition = 0;
	CoAuthorInfo* coareader = new CoAuthorInfo();
	string tmp_nickname = search_name.substr(0, 3);
	transfFileName(tmp_nickname);
	ifstream infile(save_url + "coauthor\\" + tmp_nickname + ".txt", ios::in);
	getline(infile, tempstr);
	while (!infile.eof()) 
	{
		if (tempstr.find(search_name) != string::npos)
		{
			size_t startPos = tempstr.find_last_of("=") + 1;                                //urlpt="中，获取=的位置后+1，即“位置
			size_t endPos = tempstr.find_last_of("\"");                                     //最后的”位置
			locatePosition = strToLong(tempstr.substr(startPos + 1, endPos - (startPos + 1)));
			setCoName();
		}
		getline(infile, tempstr);
	}
	infile.close();
	BrowseSet();
}

