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
	cout << "�Ƿ����������ݿ⣿" << "����Ҫ������Y����������N��" << endl;
	cin >> choice;
	if (choice == 'Y') {}
	else if (choice == 'N')return 0;
	cout << "���ݿ�׼������" << endl;
	cout << "·�������ļ��У�" << save_url << "������ϣ�" << endl;
	cout << "�����������������ص������ڣ��������������ִ�����ɳ���" << endl;
	system("pause");

	cout << "allAuthorĿ¼��������" << endl;
	AllAuthorWriter x_100;
	//c.AuthorWriter(); //��ȡ���ݼ���������������
	//c.Author_RBProcessor();

	cout << "PublicationĿ¼��������" << endl;
	PubWriter in_Pub;
	//a.writePub();  //��ȡ���ݼ�������essay����ƫ����

	cout << "coauthorĿ¼��������" << endl;
	CoauthorWriter in_coAu;
	//b.writeCoAuthor();  //��ȡ���ݼ��������Լ��ĺ�����������

	cout << "YearĿ¼��������" << endl;
	YearHotWord d;
	//d.YearAna_Writer(); //��ȡ���ݼ������е����ı���
	//main_WriterTrieTree(); //����������������洢��yearWordAnalysis����
	CoAuthorInfo coAuInfo;
	PubReader pubRead;
	matchAlg pipei;
	Cluster myCluster;


	int funcWhat = 0;
	cout << "-----------------------------------" << '\n'<<endl;
	cout << "�����ҽ�Ϊ��չʾ����˵����" << endl;
	cout << '\t' << "����1����������������Ϣ" << endl;
	cout << '\t' << "����2������������Ϣ" << endl;
	cout << '\t' << "����3���������ߵĺ�������" << endl;
	cout << '\t' << "����4��ͳ����������ǰ100������" << endl;
	cout << '\t' << "����5������ÿ�����ȴ�Ƶ" << endl;
	cout << '\t' << "����6�����������ؼ��ֵ�����" << endl;
	cout << '\t' << "����7�����ŷ���" << endl;
	cout << '\t' << "����8���رչ���ģ��" << endl;
	cout << "-----------------------------------" <<'\n'<< endl;
	cout << "��������ѡ������Ҫִ�еĹ��ܣ�" << endl;

	while (cin >> funcWhat)
	{
		if (funcWhat == 8)break;
		switch (funcWhat)
		{
		 case 1:
		 {
			 string f;
			 cout << "������������" << endl;
			 cin.ignore();
		     getline(cin, f);
		      coAuInfo.personalWorks(f);
		      cout << "ִ����ϣ�ѡ����һ�����ܣ�" << endl;
		 break;
		 }
		 case 2:
		 {
			 	string f;
				cout << "�������ı���" << endl;
				cin.ignore();
			 	getline(cin,f);
			 	pubRead.showPub(f);
				cout << "ִ����ϣ�ѡ����һ�����ܣ�" << endl;
				break;
		 }
		 case 3:
		 {
		       string f;
			   cout << "��������" << endl;
			   cin.ignore();
		       getline(cin, f);
		       coAuInfo.showCoWriter(f);
			   cout << "ִ����ϣ�ѡ����һ�����ܣ�" << endl;
			   break;
		 }
		 case 4:
		 {
			 x_100.Author100();
			 cout << "ִ����ϣ�ѡ����һ�����ܣ�" << endl;
			 break;
		 }
		 case 5:
		 {
			 main_WriterTrieTree();
			 cout << "ִ����ϣ�ѡ����һ�����ܣ�" << endl;
			 break;
		 }
		 case 6:
		 {
			 mainTest(pipei);
			 matchSearch(pipei);
			 cout << "ִ����ϣ�ѡ����һ�����ܣ�" << endl;
			 break;
		 }
		 case 7:
		 {
			 testCluster(myCluster);
			 cout << "ִ����ϣ�ѡ����һ�����ܣ�" << endl;
			 break;
		 }
		 default:
		 {
			 cout << "���ֲ���ȷ�����������룡" << endl;
			 break;
		 }
		}
	}
	return 0;
}
