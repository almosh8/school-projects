#include <stdio.h>

#include "bst.h"

int cmpf(int a, int b) { return a - b; }

int main() {
    // Test case 1: Insert nodes with values 10, 5, 15
    t_btree *root = NULL;
    root = bstree_insert(root, 10, cmpf);
    root = bstree_insert(root, 5, cmpf);
    root = bstree_insert(root, 15, cmpf);

    printf("Inserted nodes:\n");
    printf("Root: %d\n", root->item);
    printf("Left child: %d\n", root->left->item);
    printf("Right child: %d\n", root->right->item);

    bstree_destroy(root);

    // Test case 2: Insert nodes with values 8, 12, 3, 7, 11, 13
    t_btree *root2 = NULL;
    root2 = bstree_insert(root2, 8, cmpf);
    root2 = bstree_insert(root2, 12, cmpf);
    root2 = bstree_insert(root2, 3, cmpf);
    root2 = bstree_insert(root2, 7, cmpf);
    root2 = bstree_insert(root2, 11, cmpf);
    root2 = bstree_insert(root2, 13, cmpf);

    printf("\nInserted nodes:\n");
    printf("Root: %d\n", root2->item ? root2->item : -1);
    printf("Left child: %d\n", root2 && root2->left ? root2->left->item : -1);
    printf("Right child: %d\n", root2 && root2->right ? root2->right->item : -1);
    printf("Left-left child: %d\n", root2 && root2->left && root2->left->left ? root2->left->left->item : -1);
    printf("Left-right child: %d\n",
           root2 && root2->left && root2->left->right ? root2->left->right->item : -1);
    printf("Right-left child: %d\n",
           root2 && root2->right && root2->right->left ? root2->right->left->item : -1);
    printf("Right-right child: %d\n",
           root2 && root2->right && root2->right->right ? root2->right->right->item : -1);

    bstree_destroy(root2);

    return 0;
}
