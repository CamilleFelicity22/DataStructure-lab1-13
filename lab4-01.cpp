#include <cstdio>
#include <string>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// 检查 word 是否为 T 的子序列
bool isSubsequence(const string &T, const string &word) {
    int tIndex = 0, wIndex = 0;
    
    // 遍历字符串 T
    while (tIndex < T.size() && wIndex < word.size()) {
        // 如果 T 的当前字符和 word 的当前字符相同，移动 word 的指针
        if (T[tIndex] == word[wIndex]) {
            wIndex++;
        }
        // 始终移动 T 的指针
        tIndex++;
    }
    
    // 如果 word 的指针指向末尾，说明成功匹配整个单词
    return wIndex == word.size();
}

// 计算 words 中是 T 子序列的单词个数
int numMatchingSubseq(const string &T, const vector<string> &words) {
    int count = 0;
    
    // 对每个单词进行子序列检查
    for (const string &word : words) {
        if (isSubsequence(T, word)) {
            count++;
        }
    }
    
    return count;
}

int main() {
    // 自定义输入
    string T;
    cout << "请输入字符串 T：" << endl;
    cin >> T;

    int numWords;
    cout << "请输入单词数量：" << endl;
    cin >> numWords;

    vector<string> words(numWords);
    cout << "请输入单词数组：" << endl;
    for (int i = 0; i < numWords; ++i) {
        cin >> words[i];
    }

    // 调用 numMatchingSubseq 函数计算结果并输出
    int result = numMatchingSubseq(T, words);

    cout << "子序列单词的数量为：" << result << endl;

    return 0;
}



/*
时间复杂度：
O(m * n)。
空间复杂度：
由于没有使用任何额外的数据结构，空间复杂度为 O(1)。
*/