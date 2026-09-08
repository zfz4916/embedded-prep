/*
Given a sequence of N integers ({A1,A2,...,A_N}), find the maximum value of the function
*/

int MaxSubseqSum1 (int A[], int N) {
//O(n^3)
    int thissum,maxsum = 0;
    for (int i = 0; i < N; i++) {
    //i is the left number
        for (j = i; j < N, j++) {
        //j is the right number
            thissum = 0;
            for (k = i; k <= j; k++) {
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
        for (j = i; j < N; j++) {
            thissum += A[j];
            if (thissum > maxsum) {
                maxsum = thissum;
            }
        }
    }
    return maxsum;
}

int MaxSubseqSum3 (int A[], int N) {
//O(nlogn)
    return MaxSubseqSum4(A, 0, N-1);
}