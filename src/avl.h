#ifndef AVL_TREE_H
#define AVL_TREE_H

typedef struct avl_node {
    double key;
    int count;
    struct avl_node *left;
    struct avl_node *right;
    int height;
} AVLTree;

int avl_height(AVLTree *avl);
AVLTree *avl_create_node(double key);
int avl_balance(AVLTree *node);
AVLTree *avl_right_rotate(AVLTree *y);
AVLTree *avl_left_rotate(AVLTree *x);
AVLTree *avl_insert(AVLTree *node, double key);
void avl_preorder(AVLTree *node);
void avl_inorder(AVLTree *node);
int avl_total(AVLTree *node);
int avl_more_than(AVLTree *node, double val);
void avl_destroy(AVLTree *node);

#endif //AVL_TREE_H
