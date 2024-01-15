#include <algorithm>
#include <list>

#include "utils.h"

using namespace std;

// --------- Init ---------
void initList(int n, list<float>** lstRef) {
    for (int i = 0; i < n; i++)
        (*lstRef)->push_back(randomFloat());
}

// --------- Sort ---------
void listMerge(list<float>* lst, int p, int q, int r) {
    long i, j, k;
    long nL = q - p + 1;  // length of A[p:q]
    long nR = r - q;      // length of A[q + 1:r]

    float* L = new float[nL];
    float* R = new float[nR];

    // initialize L, and R
    for (i = 0; i < nL; i++)
        L[i] = lst->front();
    for (j = 0; j < nR; j++)
        R[j] = lst->front();

    i = 0;  // smallest remaining element in L
    j = 0;  // smallest remaining element in R
    k = p;  // location in A to fill
    while (i < nL && j < nR) {
        if (L[i] <= R[j]) {
            lst->push_back(L[i]);
            i++;
        } else {
            lst->push_back(R[j]);
            j++;
        }
        k++;
    }

    // Having gone through one of the L, or R entirely,
    // copy the remainder of the other to the end of A[p:r]
    while (i < nL) {
        lst->push_back(L[i]);
        i++;
        k++;
    }
    while (j < nR) {
        lst->push_back(R[j]);
        j++;
        k++;
    }

    delete[] L;
    delete[] R;
}

void listMergeSort(list<float>* lst, int l, int r) {
    if (l >= r)
        return;

    int m = l + (r - l) / 2;  // midpoint of A[l:r]

    listMergeSort(lst, l, m);      // recursively sort A[l:m]
    listMergeSort(lst, m + 1, r);  // recursively sort A[m + 1:r]
    listMerge(lst, l, m, r);       // merge the two sorted subarrays
}

void stdSearch() {
    
}

// --------- Search ---------
bool listSearch(list<float>* lst, float val) {
    return binary_search(lst->begin(), lst->end(), val);

    // if (l > r)
    //     return false;

    // int m = l + (r - l) / 2;

    // float v = getValue(lst, m);
    // if (v == val)
    //     return true;
    // else if (v > val)
    //     return listSearch(lst, val, l, m - 1);
    // else
    //     return listSearch(lst, val, m + 1, r);
}
