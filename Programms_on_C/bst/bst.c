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
