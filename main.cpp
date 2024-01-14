#include <time.h>
#include <array>
#include <iostream>
#include <list>
#include <random>

#include "array.h"
#include "bst.cpp"
#include "linkedList.cpp"
#include "list.cpp"
#include "utils.h"

using namespace std;

// --------- Array ---------

void initArray(int n, float* arr) {
    auto duration = timer([&]() { genRndFloatArray(arr, n); });

    cout << "Initiated " << formatNumberForDisplay(n) << " item array in " << longToString(duration)
         << " μs." << endl;
}

void testArrayMergeSort(float arr[], int n) {
    auto duration = timer([&]() { arrayMergeSort(arr, 0, n - 1); });
    cout << "Sorted in " << longToString(duration) << " μs." << endl;
}

void testArrayBinarySearch(float arr[], int n) {
    long long presentRecords[100];
    long long absentRecords[100];

    for (int i = 0; i < 100; i++) {
        float rndFloat = randomFloat();
        int rndIdx = randomInt(n);
        long long duration = 0;

        duration = timer([&]() { arrayBinarySearch(arr, 0, n - 1, arr[rndIdx]); });
        presentRecords[i] = duration;

        duration = timer([&]() { arrayBinarySearch(arr, 0, n - 1, rndFloat); });
        absentRecords[i] = duration;
    }

    cout << "Searched 100 present values in min: " << minArray(presentRecords, 100)
         << ", mean: " << meanArray(presentRecords, 100)
         << ", max: " << maxArray(presentRecords, 100) << " μs" << endl;
    cout << "Searched 100 absent values in min: " << minArray(absentRecords, 100)
         << ", mean: " << meanArray(absentRecords, 100) << ", max: " << maxArray(absentRecords, 100)
         << " μs" << endl;
}

void testArray() {
    cout << "----- Testing Arrays -----" << endl;

    for (int n = 100'000; n <= 10'000'000; n *= 10) {
        float* arr = new float[n];
        initArray(n, arr);

        testArrayMergeSort(arr, n);
        testArrayBinarySearch(arr, n);

        cout << "------------------------" << endl;

        delete[] arr;
    }
}

// --------- Linked List ---------

void testInitLinkedList(int n, LinkedList** listRef) {
    auto duration = timer([&]() { initLinkedList(n, listRef); });
    cout << "Initiated " << formatNumberForDisplay(n) << " item LinkedList in "
         << longToString(duration) << " μs." << endl;
}

void testLinkedListMergeSort(LinkedList** listRef) {
    auto duration = timer([&]() { linkedListMergeSort(listRef); });
    cout << "Sorted in " << longToString(duration) << " μs." << endl;
}

void testLinkedList() {
    cout << "----- Testing LinkedLists -----" << endl;

    for (int n = 100'000; n <= 10'000'000; n *= 10) {
        LinkedList* list;
        testInitLinkedList(n, &list);
        testLinkedListMergeSort(&list);
        cout << "------------------------" << endl;
    }
}

// --------- BST ---------

void testInitBST(int n, TreeNode** nodeRef) {
    auto duration = timer([&]() { initBST(n, nodeRef); });

    cout << "Initiated " << formatNumberForDisplay(n) << " item BinaryTree in "
         << longToString(duration) << " μs." << endl;
}

void testBSTSearch(int n, TreeNode* root) {
    long long presentRecords[100];
    long long absentRecords[100];

    for (int i = 0; i < 100; i++) {
        float rndFloat = randomFloat();
        int rndIdx = randomInt(n);
        long long duration = 0;

        duration = timer([&]() { bstSearch(root, root->val); });
        presentRecords[i] = duration;

        duration = timer([&]() { bstSearch(root, rndFloat); });
        absentRecords[i] = duration;
    }

    cout << "Searched 100 present values in min: " << minArray(presentRecords, 100)
         << ", mean: " << meanArray(presentRecords, 100)
         << ", max: " << maxArray(presentRecords, 100) << " μs" << endl;
    cout << "Searched 100 absent values in min: " << minArray(absentRecords, 100)
         << ", mean: " << meanArray(absentRecords, 100) << ", max: " << maxArray(absentRecords, 100)
         << " μs" << endl;
}

int testBST() {
    cout << "----- Testing Arrays -----" << endl;

    for (int n = 100'000; n <= 10'000'000; n *= 10) {
        TreeNode* root;
        testInitBST(n, &root);
        testBSTSearch(n, root);

        cout << "------------------------" << endl;
    }

    return 0;
}

// --------- std:list ---------
void testInitList(int n, list<float>** lst) {
    auto duration = timer([&]() { initList(n, lst); });

    cout << "Initiated " << formatNumberForDisplay(n) << " item list in " << longToString(duration)
         << " μs." << endl;
}

void testListMergeSort(list<float>* lst) {
    long long duration = 0;

    duration = timer([&]() { listMergeSort(lst, 0, lst->size()); });

    cout << "Custom merge-sort in " << longToString(duration) << " μs." << endl;
}

void testListDefaultSort(list<float>* lst) {
    long long duration = 0;

    duration = timer([&]() { lst->sort(); });

    cout << "Default sort in " << longToString(duration) << " μs." << endl;
}

void testListSearch(list<float>* lst) {
    long long presentRecords[100];
    long long absentRecords[100];

    for (int i = 0; i < 100; i++) {
        int rndIdx = randomInt(lst->size());
        // get the value of item at rndIdx
        list<float>::iterator it = lst->begin();
        advance(it, rndIdx);

        long long duration = 0;

        duration = timer([&]() { listSearch(lst, *it); });
        presentRecords[i] = duration;
    }
    cout << "Searched 100 present values in min: " << minArray(presentRecords, 100)
         << ", mean: " << meanArray(presentRecords, 100)
         << ", max: " << maxArray(presentRecords, 100) << " μs" << endl;

    for (int i = 0; i < 100; i++) {
        float rndFloat = randomFloat();
        long long duration = 0;

        duration = timer([&]() { listSearch(lst, rndFloat); });
        absentRecords[i] = duration;
    }
    cout << "Searched 100 absent values in min: " << minArray(absentRecords, 100)
         << ", mean: " << meanArray(absentRecords, 100) << ", max: " << maxArray(absentRecords, 100)
         << " μs" << endl;
}

void testList() {
    cout << "----- Testing Lists -----" << endl;

    for (int n = 100'000; n <= 10'000'000; n *= 10) {
        list<float>* lst = new list<float>();
        testInitList(n, &lst);
        testListDefaultSort(lst);
        testListMergeSort(lst);
        testListSearch(lst);

        cout << "------------------------" << endl;
    }
}

// --------- Menu ---------
void displayMenu() {
    std::cout << "----- Test Menu -----" << std::endl;
    std::cout << "1. Test Arrays" << std::endl;
    std::cout << "2. Test Linked Lists" << std::endl;
    std::cout << "3. Test BST" << std::endl;
    std::cout << "4. std::list" << std::endl;
    std::cout << "0. Exit" << std::endl;
    std::cout << "---------------------" << std::endl;
    std::cout << "Enter your choice: ";
}

int main() {
    srand(time(nullptr));  // set random seed

    int choice;
    do {
        displayMenu();
        std::cin >> choice;

        switch (choice) {
            case 1:
                testArray();
                break;
            case 2:
                testLinkedList();
                break;
            case 3:
                testBST();
                break;
            case 4:
                testList();
                break;
            case 0:
                std::cout << "Exiting..." << std::endl;
                break;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
                break;
        }

        std::cout << std::endl;
    } while (choice != 0);

    return 0;
}
