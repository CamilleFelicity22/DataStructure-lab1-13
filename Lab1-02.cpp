#define N 10010
#include<cstdio>
#include<iostream>
using namespace std;

int findSpecialInteger(int* arr, int arrSize){
    int count[N];
    // 给个数全部赋为1
    for(int i = 0; i < arrSize; i++){
        count[i] = 1;
    }

    // 统计每个元素在连续的区间中出现的次数
    for(int i = 0; i < arrSize; i = i+count[i]){    //步长不再是1
        if(arr[i] != 0){
            for(int j = i+1;j < arrSize; j++){
                if(arr[i] == arr[j])
                    count[i]++;
                else
                    break;
            }
        }
    }
    
    // 查找出现次数超过 arrSize / 4 的元素
    int max = 0;
    for(int i = 0; i < arrSize; i++){
        if(count[i] > (arrSize/4))
            max = arr[i];
    }
    return max;
}

int main() {

    int n, arr[N];

    cin >> n;
    for(int i = 0; i < n; i++)
        cin >> arr[i];

    cout << findSpecialInteger(arr, n) << endl;

    // 时间复杂度：
    // 初始化数组：时间复杂度为 O(n)
    /* 统计每个元素出现个数：外层循环的步长是 count[i]，因此外层循环的迭代次数不一定是 n 次。在最坏情况下，可能会遍历到数组的最后一个元素。
     因此，最坏情况下，总的时间复杂度为 O(n^2)，因为内层循环在最坏情况下会执行 O(n) 次操作，并且可能会有 O(n) 次外层循环。*/
    // 查找出现次数超过 arrSize / 4 的元素:时间复杂度为 O(n)
    // 整体时间复杂度是 O(n^2)




    // 空间复杂度：
    // count 数组:空间复杂度为 O(n)。
    // 其他变量: 函数中的其他变量 max、i、j、n，空间复杂度是 O(1)。
    // 整体空间复杂度为 O(n)
    return 0;
}