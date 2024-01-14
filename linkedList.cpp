#include <stdio.h>
#include <string>
#include "utils.h"

// data structure
struct LinkedList {
    float value;
    LinkedList* next;

    LinkedList() : value(0), next(nullptr){};
    LinkedList(float val) : value(val), next(nullptr){};
    LinkedList(float val, LinkedList* nxt) : value(val), next(nxt){};
};

// --------- Init ---------
void initLinkedList(int n, LinkedList** listRef) {
    LinkedList* currentList = new LinkedList();
    *listRef = currentList;
    for (int i = 0; i < n - 1; i++) {
        currentList->value = randomFloat();
        currentList->next = new LinkedList();
        currentList = currentList->next;
    }
    currentList->value = randomFloat();
    currentList->next = nullptr;
}

// --------- Sort ---------
void linkedListMerge(LinkedList** listRef1, LinkedList** listRef2) {
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

void linkedListMergeSort(LinkedList** listRef) {
    LinkedList* list = *listRef;

    // base case: 0 or 1 element
    if (list == nullptr || list->next == nullptr)
        return;

    LinkedList* slow = list;
    LinkedList* fast = list->next;

    // take two steps in fast and one step in slow
    while (fast != nullptr) {
        fast = fast->next;

        if (fast != nullptr) {
            slow = slow->next;
            fast = fast->next;
        }
    }

    // split the list
    LinkedList* left = list;
    LinkedList* right = slow->next;
    slow->next = nullptr;

    // list is the head of the left part
    linkedListMergeSort(&left);
    // slow.next is the head of the right part
    linkedListMergeSort(&right);

    linkedListMerge(&left, &right);
    *listRef = left;
}