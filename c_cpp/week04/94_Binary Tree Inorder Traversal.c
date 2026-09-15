/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int countNodes(struct TreeNode* node) {
    if (!node) 
        return 0;
    return 1 + countNodes(node->left) + countNodes(node->right);
}

void Recursion (struct TreeNode* node, int* arr, int* index) {
    if (node) {
        Recursion(node -> left, arr, index);
        arr[(*index)++] = node -> val;
        Recursion(node -> right, arr, index);
    }
}

int* inorderTraversal(struct TreeNode* root, int* returnSize) {
    int n = countNodes(root);            // O(n)
    int* result = (int*)malloc(sizeof(int) * n);
    int index = 0;
    Recursion(root, result, &index);       // O(n)
    *returnSize = n;
    return result;

}