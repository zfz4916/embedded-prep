/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
//采用后序交换
void ChangeNode(struct TreeNode* root) {
    if (root) {
        ChangeNode(root -> left);
        ChangeNode(root -> right);
        struct TreeNode* a = root -> left;
        root -> left = root -> right;
        root -> right = a;
    }
}
struct TreeNode* flipTree(struct TreeNode* root) {
    ChangeNode(root);
    return root;
}