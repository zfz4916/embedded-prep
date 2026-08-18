#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

void CreateNode(int data, struct Node* head) {
    struct Node *ptr = malloc(sizeof(struct Node));
    if (ptr == NULL) {
        fprintf(stderr, "Error: Failed to allocate memory for new node\n");
        return;
    }
    ptr->data = data;
    ptr->next = head->next;
    head->next = ptr;
}


void FreeList(struct Node* head) {
    struct Node* temp = head;
    while (temp != NULL) {
        struct Node* next = temp->next;
        free(temp);
        temp = next;
    }
    if (head->next == NULL) {
        return;
    }
}

void PrintList(struct Node* head) {
    struct Node* current = head->next;
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

int main() {
    printf("Creating a linked list with one node...\n");
    struct Node* head = NULL;
    head = malloc(sizeof(struct Node));
    if (head == NULL) {
        fprintf(stderr, "Error: Failed to allocate memory for head node\n");
        return 1;
    }
    head->data = 0; // Initialize head data
    head->next = NULL;
    CreateNode(1, head);
    PrintList(head);
    FreeList(head);
    return 0;
}