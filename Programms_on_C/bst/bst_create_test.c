#include <stdio.h>
#include <stdlib.h>
#include "bst.h"

int main() {
    Node* node1 = bstree_create_node(10);
    if (node1 != NULL) {
        printf("Node 1 created with %d\n", node1->data);
        printf("Node 1 left child: %p\n", node1->left);
        printf("Node 1 right child: %p\n", node1->right);
    } else {
        printf("Failed to create node 1\n");
    }

    Node* node2 = bstree_create_node(25);
    if (node2 != NULL) {
        printf("Node 2 created with %d\n", node2->data);
         printf("Node 2 left child: %p\n", node2->left);
        printf("Node 2 right child: %p\n", node2->right);
    } else {
        printf("Failed to create node 2\n");
    }

     if (node1 != NULL) {
        free(node1); 
    }
    if (node2 != NULL) {
        free(node2); 
    }

    return 0;
}
