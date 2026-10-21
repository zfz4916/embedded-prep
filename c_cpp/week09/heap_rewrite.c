#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <assert.h>

struct Heap {
    int *data;
    int size;
    int capacity;
};

/* 只创建空堆，capacity = size */
struct Heap *CreatHeap(int size) {
    if (size <= 0) return NULL;

    struct Heap *head = (struct Heap *)malloc(sizeof(struct Heap));
    if (!head) return NULL;

    head->data = (int *)malloc((size + 1) * sizeof(int));
    if (!head->data) { free(head); return NULL; }

    head->size = 0;
    head->capacity = size;
    head->data[0] = INT_MAX;       /* 哨兵 */
    return head;
}

bool IsFullHeap(struct Heap *head) {
    return head->size == head->capacity;
}

bool IsEmptyHeap(struct Heap *head) {
    return head->size == 0;
}

void FreeHeap(struct Heap *head) {
    if (!head) return;
    free(head->data);
    free(head);
}

/* 插入：向上调整（大顶堆） */
void PushHeap(struct Heap *head, int value) {
    if (IsFullHeap(head)) {
        printf("  [warn] heap full, %d dropped\n", value);
        return;
    }

    int i = ++head->size;
    while (i > 1 && head->data[i / 2] < value) {
        head->data[i] = head->data[i / 2];
        i /= 2;
    }
    head->data[i] = value;
}

/* 弹出堆顶：向下调整
 * 注意：tmp > data[child] 保持你原来的写法不变
 */
int PopHeap(struct Heap *head) {
    if (head->size == 0) {
        return -1;
    }

    int ret = head->data[1];
    int tmp = head->data[head->size--];

    int parent = 1;
    int child = parent * 2;

    while (child <= head->size) {
        if (child < head->size &&
            head->data[child] < head->data[child + 1]) {
            child++;
        }
        if (tmp > head->data[child]) break;

        head->data[parent] = head->data[child];
        parent = child;
        child = parent * 2;
    }
    head->data[parent] = tmp;
    return ret;
}

void PrintHeap(struct Heap *H) {
    printf("  heap[size=%d]: ", H->size);
    for (int i = 1; i <= H->size; i++) printf("%d ", H->data[i]);
    printf("\n");
}

int main(void) {
    printf("===== 1. 创建：非法参数 =====\n");
    {
        assert(CreatHeap(0)  == NULL);
        assert(CreatHeap(-1) == NULL);
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
        assert(PopHeap(H) == -1);          /* 空堆返回 -1 */
        FreeHeap(H);
        printf("  空堆 Pop 返回 -1 ✅\n");
    }

    printf("\n===== 4. 满堆：Push 被拒绝 =====\n");
    {
        struct Heap *H = CreatHeap(2);
        PushHeap(H, 5);
        PushHeap(H, 3);
        assert(IsFullHeap(H));

        PushHeap(H, 100);                  /* 被拒绝 */
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
        PushHeap(H, 10);                   /* 应升到堆顶 */
        assert(H->data[1] == 10);
        PrintHeap(H);

        PushHeap(H, 0);                    /* 最小，沉底 */
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
        assert(PopHeap(H) == 42);
        assert(IsEmptyHeap(H));
        FreeHeap(H);
    }

    printf("\n===== 8. 全相同元素 =====\n");
    {
        struct Heap *H = CreatHeap(4);
        for (int i = 0; i < 4; i++) PushHeap(H, 5);
        for (int i = 0; i < 4; i++) assert(PopHeap(H) == 5);
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
        assert(PopHeap(H) == 8);
        PushHeap(H, 7);
        assert(PopHeap(H) == 7);
        assert(PopHeap(H) == 5);
        assert(PopHeap(H) == 3);
        assert(IsEmptyHeap(H));
        FreeHeap(H);
    }

    printf("\n===== ALL PASSED =====\n");
    return 0;
}