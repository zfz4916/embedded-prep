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
    printf("===== 1. 创建：非法参数 =====\n");
    {
        struct Heap *h0 = CreatHeap(0);
        struct Heap *h1 = CreatHeap(-1);
        assert(h0 == NULL);
        assert(h1 == NULL);
        printf("  size=0 / size<0 都返回 NULL ✅\n");
    }

    printf("\n===== 2. 创建：正常空堆 =====\n");
    {
        struct Heap *H = CreatHeap(8);
        assert(H != NULL);
        assert(H->size == 0);
        assert(H->capacity == 8);
        assert(H->data[0] == INT_MAX);
        assert(IsEmptyHeap(H));
        assert(!IsFullHeap(H));
        FreeHeap(H);
        printf("  空堆创建成功 ✅\n");
    }

    printf("\n===== 3. 空堆 Pop =====\n");
    {
        struct Heap *H = CreatHeap(5);
        int v = PopHeap(H);
        assert(v == -1);
        FreeHeap(H);
        printf("  空堆 Pop 返回 -1 ✅\n");
    }

    printf("\n===== 4. 满堆：Push 被拒绝 =====\n");
    {
        struct Heap *H = CreatHeap(2);
        PushHeap(H, 5);
        PushHeap(H, 3);
        assert(IsFullHeap(H));

        PushHeap(H, 100);
        assert(H->size == 2);
        PrintHeap(H);
        FreeHeap(H);
    }

    printf("\n===== 5. Push：向上调整 =====\n");
    {
        struct Heap *H = CreatHeap(10);
        PushHeap(H, 1);
        PushHeap(H, 2);
        PushHeap(H, 3);
        PushHeap(H, 10);
        assert(H->data[1] == 10);
        PrintHeap(H);

        PushHeap(H, 0);
        PrintHeap(H);
        FreeHeap(H);
    }

    printf("\n===== 6. Pop：向下调整 =====\n");
    {
        int a[] = {9, 8, 7, 6, 5, 4, 3, 2, 1};
        int n = 9;
        struct Heap *H = CreatHeap(n);
        for (int i = 0; i < n; i++) PushHeap(H, a[i]);
        PrintHeap(H);

        int prev = INT_MAX;
        while (!IsEmptyHeap(H)) {
            int v = PopHeap(H);
            assert(v <= prev);
            printf("  pop = %d\n", v);
            prev = v;
        }
        assert(IsEmptyHeap(H));
        FreeHeap(H);
    }

    printf("\n===== 7. 单元素堆 =====\n");
    {
        struct Heap *H = CreatHeap(1);
        PushHeap(H, 42);
        assert(IsFullHeap(H));

        int v = PopHeap(H);
        assert(v == 42);
        assert(IsEmptyHeap(H));
        FreeHeap(H);
    }

    printf("\n===== 8. 全相同元素 =====\n");
    {
        struct Heap *H = CreatHeap(4);
        for (int i = 0; i < 4; i++) PushHeap(H, 5);
        for (int i = 0; i < 4; i++) {
            int v = PopHeap(H);
            assert(v == 5);
        }
        FreeHeap(H);
    }

    printf("\n===== 9. 降序输入 =====\n");
    {
        int a[] = {100, 90, 80, 70, 60, 50, 40};
        int n = 7;
        struct Heap *H = CreatHeap(n);
        for (int i = 0; i < n; i++) PushHeap(H, a[i]);

        int prev = INT_MAX;
        while (!IsEmptyHeap(H)) {
            int v = PopHeap(H);
            assert(v <= prev);
            prev = v;
        }
        FreeHeap(H);
    }

    printf("\n===== 10. 交替 Push / Pop =====\n");
    {
        struct Heap *H = CreatHeap(10);
        PushHeap(H, 5);
        PushHeap(H, 3);
        PushHeap(H, 8);

        int v1 = PopHeap(H);
        assert(v1 == 8);

        PushHeap(H, 7);

        int v2 = PopHeap(H);
        assert(v2 == 7);

        int v3 = PopHeap(H);
        assert(v3 == 5);

        int v4 = PopHeap(H);
        assert(v4 == 3);

        assert(IsEmptyHeap(H));
        FreeHeap(H);
    }

    printf("\n===== ALL PASSED =====\n");
    return 0;
}