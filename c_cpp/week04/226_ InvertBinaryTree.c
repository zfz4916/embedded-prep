/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
void Change(struct TreeNode* root) {
    struct TreeNode* node = NULL;
    if (root) {
        node = root -> left;
        root -> left = root -> right;
        root -> right = node;
        Change(root->left);
        Change(root->right);
    }
}

struct TreeNode* invertTree(struct TreeNode* root) {
    Change(root);
    return root;
}