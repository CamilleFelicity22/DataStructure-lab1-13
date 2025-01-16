#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>

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

TreeNode *buildTree(const vector<string> &nodes)
{
    if (nodes.empty() || nodes[0] == "null")
    {
        return nullptr; // 如果节点列表为空或第一个节点是null，返回空树
    }

    TreeNode *root = new TreeNode(stoi(nodes[0])); // 根节点
    queue<TreeNode *> q;                           // 队列用于层序构造
    q.push(root);
    int i = 1; // 指向下一个节点的位置

    while (!q.empty() && i < nodes.size())
    {
        TreeNode *current = q.front(); // 当前处理的节点
        q.pop();

        // 如果当前节点为空，需要在队列中插入两个null占位符来维持层序结构
        if (current == nullptr)
        {
            q.push(nullptr); // 左子节点的占位符
            q.push(nullptr); // 右子节点的占位符
            i += 2;
            continue;
        }

        // 构造左子节点
        if (i < nodes.size())
        {
            if (nodes[i] != "null")
            {
                current->left = new TreeNode(stoi(nodes[i])); // 非null值构造子节点
                q.push(current->left);                        // 左子节点加入队列
            }
            else
            {
                current->left = nullptr; // null值则将左子节点置为空
                q.push(nullptr);         // 左子节点的占位符加入队列
            }
        }
        i++;

        // 构造右子节点
        if (i < nodes.size())
        {
            if (nodes[i] != "null")
            {
                current->right = new TreeNode(stoi(nodes[i])); // 非null值构造子节点
                q.push(current->right);                        // 右子节点加入队列
            }
            else
            {
                current->right = nullptr; // null值则将右子节点置为空
                q.push(nullptr);          // 右子节点的占位符加入队列
            }
        }
        i++;
    }

    return root; // 返回构造好的树的根节点
}

// 你可以通过修改结构来完成本Lab。
// main函数，头文件，Solution类可以自行添加。
TreeNode* pruneTree(TreeNode* root) {
     // 如果当前节点为空，直接返回空节点
    if (root == nullptr) {
        return nullptr;
    }

    // 递归处理左子树
    root->left = pruneTree(root->left);
    // 递归处理右子树
    root->right = pruneTree(root->right);

    // 如果当前节点的值为0，并且左右子树都为空，说明该子树不包含1，进行剪枝（返回空节点）
    if (root->val == 0 && root->left == nullptr && root->right == nullptr) {
        return nullptr;
    }

    // 否则，返回当前节点
    return root;
}


int main()
{
    vector<string> nodes;
    nodes.push_back("1");
    nodes.push_back("null");
    nodes.push_back("0");
    nodes.push_back("null");
    nodes.push_back("null");
    nodes.push_back("0");
    nodes.push_back("1");
    /*nodes.push_back("1");
    nodes.push_back("1");
    nodes.push_back("0");
    nodes.push_back("1");
    nodes.push_back("1");
    nodes.push_back("0");
    nodes.push_back("1");
    nodes.push_back("0");*/
    TreeNode *root = buildTree(nodes);
    levelOrder(root);
    pruneTree(root);
    levelOrder(root);
    return 0;
}

/*
时间复杂度：O(n)
空间复杂度：O(n)
*/