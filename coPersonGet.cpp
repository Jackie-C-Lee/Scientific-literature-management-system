#include "coPersonGet.h"
using namespace std;
void CoauthorWriter::writeCoAuthor()
{
	CoauthorWriter* coawriter = new CoauthorWriter();
	string tempstr;
	int counter = 0;
	long long divcounter = 0;                                                                       //记录偏移量，便于映射，提高查找的效率
	ifstream infile;
	infile.open(save_url + "dblp.xml", ios::in | ios::binary);                                      //文件读取
	getline(infile, tempstr);
	int N = 0;
	//while (tempstr.find("</dblp>") == string::npos)                                                 //直到读完为之
	while(N<300000)
	{
		if (checkStartElem(tempstr))                                                             //文件article头，写入偏移量
		{
			bool judge = false;
			vector<string> author_name;                                                             //局部name数组
			coawriter->coauthor->coauthor_offset = divcounter;
			getline(infile, tempstr);
			while (tempstr.find("<author>") != string::npos)                                        //找到author，写入coauthors
			{
				size_t startPos = tempstr.find_first_of(">");
				size_t endPos = tempstr.find_last_of("<");
				author_name.push_back(tempstr.substr(startPos + 1, endPos - (startPos + 1)));
				getline(infile, tempstr);
			}
			while (tempstr.find("<title>") != string::npos)                                          //找到标签“<title>”然后记录essay的名字
			{
				size_t startPos = tempstr.find_first_of(">");
				size_t endPos = tempstr.find_last_of("<");
				coawriter->coauthor->coauthor_essay = tempstr.substr(startPos + 1, endPos - (startPos + 1));
				getline(infile, tempstr);
			}
			vector<string>::iterator iter;
			for (iter = author_name.begin(); iter != author_name.end(); iter++)
			{
				string shortName = (*iter).substr(0, 3);                                             //截取作者名字来为文件命名
				transfFileName(shortName);
				ofstream outfile(save_url + "coauthor\\" + shortName + ".txt", ios::app);
				outfile << "<coauthor host=\"" + (*iter) + "\" " + "Essayname=\"" + coawriter->coauthor->coauthor_essay + "\" " +
					"urlpt=\"" + longToStr(coawriter->coauthor->coauthor_offset) + "\">" << endl;
				counter++;//测试用
				if (counter % 1000 == 0)cout << "Coauthor::counter:" << counter << endl;
				outfile.close();
			}
		}
		divcounter = infile.tellg();
		getline(infile, tempstr);
		N++;
	}
}
