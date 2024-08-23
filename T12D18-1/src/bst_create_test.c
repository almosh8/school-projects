#include <stdio.h>
#include <stdlib.h>

#include "bst.h"

int main() {
    // Test case 1: Create a node with value 10
    t_btree* node1 = bstree_create_node(10);
    printf("Created node with value: %d\n", node1->item);
    printf("Left child: %p\n", node1->left);
    printf("Right child: %p\n", node1->right);

    // Test case 2: Create a node with value 20
    t_btree* node2 = bstree_create_node(20);
    printf("Created node with value: %d\n", node2->item);
    printf("Left child: %p\n", node2->left);
    printf("Right child: %p\n", node2->right);

    free(node1);
    free(node2);
    return 0;
}
