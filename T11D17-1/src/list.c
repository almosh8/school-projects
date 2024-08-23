#include "list.h"

#include <stdlib.h>

node* init(door* door) {
    node* new_node = (node*)malloc(sizeof(node));
    if (new_node == NULL) {
        return NULL;
    }
    new_node->door = *door;
    new_node->next = NULL;
    return new_node;
}

node* add_door(node* elem, door* door) {
    node* new_node = (node*)malloc(sizeof(node));
    if (new_node == NULL) {
        return NULL;
    }
    new_node->door = *door;
    new_node->next = elem->next;
    elem->next = new_node;
    return new_node;
}

node* find_door(int door_id, node* root) {
    node* current = root;
    while (current != NULL) {
        if (current->door.id == door_id) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

node* remove_door(node* elem, node* root) {
    if (root == NULL || elem == NULL) {
        return root;
    }

    if (root == elem) {
        node* temp = root;
        root = root->next;
        free(temp);
        return root;
    }

    node* current = root;
    while (current->next != NULL) {
        if (current->next == elem) {
            node* temp = current->next;
            current->next = current->next->next;
            free(temp);
            return root;
        }
        current = current->next;
    }

    return root;
}

void destroy(node* root) {
    node* current = root;
    while (current != NULL) {
        node* temp = current;
        current = current->next;
        free(temp);
    }
}