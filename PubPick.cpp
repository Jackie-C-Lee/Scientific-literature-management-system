#include"PubPick.h"
using namespace std;

void transfFileName(string& tmpNickname)
{
	if ((_stricmp(tmpNickname.c_str(), "CON") == 0) || (_stricmp(tmpNickname.c_str(), "PRN") == 0) ||
		(_stricmp(tmpNickname.c_str(), "AUX") == 0) || (_stricmp(tmpNickname.c_str(), "NUL") == 0))tmpNickname += "_a";//特殊命名处理
	if (tmpNickname.find(".") != string::npos)tmpNickname.replace(tmpNickname.find("."), 1, "_b");
	if (tmpNickname.find("/") != string::npos)tmpNickname.replace(tmpNickname.find("/"), 1, "_c");
	if (tmpNickname.find(">") != string::npos)tmpNickname.replace(tmpNickname.find(">"), 1, "_f");
	if (tmpNickname.find("\"") != string::npos)tmpNickname.replace(tmpNickname.find("\""), 1, "_g");
	if (tmpNickname.find(":") != string::npos)tmpNickname.replace(tmpNickname.find(":"), 1, "_h");
	if (tmpNickname.find("|") != string::npos)tmpNickname.replace(tmpNickname.find("|"), 1, "_i");
	if (tmpNickname.find("*") != string::npos)tmpNickname.replace(tmpNickname.find("*"), 1, "_j");
	if (tmpNickname.find("?") != string::npos)tmpNickname.replace(tmpNickname.find("?"), 1, "_k");
	if (tmpNickname.find(" ") != string::npos)tmpNickname.replace(tmpNickname.find(" "), 1, "_l");
	if (tmpNickname.find("$") != string::npos)tmpNickname.replace(tmpNickname.find("$"), 1, "_m");
	if (tmpNickname.find("\\") != string::npos)tmpNickname.replace(tmpNickname.find("\\"), 1, "_d");
	if (tmpNickname.find("<") != string::npos)tmpNickname.replace(tmpNickname.find("<"), 1, "_e");
}
	

bool checkStartElem(string tempstr)                                                                  //判定起始条件
{
	if ((tempstr.find("<article") != string::npos) || (tempstr.find("<inproceedings") != string::npos) ||
		(tempstr.find("<proceedings") != string::npos) || (tempstr.find("<book") != string::npos) ||
		(tempstr.find("<incollection") != string::npos) || (tempstr.find("<phdthesis") != string::npos) ||
		(tempstr.find("<mastersthesis") != string::npos) || (tempstr.find("<www") != string::npos))
		return true;
	else return false;
};

string longToStr(long long l)                                                                             //返回string
{
	ostringstream os;
	os << l;
	string result;
	istringstream is(os.str());
	is >> result;
	return result;
}

void PubWriter::writePub()
{
	PubWriter* pubwriter = new PubWriter();
	string tempstr;
	int counter = 0;
	long long divcounter = 0;                                                                      //记录偏移量，便于映射
	ifstream infile;
	infile.open(save_url + "dblp.xml", ios::in | ios::binary);                                    //打开总文件
	getline(infile, tempstr);
	while (tempstr.find("</dblp>") == string::npos) 
	{
		if (checkStartElem(tempstr))                                                            //文件article头，写入偏移量
		{
			pubwriter->publication->pubUrlpt = divcounter;
			while (tempstr.find("<title>") == string::npos)                         //循环往下读取
			{
				divcounter = infile.tellg();
				getline(infile, tempstr);
			}
			if (tempstr.find("<title>") != string::npos)                                         //找到title，写入publications
			{
				size_t startPos = tempstr.find_first_of(">");
				size_t endPos = tempstr.find_last_of("<");
				pubwriter->publication->pubName = tempstr.substr(startPos + 1, endPos - (startPos + 1));  //记录title
				string tmp_nickname = pubwriter->publication->pubName.substr(0, 3);
				transfFileName(tmp_nickname);
				ofstream outfile(save_url + "publication\\" + tmp_nickname + ".txt", ios::app);
				outfile << "<publication pname=\"" + pubwriter->publication->pubName + "\" " +      //每个文件存储essay名和偏移量
					"urlpt=\"" + longToStr(pubwriter->publication->pubUrlpt) + "\">" << endl;
				counter++;//测试用
				if (counter % 1000 == 0)cout << "Publication_Writer::counter:" << counter << endl;
				outfile.close();
			}
		}
		divcounter = infile.tellg();                                                  //一直在更新数值
		getline(infile, tempstr);
	}


}

//int main()
//{
//	PublicationWriter a;
//	a.main_Writer();
//}