#include <iostream>
#include <vector>
#include <string>
using namespace std;

// KMP算法
vector<int> computeKMP(const string &pattern) {
    int m = pattern.size();
    vector<int> p(m, 0);
    int len = 0;   //最长的相等前后缀之间的长度
    int i = 1;     //从第二个字符开始
    while (i < m) {
        if (pattern[i] == pattern[len]) {
            len++;
            p[i] = len;
            i++;
        } else {
            if (len != 0) {
                len = p[len - 1];
            } else {
                p[i] = 0;
                i++;
            }
        }
    }
    return p;
}

int repeatedStringMatch(string a, string b) {
    int n = a.size();
    int m = b.size();
    vector<int> p = computeKMP(b);
    int i = 0;
    int j = 0;
    int count = 1;
    while(i<= n*count) {
        if (a[i%n] == b[j]) {
            i++;
            j++;
            if (j == m) {
                return (i+n-1)/n;
            }
            
        } else {
            if (j != 0) {
                j = p[j - 1];
            } else {
                i++;
            }
        }
        if (j == m) {
            return count;
        }
        if(i >= n*count && j != 0) {
            count++;
    }
    }

    /*int maxRepeats = (m / n) + 2; // 最多重复次数，向上取整再加一
    string repeatedA = "";
    for (int i = 1; i <= maxRepeats; i++) {
        repeatedA += a;
        if (repeatedA.find(b) != string::npos) {
            return i;
        }
    }*/
    return -1;
}

int main() {
    string a = "abcd";

    string b = "cdabcdab";
    cout << repeatedStringMatch(a, b) << endl;  // 输出：3

    a = "abc";
    b = "wxyz";
    cout << repeatedStringMatch(a, b) << endl;  // 输出：-1

    return 0;
}

//时间复杂度：O(m + n)
//空间复杂度：O(m）