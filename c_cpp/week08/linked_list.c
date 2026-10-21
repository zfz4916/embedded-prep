#include <stdio.h>
#include <stdlib.h>

struct Node {
    int val; 
    struct Node *next; }
;
/* 建表（尾插） */
struct Node  *list_create(int a[], int n){
    if (a == NULL || n == 0){
        return NULL;
    }
    struct Node *head = NULL;
    struct Node *cur = NULL;
    for (int i = 0 ; i < n; i++) {
        struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));
        new_node->val = a[i];
        new_node->next = NULL;
        if (i == 0) {
            head = new_node;
        } else {
            cur->next = new_node;
        }
        cur = new_node;
    }
    return head;
}       
void list_push_head(struct Node **head, int val) {
    struct Node *new_head = (struct Node *)malloc(sizeof(struct Node));
    new_head->val = val;
    new_head->next = *head;
    *head = new_head;
}
void list_push_tail(struct Node **head, int val){
    if (*head == NULL) {
        list_push_head(head, val);
        return;
    }
    struct Node *new_tail = (struct Node *)malloc(sizeof(struct Node));
    new_tail->val = val;
    new_tail->next = NULL;
    struct Node *cur = *head;
    while (cur->next != NULL) {
        cur = cur->next;
    }
    cur->next = new_tail;
}
struct Node *list_find(struct Node *head, int val){
    struct Node *cur = head;
    while (cur != NULL) {
        if (cur->val == val) {
            return cur;
        }
        cur = cur->next;
    }
    return NULL;
}
void  list_delete(struct Node **head, int val){
    struct Node *cur = *head;
    struct Node *prev = NULL;
    while (cur != NULL) {
        if (cur->val == val) {
            if (prev == NULL) {
                *head = cur->next;
            } else {
                prev->next = cur->next;
            }
            free(cur);
            return;
        }
        prev = cur;
        cur = cur->next;
    }
}
struct Node *list_reverse(struct Node *head){
    struct Node *new_head = NULL;
    struct Node *cur = head;
    while (cur != NULL) {
        struct Node *next = cur->next;
        cur->next = new_head;
        new_head = cur;
        cur = next;
    }
    return new_head;
}
void list_free(struct Node **head){
    struct Node *cur = *head;
    while (cur != NULL) {
        struct Node *next = cur->next;
        free(cur);
        cur = next;
    }
    *head = NULL;
}


void list_print(struct Node *head) {
    if (head == NULL) {
        printf("(nil)\n");
        return;
    }
    for (struct Node *p = head; p; p = p->next)
        printf("%d ", p->val);
    printf("\n");
}


int main(void) {
    int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    struct Node *head = list_create(a, 10);

    list_push_head(&head, 0);
    printf("push_head(0):    "); 
    list_print(head);

    list_push_tail(&head, 11);
    printf("push_tail(11):   "); 
    list_print(head);

    list_delete(&head, 0);
    printf("delete head(0):  "); 
    list_print(head);

    list_delete(&head, 5);
    printf("delete mid(5):   "); 
    list_print(head);

    list_delete(&head, 11);
    printf("delete tail(11): "); 
    list_print(head);

    list_delete(&head, 99);
    printf("delete miss(99): "); 
    list_print(head);

    head = list_reverse(head);
    printf("reverse:         "); 
    list_print(head);

    list_free(&head);
    printf("after free:      "); 
    list_print(head);

    return 0;
}