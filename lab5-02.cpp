#include <cstdio>
#include <iostream>
#include <stack>
using namespace std;

class MyQueue
{
private:
    stack<int> s1;
    stack<int> s2;
     // 辅助函数：将s1中的所有元素移动到s2
    void transfer()
    {
        while (!s1.empty())
        {
            s2.push(s1.top());
            s1.pop();
        }
    }

public:
    MyQueue()
    {
    }

    void push(int x)
    {
        s1.push(x);
    }

    int pop()
    {
        // 如果s2为空，则将s1中的元素转移到s2
        if (s2.empty())
        {
            transfer();
        }
        // 弹出并返回s2的栈顶元素（即队列的开头元素）
        int topVal = s2.top();
        s2.pop();
        return topVal;
    }

    int peek()
    {
        if (s2.empty())
            {
                transfer();
            }
            return s2.top();
    }

    bool empty()
    {
        // 当s1和s2都为空时，队列为空
        if(s1.empty() && s2.empty()) return true;
        return false;
    }
};

int main()
{
    MyQueue q;
    q.push(1);
    q.push(2);
    cout << q.peek() << endl; // 返回1
    cout << q.pop() << endl;  // 返回1
    q.push(3);
    cout << q.pop() << endl;   // 返回2
    cout << q.pop() << endl;   // 返回3
    cout << q.empty() << endl; // 返回1
    return 0;
}

/* 
时间复杂度：O(1)
空间复杂度：O(n)
*/