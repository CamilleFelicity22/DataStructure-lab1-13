#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;

//思路：自顶向下归并排序
class Solution
{
public:
    int reversePairs(vector<int>& record) {
        vector<int> temp(record.size());
        return mergeSort(record, temp, 0, record.size() - 1);
    }
private:
    
    int mergeSort(vector<int>& record, vector<int>& temp, int left, int right) {
        if (left >= right) return 0;  // 如果子数组只有一个元素，则没有逆序对
        int mid = left + (right - left) / 2;
        // 左半部分
        int count = mergeSort(record, temp, left, mid); 
        // 右半部分
        count += mergeSort(record, temp, mid + 1, right);
        count += merge(record, temp, left, mid, right);
        return count;
    }
    
    // 合并，同时统计逆序对
    int merge(vector<int>& record, vector<int>& temp, int left, int mid, int right) {
        for (int i = left; i <= right; ++i) {
            temp[i] = record[i];
        }
        int i = left, j = mid + 1, k = left, count = 0;
        // 合并两部分
        while (i <= mid && j <= right) {
            if (temp[i]<=temp[j]) {
                record[k++]=temp[i++];
            } else {
                record[k++]=temp[j++];
                count+= (mid - i + 1);  
            }
        }
        // 如果左边部分还有剩余
        while (i <= mid) {
            record[k++]=temp[i++];
        }
        // 如果右边部分还有剩余
        while (j <= right) {
            record[k++]=temp[j++];
        }
        return count;
    }
};

int main()
{
    Solution s;
    vector<int> record;
    record.push_back(2);
    record.push_back(3);
    record.push_back(4);
    record.push_back(5);
    record.push_back(6);
    record.push_back(1);
    cout << s.reversePairs(record) << endl; // 5
    vector<int> record2;
    record2.push_back(9);
    record2.push_back(7);
    record2.push_back(5);
    record2.push_back(4);
    record2.push_back(6);

    cout << s.reversePairs(record2) << endl; // 8
    return 0;
}


//时间复杂度是 O(nlog n)
//空间复杂度是 O(n)