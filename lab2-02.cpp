#include <cstdio>
#include <iostream>
#include <assert.h>

using namespace std;

const int defaultSize = 1010;

template <class Type>
class SeqList
{
public:
    // 构造函数，初始化顺序表，默认大小为 defaultSize
    SeqList(int size = defaultSize);
    // 析构函数，释放顺序表的动态数组空间
    ~SeqList() { delete[] list; }
    void PrintAll();
    int Length() const { return last + 1; }
    int Find(Type x) const;
    int Insert(Type x, int i);
    int Remove(int i);
    int removeDuplicates();
    int IsEmpty() { return last == -1; }
    int IsFull() { return last == maxSize - 1; }
    Type Get(int i);

private:
    Type *list;
    int maxSize;
    int last;
};

template <class Type>
SeqList<Type>::SeqList(int size)
{
    if (size > 0)
    {
        maxSize = size;
        last = -1;
        list = new Type[maxSize];
        if (list == NULL)
        {
            cerr << " Memory Allocation Error " << endl;
            return;
        }
    }
}

template <class Type>
Type SeqList<Type>::Get(int i)
{
    if (i < 0 || i > last)
    {
        throw std::out_of_range("Index out of bounds");
    }
    return list[i];
}

template <class Type>
void SeqList<Type>::PrintAll()
{
    for (int i = 0; i < last; i++)
        cout << list[i] << ' ';
    cout << list[last] << endl;
}

template <class Type>
int SeqList<Type>::Find(Type x) const
{
    for (int i = 0; i <= last; i++)
        if (list[i] == x)
            return i;
    return -1;
}

template <class Type>
int SeqList<Type>::Insert(Type x, int i)
{
    if (i < 0 || i > last + 1)
    {
        cout << "ILLEGAL POSITION ";
        return -1;
    }
    if (last == maxSize - 1)
    {
        cout << "Full ";
        return -1;
    }
    last++;
    for (int j = last; j > i; j--)
        list[j] = list[j - 1];
    list[i] = x;
    return 0;
}

template <class Type>
int SeqList<Type>::Remove(int i)
{
    if (i < 0 || i > last)
        return 1;
    for (int j = i; j < last; j++)
        list[j] = list[j + 1];
    last--;
    return 0;
}

template <class Type>
int SeqList<Type>::removeDuplicates()
{
    if (last < 1)     // 如果只有一个或没有元素，不需要处理
        return last + 1;

    int slow = 0;    // 慢指针初始化为第一个元素
    for (int fast = 1; fast <= last; fast++)
    {
        if (list[fast] != list[slow]) // 当找到不同元素时
        {
            slow++;            // 慢指针前进
            list[slow] = list[fast]; // 更新唯一元素到新的位置
        }
    }
    last = slow; // 更新顺序表的最后位置
    return slow + 1; // 返回唯一元素的数量
}

int main()
{
    int arr[] = {0, 0, 1, 1, 1, 2, 2, 3, 3, 4};

    SeqList<int> a(sizeof(arr) / sizeof(arr[0]));
    for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
        a.Insert(arr[i], i);

    int expectedNums[] = {0, 1, 2, 3, 4}; // 长度正确的期望答案

    int k = a.removeDuplicates(); // 调用去重函数
    cout << k << endl;   //输出唯一元素的数量

    assert(k == sizeof(expectedNums) / sizeof(expectedNums[0]));

    for (int i = 0; i < k; i++)
    {
        assert(a.Get(i) == expectedNums[i]);
    }

    a.PrintAll();

    return 0;
}


/*
1.时间复杂度：
插入元素的时间复杂度为 O(n^2)。
去重操作的时间复杂度为 O(n)。
打印操作的时间复杂度为 O(n)。
因此，整体时间复杂度为 O(n^2)，其中 n 是顺序表的元素个数。

2.空间复杂度：
空间复杂度：O(1）

*/