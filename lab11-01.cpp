#include <iostream>
#include <vector>

using namespace std;

vector<int> findSmallestSetOfVertices(int n, vector<vector<int > > &edges)
{
    //创建一个入度为n的数组
    vector<int> inDegree(n, 0);

    //遍历所有边，计算每个结点的入度
    for (const auto &edge : edges)
    {
        int target = edge[1];
        inDegree[target]++;
    }
    vector<int> ans;
    for (int i = 0; i < n; ++i)
    {
        if (inDegree[i] == 0)
        {
            ans.push_back(i);
        }
    }
    return ans;
}

int main()
{
    // vector<vector<int>> edges = {{0, 1}, {0, 2}, {2, 5}, {3, 4}, {4, 2}};
    // vector<int> ans = findSmallestSetOfVertices(6, edges);

    vector<vector<int > > edges;
    vector<int> edge1;
    edge1.push_back(0);
    edge1.push_back(1);
    edges.push_back(edge1);

    vector<int> edge2;
    edge2.push_back(2);
    edge2.push_back(1);
    edges.push_back(edge2);

    vector<int> edge3;
    edge3.push_back(3);
    edge3.push_back(1);
    edges.push_back(edge3);

    vector<int> edge4;
    edge4.push_back(1);
    edge4.push_back(4);
    edges.push_back(edge4);

    vector<int> edge5;
    edge5.push_back(2);
    edge5.push_back(4);
    edges.push_back(edge5);

    edges.push_back(edge1);
    edges.push_back(edge2);
    edges.push_back(edge3);
    edges.push_back(edge4);
    edges.push_back(edge5);

    //= {{0, 1}, {2, 1}, {3, 1}, {1, 4}, {2, 4}};
    vector<int> ans = findSmallestSetOfVertices(5, edges);
    for (const auto &x : ans)
    {
        cout << x << " ";
    }
    cout << endl;
    return 0;
}

/* 
时间复杂度： O(n+m),m是边的数量,n是节点的数量
空间复杂度： O(n)
*/