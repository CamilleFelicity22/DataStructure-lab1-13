#include <iostream>
#include <vector>
#include <queue>
#include <map>

using namespace std;

// Definition for a binary tree node.
struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

void levelOrder(TreeNode *root)
{
    if (!root)
    {
        cout << "[]" << endl;
        return;
    }

    queue<TreeNode *> q;
    q.push(root);
    int remaining = 1;
    vector<string> result;

    while (!q.empty() && remaining > 0)
    {
        TreeNode *current = q.front();
        q.pop();

        if (current == nullptr)
        {
            result.push_back("null");
            q.push(nullptr);
            q.push(nullptr);
        }
        else
        {
            result.push_back(to_string(current->val));
            remaining--;
            q.push(current->left);
            if (current->left != nullptr)
                remaining++;
            q.push(current->right);
            if (current->right != nullptr)
                remaining++;
        }
    }

    while (!result.empty() && result.back() == "null")
    {
        result.pop_back();
    }

    cout << "[";
    for (size_t i = 0; i < result.size(); ++i)
    {
        cout << result[i];
        if (i != result.size() - 1)
        {
            cout << ", ";
        }
    }
    cout << "]" << endl;
}

// 你可以通过修改结构来完成本Lab。
// main函数，头文件，Solution类可以自行添加。
class Solution
{
public:
    vector<TreeNode *> generateTrees(int n)
    {
        if(n == 0) return vector<TreeNode *>();
        return generate(1, n);    //传入1和n，作为开始和结束值
    }
    private:
    vector<TreeNode *> generate(int start, int end) {
        vector<TreeNode *> alltree;
        if(start > end) {
            alltree.push_back(nullptr);
            return alltree;
        }
        for(int i = start; i <= end; i++) {
            vector<TreeNode *> left = generate(start, i - 1);  // 生成所有可能的左子树
            vector<TreeNode *> right = generate(i + 1, end);   // 生成所有可能的右子树
            for(TreeNode *l : left) {
                for(TreeNode *r : right) {
                    // 创建一个以i为根节点的当前树
                    TreeNode *root = new TreeNode(i);
                    /*
                    将生成的左子树和右子树分别挂载到当前树的左、右子节点上
                    */
                    root->left = l;
                    root->right = r;
                    alltree.push_back(root);
                }
            }
        }
        return alltree;
    }
};

int main()
{
    Solution s;
    vector<TreeNode *> res = s.generateTrees(3);
    for (auto &root : res)
    {
        levelOrder(root);
    }
    return 0;
}
/*
时间复杂度：O(n^2)
空间复杂度：O(n)
*/