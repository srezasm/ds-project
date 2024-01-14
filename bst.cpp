#include <iostream>

#include "array.cpp"
#include "utils.h"

using namespace std;

// data structure
struct TreeNode {
    float val;
    TreeNode* left;
    TreeNode* right;

    TreeNode() : val(0.0), left(nullptr), right(nullptr){};
    TreeNode(float x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(float x, TreeNode* l, TreeNode* r) : val(x), left(l), right(r) {}
};

// --------- Init ---------
void fillBST(TreeNode** nodeRef, float* arr, int start, int end) {
    if (start > end) {
        *nodeRef = nullptr;
    } else {
        int mid = start + (end - start) / 2;
        *nodeRef = new TreeNode(arr[mid]);
        fillBST(&((*nodeRef)->left), arr, start, mid - 1);
        fillBST(&((*nodeRef)->right), arr, mid + 1, end);
    }
}

void initBST(int n, TreeNode** nodeRef) {
    float* rndArr = new float[n];
    genRndFloatArray(rndArr, n);
    arrayMergeSort(rndArr, 0, n - 1);
    fillBST(nodeRef, rndArr, 0, n - 1);
}

void testInitBST(int n, TreeNode** nodeRef) {
    auto duration = timer([&]() { initBST(n, nodeRef); });

    cout << "Initiated " << formatNumberForDisplay(n) << " item BinaryTree in "
         << longToString(duration) << " μs." << endl;
}

int main() {
    TreeNode* root;
    testInitBST(8, &root);

    return 0;
}