#include <stdio.h>
#include "utils.h"

struct LinkedList {
    float value;
    LinkedList* next;

    LinkedList() : value(0), next(nullptr){};
    LinkedList(float val) : value(val), next(nullptr){};
    LinkedList(float val, LinkedList* nxt) : value(val), next(nxt){};
};

// --------- Init ---------
void init(int n, LinkedList*& list) {
    LinkedList* currentList = new LinkedList();
    list = currentList;
    for (int i = 0; i < n - 1; i++) {
        currentList->value = randomFloat();
        currentList->next = new LinkedList();
        currentList = currentList->next;
    }
    currentList->value = randomFloat();
    currentList->next = nullptr;
}

LinkedList* init(int n) {
    LinkedList* list;
    auto duration = timer([&]() { init(n, list); });
    printf("Initiated %d item LinkedList in %lld microseconds.\n", n, duration);
    return list;
}

// --------- Sort ---------
// LinkedList* merge(LinkedList*& l1, LinkedList*& l2) {
//     if (l1 == nullptr)
//         return l2;
//     if (l2 == nullptr)
//         return l1;

//     if (l1->value <= l2->value) {
//         l1->next = merge(l1->next, l2);
//         return l1;
//     } else {
//         l2->next = merge(l1, l2->next);
//         return l2;
//     }
// }

void merge(LinkedList*& l1, LinkedList*& l2) {
    int len1, len2;
    if (l1 == nullptr)
        len1 = 0;
    if (l2 == nullptr)
        len2 = 0;

    LinkedList *l = l1, *r = l2;
    while (l != nullptr) {
        l = l->next;
        len1++;
    }
    while (r != nullptr) {
        r = r->next;
        len2++;
    }

    printf("\nlen1: %d \tlen2: %d\n", len1, len2);
}

void mergeSort(LinkedList*& list) {
    if (list->next == nullptr)
        return;

    LinkedList* left = list;
    LinkedList* right = list->next;

    LinkedList* cl = left;
    LinkedList* cr = right;

    while (cr->next != nullptr) {
        cl->next = cl->next->next;
        cl = cl->next;

        cr->next = cr->next->next;
        cr = cr->next;
    }

    cl->next = nullptr;

    mergeSort(left);
    mergeSort(right);

    merge(list, right);
}

void runMergeSort(LinkedList*& list) {
    auto duration = timer([&]() { mergeSort(list); });
    printf("\nSorted in %lld microseconds.\n", duration);
}

int main() {
    srand(time(NULL));  // set random seed

    printf("----- Testing LinkedLists -----\n");

    // for (int n = 100'000; n <= 10'000'000; n *= 10) {
    //     LinkedList* arr = init(n);
    //     printf("------------------------\n");
    // }

    LinkedList* arr = init(10);
    // printf("\nlist values\n");
    // while (arr != nullptr) {
    //     printf("%f ", arr->value);
    //     arr = arr->next;
    // }
    runMergeSort(arr);
    printf("\nmerged\n");
    while (arr != nullptr) {
        printf("%f ", arr->value);
        arr = arr->next;
    }

    return 0;
}