/**
 * Note: The returned array must be malloced, assume caller calls free().
 */



 //this is the first solution, time complexity is O(n^2)
int* twoSum1(int* nums, int numsSize, int target, int* returnSize) {
    int i = 0;
    int j = 0;
    int sum = 0;
    for (; i < numsSize; i++) {
        for (j = i + 1; j < numsSize; j++) {
            sum = nums[i] + nums[j];
            if (sum == target) {
                int* res = malloc(2 * sizeof(int));
                res[0] = i;
                res[1] = j;
                *returnSize = 2;
                return res;
            }
        }
    }
    return NULL; 
}

