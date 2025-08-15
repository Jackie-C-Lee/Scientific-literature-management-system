#include "AllAuthor_get.h"
#include <algorithm>
using namespace std;

string intStr(int temp)                                                     //����->�ַ���
{
	stringstream Trans;                                                //tempд��
	Trans << temp;
	string nothing;
	Trans >> nothing;
	return nothing;
}

void AllAuthorWriter::AuthorWriter()                                        //д�����ߵ����� ||
{                                                                           //               \/
	string tempstr;
	int counter = 0;
	ifstream infile;
	infile.open(save_url + "dblp.xml", ios::in | ios::binary);                //�ļ���ȡ
	getline(infile, tempstr);
	string authorName;
	int namecounter = 1;
	while (tempstr.find("</dblp>") == string::npos)                            //��ֹ����
	{
		if (tempstr.find("<author>") != string::npos)                          //�ҵ���ǩ
		{
			size_t startPos = tempstr.find_first_of(">");
			size_t endPos = tempstr.find_last_of("<");
			authorName = tempstr.substr(startPos + 1, endPos - (startPos + 1));
			ofstream outfile(save_url + "allAuthor\\nameList" + intStr(namecounter) + ".txt", ios::app);
			outfile << authorName << endl;
			counter++;//������
			if (counter % 1000 == 0)cout << "Author_RBWriter()::counter:" << counter << endl;
			if (counter % 100000 == 0)namecounter++;
			outfile.close();
		}
		getline(infile, tempstr);
	}
	cout << "Already Done!!!" << endl;
}

//int main()
//{
//	AllAuthorWriter a;
//	a.AuthorWriter();
//}