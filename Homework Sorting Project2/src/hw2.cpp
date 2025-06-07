#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
using namespace std;

struct Node {
    int val;  // node 值 
    Node* left;   //左子樹
    Node* right;  //右子樹
};

Node* insert(Node* root, int x) {
    if (root == nullptr) {
        root = new Node;
        root->val = x;
        root->left = nullptr;
        root->right = nullptr;
        return root;
    }
    if (x < root->val)
        root->left = insert(root->left, x);
    else
        root->right = insert(root->right, x);
    return root;
}

int getHeight(Node* root) {
    if (root == nullptr) return 0;
    int l = getHeight(root->left);
    int r = getHeight(root->right);
    return max(l, r) + 1;
}

int getRandom(int min, int max) {
    return rand() % (max - min + 1) + min;
}

int main() {
    srand(time(0));

    for (int n = 100; n <= 10000; n += 500) {
        Node* root = nullptr;
        for (int i = 0; i < n; i++) {
            int x = getRandom(1, n * 10);
            root = insert(root, x);
        }
        int h = getHeight(root);
        double logn = log2(n);
        double ratio = h / logn;
        cout << "n = " << n << ", height = " << h << ", log2(n) = " << logn << ", ratio = " << ratio << endl;
    }

    return 0;
}
