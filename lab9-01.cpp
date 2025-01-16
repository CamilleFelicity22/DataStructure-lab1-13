#include <iostream>
#include <vector>

using namespace std;
vector<int> Count(vector<int> &nums,int low,int high)
{
    vector<int> result;
    int mid ;
    while(low <= high){
        mid = (low + high)/2;
        if(nums[mid] < 0){
            low = mid + 1;
        }
        else{
            high = mid-1;
        }
    }
    //此时low指向第一个非负数的位置
    //现在开始排除0
    int first = low;
    while(first < nums.size() && nums[first] == 0){
        first++;
    }
    int abovezero = nums.size() - first;
    int belowzero = low;
    result.push_back(belowzero);
    result.push_back(abovezero);
return result;
};

int main()
{
    vector<int> nums;
    nums.push_back(-2);
    nums.push_back(-1);
    nums.push_back(-1);
    nums.push_back(1);
    nums.push_back(2);
    nums.push_back(3);


    // vector<int> nums = {-3, -2, -1, 0, 0, 1, 2};
    // vector<int> nums = {5, 20, 66, 1314};
    vector<int> ans = Count(nums, 0, nums.size() - 1);
    cout << ans[0] << " " << ans[1] << endl;
    return 0;
}