#include "AllAuthor_get.h"
#include <algorithm>
using namespace std;

string intStr(int temp)                                                     //整型->字符串
{
	stringstream Trans;                                                //temp写入
	Trans << temp;
	string nothing;
	Trans >> nothing;
	return nothing;
}

void AllAuthorWriter::AuthorWriter()                                        //写入作者的名字 ||
{                                                                           //               \/
	string tempstr;
	int counter = 0;
	ifstream infile;
	infile.open(save_url + "dblp.xml", ios::in | ios::binary);                //文件读取
	getline(infile, tempstr);
	string authorName;
	int namecounter = 1;
	while (tempstr.find("</dblp>") == string::npos)                            //终止条件
	{
		if (tempstr.find("<author>") != string::npos)                          //找到标签
		{
			size_t startPos = tempstr.find_first_of(">");
			size_t endPos = tempstr.find_last_of("<");
			authorName = tempstr.substr(startPos + 1, endPos - (startPos + 1));
			ofstream outfile(save_url + "allAuthor\\nameList" + intStr(namecounter) + ".txt", ios::app);
			outfile << authorName << endl;
			counter++;//测试用
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