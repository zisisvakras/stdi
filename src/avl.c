#include <stdio.h>
#include <stdlib.h>
#include "avl.h"

#define MAX(x, y) ((x) > (y) ? (x) : (y))

//Return the height of a node
int avl_height(AVLTree *avl){
    if(avl==NULL) return 0;
    return avl->height;
}

//A function to create a new node
//Height of node is initially 1, since the simple bst insertion, inserts the node as a leaf
AVLTree *avl_create_node(double key){
    AVLTree *node = calloc(1, sizeof(AVLTree));
    node->key = key;
    ++node->count;
    node->height = 1;
    return node;
}

//Return the balance of a current node
int avl_balance(AVLTree *node){
    if (node==NULL) return 0;
    return avl_height(node->left) - avl_height(node->right);
}

//Function to perform a right rotation on a node
AVLTree *avl_right_rotate(AVLTree *y){
    if (!y || !y->left) return y;
    AVLTree* x = y->left;
    AVLTree* t2 = x->right;
    x->right = y;
    y->left = t2;
    y->height = MAX(avl_height(y->left), avl_height(y->right)) + 1;
    x->height = MAX(avl_height(x->left), avl_height(x->right)) + 1;
    return x;
}

//Function to perform a left rotation on a node
AVLTree *avl_left_rotate(AVLTree *x){
    if (!x || !x->right) return x;
    AVLTree* y = x->right;
    AVLTree* t2 = y->left;
    y->left = x;
    x->right = t2;
    x->height = MAX(avl_height(x->left), avl_height(x->right)) + 1;
    y->height = MAX(avl_height(y->left), avl_height(y->right)) + 1;
    return y;
}

//Function to insert a node in an AVL tree
AVLTree *avl_insert(AVLTree *node, double key){
    /* Insert */
    if (!node) return avl_create_node(key);
    if (node->key > key)
        node->left = avl_insert(node->left, key);
    else if (node->key < key)
        node->right = avl_insert(node->right, key);
    else {
        ++node->count;
        return node;
    }

    int balance = avl_balance(node);
    /* Balance */
    node->height = MAX(avl_height(node->left), avl_height(node->right)) + 1;
    if (balance > 1 && node->left->key > key) { // l-l
        node = avl_right_rotate(node);
    }
    else if (balance > 1 && node->left->key < key) { // l-r
        node->left = avl_left_rotate(node->left);
        node = avl_right_rotate(node);
    }
    else if (balance < -1 && node->right->key < key) { // r-r
        node = avl_left_rotate(node);
    }
    else if (balance < -1 && node->right->key > key) {                                                  // r-l
        node->right = avl_right_rotate(node->right);
        node = avl_left_rotate(node);
    }
    return node;
}

void avl_preorder(AVLTree *node){
    if(node != NULL) {
        printf("%.2lf: %d\n",node->key, node->count);
        avl_preorder(node->left);
        avl_preorder(node->right);
    }
}

void avl_inorder(AVLTree *node){
    if(node != NULL) {
        avl_inorder(node->left);
        if (node->key == (int) node->key)
            printf("%3d: %d\n", (int)node->key, node->count);
        else
            printf("%.1lf: %d\n", node->key, node->count);
        avl_inorder(node->right);
    }
}

int avl_total(AVLTree *node) {
    if (node == NULL) return 0;
    int sum = avl_total(node->right);
    sum += avl_total(node->left);
    sum += node->count;
    return sum;
}

int avl_more_than(AVLTree *node, double val) {
    if (node == NULL) return 0;
    int sum = avl_more_than(node->right, val);
    sum += avl_more_than(node->left, val);
    if (node->key >= val) sum += node->count;
    return sum;
}

void avl_destroy(AVLTree *node){
    if (node != NULL) {
        avl_destroy(node->left);
        avl_destroy(node->right);
        free(node);
    }
}