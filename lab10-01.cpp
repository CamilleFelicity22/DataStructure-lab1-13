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

// 递归获得现在的高度
int getHeight(TreeNode *root){
    if(root == nullptr) return 0;
    return 1 + max(getHeight(root->left), getHeight(root->right));
}

//判断是否为二叉搜索树
bool isBST(TreeNode *root,int min,int max) {
    if (root == nullptr) return true;
    if(root->val <= min || root->val >= max) return false;
    if (!isBST(root->left,min,root->val)) return false;
    if (!isBST(root->right,root->val,max)) return false;
    return true;
}
bool isBST(TreeNode *root) {
    return isBST(root, INT_MIN, INT_MAX); // 初始化最小值和最大值
}

//判断是否平衡
bool isBalanced(TreeNode *root) {
    if (root == nullptr) return true;
    int left = getHeight(root->left);
    int right = getHeight(root->right);
    if (abs(left - right) > 1)
        return false;
    return isBalanced(root->left) && isBalanced(root->right);   //递归查找左子树和右子树是不是平衡的
}

bool isAVL(TreeNode *root)
{
    if(root == nullptr) return true;
    if(!isBST(root)) return false;
    return isBalanced(root);
}

int main()
{
    // vector<string> nodes = {"2", "1", "3"}; // true
    // vector<string> nodes = {"1", "2", "2", "3", "3", "null", "null", "4", "4"}; // false
    // vector<string> nodes = {"5", "4", "6", "null", "null", "3", "7"}; // false
    vector<string> nodes;
    nodes.push_back("2");
    nodes.push_back("1");
    nodes.push_back("3");
    /*nodes.push_back("3");
    nodes.push_back("3");
    nodes.push_back("null");
    nodes.push_back("null");

    nodes.push_back("4");
    nodes.push_back("4");*/
    TreeNode *root = buildTree(nodes);
    cout << isAVL(root) << endl;

    return 0;
}

//时间复杂度O(n^2)