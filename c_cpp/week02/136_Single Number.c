int singleNumber(int* nums, int numsSize) {
    int ret = nums[0];
    for (int i = 1; i < numsSize; i++) {
        ret = ret ^ nums[i];
    }
    return ret;
}