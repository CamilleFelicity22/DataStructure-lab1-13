#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>
using namespace std;

void dfs(int node,const vector<vector<int > > &graph,vector<bool> &visited,unordered_set<int> &component){
    visited[node] = true;
    component.insert(node);
    for (int neighbor : graph[node]) {
        if (!visited[neighbor]) {
            dfs(neighbor, graph, visited, component);
        }
    }
}
bool isCompleteComponent(const unordered_set<int>& component, vector<vector<int > > &graph)
{
    int n = component.size();

    // 将连通分量中的节点存储到一个 vector 中，便于进行组合
    vector<int> nodes(component.begin(), component.end());
    // 检查每一对节点是否都有边
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            int nodeA = nodes[i];
            int nodeB = nodes[j];

            // 如果节点 nodeA 和 nodeB 没有边相连，返回 false
            if (find(graph[nodeA].begin(), graph[nodeA].end(), nodeB) == graph[nodeA].end()) {
                return false;
            }
        }
    }

    return true;
}

int countCompleteComponents(int n, vector<vector<int > > &edges){
    vector<vector<int > > graph(n);
    for(const vector<int>& edge : edges){
        graph[edge[0]].push_back(edge[1]);
        graph[edge[1]].push_back(edge[0]);
    }//无向图
    vector<bool> visited(n, false);
    int count = 0;
    for(int i=0;i<n;i++){
        if(!visited[i]){
            unordered_set<int> component;
            dfs(i,graph,visited,component);
            if(isCompleteComponent(component,graph)){
                ++count;
            }
        }
    }
    return count;
}

int main()
{
    vector<vector<int > > edges;
    vector<int> edge01;
    edge01.push_back(0);
    edge01.push_back(1);
    edges.push_back(edge01);

    vector<int> edge02;
    edge02.push_back(0);
    edge02.push_back(2);
    edges.push_back(edge02);

    vector<int> edge03;
    edge03.push_back(1);
    edge03.push_back(2);
    edges.push_back(edge03);

    vector<int> edge04;
    edge04.push_back(3);
    edge04.push_back(4);
    edges.push_back(edge04);

    // vector<vector<int>> edges = {{0, 1}, {0, 2}, {1, 2}, {3, 4}};
    cout << countCompleteComponents(6, edges) << endl; // 3

    vector<vector<int > > edges2;
    vector<int> edge11;
    edge11.push_back(0);
    edge11.push_back(1);
    edges2.push_back(edge11);

    vector <int> edge12;
    edge12.push_back(0);
    edge12.push_back(2);
    edges2.push_back(edge12);

    vector <int> edge13;
    edge13.push_back(1);
    edge13.push_back(2);
    edges2.push_back(edge13);

    vector <int> edge14;
    edge14.push_back(3);
    edge14.push_back(4);
    edges2.push_back(edge14);

    vector <int> edge15;
    edge15.push_back(3);
    edge15.push_back(5);
    edges2.push_back(edge15);

    // vector<vector<int > > edges2 = {{0, 1 }, {0, 2}, {1, 2}, {3, 4}, {3, 5}};
    cout << countCompleteComponents(6, edges2) << endl; // 1

    return 0;
}
/*
m是边数，n是节点数
时间复杂度：O(m + n + n^2)
空间复杂度：O(n+m)
*/