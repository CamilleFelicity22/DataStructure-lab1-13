#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

vector<int> findDuplicates(vector<int> &nums)
{
    vector<int> result;//将结果存储在result中
    for(int i = 0; i < nums.size(); i++){
        int index = abs(nums[i]) - 1;
        if(nums[index] < 0){
            result.push_back(index + 1);  //是负数，说明index下标出现过，即nums[i]的数出现过
        }else{
        nums[index] = -nums[index];    //将以“出现过的数字”为下标的nums中元素置为负数
        }
    }
    return result;
}

int main()
{
    vector<int> nums;
    nums.push_back(4);
    nums.push_back(3);
    nums.push_back(2);
    nums.push_back(7);
    nums.push_back(8);
    nums.push_back(2);
    nums.push_back(3);
    nums.push_back(1);
    //= {4, 3, 2, 7, 8, 2, 3, 1}; // 2 3
    // vector<int> nums = {1, 1, 2}; // 1
    // vector<int> nums = {1}; // []
    vector<int> res = findDuplicates(nums);
    for (int i = 0; i < res.size(); i++)
    {
        cout << res[i] << " ";
    }
    cout << endl;
    return 0;
}

//时间复杂度为O(n),空间复杂度为O(1)