#include "coPersonRead.h"
using namespace std;

bool checkTailElem(string tempstr)                                                //�ж���ֹ����
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
	set<string>::iterator MJiter = coauthorSet.begin();                          //�����������ڱ���set����
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
		finderDblp.seekg(locatePosition, ios::beg);    //����ƫ������λ������������λ��
		getline(finderDblp, tempstr);//1���Ե���һ��(��Ϊ�еļ�¼�쳣����β��־����ʼ��־��ͬһ��)
		getline(finderDblp, tempstr);//2��Ȼ��ʹӵڶ��п�ʼ�ж��Լ�����
		while (!checkTailElem(tempstr))
		{
			if (tempstr.find("<author>") != string::npos)                       //��author���ִ��뵽set��ȥ
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
	while (!infile.eof())                                                          //����������ߵ�������������
	{
		if (tempstr.find(search_name) != string::npos)
		{
			size_t startPos = tempstr.find_last_of("=") + 1;             //Ѱ��ƫ��������ʼλ�ã�������=����λ�ú�һ��
			size_t endPos = tempstr.find_last_of("\"");                  //��ֹλ��
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

void CoAuthorInfo::showCoWriter(string search_name)                                                //������к������ߵ�����
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
			size_t startPos = tempstr.find_last_of("=") + 1;                                //urlpt="�У���ȡ=��λ�ú�+1������λ��
			size_t endPos = tempstr.find_last_of("\"");                                     //���ġ�λ��
			locatePosition = strToLong(tempstr.substr(startPos + 1, endPos - (startPos + 1)));
			setCoName();
		}
		getline(infile, tempstr);
	}
	infile.close();
	BrowseSet();
}

