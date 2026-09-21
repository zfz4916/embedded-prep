//max heap
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

struct Heap {
    int* data;
    int size;
    int capacity;
};
//default data[0] = MaxSize


struct Heap* CreateHeap(int cap) {
    struct Heap* h = malloc(sizeof(struct Heap));
    h->data = malloc(sizeof(int) * (cap + 1));
    h->data[0] = INT_MAX;
    h->size = 0;  h->capacity = cap;
    return h;
}

bool IsAvailable (struct Heap* heap) {
    if (heap -> size == heap -> capacity){
        return false;
    }
    return true;
}

void PushHeap (struct Heap* heap, int value) {
    if (!IsAvailable(heap)) {
        return;
    }
    int i = heap -> size ++;

    for (; heap -> data[i/2] < value; i /= 2) {
        heap -> data[i] = heap -> data[i/2];
    }
    heap -> data[i] = value;
}

struct Heap PopHeap (struct Heap* heap) {
    if (heap -> size == 0) {
        return;
    }

    int ret = heap -> data[1];
    int temp = heap -> data[heap -> size --];
    int parent = 1;
    for (; parent * 2 <= heap -> size; parent = child) {
        int child = parent * 2;
        if ((child != heap -> size) && (heap -> data[child] < heap -> data[child + 1])){
            child ++;
        }
        if (temp > heap -> data[child]) {
            break;
        } else {
            heap -> data[parent] = heap -> data[child];
        }
    }
    heap -> data[parent] = temp;
    return ret;
}

int PeekHeap (struct Heap* heap) {
    if (heap -> size == 0) {
        return -1;
    }
    return heap -> data[1];
}