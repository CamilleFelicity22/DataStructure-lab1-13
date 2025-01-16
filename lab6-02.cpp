#include <iostream>
#include <algorithm>
#include <queue>
#include <unordered_set>

using namespace std;

int find(string start) {
    string end = "12345678x";
    
    if (start == end) return 0;
    //这里用一个队列q，来存储每一步的状态和已使用的步数
    queue<pair<string, int > > q;
    //already记录之前的状态，避免在搜索时重复处理相同的状态
    unordered_set<string> already;

    q.push(make_pair(start, 0));
    already.insert(start);

    while (!q.empty()) {
        //取出队列里第一个状态和步数
        string current = q.front().first;
        int steps = q.front().second;
        q.pop();
        // 先找到x在的位置
        int p = current.find('x');
        int x = p / 3;
        int y = p % 3;

        int dx[] = {-1, 1, 0, 0};
        int dy[] = {0, 0, -1, 1};

        for (int i = 0; i < 4; ++i) {
            int X = x + dx[i];
            int Y = y + dy[i];
            if (X >= 0 && X < 3 && Y >= 0 && Y < 3) {
                //复制当前状态current到next，然后交换x和目标位置的字符，生成新的状态next。
                string next = current;
                swap(next[x * 3 + y], next[X * 3 + Y]);
                if (next == end) {
                    return steps + 1;
                }
                if (already.find(next) == already.end()) {
                    q.push(make_pair(next, steps + 1));
                    already.insert(next);
                }
            }
        }
    }
    return -1;
}

int main() {
    string start;
    for (int i = 0; i < 9; i++) {
        char c;
        cin >> c;
        start += c;
    }

    cout << find(start) << endl;

    return 0;
}
/*
时间复杂度：O(1)
空间复杂度：O(n)
*/