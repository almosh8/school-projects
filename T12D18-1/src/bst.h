#ifndef BST_H
#define BST_H

typedef struct s_btree {
    int item;
    struct s_btree *left;
    struct s_btree *right;
} t_btree;

// Function to create a new BST node
t_btree *bstree_create_node(int item);

// Function to insert a new node into the BST
t_btree *bstree_insert(t_btree *root, int item, int (*cmpf)(int, int));

// Tree traversal functions
void bstree_apply_infix(t_btree *root, void (*applyf)(int));
void bstree_apply_prefix(t_btree *root, void (*applyf)(int));
void bstree_apply_postfix(t_btree *root, void (*applyf)(int));

// Function to destroy the binary search tree
void bstree_destroy(t_btree *root);

#endif  // BST_H
