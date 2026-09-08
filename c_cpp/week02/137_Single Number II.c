/*
法1：先排序，然后第一个和第三个是否相等，相等i+1，继续比，不想等直接返回 快速排序O(n log n)再加一个循环traverse
法2: 挂numsSize/3 + 1 个链表，头节点的两个值，一个值代表这是几，另一个是bool，只有这一个节点的时候bool ture
     但是如果不给malloc的话用不了 （hash的思路）
法3：hash 其中的键是nums的element，值是这个element出现的次数
法4：字节运算：（1）一个数出现了3次，所有数的同一位全部相加%3，最终得到只有这个signal在该位的值，再将所有位全部拼成，就是这个signal
                （2）写一个三进制器
*/


/*------------------------------------hash--------0(n)----------------------*/
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int key;            // element
    int val;            // num
    struct Node *next;  // pointer
} Node;

//负数情况下，直接对一个值取余再转换为unsigned
#define HASH_SIZE 1024

// 哈希函数
int hash(int key) {
    return ((unsigned int)key) % HASH_SIZE;
}

// 查找：返回对应 key 的节点，不存在返回 NULL
Node* hash_find(Node *table[], int key) {
    int idx = hash(key);
    Node *cur = table[idx];
    while (cur) {
        if (cur->key == key) return cur;
        cur = cur->next;
    }
    return NULL;
}

// 添加/更新：存在则次数+1，不存在则新建
void hash_add(Node *table[], int key) {
    Node *node = hash_find(table, key);
    if (node) {
        node->val++;
    } else {
        int idx = hash(key);
        Node *newNode = malloc(sizeof(Node));
        newNode->key = key;
        newNode->val = 1;
        newNode->next = table[idx];  // 头插法
        table[idx] = newNode;
    }
}

int singleNumber(int *nums, int numsSize) {
    Node *table[HASH_SIZE] = {NULL};  // 哈希表数组，初始全空
    
    // 统计次数
    for (int i = 0; i < numsSize; i++) {
        hash_add(table, nums[i]);
    }
    
    // 找出现次数为 1 的
    int ans = 0;
    for (int i = 0; i < numsSize; i++) {
        Node *node = hash_find(table, nums[i]);
        if (node && node->val == 1) {
            ans = nums[i];
            break;
        }
    }
    
    return ans;
}

/*-----------------------三进制计算------------------O(n)------------*/
int singleNumber(int *nums, int numsSize) {
    int one = 0, two = 0;   // 所有位初始都是 0 次状态
    
    for (int i = 0; i < numsSize; i++) {
        int n = nums[i];
        
        // 第一步：更新 one
        // 如果 two=1（已经2次了），one 必须变0（因为2次+1次=3次归零，或2次+0次不变）
        // 如果 two=0，one 正常做异或（来1翻转，来0不变）
        one = (one ^ n) & ~two;
        
        // 第二步：更新 two
        // 利用刚刚算出的新 one，来阻止 two 的错误翻转
        two = (two ^ n) & ~one;
    }
    
    return one;   // 最后 one 里存的就是「出现1次」的那些位
}

/*---------------------------按位----------------O(n)---------------------*/
int singleNumber(int* nums, int numsSize) {
    int ans = 0;
    
    // 遍历 int 的 32 个二进制位
    for (int bit = 0; bit < 32; bit++) {
        int count = 0;
        
        // 统计所有数字在第 bit 位上有多少个 1
        for (int i = 0; i < numsSize; i++) {
            count += (nums[i] >> bit) & 1;
        }
        
        // 如果这一位上 1 的个数不是 3 的倍数，
        // 说明「只出现一次的那个数字」在这一位上是 1
        if (count % 3 != 0) {
            ans |= (1u << bit);   // 把答案的这一位置为 1
        }
    }
    
    return ans;
}

/*--------------------------排序-------------O(n log n)------------------*/
#include <stdlib.h>

int cmp(const void *a, const void *b) {
    int x = *(const int *)a;
    int y = *(const int *)b;
    return (x > y) - (x < y);  // 安全比较，防溢出，如果数值接近 INT_MAX/INT_MIN，相减可能溢出
}

int singleNumber(int *nums, int numsSize) {
    qsort(nums, numsSize, sizeof(int), cmp);
    
    // 排序后，出现3次的数字会连续排列
    for (int i = 0; i < numsSize; i += 3) {
        // 最后一个元素，或当前元素与下一个不同，就是答案
        if (i == numsSize - 1 || nums[i] != nums[i + 1]) {
            return nums[i];
        }
    }
    return 0;
}