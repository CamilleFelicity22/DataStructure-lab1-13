#include <iostream>
#include <vector>
#include <numeric>
#include <queue>
using namespace std;

int manhattanDistance(vector<int> &a, vector<int> &b)
{
    return abs(a[0] - b[0]) + abs(a[1] - b[1]);
}
// 使用Prim算法计算最小生成树的总代价
int minCostConnectPoints(vector<vector<int > >& points) {
    int n = points.size();
    vector<bool> visited(n, false);  // 标记点是否被访问过
    priority_queue<pair<int, int>, vector<pair<int, int > >, greater<pair<int, int > > > pq;  // 最小堆，存储 (距离, 点索引)
    
    int totalCost = 0;
    int edgesCount = 0;
    
    // 从第一个点开始
    pq.push(make_pair(0, 0));  // 初始点到自己的距离是 0
    while (!pq.empty() && edgesCount < n) {
        auto top = pq.top();
        int cost = top.first;
        int u = top.second;
        pq.pop();
        
        if (visited[u]) continue;  // 如果已经访问过，跳过
        
        visited[u] = true;
        totalCost += cost;
        edgesCount++;
        
        // 将当前点与其他未访问点之间的边加入优先队列
        for (int v = 0; v < n; ++v) {
            if (!visited[v]) {
                int dist = manhattanDistance(points[u], points[v]);
                pq.push(make_pair(dist, v));
            }
        }
    }
    
    return totalCost;
}


int main()
{
    vector<vector<int > > points1;

    vector<int> point11;
    point11.push_back(3);
    point11.push_back(12);
    points1.push_back(point11);

    vector<int> point12;
    point12.push_back(-2);
    point12.push_back(5);
    points1.push_back(point12);

    vector<int> point13;
    point13.push_back(-4);
    point13.push_back(1);
    points1.push_back(point13);
    // = {{3, 12}, {-2, 5}, {-4, 1}};
    cout << minCostConnectPoints(points1) << endl; // 18

    vector<vector<int > > points2;
    //= {{-1000000, -1000000}, {1000000, 1000000}};
    vector<int> point21;
    point21.push_back(-1000000);
    point21.push_back(-1000000);
    points2.push_back(point21);

    vector<int> point22;
    point22.push_back(1000000);
    point22.push_back(1000000);
    points2.push_back(point22);
    cout << minCostConnectPoints(points2) << endl; // 4000000

    return 0;
}
/*
时间复杂度：O(n^2 * logn)
空间复杂度：O(n)
*/
//点多，边少