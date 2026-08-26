/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    int i = 0;
    unordered_map<int, int> hashMap;
    bool findTarget(TreeNode* root, int k) {
        if (!root) return false;


        if (findTarget(root->left, k)) return true;

        int comp = k - root->val;
        if (hashMap.count(comp)) return true;
        hashMap[root->val] = i;
        i++;

        if (findTarget(root->right, k)) return true;

        return false;
    }
};