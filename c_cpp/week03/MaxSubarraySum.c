/*
Given a sequence of N integers ({A1,A2,...,A_N}), find the maximum value of the function
*/

#include <stdio.h>

int MaxSubseqSum1 (int A[], int N) {
//O(n^3)
    int thissum,maxsum = 0;
    for (int i = 0; i < N; i++) {
    //i is the left number
        for (int j = i; j < N; j++) {
        //j is the right number
            thissum = 0;
            for (int k = i; k <= j; k++) {
                thissum += A[k];
            }
            if (thissum > maxsum) {
                maxsum = thissum;
            }
        }
    }
    return maxsum;
}

int MaxSubseqSum2 (int A[], int N) {
//O(n^2) 
    int thissum, maxsum = 0;
    for (int i = 0; i < N; i++) {
        for (int j = i; j < N; j++) {
            thissum = 0;
            thissum += A[j];
            if (thissum > maxsum) {
                maxsum = thissum;
            }
        }
    }
    return maxsum;
}

int MaxSubseqSum3 (int A[], int N) {
    int thissum, maxsum;
    thissum = maxsum = 0;
    for (int i = 0; i < N; i++) {
        thissum += A[i];
        if (thissum > maxsum) {
            maxsum = thissum;
        } else if (thissum < 0) {
            thissum = 0;
        }
    }
    return maxsum;
}

int main(void) {
    /* 用例1：经典数组，正确答案 6（子数组 [4,-1,2,1]）*/
    int a1[] = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    printf("case1: %d (expect 6)\n", MaxSubseqSum3(a1, 9));

    /* 用例2：全负数组，按"空子列=0"约定正确答案 0 */
    int a2[] = {-3, -1, -2};
    printf("case2: %d (expect 0)\n", MaxSubseqSum3(a2, 3));

    /* 用例3：单元素，答案就是它自己 */
    int a3[] = {5};
    printf("case3: %d (expect 5)\n", MaxSubseqSum3(a3, 1));

    return 0;
}