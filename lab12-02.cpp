#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Solution
{
public:
    vector<int> findOrder(int numCourses, vector<vector<int > > &prerequisites)
    {
        //创建邻接表和入度数组
        vector<vector<int > > adjustList(numCourses);
        vector<int> inDegree(numCourses, 0);
        //计算入度
        for(const auto&prereq : prerequisites){
            int course = prereq[0];
            int prereqCourse = prereq[1];
            adjustList[prereqCourse].push_back(course);
            inDegree[course]++;
        }

        //初始化队列，加入入度为0的节点
        queue<int> q;
        for(int i=0;i<numCourses;i++){
            if(inDegree[i] == 0){  //如果课程没有先修课程（入度为0），可以直接学习
                q.push(i);
            }
        }

        //拓扑排序
        vector<int> result;
        while(!q.empty()){
            int course = q.front();
            q.pop();
            result.push_back(course);    //加入

            for(int i=0;i<adjustList[course].size();i++){
                int nextCourse = adjustList[course][i];
                inDegree[nextCourse]--;
                if(inDegree[nextCourse] == 0){
                    q.push(nextCourse);
                }
            }
        }

        //检查，是不是所有课程都学习了
        if(result.size() != numCourses){
            result.clear();
        }
        return result;
    }
};

int main()
{
    Solution solution;
    int numCourses = 2;
    vector<vector<int > > prerequisites;
    vector<int> place1;
    place1.push_back(1);
    place1.push_back(0);
    prerequisites.push_back(place1);
    vector<int> result = solution.findOrder(numCourses, prerequisites);
    for (int i = 0; i < result.size(); i++)
    {
        cout << result[i] << " ";
    }
    cout << endl;

    Solution solution2;
    numCourses = 4;
    prerequisites.clear();
    vector<int> place2;
    place2.push_back(1);
    place2.push_back(0);
    prerequisites.push_back(place2);
    vector<int> place3;
    place3.push_back(2);
    place3.push_back(0);
    prerequisites.push_back(place3);
    vector<int> place4;
    place4.push_back(3);
    place4.push_back(1);
    prerequisites.push_back(place4);
    vector<int> place5;
    place5.push_back(3);
    place5.push_back(2);
    prerequisites.push_back(place5);

    result = solution2.findOrder(numCourses, prerequisites);
    for (int i = 0; i < result.size(); i++)
    {
        cout << result[i] << " ";
    }
    cout << endl;

    Solution solution3;
    numCourses = 3;
    prerequisites.clear();
    vector <int> place6;
    place6.push_back(1);
    place6.push_back(0);
    prerequisites.push_back(place6);
    vector <int> place7;
    place7.push_back(2);
    place7.push_back(0);
    prerequisites.push_back(place7);
    vector <int> place8;
    place8.push_back(0);
    place8.push_back(2);
    prerequisites.push_back(place8);

    result = solution3.findOrder(numCourses, prerequisites);
    for (int i = 0; i < result.size(); i++)
    {
        cout << result[i] << " ";
    }
    cout << endl;
    return 0;
}

/*
时间复杂度：
    1. 构建图 O(边数)
    2. 拓扑排序 O(课程数 + 边数)，其中 n 是课程数量，m 是边的数量。
    总： O(课程数 + 边数)
*/

