#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

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
    printf("===== 1. 创建 + 三种遍历 =====\n");
    {
        int a[] = {50, 30, 70, 20, 40, 60, 80, 35, 45, 65};
        int n = (int)(sizeof(a) / sizeof(a[0]));
        struct Node *root = createFromArray(a, n);
        assert(root != NULL);

        printf("  前序: "); preorder(root);  printf("\n");
        printf("  中序: "); inorder(root);   printf("\n");
        printf("  后序: "); postorder(root); printf("\n");

        freeTree(root);
    }

    printf("\n===== 2. 查询：命中 / 未命中 =====\n");
    {
        int a[] = {50, 30, 70, 20, 40, 60, 80, 35, 45, 65};
        int n = (int)(sizeof(a) / sizeof(a[0]));
        struct Node *root = createFromArray(a, n);

        struct Node *hit  = search(root, 40);
        struct Node *miss = search(root, 99);
        assert(hit  != NULL);
        assert(hit->val == 40);
        assert(miss == NULL);
        printf("  search(40) 命中, search(99) 未命中 ✅\n");

        freeTree(root);
    }

    printf("\n===== 3. 插入 =====\n");
    {
        int a[] = {50, 30, 70, 20, 40, 60, 80, 35, 45, 65};
        int n = (int)(sizeof(a) / sizeof(a[0]));
        struct Node *root = createFromArray(a, n);

        root = insert(root, 55);
        root = insert(root, 10);

        printf("  插入 55,10 后中序: ");
        inorder(root);
        printf("\n");

        freeTree(root);
    }

    printf("\n===== 4. 删除：叶子 / 单孩子 / 双孩子 =====\n");
    {
        int a[] = {50, 30, 70, 20, 40, 60, 80, 35, 45, 65, 55, 10};
        int n = (int)(sizeof(a) / sizeof(a[0]));
        struct Node *root = createFromArray(a, n);

        printf("  初始中序: "); inorder(root); printf("\n");

        delete(&root, 35);
        printf("  删 35 后: "); inorder(root); printf("\n");

        delete(&root, 60);
        printf("  删 60 后: "); inorder(root); printf("\n");

        delete(&root, 30);
        printf("  删 30 后: "); inorder(root); printf("\n");

        freeTree(root);
    }

    printf("\n===== 5. 删除根节点 =====\n");
    {
        int a[] = {50, 30, 70, 20, 40, 60, 80, 35, 45, 65, 55, 10};
        int n = (int)(sizeof(a) / sizeof(a[0]));
        struct Node *root = createFromArray(a, n);

        delete(&root, 50);
        printf("  删 50 后中序: "); inorder(root); printf("\n");

        freeTree(root);
    }

    printf("\n===== 6. 删除 20，期望 10 40 45 55 65 70 80 =====\n");
    {
        int a[] = {55, 40, 70, 10, 45, 65, 80, 20};
        int n = (int)(sizeof(a) / sizeof(a[0]));
        struct Node *root = createFromArray(a, n);

        printf("  初始中序: "); inorder(root); printf("\n");

        delete(&root, 20);
        printf("  删 20 后: "); inorder(root); printf("\n");

        int expected[] = {10, 40, 45, 55, 65, 70, 80};
        int exp_n = (int)(sizeof(expected) / sizeof(expected[0]));

        int got[16];
        int got_n = 0;
        struct Node *stack[16];
        int top = 0;
        struct Node *cur = root;
        while (cur || top > 0) {
            while (cur) { stack[top++] = cur; cur = cur->left; }
            cur = stack[--top];
            got[got_n++] = cur->val;
            cur = cur->right;
        }

        assert(got_n == exp_n);
        for (int i = 0; i < exp_n; i++) {
            assert(got[i] == expected[i]);
        }
        printf("  期望序列完全匹配 ✅\n");

        freeTree(root);
    }

    printf("\n===== 7. solo 单节点：newNode(7) → delete → NULL =====\n");
    {
        struct Node *solo = newNode(7);
        assert(solo != NULL);
        assert(solo->val == 7);
        assert(solo->left == NULL);
        assert(solo->right == NULL);

        delete(&solo, 7);
        assert(solo == NULL);

        printf("  单节点删除后 solo == NULL ✅\n");
    }

    printf("\n===== ALL PASSED =====\n");
    return 0;
}