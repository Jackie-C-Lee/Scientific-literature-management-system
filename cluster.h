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
    string presentName = "Jack";                             //初始化名字str
    map<set<string>, unordered_set<string>> bigVisit;        //记录所有子图各自的已访问节点
    bool hasDuplicateClique(const set<string>&);             //避免添加相同子图

    void addVertex(const string& author);
    void addEdge(const string& from, const string& to);

    vector<set<string>> findCliques();                      // 查找完全子图
    map<int, int> countCliqueOrders();                      // 统计子图阶数

    unordered_map<string, vector<string>> adjacencyList;    //所有作者的邻接表
    vector<set<string>> cliques;                           // 完全子图列表

    void DFS(const string& presentVer, set<string>& subgraph, map<set<string>, unordered_set<string>>& bigLoad);  // 深度优先搜索函数
};
void testCluster(Cluster &);
