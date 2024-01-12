#include <stdio.h>
#include "utils.h"
#include <string>

struct LinkedList {
    float value;
    LinkedList* next;

    LinkedList() : value(0), next(NULL){};
    LinkedList(float val) : value(val), next(NULL){};
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
    currentList->next = NULL;
}

LinkedList* init(int n) {
    LinkedList* list;
    auto duration = timer([&]() { init(n, list); });
    printf("Initiated %s item LinkedList in %s μs.\n", formatNumberForDisplay(n), longToString(duration));
    return list;
}

// --------- Sort ---------
void merge(LinkedList** listRef1, LinkedList** listRef2) {
    LinkedList* result = nullptr;
    LinkedList** lastPtrRef = &result;

    while (*listRef1 && *listRef2) {
        if ((*listRef1)->value <= (*listRef2)->value) {
            *lastPtrRef = *listRef1;
            *listRef1 = (*listRef1)->next;
        } else {
            *lastPtrRef = *listRef2;
            *listRef2 = (*listRef2)->next;
        }
        lastPtrRef = &((*lastPtrRef)->next);
    }

    if (*listRef1) {
        *lastPtrRef = *listRef1;
    } else {
        *lastPtrRef = *listRef2;
    }

    *listRef1 = result;
}

void mergeSort(LinkedList** listRef) {
    LinkedList* list = *listRef;

    // base case: 0 or 1 element
    if (list == NULL || list->next == NULL)
        return;

    LinkedList* slow = list;
    LinkedList* fast = list->next;

    // take two steps in fast and one step in slow
    while (fast != NULL) {
        fast = fast->next;

        if (fast != NULL) {
            slow = slow->next;
            fast = fast->next;
        }
    }

    // split the list
    LinkedList* left = list;
    LinkedList* right = slow->next;
    slow->next = NULL;

    // list is the head of the left part
    mergeSort(&left);
    // slow.next is the head of the right part
    mergeSort(&right);

    merge(&left, &right);
    *listRef = left;
}

void runMergeSort(LinkedList** listRef) {
    auto duration = timer([&]() { mergeSort(listRef); });
    printf("Sorted in %s μs.\n", longToString(duration));
}

int main() {
    srand(time(NULL));  // set random seed

    printf("----- Testing LinkedLists -----\n");

    for (int n = 100'000; n <= 10'000'000; n *= 10) {
        LinkedList* list = init(n);
        runMergeSort(&list);
        printf("------------------------\n");
    }

    return 0;
}