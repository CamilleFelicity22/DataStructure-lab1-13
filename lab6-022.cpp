#include <iostream>
#include <queue>
#include <unordered_set>
#include <vector>

using namespace std;

class State {
public:
    State(string s) : board(s) {}
    bool operator==(const State& other) const {
        return board == other.board;
    }
    bool isGoal() const {
        return board == "12345678x";
    }
    vector<State> getNextStates() const {
        vector<State> nextStates;
        int pos = board.find('x');
        int x = pos / 3;
        int y = pos % 3;
        
        // 上下左右移动
        int dx[] = {-1, 1, 0, 0};
        int dy[] = {0, 0, -1, 1};
        
        for (int i = 0; i < 4; ++i) {
            int newX = x + dx[i];
            int newY = y + dy[i];
            if (newX >= 0 && newX < 3 && newY >= 0 && newY < 3) {
                string nextBoard = board;
                swap(nextBoard[x * 3 + y], nextBoard[newX * 3 + newY]);
                nextStates.push_back(State(nextBoard));
            }
        }
        
        return nextStates;
    }
    string getBoard() const {
        return board;
    }

private:
    string board;
};

int find(string start) {
    State initialState(start);
    
    if (initialState.isGoal()) return 0;

    unordered_set<string> visited;
    queue<pair<State, int > > q;
    q.push(make_pair(initialState, 0));
    visited.insert(initialState.getBoard());

    while (!q.empty()) {
        State current = q.front().first;
        int steps = q.front().second;
        q.pop();

        vector<State> nextStates = current.getNextStates();
        for (const auto& nextState : nextStates) {
            if (nextState.isGoal()) {
                return steps + 1;
            }
            if (visited.find(nextState.getBoard()) == visited.end()) {
                q.push(make_pair(nextState, steps + 1));
                visited.insert(nextState.getBoard());
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