/*
To change a queue(array)
*/

#include <stdio.h>
#include <stdlib.h>
#include "94_BinaryTreeInorderTraversal.h"

// struct QueueNode {
//     int val;
//     struct QueueNode* next;
// };

// struct QueueNode* CreatNode (int value) {
//     QueueNode *head = (QueueNode*)malloc(maxsize * sizeof(QueueNode));
    
//     if (!head) {
//         //加打印，打印框架后面补充
//     }
//     head -> val = value;
//     head -> next = NULL;
//     return head;
// }

// void PushNodeInQueue (struct QueueNode* node) {
    
// }

int* levelOrderToArray(TreeNode* root, int* size) {
    if (!root) { *size = 0; return NULL; }

    int n = countNodes(root);
    int* arr = (int*)malloc(sizeof(int) * n);
    TreeNode** queue = (TreeNode**)malloc(sizeof(TreeNode*) * n);

    int front = 0, rear = 0;
    queue[rear++] = root;

    int idx = 0;
    while (front < rear) {
        TreeNode* cur = queue[front++];
        arr[idx++] = cur->val;
        if (cur->left)  queue[rear++] = cur->left;
        if (cur->right) queue[rear++] = cur->right;
    }

    free(queue);
    *size = n;
    return arr;
}
