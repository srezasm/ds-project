#include <stdio.h>
#include "utils.h"

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
    printf("Initiated %d item LinkedList in %lld microseconds.\n", n, duration);
    return list;
}

// --------- Sort ---------
LinkedList* merge(LinkedList* l1, LinkedList* l2) {
    if (l1 == NULL)
        return l2;
    if (l2 == NULL)
        return l1;

    LinkedList* result;

    if (l1->value <= l2->value) {
        result = l1;
        result->next = merge(l1->next, l2);
    } else {
        result = l2;
        result->next = merge(l1, l2->next);
    }

    return result;
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
    slow->next = NULL;

    // list is the head of the left part
    mergeSort(&list);
    // slow.next is the head of the right part
    mergeSort(&slow->next);

    *listRef = merge(list, slow->next);
}

void runMergeSort(LinkedList** listRef) {
    auto duration = timer([&]() { mergeSort(listRef); });
    printf("\nSorted in %lld microseconds.\n", duration);
}

int main() {
    srand(time(NULL));  // set random seed

    printf("----- Testing LinkedLists -----\n");

    // for (int n = 100'000; n <= 10'000'000; n *= 10) {
    //     LinkedList* arr = init(n);
    //     printf("------------------------\n");
    // }

    LinkedList* list = init(4);
    // printf("\nlist values\n");
    // while (arr != NULL) {
    //     printf("%f ", arr->value);
    //     arr = arr->next;
    // }
    runMergeSort(&list);
    printf("\nmerged\n");
    while (list != NULL) {
        printf("%f ", list->value);
        list = list->next;
    }

    return 0;
}