/*The complete lifecycle of a max_heap*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int MAX_NUMBER = 1000000000;

struct heap {
    int * arr;
    int size;
    int capacity;
};

struct heap* CreatHeap (int maxsize) {
	struct heap* H = (struct heap*) malloc (sizeof(struct heap));
	if (!H) {
        return NULL;
    }
    H -> arr = (int*) malloc ((maxsize + 1) * sizeof (int));
	if (!H -> arr) {
		free(H);
		return NULL;
	}
    H -> size = 0;
	H -> capacity = maxsize;
    H -> arr[0] = MAX_NUMBER;
    return H;
}

bool IsHeapEmpty (struct heap* H) {
    if (H -> size == 0){
        return true;
    } else {
        return false;
    }
}

bool IsHeapFull (struct heap* H) {
    if (H -> size == H -> capacity) {
        return true;
    } else {
        return false;
    }
}

void PushHeap (int x, struct heap* H) {
    if (IsHeapFull(H)) { 
        printf("Heap is full\n");
        return;
    }
    int i = ++H->size;
    for( ; x > H->arr[i/2]; i /= 2) {
        H -> arr[i] = H -> arr[i/2];
    }
    H -> arr[i] = x;
}

// void ReadMaxNum (struct heap* H) {
//     if (IsHeapEmpty(H)) {
//         printf("Heap is empty\n");
//         return;
//     }
//     return H -> arr[1];
// }

int PopHeapMax (struct heap* H) {
    if (IsHeapEmpty(H)) {
        printf("Heap is empty\n");
        return -1;
    }
    int maxnum = H -> arr[1];
    int x = H -> arr[H -> size--];
    int parent = 1;
    int child = parent * 2;
    for ( ; parent * 2 <= H -> size; parent = child) {
        child = parent * 2;
        if ( child != H-> size && H->arr[child] < H->arr[child + 1]) {
            child++;
        }
        if (x < H -> arr[child]){
            H -> arr[parent] = H -> arr[child];
        } else {
            break;
        }
    }
    H -> arr[parent] = x;
    return maxnum;
}

void FreeHeap (struct heap* H) {
    free(H -> arr);
    free(H);
}

int main() {
    struct heap* H = CreatHeap(100);
    PushHeap(10, H);
    PushHeap(20, H);
    PushHeap(30, H);
    PushHeap(70, H);
    PushHeap(80, H);
    PushHeap(60, H);
    PushHeap(90, H);
    PushHeap(100, H);
    PushHeap(140, H);
    PushHeap(120, H);
    PushHeap(160, H);
    PushHeap(150, H);
    PushHeap(170, H);
    int maxnum = PopHeapMax(H);
    printf("maxnum: %d\n", maxnum);
    maxnum = PopHeapMax(H);
    printf("maxnum: %d\n", maxnum);
    maxnum = PopHeapMax(H);
    printf("maxnum: %d\n", maxnum);
    maxnum = PopHeapMax(H);
    printf("maxnum: %d\n", maxnum);
    maxnum = PopHeapMax(H);
    printf("maxnum: %d\n", maxnum);
    maxnum = PopHeapMax(H);
    printf("maxnum: %d\n", maxnum);
    maxnum = PopHeapMax(H);
    printf("maxnum: %d\n", maxnum);
    maxnum = PopHeapMax(H);
    printf("maxnum: %d\n", maxnum);
    maxnum = PopHeapMax(H);
    printf("maxnum: %d\n", maxnum);
    maxnum = PopHeapMax(H);
    printf("maxnum: %d\n", maxnum);
    maxnum = PopHeapMax(H);
    printf("maxnum: %d\n", maxnum);
    FreeHeap(H);
    return 0;
}




