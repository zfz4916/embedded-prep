 
 struct Heap {
    int *data;
    int size;
    int capacity;
};

void * HeapBulid (struct Heap * head) {
    if ( head -> siize <= 1 || head == NULL) {
        return NULL;
    }

    for (int i = (head -> size) / 2; i > 0 ; i--) {
        int parent = i;
        int child = parent * 2;
        int tmp = head -> data[parent];

        while (child <= head -> size) {
            if (child < head -> size && head -> data[child] < head -> data[hild +1]) {
                child++;
            }
            if (tmp > head -> data[child]) {
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