#include <stdio.h>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <functional>
#include <limits>
#include "utils.h"

// --------- Init ---------
void randomFloatArray(float array[], int n) {
    for (int i = 0; i < n; i++)
        array[i] = randomFloat();
}

float* init(int n) {
    float* arr = new float[n];

    auto duration = timer([&]() { randomFloatArray(arr, n); });

    printf("Initiated %s item array in %s μs.\n", formatNumberForDisplay(n),
           longToString(duration));

    return arr;
}

// --------- Sort ---------
void merge(float arr[], int p, int q, int r) {
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

void mergeSort(float arr[], int l, int r) {
    if (l >= r)
        return;

    int m = l + (r - l) / 2;  // midpoint of A[l:r]

    mergeSort(arr, l, m);      // recursively sort A[l:m]
    mergeSort(arr, m + 1, r);  // recursively sort A[m:r]

    // Merge A[l:m], and A[m + 1:r] into A[l:r]
    merge(arr, l, m, r);
}

void mergeSort(float arr[], int n) {
    auto duration = timer([&]() { mergeSort(arr, 0, n - 1); });
    printf("Sorted in %s μs.\n", longToString(duration));
}

// --------- Search ---------
int binarySearch(float arr[], int l, int r, float x) {
    if (r < l)
        return -1;

    int mid = l + (r - l) / 2;

    if (arr[mid] == x)
        return mid;

    if (arr[mid] > x)
        return binarySearch(arr, l, mid - 1, x);  // search left half
    else
        return binarySearch(arr, mid + 1, r, x);  // search right half
}

void binarySearch(float arr[], int n) {
    long long presentRecords[100];
    long long absentRecords[100];

    for (int i = 0; i < 100; i++) {
        float randVal = randomFloat();
        int randIndex = randomInt(n);
        long long duration = 0;

        duration = timer([&]() { binarySearch(arr, 0, n - 1, arr[randIndex]); });
        presentRecords[i] = duration;

        duration = timer([&]() { binarySearch(arr, 0, n - 1, randVal); });
        absentRecords[i] = duration;
    }

    printf("Searched 100 present values in min: %lld, mean: %f, max: %lld μs\n",
           minArray(presentRecords, 100), meanArray(presentRecords, 100),
           maxArray(presentRecords, 100));
    printf("Searched 100 absent values in min: %lld, mean: %f, max: %lld μs\n",
           minArray(absentRecords, 100), meanArray(absentRecords, 100),
           maxArray(absentRecords, 100));
}

int main() {
    srand(time(NULL));  // set random seed

    printf("----- Testing Arrays -----\n");

    for (int n = 100'000; n <= 10'000'000; n *= 10) {
        float* arr = init(n);
        mergeSort(arr, n);
        binarySearch(arr, n);
        printf("------------------------\n");
    }

    return 0;
}
