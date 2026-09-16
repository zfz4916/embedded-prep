#include <stdio.h>
#include <stdlib.h>

 struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
 };

int countNodes(struct TreeNode* node);
