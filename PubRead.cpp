#include"PubRead.h"
using namespace std;

long long strToLong(string str)                            //stringת 换成 ong long
{
	long long result;
	istringstream is(str);
	is >> result;
	return result;
}
void PubReader::showPub(string search_name)
{
	PubReader* pubwriter = new PubReader();
	string tempstr;
	long long div_finder = 0;
	string tmp_nickname = search_name.substr(0, 3);
	transfFileName(tmp_nickname);
	ifstream infile(save_url + "publication\\" + tmp_nickname + ".txt", ios::in);
	getline(infile, tempstr);
	while (!infile.eof()) 
	{
		if (tempstr.find(search_name) != string::npos)
		{
			size_t startPos = tempstr.find_last_of("=") + 1;
			size_t endPos = tempstr.find_last_of("\"");
			div_finder = strToLong(tempstr.substr(startPos + 1, endPos - (startPos + 1)));
			break;
		}
		getline(infile, tempstr);
	}
	infile.close();
	if (div_finder != 0)
	{
		ifstream indblp(save_url + "dblp.xml", ios::in | ios::binary);
		indblp.seekg(div_finder, ios::beg);
		getline(indblp, tempstr);//吃掉第一行
		cout << tempstr << endl;
		getline(indblp, tempstr);
		while(!checkTailElem(tempstr))
		{
			cout << tempstr << endl;
			getline(indblp, tempstr);
		}
	}
}

//int main()
//{
//	PublicationReader a;
//	string f;
//	getline(cin,f);
//	a.main_Reader(f);
//}
