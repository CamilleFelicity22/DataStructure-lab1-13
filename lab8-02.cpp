#include <iostream>
#include <vector>

using namespace std;

class Solution
{
public:
    // heaping函数：调整堆，从根节点向下检查子节点是否比根节点大
    void heaping(vector<int> &nums, int i, int n)
    {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        // 找到三个子节点中最大的
        if (left < n && nums[left] > nums[largest])
        {
            largest = left;
        }
        if (right < n && nums[right] > nums[largest])
        {
            largest = right;
        }
        if (largest != i)
        {
            swap(nums[i], nums[largest]);
            // 递归，继续调整数的大小
            heaping(nums, largest, n);
        }
    }
    //时间复杂度：O(logn)
    //空间复杂度：O(1)

    // 建最大堆
    void buildMaxheap(vector<int> &heap,int n)
    {
        int start = n / 2 - 1;
        for (int i = start; i >= 0; i--)
        {
            heaping(heap, i, n);
        }
    }

    // 在建了最大堆之后，进行k-1次堆顶元素的交换，最后的堆顶上就是第k大的元素
    int findKthLargest(vector<int> &nums, int k)
    {
        int n = nums.size();
        buildMaxheap(nums, n);
        for (int i = n - 1; i >= n - k + 1; i--)
        {
            swap(nums[0], nums[i]);
            heaping(nums, 0, i);
        }
        return nums[0];
    }
};

int main()
{
    Solution s;
    vector<int> nums;
    nums.push_back(3); 
    nums.push_back(2);
    nums.push_back(1);
    nums.push_back(5);
    nums.push_back(6);
    nums.push_back(4);
    cout << s.findKthLargest(nums, 2) << endl; // 5

    vector<int> nums2;
    nums2.push_back(3); 
    nums2.push_back(2);
    nums2.push_back(3);
    nums2.push_back(1);
    nums2.push_back(2);
    nums2.push_back(4);
    nums2.push_back(5);
    nums2.push_back(5);
    nums2.push_back(6);
    cout << s.findKthLargest(nums2, 4) << endl; // 4

    vector<int> nums3;
    nums3.push_back(3);
    nums3.push_back(2);
    nums3.push_back(1);
    nums3.push_back(5);
    nums3.push_back(6);
    nums3.push_back(4);
    cout << s.findKthLargest(nums3, 1) << endl; // 6

    return 0;
}
/*
时间复杂度：O(n)
空间复杂度：O(1)
*/
