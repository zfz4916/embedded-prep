/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
struct TreeNode* deleteNode(struct TreeNode* root, int key) {
    if(!root) {
        return NULL;
    }
    if (key < root -> val) {
        root -> left = deleteNode(root -> left, key);
    } else if (key > root -> val) {
        root -> right = deleteNode(root -> right, key);
    } else {
        struct TreeNode* child = NULL;
        if (root->left && root->right) {
            child = root -> right;
            while (child -> left) {
                child = child -> left;
            }
            root -> val = child -> val;
            root -> right = deleteNode(root -> right, child -> val);
        } else {
            child = root -> left ? root -> left : root -> right;
            free(root);
            return child;
        }
    }
    return root;
}