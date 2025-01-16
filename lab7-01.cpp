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

// 层序遍历函数
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

//去除末尾的null
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
// 构建二叉树的类
class Solution
{
private:
    unordered_map<int, int> inorder_map; // 中序遍历中值和索引的映射

    TreeNode *buildTreeHelper(vector<int> &preorder, int preStart, int preEnd, int inStart, int inEnd)
    {
        // 检查递归结束条件，索引越界，返回nullptr
        if (preStart > preEnd || inStart > inEnd)
        {
            return nullptr;
        }

        // 前序遍历的第一个元素是当前子树的根节点，获取当前根节点的值
        int rootVal = preorder[preStart];
        TreeNode *root = new TreeNode(rootVal);

        // 在中序遍历中，根节点的左边部分是左子树，右边部分是右子树。
        //查找根节点在中序遍历中的位置inRootIndex，并计算左子树的大小 leftSubtreeSize。
        int inRootIndex = inorder_map[rootVal];
        int leftSubtreeSize = inRootIndex - inStart;

        // 递归构建左子树
        root->left = buildTreeHelper(preorder, preStart + 1, preStart + leftSubtreeSize, inStart, inRootIndex - 1);

        // 递归构建右子树
        root->right = buildTreeHelper(preorder, preStart + leftSubtreeSize + 1, preEnd, inRootIndex + 1, inEnd);

        return root;
    }

public:
    TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder)
    {
        if (preorder.empty() || inorder.empty())
            return nullptr;

        for (int i = 0; i < inorder.size(); ++i)
        {
            // 将中序遍历的值与索引位置存储在哈希表中，方便接下来递归的时候找到根节点
            inorder_map[inorder[i]] = i;
        }

        return buildTreeHelper(preorder, 0, preorder.size() - 1, 0, inorder.size() - 1);
    }
};

int main()
{
    Solution s;
    
    vector<int> preorder;
    preorder.push_back(3);
    preorder.push_back(9);
    preorder.push_back(20);
    preorder.push_back(15);
    preorder.push_back(7);
    

    vector<int> inorder;
    inorder.push_back(9);
    inorder.push_back(3);
    inorder.push_back(15);
    inorder.push_back(20);
    inorder.push_back(7);
    
   
    TreeNode *root = s.buildTree(preorder, inorder);

    if (root != nullptr)
    {
        levelOrder(root); 
    }
    else
    {
        cout << "Failed to build tree" << endl;
    }

    return 0;
}

/*
时间复杂度：O(n)
空间复杂度：O(n)
*/