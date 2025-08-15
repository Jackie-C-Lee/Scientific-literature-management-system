#pragma once
#include <unordered_set>
#include <unordered_map>
#include<map>
#include"allFunc.h"
using namespace std;
class Cluster {
public:
    Cluster() {}
    ~Cluster() {}
    string presentName = "Jack";                             //��ʼ������str
    map<set<string>, unordered_set<string>> bigVisit;        //��¼������ͼ���Ե��ѷ��ʽڵ�
    bool hasDuplicateClique(const set<string>&);             //���������ͬ��ͼ

    void addVertex(const string& author);
    void addEdge(const string& from, const string& to);

    vector<set<string>> findCliques();                      // ������ȫ��ͼ
    map<int, int> countCliqueOrders();                      // ͳ����ͼ����

    unordered_map<string, vector<string>> adjacencyList;    //�������ߵ��ڽӱ�
    vector<set<string>> cliques;                           // ��ȫ��ͼ�б�

    void DFS(const string& presentVer, set<string>& subgraph, map<set<string>, unordered_set<string>>& bigLoad);  // ���������������
};
void testCluster(Cluster &);
