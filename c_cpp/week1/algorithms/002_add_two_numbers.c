/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */


//this is the first solution, time complexity is O(n)
struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2) {
    
    //创建一个空节点用来定位
    struct ListNode* head =(struct ListNode*)malloc(sizeof(struct ListNode));
    head -> next = NULL;
    //换一个名字
    struct ListNode* node = head;
    int carry = 0;     //进位
    while (l1 != NULL || l2 != NULL || carry !=0) {
        int a = (l1 != NULL) ? l1 -> val : 0;
        int b = (l2 != NULL) ? l2 -> val : 0;
        //创建节点
        struct ListNode* p =(struct ListNode*)malloc(sizeof(struct ListNode));
        //一个一个计算
        int sum = a + b + carry;
        //取个位数
        p -> val = sum % 10;
        p -> next = NULL;
        //新进位
        carry = sum / 10;

        node -> next = p;
        node = node -> next;
        
        if (l1 != NULL) l1 = l1 -> next;
        if (l2 != NULL) l2 = l2 -> next;
    }
    struct ListNode* result = head ->next;
    free(head);
    return result;
} 