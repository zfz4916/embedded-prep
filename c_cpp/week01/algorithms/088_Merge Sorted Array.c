void merge(int* nums1, int nums1Size, int m, int* nums2, int nums2Size, int n) {
    int i = m - 1;      // nums1 有效区末尾
    int j = n - 1;      // nums2 末尾
    int k = m + n - 1;  // 合并后末尾
    while (i >= 0 && j >= 0) {
        // 比较 nums1[i] 和 nums2[j]，大的放 nums1[k]，对应指针前移
        if (nums1[i] > nums2[j]) {
            nums1[k] = nums1[i];
            i--;
        } else {
            nums1[k] = nums2[j];
            j--;
        }
        k--;
    }
    while (j >= 0) {
        // nums2 剩下的全补到前面
        nums1[k] = nums2[j];
        j--;
        k--;
    }
}
