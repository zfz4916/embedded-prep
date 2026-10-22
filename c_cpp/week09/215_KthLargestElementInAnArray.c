#include <stdlib.h>
#include <limits.h>


struct Heap {
    int * data;
    int size;
    int capacity;
};

void BuildHeap (struct Heap * head) {
    if (head == NULL || head -> size <= 1) {
        return;
    }

    for (int i = (head -> size) / 2; i > 0; i--) {
        int parent = i;
        int child = parent * 2;
        int tmp = head -> data[parent];

        while (child <= head -> size) {
            if(child < head -> size && head -> data[child] < head -> data[child + 1]) {
                child ++;
            }
            if (tmp >= head -> data[child]) {
                break;
            } else {
                head -> data[parent] = head -> data[child];
                parent = child;
                child = parent * 2;
            }
        }
        head -> data[parent] = tmp;
    }    
}

struct Heap * CreatHeap (int * nums, int numsSize) {
    struct Heap * head = (struct Heap *)malloc(sizeof(struct Heap));
    head -> data = (int *)malloc((numsSize + 1) * sizeof (int));
    head -> data[0] = INT_MAX;
    head -> size = 0;
    head -> capacity = numsSize;

    for (int i = 1; i <= head -> capacity; i++) {
        head -> size ++;
        head -> data[i] = nums[i-1];
    }

    BuildHeap(head);
    return head;
}

int PopHeap (struct Heap * head) {
    if (head == NULL || head -> size < 1) {
        return -1;
    }
    int ret = head -> data[1];

    int tmp = head -> data[head -> size --];

    int parent = 1;
    int child = parent * 2;
    while (child <= head -> size) {
        if (child < head -> size && head -> data[child] < head -> data[child 
        + 1]) {
            child ++;
        }
        if (tmp >= head -> data[child]) {
            break;
        } else {
            head -> data[parent] = head -> data[child];
            parent = child;
            child *= 2;
        }
    }
    head -> data[parent] = tmp;

    return ret;
}

int findKthLargest(int* nums, int numsSize, int k) {
    struct Heap * head = CreatHeap(nums, numsSize);
    int maxk = 0;
    for (int i = 0; i < k; i ++){
        maxk = PopHeap(head);
    }

    free(head->data);
    free(head);

    return maxk;
}