#include <stdio.h>
#include <stdlib.h>

struct TreeNode {
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
};

struct TreeNode* createNode(int val) {
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    newNode->val = val;
    newNode->left = newNode->right = NULL;
    return newNode;
}

struct TreeNode* insert(struct TreeNode* node, int val) {
    if (node == NULL)
        return createNode(val);

    if (val < node->val)
        node->left = insert(node->left, val);
    else if (val > node->val)
        node->right = insert(node->right, val);

    return node;
}

int closestValue(struct TreeNode* root, double target) {
    int closest = root->val;
    struct TreeNode* current = root;

    while (current != NULL) {
        closest = abs(current->val - target) < abs(closest - target) ? current->val : closest;

        if (target < current->val)
            current = current->left;
        else
            current = current->right;
    }

    return closest;
}

void freeTree(struct TreeNode* node) {
    if (node == NULL)
        return;

    freeTree(node->left);
    freeTree(node->right);
    free(node);
}

int main() {
    struct TreeNode* root = NULL;
    int val;
    double target;

    // Create BST based on user input
    printf("Enter the elements of the BST (-1 to stop):\n");
    while (1) {
        scanf("%d", &val);
        if (val == -1)
            break;
        root = insert(root, val);
    }

    // Get target value from the user
    printf("Enter the target value: ");
    scanf("%lf", &target);

    // Find the closest value in the BST
    int closest = closestValue(root, target);
    printf("Closest number = %d\n", closest);

    // Free the memory
    freeTree(root);

    return 0;
}
