//#define _CRT_SECURE_NO_WARNINGS
#include"PubRead.h"
#include"PubPick.h"
#include"coPersonRead.h"
#include"coPersonGet.h"
#include"AllAuthor_get.h"
#include"YearWordPick.h"
#include"matchWord.h"
#include"cluster.h"
using namespace std;

int main()
{
	char choice;
	cout << "是否开启您的数据库？" << "（需要请输入Y，否则输入N）" << endl;
	cin >> choice;
	if (choice == 'Y') {}
	else if (choice == 'N')return 0;
	cout << "数据库准备开启" << endl;
	cout << "路径及其文件夹：" << save_url << "生成完毕！" << endl;
	cout << "请您完成上述操作后回到本窗口，按任意键，继续执行生成程序；" << endl;
	system("pause");

	cout << "allAuthor目录即将生成" << endl;
	AllAuthorWriter x_100;
	//c.AuthorWriter(); //读取数据加载所有作者名字
	//c.Author_RBProcessor();

	cout << "Publication目录即将生成" << endl;
	PubWriter in_Pub;
	//a.writePub();  //读取数据加载所有essay名和偏移量

	cout << "coauthor目录即将生成" << endl;
	CoauthorWriter in_coAu;
	//b.writeCoAuthor();  //读取数据加载作者自己的合作论文名单

	cout << "Year目录即将生成" << endl;
	YearHotWord d;
	//d.YearAna_Writer(); //读取数据加载所有的论文标题
	//main_WriterTrieTree(); //分析并产生结果，存储在yearWordAnalysis里面
	CoAuthorInfo coAuInfo;
	PubReader pubRead;
	matchAlg pipei;
	Cluster myCluster;


	int funcWhat = 0;
	cout << "-----------------------------------" << '\n'<<endl;
	cout << "下面我将为您展示功能说明：" << endl;
	cout << '\t' << "输入1：搜索作者论文信息" << endl;
	cout << '\t' << "输入2：搜索论文信息" << endl;
	cout << '\t' << "输入3：搜索作者的合作作者" << endl;
	cout << '\t' << "输入4：统计文章数量前100的作者" << endl;
	cout << '\t' << "输入5：分析每年的年度词频" << endl;
	cout << '\t' << "输入6：搜索包含关键字的论文" << endl;
	cout << '\t' << "输入7：聚团分析" << endl;
	cout << '\t' << "输入8：关闭功能模块" << endl;
	cout << "-----------------------------------" <<'\n'<< endl;
	cout << "接下来请选择您想要执行的功能：" << endl;

	while (cin >> funcWhat)
	{
		if (funcWhat == 8)break;
		switch (funcWhat)
		{
		 case 1:
		 {
			 string f;
			 cout << "输入作者名字" << endl;
			 cin.ignore();
		     getline(cin, f);
		      coAuInfo.personalWorks(f);
		      cout << "执行完毕！选择下一个功能：" << endl;
		 break;
		 }
		 case 2:
		 {
			 	string f;
				cout << "输入论文标题" << endl;
				cin.ignore();
			 	getline(cin,f);
			 	pubRead.showPub(f);
				cout << "执行完毕！选择下一个功能：" << endl;
				break;
		 }
		 case 3:
		 {
		       string f;
			   cout << "输入作者" << endl;
			   cin.ignore();
		       getline(cin, f);
		       coAuInfo.showCoWriter(f);
			   cout << "执行完毕！选择下一个功能：" << endl;
			   break;
		 }
		 case 4:
		 {
			 x_100.Author100();
			 cout << "执行完毕！选择下一个功能：" << endl;
			 break;
		 }
		 case 5:
		 {
			 main_WriterTrieTree();
			 cout << "执行完毕！选择下一个功能：" << endl;
			 break;
		 }
		 case 6:
		 {
			 mainTest(pipei);
			 matchSearch(pipei);
			 cout << "执行完毕！选择下一个功能：" << endl;
			 break;
		 }
		 case 7:
		 {
			 testCluster(myCluster);
			 cout << "执行完毕！选择下一个功能：" << endl;
			 break;
		 }
		 default:
		 {
			 cout << "数字不正确，请重新输入！" << endl;
			 break;
		 }
		}
	}
	return 0;
}
