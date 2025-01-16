#include <iostream>
#include <vector>
using namespace std;

class MyCircularQueue
{
private:
    vector<int> data;  // 用于存储队列数据
    int head;          // 队列头指针
    int tail;          // 队列尾指针
    int size;          // 队列的最大容量
    int count;         // 队列当前元素数量

public:
    // 构造函数，初始化队列的大小和指针
    MyCircularQueue(int k)
    {
        data.resize(k);  // 分配大小为k的数组
        head = 0;
        tail = -1;
        size = k;
        count = 0;
    }

    // 向循环队列插入一个元素。如果成功插入则返回 true
    bool enQueue(int value)
    {
        if (isFull()) return false;  // 如果队列已满，插入失败
        tail = (tail + 1) % size;    // 移动尾指针
        data[tail] = value;          // 插入新值
        count++;                     // 队列元素数增加
        return true;
    }

    // 从循环队列中删除一个元素。如果成功删除则返回 true
    bool deQueue()
    {
        if (isEmpty()) return false; // 如果队列为空，删除失败
        head = (head + 1) % size;    // 移动头指针
        count--;                     // 队列元素数减少
        return true;
    }

    // 获取队列头部的元素。如果队列为空，返回 -1
    int Front()
    {
        if (isEmpty()) return -1;
        return data[head];
    }

    // 获取队列尾部的元素。如果队列为空，返回 -1
    int Rear()
    {
        if (isEmpty()) return -1;
        return data[tail];
    }

    // 检查队列是否为空
    bool isEmpty()
    {
        return count == 0;
    }

    // 检查队列是否已满
    bool isFull()
    {
        return count == size;
    }
};

// 测试代码
int main()
{
    MyCircularQueue circularQueue(3); // 设置长度为 3
    cout << circularQueue.enQueue(1) << endl;  // 返回 true
    cout << circularQueue.enQueue(2) << endl;  // 返回 true
    cout << circularQueue.enQueue(3) << endl;  // 返回 true
    cout << circularQueue.enQueue(4) << endl;  // 返回 false，队列已满
    cout << circularQueue.Rear() << endl;      // 返回 3
    cout << circularQueue.isFull() << endl;    // 返回 true
    cout << circularQueue.deQueue() << endl;   // 返回 true
    cout << circularQueue.enQueue(4) << endl;  // 返回 true
    cout << circularQueue.Rear() << endl;      // 返回 4
    return 0;
}


/*
时间复杂度：O(1)
空间复杂度：O(n)
*/