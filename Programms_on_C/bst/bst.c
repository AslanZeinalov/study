#include <stdio.h>
#include <stdlib.h>
#include "bst.h"

Node* bstree_create_node(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        perror("Failed to allocate memory for new node");
        return NULL;
    }
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

InsertResult bstree_insert(t_btree *root, int item, int (*cmpf) (int, int)) {
    if (*root == NULL) {
        *root = bstree_create_node(item);
        return INSERTED_ROOT;
    }

    int comparisonResult = cmpf(item, (*root)->data);

    if (comparisonResult < 0) {
        if ((*root)->left == NULL) {
            (*root)->left = bstree_create_node(item);
            return INSERTED_LEFT;
        } else {
            InsertResult result = bstree_insert(&(*root)->left, item, cmpf);
            return result;
        }
    } else if (comparisonResult > 0) {
        if ((*root)->right == NULL) {
            (*root)->right = bstree_create_node(item);
            return INSERTED_RIGHT;
        } else {
            InsertResult result = bstree_insert(&(*root)->right, item, cmpf);
            return result;
        }
    } else {
        return DUPLICATE;
    }
}

void freeTree(t_btree root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

void bstree_apply_infix(t_btree root, void (*applyf) (int)) {
    if (root != NULL) {
        bstree_apply_infix(root->left, applyf);
        applyf(root->data);
        bstree_apply_infix(root->right, applyf);
    }
}

void bstree_apply_prefix(t_btree root, void (*applyf) (int)) {
    if (root != NULL) {
        applyf(root->data);
        bstree_apply_prefix(root->left, applyf);
        bstree_apply_prefix(root->right, applyf);
    }
}

void bstree_apply_postfix(t_btree root, void (*applyf) (int)) {
    if (root != NULL) {
        bstree_apply_postfix(root->right, applyf);
        applyf(root->data);
        bstree_apply_postfix(root->left, applyf);
    }
}

int intComparatorAsc(int a, int b) {
    return a - b;
}

int intComparatorDesc(int a, int b) {
    return b - a;
}
