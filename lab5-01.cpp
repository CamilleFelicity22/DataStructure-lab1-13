#include <cstdio>
#include <iostream>
#include <string>
#include <stack>
#include <algorithm>
using namespace std;

string removeDuplicates(string s, int k)
{
    // 栈中存储字符及其连续出现的次数
    stack<pair<char, int > > st;

    // 遍历字符串的每一个字符
    for (char c : s) {
        // 如果栈为空或者栈顶字符不等于当前字符
        if (st.empty() || st.top().first != c) {
            st.push(make_pair(c, 1));  // 新字符入栈，计次数为1
        } else {
            st.top().second++;  // 栈顶字符与当前字符相同，增加计数
            if (st.top().second == k) {
                st.pop();  // 如果计数等于k，则弹出该字符
            }
        }
    }
    string result;
    while (!st.empty()) {
        result.append(st.top().second, st.top().first);  // 追加栈中每个字符出现的次数
        st.pop();
    }

    // 由于出栈的顺序是反的，所以要反转字符串
    reverse(result.begin(), result.end());
    
    return result;

}

int main()
{
    string s = "deeedbbcccbdaa";
    int k = 3;
    cout << removeDuplicates(s, k) << endl;
    return 0;
}

/*
时间复杂度：O(n)
空间复杂度：O(1)
*/
