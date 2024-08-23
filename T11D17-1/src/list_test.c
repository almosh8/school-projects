#include "list.h"

#include <stdio.h>
#include <stdlib.h>

#define SUCCESS 0
#define FAIL 1

int test_add_door() {
    node* root = init(&(door){1, 0});
    if (root == NULL) {
        return FAIL;
    }

    node* new_node = add_door(root, &(door){2, 1});
    if (new_node == NULL) {
        destroy(root);
        return FAIL;
    }
    if (new_node->door.id != 2 || new_node->door.status != 1 || root->next != new_node) {
        destroy(root);
        return FAIL;
    }

    destroy(root);
    return SUCCESS;
}

int test_remove_door() {
    node* root = init(&(door){1, 0});
    if (root == NULL) {
        return FAIL;
    }

    node* new_node = add_door(root, &(door){2, 1});
    if (new_node == NULL) {
        destroy(root);
        return FAIL;
    }

    root = remove_door(new_node, root);
    if (root->next != NULL) {
        destroy(root);
        return FAIL;
    }

    destroy(root);
    return SUCCESS;
}

int main() {
    printf("test_add_door: %s\n", test_add_door() == SUCCESS ? "ok" : "fail");
    printf("test_remove_door: %s\n", test_remove_door() == SUCCESS ? "ok" : "fail");
    return 0;
}