#define N 100010
#include<cstdio>
#include<iostream>



int mySortAndCount(int* arr,int arrSize)
{
    //使用冒泡排序对数组进行排序
    for(int i = 0; i < arrSize - 1; i++){
        for(int j = i + 1; j < arrSize; j++){
            if(arr[i] > arr[j]){
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
    int k= 1;//一开始，认为数组中至少有一个不同的元素
    //以下计算数组里面不一样的元素个数
    //先排好序，再算k，比较容易
    for(int i = 0; i < arrSize - 1; i++){
        if(arr[i] != arr[i + 1])
            k++;
    }

    return k;
}


int main() {

    int n, k;

    std::cin >> n;
    int arr[n];
    for(int i = 0; i < n; i++)
        std::cin >> arr[i];

    k = mySortAndCount(arr, n);

    for(int i = 0; i < n - 1; i++)
        std::cout << arr[i] << ' ';
    std::cout << arr[n - 1] << std::endl;

    std::cout << "k = " << k << std::endl;

    // 时间复杂度：
    // 冒泡排序的时间复杂度为 O(n^2)，
    // 计算不同元素的个数的时间复杂度为 O(n)，
    // 总体时间复杂度为 O(n^2)。


    // 空间复杂度：
    // 变量：如temp、k、i、j等，它们占用常量空间 O(1)。
    // 整体空间复杂度为 O(1)。
    return 0;
}