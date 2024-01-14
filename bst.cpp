#include "utils.h"
#include "array.h"

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

// --------- Search ---------
bool bstSearch(TreeNode* node, float val) {
    if (node == nullptr)
        return false;
    else if (node->val == val)
        return true;
    else if (node->val > val)
        return bstSearch(node->left, val);
    else
        return bstSearch(node->right, val);
}
