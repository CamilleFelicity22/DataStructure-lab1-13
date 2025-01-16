#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>

using namespace std;
/*比较思路：
1.如果p和q的值都小于root的值，说明p和q都在root的左子树中，于是可以将root的左子树作为下一步查找的范围。
2.如果p和q的值都大于root的值，说明p和q都在root的右子树中，于是可以将root的右子树作为下一步查找的范围。
3.如果p和q分别在root的左右子树中，那么root就是它们的最近公共祖先。也就是说，root的值大于p的值、小于q的值，或者大于q的值、小于p的值时，root即为答案。
*/
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
// main函数，头文件，函数可以自行添加。
TreeNode *lowestCommonAncestor(TreeNode *root, int a, int b)
{
    if(root == nullptr){
        return nullptr;
    }
    if(root->val == a && root->val == b){
        return root;
    }
    if(root->val > a && root->val > b){
        return lowestCommonAncestor(root->left, a, b);
    }
    if(root->val < a && root->val < b){
        return lowestCommonAncestor(root->right, a, b);
    }
    return root;

}

int main()
{
    // root = [6,2,8,0,4,7,9,null,null,3,5]
    vector<string> nodes ;
    nodes.push_back("6");
    nodes.push_back("2");
    nodes.push_back("8");
    nodes.push_back("0");
    nodes.push_back("4");
    nodes.push_back("7");
    nodes.push_back("9");
    nodes.push_back("null");
    nodes.push_back("null");
    nodes.push_back("3");
    TreeNode *root = buildTree(nodes);
    cout << lowestCommonAncestor(root, 2, 8)->val << endl; // 6
    cout << lowestCommonAncestor(root, 2, 4)->val << endl; // 2
    return 0;
}
