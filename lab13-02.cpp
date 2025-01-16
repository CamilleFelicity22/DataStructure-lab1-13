#include <iostream>
#include <cstdio>
#include <vector>
#include <unordered_map>
#include <queue>
using namespace std;

vector<int> topKFrequent(vector<int>& nums, int k) {
    unordered_map<int, int> frequencyMap;  
    for (int num : nums) {
        frequencyMap[num]++;
    }  //统计每个元素的频率
    //使用最小堆存储前k个频率最高的元素
    priority_queue<pair<int, int>, vector<pair<int, int > >, greater<pair<int, int> > > minHeap;
    for (auto& entry : frequencyMap) {
        minHeap.push(make_pair(entry.second, entry.first));
        if (minHeap.size() > k) {
            minHeap.pop();  
        }
    }
    vector<int> result;
    while (!minHeap.empty()) {
        result.push_back(minHeap.top().second);
        minHeap.pop();
    }
    return result;
}

int main()
{
    vector<int> nums;
    //{1, 1, 1, 2, 2, 3};
    nums.push_back(1);
    nums.push_back(1);
    nums.push_back(1);
    nums.push_back(2);
    nums.push_back(2);
    nums.push_back(3);
    int k = 2;
    vector<int> ret = topKFrequent(nums, k);
    for (auto &v : ret)
    {
        cout << v << " ";
    }
    cout << endl;

    vector<int> nums2;
    nums2.push_back(1);
    int k2 = 1;
    vector<int> ret2 = topKFrequent(nums2, k2);
    for (auto &v : ret2)
    {
        cout << v << " ";
    }
    cout << endl;
    return 0;
}

//n是数组大小，k是堆的大小
//时间复杂度：O(n+klogk)
//空间复杂度：O(k)