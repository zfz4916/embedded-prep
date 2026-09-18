#include <stdio.h>
#include <stdlib.h>

/*
Implement Binary Search Using a Binary Tree
*/

struct Node {
    int val;
    struct Node* left;
    struct Node* right;
};

struct Node* CreatNode (int value, struct Node* BST) {
    if (!BST) {
        BST = (struct Node*)malloc(sizeof(struct Node));
        BST -> val = value;
        BST -> left = NULL;
        BST -> right = NULL;
        return BST;
    }
    if (value < BST -> val) {
        BST -> left = CreatNode(value, BST -> left);
    } else if (value > BST -> val) {
        BST -> right = CreatNode(value, BST -> right);
    }
    return BST;
}

struct Node* SearchNode (int value, struct Node* BST) {
    if (!BST) {
        return NULL;
    }
    if (value < BST -> val) {
        return SearchNode(value, BST -> left);
    } else if (value > BST -> val) {
        return SearchNode(value, BST -> right);
    } else {
        return BST;
    }
}

struct Node* DeleteNode (int value, struct Node* BST) {
    if (!BST) {
        printf("The node is not in the BST\n");
        return NULL;
    }
    if (value < BST -> val) {
        BST -> left = DeleteNode(value, BST -> left);
    } else if (value > BST -> val) {
        BST -> right = DeleteNode(value, BST -> right);
    } else {
        if (BST -> left && BST -> right) {
            struct Node* temp = BST -> right;
            while (temp -> left) {
                temp = temp -> left;
            }
            BST -> val = temp -> val;
            BST -> right = DeleteNode(temp -> val, BST -> right);
        } else {
            struct Node* child = BST->left ? BST->left : BST->right;
            free(BST);
            return child; 
        }
    }
    return BST;
}

void Inorder(struct Node* BST) {
    if (!BST) return;
    Inorder(BST->left);
    printf("%d ", BST->val);
    Inorder(BST->right);
}

int main(void) {
    int a[] = {50, 30, 70, 20, 40, 60, 80};
    struct Node* root = NULL;
    for (int i = 0; i < 7; i++) root = CreatNode(a[i], root);
    Inorder(root); printf("\n");            /* 期望：20 30 40 50 60 70 80 */

    printf("%s\n", SearchNode(40, root) ? "found" : "miss");   /* found */
    printf("%s\n", SearchNode(45, root) ? "found" : "miss");   /* miss  */

    root = DeleteNode(20, root);   /* 删叶子 */
    root = DeleteNode(30, root);   /* 删单孩子……本树30有两个，换成删40测单孩子 */
    root = DeleteNode(50, root);   /* 删两个孩子（根） */
    Inorder(root); printf("\n");   /* 每删一次打一遍，看升序是否保持 */
    return 0;
}
