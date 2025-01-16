#include <iostream>
#include <vector>
#include <queue>
using namespace std;


// Dijkstra 算法
vector<int> dijkstra(int n, const vector<vector<pair<int, int > > >& graph, int source) {
    vector<int> dist(n, INT_MAX);  // 存储最短路径
    dist[source] = 0;
    
    priority_queue<pair<int, int>, vector<pair<int, int > >, greater<pair<int, int > > > pq;
    pq.push(make_pair(0, source));
    
    while (!pq.empty()) {
        int u = pq.top().second;
        int d = pq.top().first;
        pq.pop();
        if (d > dist[u]) continue;
        // 遍历
        for (const auto& neighbor : graph[u]) {
            int v = neighbor.first;
            int weight = neighbor.second;
            
            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.push(make_pair(dist[v], v));
            }
        }
    }
    return dist;
}

vector<bool> findAnswer(int n, vector<vector<int > > &edges)
{
    //图的邻接表
    vector<vector<pair<int, int > > > graph(n);
    for(const vector<int>& edge : edges){  
        int u = edge[0];
        int v = edge[1];
        int w = edge[2];
        graph[u].push_back(make_pair(v, w));
        graph[v].push_back(make_pair(u, w));
    }

    //从节点0开始
    vector<int> dist = dijkstra(n, graph, 0);
    //从节点n-1开始
    vector<int> dist2 = dijkstra(n, graph, n-1);
    //从节点0开始到节点n-1的最短路径
    int minDist = dist[n-1];
    vector<bool> ans(edges.size(), false);
    //遍历所有边,检查是不是每条边在这个最短路径上
    for(int i=0;i<edges.size();i++){
        int u = edges[i][0];
        int v = edges[i][1];
        int w = edges[i][2];
        //0 -> u -> v -> n-1 或者 0 -> v -> u -> n-1
        if(dist[u] + w + dist2[v] == minDist || dist[v] + w + dist2[u] == minDist){
            ans[i] = true;
        }
    }
    return ans;

}

int main()
{
    int n = 6;
    vector< vector<int > > edges;
    vector<int> edges11;
    edges11.push_back(0);
    edges11.push_back(1);
    edges11.push_back(4);
    edges.push_back(edges11);

    vector<int> edges12;
    edges12.push_back(0);
    edges12.push_back(2);
    edges12.push_back(1);
    edges.push_back(edges12);

    vector<int> edges13;
    edges13.push_back(1);
    edges13.push_back(3);
    edges13.push_back(2);
    edges.push_back(edges13);

    vector<int> edges14;
    edges14.push_back(1);
    edges14.push_back(4);
    edges14.push_back(3);
    edges.push_back(edges14);

    vector<int> edges15;
    edges15.push_back(1);
    edges15.push_back(5);
    edges15.push_back(1);
    edges.push_back(edges15);

    vector<int> edges16;
    edges16.push_back(2);
    edges16.push_back(3);
    edges16.push_back(1);
    edges.push_back(edges16);

    vector<int> edges17;
    edges17.push_back(3);
    edges17.push_back(5);
    edges17.push_back(3);
    edges.push_back(edges17);

    vector<int> edges18;
    edges18.push_back(4);
    edges18.push_back(5);
    edges18.push_back(2);
    edges.push_back(edges18);


    vector<bool> ans = findAnswer(n, edges);
    for (int i = 0; i < ans.size(); i++)
    {
        cout << ans[i] << " ";
    }
    cout << endl;

    n = 4;
    edges.clear();
    vector<int> edges21;
    edges21.push_back(2);
    edges21.push_back(0);
    edges21.push_back(1);
    vector<int> edges22;
    edges22.push_back(0);
    edges22.push_back(1);
    edges22.push_back(1);
    vector<int> edges23;
    edges23.push_back(0);
    edges23.push_back(3);
    edges23.push_back(4);
    vector<int> edges24;
    edges24.push_back(3);
    edges24.push_back(2);
    edges24.push_back(2);
    edges.push_back(edges21);
    edges.push_back(edges22);
    edges.push_back(edges23);
    edges.push_back(edges24);
    ans = findAnswer(n, edges);
    for (int i = 0; i < ans.size(); i++)
    {
        cout << ans[i] << " ";
    }
    cout << endl;
    

    n = 3;
    edges.clear();
    vector<int> edges31;
    edges31.push_back(2);
    edges31.push_back(1);
    edges31.push_back(6);
    edges.push_back(edges31);
    ans = findAnswer(n, edges);
    for (int i = 0; i < ans.size(); i++)
    {
        cout << ans[i] << " ";
    }
    cout << endl;

    return 0;
}

/*
Dijkstra的时间复杂度是 O((n + m)*log(n))，n是节点数,m是边数。
处理每条边的检查是 O(m)。
总：O((n + m)*log(n) + m)。
*/