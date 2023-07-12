#pragma once

#include <vector>
#include <numeric>
#include <algorithm>
#include <queue>

using namespace std;

// 前序遍历
vector<int> preorderTraversal(TreeNode* root);

// 层序遍历
vector<vector<int>> levelOrder(TreeNode* root);

// 最大深度
int maxDepth(TreeNode* root);

struct TreeNode
{
    int val;
    TreeNode* left;
    TreeNode* right;

    TreeNode() :val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) :val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) :val(x), left(left), right(right) {}
};

void preorder(TreeNode* root, vector<int>& res) 
{
    if (!root)
        return;

    res.push_back(root->val);
    preorder(root->left, res);
    preorder(root->right, res);
}
vector<int> preorderTraversal(TreeNode* root) 
{
    vector<int> res;
    preorder(root, res);
    return res;
}

vector<vector<int>> levelOrder(TreeNode* root)
{
    vector<vector<int>>res;
    queue<TreeNode*>que;
    if (!root)
        return res;

    que.push(root);
    while (!que.empty()) {
        int length = que.size();
        res.push_back(vector<int>());

        for (int i = 0; i < length; ++i) {
            auto node = que.front();
            que.pop();
            res.back().push_back(node->val);

            if (node->left) que.push(node->left);
            if (node->right) que.push(node->right);
        }
    }
    return res;
}

int maxDepth(TreeNode* root) 
{
    if (root == nullptr) 
        return 0;
    return max(maxDepth(root->left), maxDepth(root->right)) + 1;
}