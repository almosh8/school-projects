#include <stdio.h>

#include "bst.h"

int cmpf(int a, int b) { return a - b; }

void print_node(int item) { printf("%d ", item); }

int main() {
    // Test case 1: Insert nodes with values 10, 5, 15
    t_btree *root = NULL;
    root = bstree_insert(root, 10, cmpf);
    root = bstree_insert(root, 5, cmpf);
    root = bstree_insert(root, 15, cmpf);

    printf("Infix traversal: ");
    bstree_apply_infix(root, print_node);
    printf("\n");

    printf("Prefix traversal: ");
    bstree_apply_prefix(root, print_node);
    printf("\n");

    printf("Postfix traversal: ");
    bstree_apply_postfix(root, print_node);
    printf("\n");

    bstree_destroy(root);

    // Test case 2: Insert nodes with values 8, 12, 3, 7, 11, 13
    t_btree *root2 = NULL;
    root2 = bstree_insert(root2, 8, cmpf);
    root2 = bstree_insert(root2, 12, cmpf);
    root2 = bstree_insert(root2, 3, cmpf);
    root2 = bstree_insert(root2, 7, cmpf);
    root2 = bstree_insert(root2, 11, cmpf);
    root2 = bstree_insert(root2, 13, cmpf);

    printf("\nInfix traversal: ");
    bstree_apply_infix(root2, print_node);
    printf("\n");

    printf("Prefix traversal: ");
    bstree_apply_prefix(root2, print_node);
    printf("\n");

    printf("Postfix traversal: ");
    bstree_apply_postfix(root2, print_node);
    printf("\n");

    bstree_destroy(root2);

    return 0;
}
