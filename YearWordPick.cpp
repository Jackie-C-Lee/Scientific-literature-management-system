#include "YearWordPick.h"
using namespace std;

void YearHotWord::YearAna_Writer()
{
	string tempstr;
	int counter = 0;
	ifstream infile;
	infile.open(save_url + "dblp.xml", ios::in | ios::binary);                    
	getline(infile, tempstr);
	//while (tempstr.find("</dblp>") == string::npos) 
	int testn = 300000;
	while (testn>=0)
	{
		if (tempstr.find("<title>") != string::npos)                                       //��ȡ����
		{
			size_t startPos = tempstr.find_first_of(">");
			size_t endPos = tempstr.find_last_of("<");
			yearer->yearText = tempstr.substr(startPos + 1, endPos - (startPos + 1));
		}
		if (tempstr.find("<year>") != string::npos)                                         //�ҵ����
		{
			size_t startPos = tempstr.find_first_of(">");
			size_t endPos = tempstr.find_last_of("<");
			yearer->yearTime = tempstr.substr(startPos + 1, endPos - (startPos + 1));
			ofstream outfile(save_url + "year\\" + yearer->yearTime + ".txt", ios::app);    //д��ÿһ������б���
			outfile << yearer->yearText << endl;
			counter++;//������
			if (counter % 100000 == 0)cout << "YearAna_Writer::counter:" << counter << endl;
			outfile.close();
		}
		getline(infile, tempstr);
		testn--;//TEST
	}
	cout << "Continue to next step!" << endl;
}

//int main()
//{
//	YearHotWord z;
//	z.YearAna_Writer();
//}
