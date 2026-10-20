#include <stdio.h>
#include <stdlib.h>


struct Node {
    int val;
    struct Node * left;
    struct Node * right;
};


struct Node *newNode(int val) {
    struct Node *n = (struct Node *)malloc(sizeof(struct Node));
    if (!n) return NULL;
    n->val   = val;
    n->left  = NULL;
    n->right = NULL;
    return n;
}

struct Node * insert(struct Node * root, int val) {
    if (root == NULL) {
        return newNode(val);
    }
    if (root->val > val) {
        root->left = insert(root->left, val);
    } else {
        root->right = insert(root->right, val);
    }
    return root;
}

struct Node * search(struct Node * root, int val) {
    if (root == NULL) {
        return NULL;
    }
    if (root->val == val) {
        return root;
    }
    if (root->val > val) {
        return search(root->left, val);
    } else {
        return search(root->right, val);
    }
}

void delete(struct Node **root, int val) {
    if (*root == NULL) return;

    if ((*root)->val > val) {
        delete(&(*root)->left, val);
    } else if ((*root)->val < val) {
        delete(&(*root)->right, val);
    } else {
        struct Node *cur = *root;

        if (cur->left && cur->right) {
            struct Node *tmp = cur->right;
            while (tmp->left) tmp = tmp->left;

            cur->val = tmp->val;
            delete(&cur->right, tmp->val);
        } else {
            /* 0 或 1 个孩子 */
            struct Node *child = cur->left ? cur->left : cur->right;
            *root = child;
            free(cur);
        }
    }
}

void preorder (struct Node * root) {
    if (root == NULL) {
        return;
    }
    printf("%d ", root->val);
    preorder(root->left);
    preorder(root->right);
}

void inorder (struct Node * root) {
    if (root == NULL) {
        return;
    }
    inorder(root->left);
    printf("%d ", root->val);
    inorder(root->right);
}

void postorder (struct Node * root) {
    if (root == NULL) {
        return;
    }
    postorder(root->left);
    postorder(root->right);
    printf("%d ", root->val);
}

void freeTree(struct Node *root) {
    if (!root) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

struct Node *createFromArray(int a[], int n) {
    struct Node *root = NULL;
    for (int i = 0; i < n; i++) {
        root = insert(root, a[i]);
    }
    return root;
}

int main(void) {
    int a[] = {50, 30, 70, 20, 40, 60, 80, 35, 45, 65};
    int n = (int)(sizeof(a) / sizeof(a[0]));
 
    struct Node *root = createFromArray(a, n);
    printf("创建完成，共 %d 个节点\n\n", n);

    preorder(root);  
    printf("\n");
    inorder(root);   
    printf("\n");
    postorder(root); 
    printf("\n\n");


    struct Node *hit  = search(root, 40);
    struct Node *miss = search(root, 99);
    printf("search(40): %s\n", hit  ? "找到" : "未找到");
    printf("search(99): %s\n\n", miss ? "找到" : "未找到");


    root = insert(root, 55);
    root = insert(root, 10);
    printf("插入 55, 10 后中序: ");
    inorder(root);
    printf("\n\n");


    delete(&root, 30);
    printf("删除 30 后中序: ");
    inorder(root);
    printf("\n");

    delete(&root, 50);
    printf("删除 50 后中序: ");
    inorder(root);
    printf("\n");

    delete(&root, 99);
    printf("删除 99 后中序: ");
    inorder(root);
    printf("\n\n");


    freeTree(root);
    printf("释放完成\n");
    return 0;
}