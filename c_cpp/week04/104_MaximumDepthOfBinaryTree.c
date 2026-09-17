/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

int maxDepth(struct TreeNode* root) {
    int leftdep = 0;
    int rightdep = 0;
    if(root) {
        leftdep = 1 + maxDepth(root -> left);
        rightdep = 1 + maxDepth(root -> right);
    }
    return leftdep > rightdep ? leftdep : rightdep;
}