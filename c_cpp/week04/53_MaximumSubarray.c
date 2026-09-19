int maxSubArray(int* nums, int numsSize) {
    int thissum = 0;
    int maxsum = nums[0];
    for (int i = 0; i < numsSize; i++) {
        thissum += nums[i];
        if (thissum > maxsum) {
            maxsum = thissum;
        }
        if (thissum < 0) {
            thissum = 0;
        }
    }
    return maxsum;
}