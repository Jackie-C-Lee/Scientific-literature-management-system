#include"cluster.h"
using namespace std;
static int dfs_N;
void createAdList(Cluster& graph)
{
    string tempstr;
    ifstream infile;
    infile.open(save_url + "dblp.xml", ios::in | ios::binary);
    getline(infile, tempstr);
    int N = 4; // ����
    while (N > 0 )
    {
        if (checkStartElem(tempstr))
        {
            vector<string> author_name;
            getline(infile, tempstr);
            while (tempstr.find("<author>") != string::npos)
            {
                    size_t startPos = tempstr.find_first_of(">");
                    size_t endPos = tempstr.find_last_of("<");
                    string author = tempstr.substr(startPos + 1, endPos - (startPos + 1));
                    author_name.push_back(author);
                    getline(infile, tempstr);
            }
            for (int i = 0; i < author_name.size(); ++i)
            {
                for (int j = 0; j < author_name.size(); ++j)
                {
                    if (i == j)continue;
                    graph.addEdge(author_name[i], author_name[j]);
                }
            }
            author_name.clear();
        }
        getline(infile, tempstr);
        N--;
       if(N%1000==0)cout<<"("<<N<<")";
    }
}

void Cluster::addVertex(const string& name)
{
    if (adjacencyList.find(name) == adjacencyList.end())
        adjacencyList[name] = vector<string>();
}
void Cluster::addEdge(const string& from, const string& to)
{
    addVertex(from);
    addVertex(to);
    auto& fromNeighbors = adjacencyList[from];
    if (find(fromNeighbors.begin(), fromNeighbors.end(), to) == fromNeighbors.end())
        adjacencyList[from].push_back(to);
}
vector<set<string>> Cluster::findCliques()
{
    bigVisit.clear();              //��շ��ʽڵ�
    cliques.clear();              //�����ͼ�ļ���
    set<string>clique;          //ĳ����ͼ
    for (const auto& pair : adjacencyList)
    {
        presentName = pair.first;
        clique.clear();
        DFS(presentName, clique, bigVisit);
    }
    return cliques;
}
map<int, int> Cluster::countCliqueOrders()   //ͳ�����е���ͼ
{
    map<int, int> orderCount;
    for (const auto& autoSub : cliques)
    {
        int order = autoSub.size();
        orderCount[order]++;
    }
    return orderCount;
}
bool Cluster::hasDuplicateClique(const set<string>& zitu)
{
    // �ȶ� zitu ��������
    set<string> sortedZitu(zitu.begin(), zitu.end());
    // ������֪����ȫ��ͼ���Ƚ��Ƿ������ͬ����ͼ
    for (const auto& existingClique : cliques)
    {
        // �������������ȣ��������ͬ����ͼ
        if (existingClique == sortedZitu) return true;
    }
    // ��������ͬ����ͼ
    return false;
}


void Cluster::DFS(const string &presentVer, set<string>& subgraph, map<set<string>, unordered_set<string>>& bigLoad)
{
    dfs_N++; if (dfs_N % 10000 == 0)cout << dfs_N << endl;  //���ԣ���¼����
    const vector<string>& U1 = adjacencyList[presentVer];
    unordered_set<string>& U2 = bigLoad[subgraph];
    if (subgraph.empty()) {}
    else
    {
        if (subgraph.find(presentVer) != subgraph.end()) 
            return;
        else if (U2.find(presentVer) != U2.end())
            return;
        else
        {
            if (U1.size() < subgraph.size())
                return;
            else       //����Ϊ����һ��֮ǰ�����Ż��Ĵ�ʩ
            {
                const vector<string>& checK = U1;
                for (const auto& nowSub : subgraph)
                {
                    if (nowSub != presentVer && find(checK.begin(), checK.end(), nowSub) == checK.end())
                        return;
                }
            }
        }
    }
    const vector<string>& neighbors = adjacencyList[presentVer];
    if (!subgraph.empty())U2.insert(presentVer);   //���·��ʽڵ�
    subgraph.insert(presentVer);     //���µ�ǰ����ͼ
    for (const string &neighbor : neighbors)
        DFS(neighbor, subgraph, bigLoad);
    if (subgraph.size() > 1 && !hasDuplicateClique(subgraph))    //��ӽ���ȫ��ͼ����
        cliques.push_back(subgraph);

    subgraph.erase(presentVer);   //��ǰ����
}
void testCluster(Cluster &x)
{
    createAdList(x);
    vector<set<string>> Cliques = x.findCliques();
    map<int, int> outcome = x.countCliqueOrders();
    cout << "Number of cliques: " << Cliques.size() << endl;
    cout << "subgraph Orders:" << endl;
    for (const auto& pair : outcome)
        cout << "Order " << pair.first << ": " << pair.second << " cliques" << endl;
}

