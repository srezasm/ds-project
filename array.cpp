#include <stdio.h>
#include "utils.h"

// --------- Init ---------
void genRndFloatArray(float* array, int n) {
    for (int i = 0; i < n; i++)
        array[i] = randomFloat();
}

// --------- Sort ---------
void arrayMerge(float arr[], int p, int q, int r) {
    long i, j, k;
    long nL = q - p + 1;  // length of A[p:q]
    long nR = r - q;      // length of A[q + 1:r]

    float* L = new float[nL];
    float* R = new float[nR];

    // initialize L, and R
    for (i = 0; i < nL; i++)
        L[i] = arr[p + i];
    for (j = 0; j < nR; j++)
        R[j] = arr[q + 1 + j];

    i = 0;  // smallest remaining element in L
    j = 0;  // smallest remaining element in R
    k = p;  // location in A to fill
    while (i < nL && j < nR) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Having gone through one of the L, or R entirely,
    // copy the remainder of the other to the end of A[p:r]
    while (i < nL) {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < nR) {
        arr[k] = R[j];
        j++;
        k++;
    }

    delete[] L;
    delete[] R;
}

void arrayMergeSort(float arr[], int l, int r) {
    if (l >= r)
        return;

    int m = l + (r - l) / 2;  // midpoint of A[l:r]

    arrayMergeSort(arr, l, m);      // recursively sort A[l:m]
    arrayMergeSort(arr, m + 1, r);  // recursively sort A[m:r]

    // Merge A[l:m], and A[m + 1:r] into A[l:r]
    arrayMerge(arr, l, m, r);
}

// --------- Search ---------
int arrayBinarySearch(float arr[], int l, int r, float x) {
    if (r < l)
        return -1;

    int mid = l + (r - l) / 2;

    if (arr[mid] == x)
        return mid;

    if (arr[mid] > x)
        return arrayBinarySearch(arr, l, mid - 1, x);  // search left half
    else
        return arrayBinarySearch(arr, mid + 1, r, x);  // search right half
}
