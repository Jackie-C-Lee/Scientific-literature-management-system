#include "coPersonGet.h"
using namespace std;
void CoauthorWriter::writeCoAuthor()
{
	CoauthorWriter* coawriter = new CoauthorWriter();
	string tempstr;
	int counter = 0;
	long long divcounter = 0;                                                                       //��¼ƫ����������ӳ�䣬��߲��ҵ�Ч��
	ifstream infile;
	infile.open(save_url + "dblp.xml", ios::in | ios::binary);                                      //�ļ���ȡ
	getline(infile, tempstr);
	int N = 0;
	//while (tempstr.find("</dblp>") == string::npos)                                                 //ֱ������Ϊ֮
	while(N<300000)
	{
		if (checkStartElem(tempstr))                                                             //�ļ�articleͷ��д��ƫ����
		{
			bool judge = false;
			vector<string> author_name;                                                             //�ֲ�name����
			coawriter->coauthor->coauthor_offset = divcounter;
			getline(infile, tempstr);
			while (tempstr.find("<author>") != string::npos)                                        //�ҵ�author��д��coauthors
			{
				size_t startPos = tempstr.find_first_of(">");
				size_t endPos = tempstr.find_last_of("<");
				author_name.push_back(tempstr.substr(startPos + 1, endPos - (startPos + 1)));
				getline(infile, tempstr);
			}
			while (tempstr.find("<title>") != string::npos)                                          //�ҵ���ǩ��<title>��Ȼ���¼essay������
			{
				size_t startPos = tempstr.find_first_of(">");
				size_t endPos = tempstr.find_last_of("<");
				coawriter->coauthor->coauthor_essay = tempstr.substr(startPos + 1, endPos - (startPos + 1));
				getline(infile, tempstr);
			}
			vector<string>::iterator iter;
			for (iter = author_name.begin(); iter != author_name.end(); iter++)
			{
				string shortName = (*iter).substr(0, 3);                                             //��ȡ����������Ϊ�ļ�����
				transfFileName(shortName);
				ofstream outfile(save_url + "coauthor\\" + shortName + ".txt", ios::app);
				outfile << "<coauthor host=\"" + (*iter) + "\" " + "Essayname=\"" + coawriter->coauthor->coauthor_essay + "\" " +
					"urlpt=\"" + longToStr(coawriter->coauthor->coauthor_offset) + "\">" << endl;
				counter++;//������
				if (counter % 1000 == 0)cout << "Coauthor::counter:" << counter << endl;
				outfile.close();
			}
		}
		divcounter = infile.tellg();
		getline(infile, tempstr);
		N++;
	}
}
