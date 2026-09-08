/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* reverseList(struct ListNode* head) {
    struct ListNode* result = head;
    struct ListNode* p = head;
    if (head == NULL || head -> next == NULL) {
        return head; 
    }
    head = head -> next;
    result -> next = NULL;

    while (head != NULL) {
        result = head;
        head = head -> next;
        result -> next = p;
        p = result;
    }
    return result;
}